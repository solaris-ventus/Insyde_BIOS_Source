//;******************************************************************************
//;* Copyright (c) 1983-2011, Insyde Software Corporation. All Rights Reserved.
//;*
//;* You may not reproduce, distribute, publish, display, perform, modify, adapt,
//;* transmit, broadcast, present, recite, release, license or otherwise exploit
//;* any part of this publication in any form, by any means, without the prior
//;* written permission of Insyde Software Corporation.
//;*
//;******************************************************************************
/*++

Copyright (c) 2004, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  BdsConsole.c

Abstract:

  BDS Lib functions which contain all the code to connect console device

--*/

#include "GenericBdsLib.h"
#include "EfiPrintLib.h"
#include "PostCode.h"

STATIC
BOOLEAN
IsNvNeed (
  IN CHAR16 *ConVarName
  )
/**
Routine Description:

  Check if we need to save the EFI variable with "ConVarName" as name
  as NV type
  If ConVarName is NULL, then ASSERT().

  @param ConVarName The name of the EFI variable.

  @retval TRUE    Set the EFI variable as NV type.
  @retval FALSE   EFI variable as NV type can be set NonNV.
**/
{
  CHAR16 *StringPtr;

  ASSERT (ConVarName != NULL);

  StringPtr = ConVarName;

  //
  // If the variable includes "Dev" at last, we consider
  // it does not support NV attribute.
  //
  while (*StringPtr != L'\0') {
    StringPtr++;
  }

  if (((INTN)((UINTN)StringPtr - (UINTN)ConVarName) / sizeof (CHAR16)) <= 3) {
    return TRUE;
  }

  if ((*(StringPtr - 3) == 'D') && (*(StringPtr - 2) == 'e') && (*(StringPtr - 1) == 'v')) {
    return FALSE;
  } else {
    return TRUE;
  }
}

STATIC
BOOLEAN
IsConVariable (
  IN  CHAR16                    *ConVarName
  )
{
  CHAR16           *ConVarNames[6] = { L"ConIn",    L"ConOut",    L"ErrOut",
                                       L"ConInDev", L"ConOutDev", L"ErrOutDev"
                                     };
  UINTN            Index;
  BOOLEAN          VariableFound;


  VariableFound = FALSE;
  if (ConVarName != NULL) {
    for (Index = 0; Index < 6; Index++) {
      if (EfiStrCmp (ConVarName, ConVarNames[Index]) == 0) {
       VariableFound = TRUE;
       break;
      }
    }
  }
  return VariableFound;
}

EFI_STATUS
BdsLibUpdateConsoleVariable (
  IN  CHAR16                    *ConVarName,
  IN  EFI_DEVICE_PATH_PROTOCOL  *CustomizedConDevicePath,
  IN  EFI_DEVICE_PATH_PROTOCOL  *ExclusiveDevicePath
  )
/*++

Routine Description:

  This function update console variable based on ConVarName, it can
  add or remove one specific console device path from the variable

Arguments:

  ConVarName   - Console related variable name, ConIn, ConOut, ErrOut.

  CustomizedConDevicePath - The console device path which will be added to
                            the console variable ConVarName, this parameter
                            can not be multi-instance.

  ExclusiveDevicePath     - The console device path which will be removed
                            from the console variable ConVarName, this
                            parameter can not be multi-instance.

Returns:

  EFI_UNSUPPORTED         - Add or remove the same device path.

  EFI_SUCCESS             - Success add or remove the device path from
                            the console variable.

--*/
{
  EFI_DEVICE_PATH_PROTOCOL  *VarConsole;
  UINTN                     DevicePathSize;
  EFI_DEVICE_PATH_PROTOCOL  *NewDevicePath;
  UINT32                    Attributes;
  BOOLEAN                   IsConsoleVariable;


  VarConsole      = NULL;
  DevicePathSize  = 0;
  NewDevicePath   = NULL;
  //
  // Notes: check the device path point, here should check
  // with compare memory
  //
  if (CustomizedConDevicePath == ExclusiveDevicePath) {
    return EFI_UNSUPPORTED;
  }

  IsConsoleVariable = IsConVariable (ConVarName);
  //
  // Delete the ExclusiveDevicePath from current default console
  //
  VarConsole = BdsLibGetVariableAndSize (
                ConVarName,
                IsConsoleVariable ? &gEfiGlobalVariableGuid : &gEfiGenericVariableGuid,
                &DevicePathSize
                );
  //
  // Initialize NewDevicePath
  //
  NewDevicePath  = VarConsole;

  //
  // If ExclusiveDevicePath is even the part of the instance in VarConsole, delete it.
  // In the end, NewDevicePath is the final device path.
  //
  if (ExclusiveDevicePath != NULL && VarConsole != NULL) {
      NewDevicePath = BdsLibDelPartMatchInstance (VarConsole, ExclusiveDevicePath);
  }
  //
  // Try to append customized device path to NewDevicePath.
  //
  if (CustomizedConDevicePath != NULL) {
    if (!BdsLibMatchDevicePaths (NewDevicePath, CustomizedConDevicePath)) {
      //
      // In the first check, the default console variable will be null,
      // just append current customized device path
      //
      NewDevicePath = EfiAppendDevicePathInstance (NewDevicePath, CustomizedConDevicePath);
    }
  }

  //
  // The attribute for ConInDev, ConOutDev and ErrOutDev does not include NV.
  //
  if (IsNvNeed (ConVarName)) {
    //
    // ConVarName has NV attribute.
    //
    Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE;
  } else {
    //
    // ConVarName does not have NV attribute.
    //
    Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS;
  }

  //
  // Finally, Update the variable of the default console by NewDevicePath
  //
  gRT->SetVariable (
        ConVarName,
        IsConsoleVariable ? &gEfiGlobalVariableGuid : &gEfiGenericVariableGuid,
        Attributes,
        EfiDevicePathSize (NewDevicePath),
        NewDevicePath
        );

  if (VarConsole == NewDevicePath) {
    if (VarConsole != NULL) {
      gBS->FreePool(VarConsole);
    }
  } else {
    if (VarConsole != NULL) {
      gBS->FreePool(VarConsole);
    }
    if (NewDevicePath != NULL) {
      gBS->FreePool(NewDevicePath);
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
BdsLibConnectConsoleVariable (
  IN  CHAR16                 *ConVarName
  )
/*++

Routine Description:

  Connect the console device base on the variable ConVarName, if
  device path of the ConVarName is multi-instance device path, if
  anyone of the instances is connected success, then this function
  will return success.

Arguments:

  ConVarName   - Console related variable name, ConIn, ConOut, ErrOut.

Returns:

  EFI_NOT_FOUND           - There is not any console devices connected success

  EFI_SUCCESS             - Success connect any one instance of the console
                            device path base on the variable ConVarName.

--*/
{
  EFI_STATUS                Status;
  EFI_DEVICE_PATH_PROTOCOL  *StartDevicePath;
  UINTN                     VariableSize;
  EFI_DEVICE_PATH_PROTOCOL  *Instance;
  EFI_DEVICE_PATH_PROTOCOL  *Next;
  EFI_DEVICE_PATH_PROTOCOL  *CopyOfDevicePath;
  UINTN                     Size;
  BOOLEAN                   DeviceExist;

  Status      = EFI_SUCCESS;
  DeviceExist = FALSE;

  //
  // Check if the console variable exist
  //
  StartDevicePath = BdsLibGetVariableAndSize (
                      ConVarName,
                      &gEfiGlobalVariableGuid,
                      &VariableSize
                      );
  if (StartDevicePath == NULL) {
    return EFI_UNSUPPORTED;
  }

  CopyOfDevicePath = EfiDuplicateDevicePath (StartDevicePath);
  do {
    //
    // Check every instance of the console variable
    //
    Instance  = EfiDevicePathInstance (&CopyOfDevicePath, &Size);
    Next      = Instance;
    while (!IsDevicePathEndType (Next)) {
      Next = NextDevicePathNode (Next);
    }

    SetDevicePathEndNode (Next);

    //
    // Connect the instance device path
    //
    Status = BdsLibConnectDevicePath (Instance);
    if (EFI_ERROR (Status)) {
      //
      // Delete the instance from the console varialbe
      //
      BdsLibUpdateConsoleVariable (ConVarName, NULL, Instance);
    } else {
      DeviceExist = TRUE;
    }

  } while (CopyOfDevicePath != NULL);

  gBS->FreePool (StartDevicePath);

  if (DeviceExist == FALSE) {
    return EFI_NOT_FOUND;
  }

  return EFI_SUCCESS;
}

VOID
BdsLibConnectAllConsoles (
  VOID
  )
/*++

Routine Description:

  This function will search every simpletxt devive in current system,
  and make every simpletxt device as pertantial console device.

Arguments:

  None

Returns:

  None

--*/
{
  EFI_STATUS                Status;
  UINTN                     Index;
  EFI_DEVICE_PATH_PROTOCOL  *ConDevicePath;
  UINTN                     HandleCount;
  EFI_HANDLE                *HandleBuffer;

  Index         = 0;
  HandleCount   = 0;
  HandleBuffer  = NULL;
  ConDevicePath = NULL;

  //
  // Update all the console varables
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiSimpleTextInProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  for (Index = 0; Index < HandleCount; Index++) {
    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiDevicePathProtocolGuid,
                    (VOID **) &ConDevicePath
                    );
    BdsLibUpdateConsoleVariable (L"ConIn", ConDevicePath, NULL);
  }

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiSimpleTextOutProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  for (Index = 0; Index < HandleCount; Index++) {
    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiDevicePathProtocolGuid,
                    (VOID **) &ConDevicePath
                    );
    BdsLibUpdateConsoleVariable (L"ConOut", ConDevicePath, NULL);
    BdsLibUpdateConsoleVariable (L"ErrOut", ConDevicePath, NULL);
  }
  //
  // Connect all console variables
  //
  BdsLibConnectAllDefaultConsoles ();

}

EFI_STATUS
BdsLibConnectAllDefaultConsoles (
  VOID
  )
/*++

Routine Description:

  This function will connect console device base on the console
  device variable ConIn, ConOut and ErrOut.

Arguments:

  None

Returns:

  EFI_SUCCESS      - At least one of the ConIn and ConOut device have
                     been connected success.

  EFI_STATUS       - Return the status of BdsLibConnectConsoleVariable ().

--*/
{
  EFI_STATUS                Status;
  EFI_DEVICE_PATH_PROTOCOL  *VarErrout;
  UINTN                     DevicePathSize;

#ifdef Q2LSERVICE_SUPPORT
  POSTCODE (BDS_CONNECT_CONSOLE_OUT); //PostCode = 0x17, Video device initial
  Status = BdsLibConnectConsoleVariable (L"ConOut");
  if (EFI_ERROR (Status)) {
    return Status;
  }

  POSTCODE (BDS_CONNECT_CONSOLE_IN);  //PostCode = 0x16, Keyboard Controller, Keyboard and Moust initial
  Status = BdsLibConnectConsoleVariable (L"ConIn");
  if (EFI_ERROR (Status)) {
    return Status;
  }
#else
  POSTCODE (BDS_CONNECT_CONSOLE_IN);  //PostCode = 0x16, Keyboard Controller, Keyboard and Moust initial
  //
  // Because possibly the platform is legacy free, in such case,
  // ConIn devices (Serial Port and PS2 Keyboard ) does not exist,
  // so we need not check the status.
  //
  BdsLibConnectConsoleVariable (L"ConIn");

  POSTCODE (BDS_CONNECT_CONSOLE_OUT); //PostCode = 0x17, Video device initial

  Status = BdsLibConnectConsoleVariable (L"ConOut");
  if (EFI_ERROR (Status)) {
    return Status;
  }
#endif
  //
  // Special treat the err out device, becaues the null
  // err out var is legal.
  //
  POSTCODE (BDS_CONNECT_STD_ERR); //PostCode = 0x18, Error report device initial

  VarErrout = BdsLibGetVariableAndSize (
                L"ErrOut",
                &gEfiGlobalVariableGuid,
                &DevicePathSize
                );
  if (VarErrout != NULL) {
    BdsLibConnectConsoleVariable (L"ErrOut");
  }

  return EFI_SUCCESS;

}
