/** @file
  SmmUsbDispatch2 On SmmUsbDispatch Thunk
;******************************************************************************
;* Copyright (c) 2012, Insyde Software Corp. All Rights Reserved.
;*
;* You may not reproduce, distribute, publish, display, perform, modify, adapt,
;* transmit, broadcast, present, recite, release, license or otherwise exploit
;* any part of this publication in any form, by any means, without the prior
;* written permission of Insyde Software Corporation.
;*
;******************************************************************************
*/

#include <PiDxe.h>
#include <FrameworkSmm.h>

#include <Protocol/SmmUsbDispatch2.h>
#include <Protocol/SmmUsbDispatch.h>

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>

typedef struct {
  LIST_ENTRY                     Link;
  EFI_HANDLE                     DispatchHandle;
  UINTN                          DispatchFunction;
} EFI_SMM_USB_DISPATCH2_THUNK_CONTEXT;

/**
  Register a child SMI source dispatch function for the specified software SMI.

  This service registers a function (DispatchFunction) which will be called when the software 
  SMI source specified by RegisterContext->SwSmiCpuIndex is detected. On return, 
  DispatchHandle contains a unique handle which may be used later to unregister the function 
  using UnRegister().

  @param[in]  This                  Pointer to the EFI_SMM_USB_DISPATCH2_PROTOCOL instance.
  @param[in]  DispatchFunction      Function to register for handler when the specified software 
                                    SMI is generated. 
  @param[in, out]  RegisterContext  Pointer to the dispatch function's context.
                                    The caller fills this context in before calling
                                    the register function to indicate to the register
                                    function which Software SMI input value the
                                    dispatch function should be invoked for.
  @param[out] DispatchHandle        Handle generated by the dispatcher to track the
                                    function instance.

  @retval EFI_SUCCESS            The dispatch function has been successfully
                                 registered and the SMI source has been enabled.
  @retval EFI_DEVICE_ERROR       The SW driver was unable to enable the SMI source.
  @retval EFI_INVALID_PARAMETER  RegisterContext is invalid. The SW SMI input value
                                 is not within valid range.
  @retval EFI_OUT_OF_RESOURCES   There is not enough memory (system or SMM) to manage this
                                 child.
  @retval EFI_OUT_OF_RESOURCES   A unique software SMI value could not be assigned
                                 for this dispatch.
**/
EFI_STATUS
EFIAPI
SmmUsbDispatch2Register (
  IN  CONST EFI_SMM_USB_DISPATCH2_PROTOCOL *This,
  IN        EFI_SMM_HANDLER_ENTRY_POINT2   DispatchFunction,
  IN  CONST EFI_SMM_USB_REGISTER_CONTEXT   *RegisterContext,
  OUT       EFI_HANDLE                     *DispatchHandle
  );

/**
  Unregister a child SMI source dispatch function for the specified software SMI.

  This service removes the handler associated with DispatchHandle so that it will no longer be 
  called in response to a software SMI.

  @param[in] This                Pointer to the EFI_SMM_USB_DISPATCH2_PROTOCOL instance.
  @param[in] DispatchHandle      Handle of dispatch function to deregister.

  @retval EFI_SUCCESS            The dispatch function has been successfully unregistered.
  @retval EFI_INVALID_PARAMETER  The DispatchHandle was not valid.
**/
EFI_STATUS
EFIAPI
SmmUsbDispatch2UnRegister (
  IN CONST EFI_SMM_USB_DISPATCH2_PROTOCOL *This,
  IN       EFI_HANDLE                     DispatchHandle
  );

EFI_SMM_USB_DISPATCH2_PROTOCOL gSmmUsbDispatch2 = {
  SmmUsbDispatch2Register,
  SmmUsbDispatch2UnRegister
};

EFI_SMM_USB_DISPATCH_PROTOCOL *mSmmUsbDispatch;
LIST_ENTRY                    mSmmUsbDispatch2ThunkQueue = INITIALIZE_LIST_HEAD_VARIABLE (mSmmUsbDispatch2ThunkQueue);

/**
  This function find SmmUsbDispatch2Context by DispatchHandle.

  @param DispatchHandle The DispatchHandle to indentify the SmmUsbDispatch2Thunk context

  @return SmmUsbDispatch2Thunk context
**/
EFI_SMM_USB_DISPATCH2_THUNK_CONTEXT *
FindSmmUsbDispatch2ContextByDispatchHandle (
  IN EFI_HANDLE   DispatchHandle
  )
{
  LIST_ENTRY                            *Link;
  EFI_SMM_USB_DISPATCH2_THUNK_CONTEXT   *ThunkContext;

  for (Link = mSmmUsbDispatch2ThunkQueue.ForwardLink;
       Link != &mSmmUsbDispatch2ThunkQueue;
       Link = Link->ForwardLink) {
    ThunkContext = BASE_CR (
                     Link,
                     EFI_SMM_USB_DISPATCH2_THUNK_CONTEXT,
                     Link
                     );
    if (ThunkContext->DispatchHandle == DispatchHandle) {
      return ThunkContext;
    }
  }
  return NULL;
}

/**
  Framework dispatch function for a Software SMI handler.

  @param  DispatchHandle        The handle of this dispatch function.
  @param  DispatchContext       The pointer to the dispatch function's context.
                                The SwSmiInputValue field is filled in
                                by the software dispatch driver prior to
                                invoking this dispatch function.
                                The dispatch function will only be called
                                for input values for which it is registered.

  @return None

**/
VOID
EFIAPI
FrameworkDispatchFunction (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  EFI_SMM_USB_DISPATCH_CONTEXT  *DispatchContext
  )
{
  EFI_SMM_USB_DISPATCH2_THUNK_CONTEXT   *ThunkContext;
  EFI_SMM_HANDLER_ENTRY_POINT2          DispatchFunction;
  //
  // Search context
  //
  ThunkContext = FindSmmUsbDispatch2ContextByDispatchHandle (DispatchHandle);
  ASSERT (ThunkContext != NULL);
  if (ThunkContext == NULL) {
    return ;
  }
  //
  // Dispatch
  //
  DispatchFunction = (EFI_SMM_HANDLER_ENTRY_POINT2)ThunkContext->DispatchFunction;
  DispatchFunction (
    DispatchHandle,
    DispatchContext,
    NULL,
    NULL
    );
  return ;
}

/**
  Register a child SMI source dispatch function for the specified software SMI.

  This service registers a function (DispatchFunction) which will be called when the software 
  SMI source specified by RegisterContext->SwSmiCpuIndex is detected. On return, 
  DispatchHandle contains a unique handle which may be used later to unregister the function 
  using UnRegister().

  @param[in]  This                  Pointer to the EFI_SMM_USB_DISPATCH2_PROTOCOL instance.
  @param[in]  DispatchFunction      Function to register for handler when the specified software 
                                    SMI is generated. 
  @param[in, out]  RegisterContext  Pointer to the dispatch function's context.
                                    The caller fills this context in before calling
                                    the register function to indicate to the register
                                    function which Software SMI input value the
                                    dispatch function should be invoked for.
  @param[out] DispatchHandle        Handle generated by the dispatcher to track the
                                    function instance.

  @retval EFI_SUCCESS            The dispatch function has been successfully
                                 registered and the SMI source has been enabled.
  @retval EFI_DEVICE_ERROR       The SW driver was unable to enable the SMI source.
  @retval EFI_INVALID_PARAMETER  RegisterContext is invalid. The SW SMI input value
                                 is not within valid range.
  @retval EFI_OUT_OF_RESOURCES   There is not enough memory (system or SMM) to manage this
                                 child.
  @retval EFI_OUT_OF_RESOURCES   A unique software SMI value could not be assigned
                                 for this dispatch.
**/
EFI_STATUS
EFIAPI
SmmUsbDispatch2Register (
  IN  CONST EFI_SMM_USB_DISPATCH2_PROTOCOL *This,
  IN        EFI_SMM_HANDLER_ENTRY_POINT2   DispatchFunction,
  IN  CONST EFI_SMM_USB_REGISTER_CONTEXT   *RegisterContext,
  OUT       EFI_HANDLE                     *DispatchHandle
  )
{
  EFI_SMM_USB_DISPATCH2_THUNK_CONTEXT   *ThunkContext;
  EFI_SMM_USB_DISPATCH_CONTEXT          DispatchContext;
  EFI_STATUS                            Status;

  DispatchContext.Type   = RegisterContext->Type;
  DispatchContext.Device = RegisterContext->Device;
  Status = mSmmUsbDispatch->Register (
                              mSmmUsbDispatch,
                              FrameworkDispatchFunction,
                              &DispatchContext,
                              DispatchHandle
                              );
  if (!EFI_ERROR (Status)) {
    //
    // Register
    //
    Status = gSmst->SmmAllocatePool (
                      EfiRuntimeServicesData,
                      sizeof(*ThunkContext),
                      (VOID **)&ThunkContext
                      );
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      mSmmUsbDispatch->UnRegister (mSmmUsbDispatch, *DispatchHandle);
      return EFI_OUT_OF_RESOURCES;
    }

    ThunkContext->DispatchFunction = (UINTN)DispatchFunction;
    ThunkContext->DispatchHandle   = *DispatchHandle;
    InsertTailList (&mSmmUsbDispatch2ThunkQueue, &ThunkContext->Link);
  }

  return Status;
}

/**
  Unregister a child SMI source dispatch function for the specified software SMI.

  This service removes the handler associated with DispatchHandle so that it will no longer be 
  called in response to a software SMI.

  @param[in] This                Pointer to the EFI_SMM_USB_DISPATCH2_PROTOCOL instance.
  @param[in] DispatchHandle      Handle of dispatch function to deregister.

  @retval EFI_SUCCESS            The dispatch function has been successfully unregistered.
  @retval EFI_INVALID_PARAMETER  The DispatchHandle was not valid.
**/
EFI_STATUS
EFIAPI
SmmUsbDispatch2UnRegister (
  IN CONST EFI_SMM_USB_DISPATCH2_PROTOCOL *This,
  IN       EFI_HANDLE                     DispatchHandle
  )
{
  EFI_SMM_USB_DISPATCH2_THUNK_CONTEXT   *ThunkContext;
  EFI_STATUS                            Status;

  Status = mSmmUsbDispatch->UnRegister (mSmmUsbDispatch, DispatchHandle);
  if (!EFI_ERROR (Status)) {
    //
    // Unregister
    //
    ThunkContext = FindSmmUsbDispatch2ContextByDispatchHandle (DispatchHandle);
    ASSERT (ThunkContext != NULL);
    if (ThunkContext != NULL) {
      RemoveEntryList (&ThunkContext->Link);
      gSmst->SmmFreePool (ThunkContext);
    }
  }

  return Status;
}

/**
  Entry Point for this thunk driver.

  @param[in] ImageHandle  Image handle of this driver.
  @param[in] SystemTable  A Pointer to the EFI System Table.

  @retval EFI_SUCCESS  The entry point is executed successfully.
  @retval other        Some error occurred when executing this entry point.
**/
EFI_STATUS
EFIAPI
SmmUsbDispatch2ThunkMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS               Status;
  //
  // Locate Framework SMM SwDispatch Protocol
  //
  Status = gBS->LocateProtocol (&gEfiSmmUsbDispatchProtocolGuid, NULL, (VOID **)&mSmmUsbDispatch);
  ASSERT_EFI_ERROR (Status);
  //
  // Publish PI SMM SwDispatch2 Protocol
  //
  ImageHandle = NULL;
  Status = gSmst->SmmInstallProtocolInterface (
                    &ImageHandle,
                    &gEfiSmmUsbDispatch2ProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &gSmmUsbDispatch2
                    );
  ASSERT_EFI_ERROR (Status);
  return Status;
}

