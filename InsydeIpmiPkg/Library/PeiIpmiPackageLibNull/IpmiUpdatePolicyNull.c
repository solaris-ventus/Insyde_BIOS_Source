/** @file
 PEI IPMI Package library implement code - Update Policy.

;******************************************************************************
;* Copyright (c) 2013, Insyde Software Corporation. All Rights Reserved.
;*
;* You may not reproduce, distribute, publish, display, perform, modify, adapt,
;* transmit, broadcast, present, recite, release, license or otherwise exploit
;* any part of this publication in any form, by any means, without the prior
;* written permission of Insyde Software Corporation.
;*
;******************************************************************************

*/


#include <Library/PeiIpmiPackageLib.h>


/**
 Update IPMI policy according to the "Setup" variable SYSTEM_CONFIGURATION struct data.

 @param[in]         PeiServices         A pointer to EFI_PEI_SERVICES struct pointer.

 @retval EFI_SUCCESS                    Update Policy success.
 @return EFI_ERROR (Status)             Locate gEfiPeiReadOnlyVariable2PpiGuid or GetVariable error.
 @retval EFI_UNSUPPORTED                Platform does not implement this function when IPMI Config in Device Manager.
*/
EFI_STATUS
IpmiUpdatePolicy (
  IN CONST EFI_PEI_SERVICES             **PeiServices
  )
{
  return EFI_UNSUPPORTED;
}
