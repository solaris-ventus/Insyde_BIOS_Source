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

Copyright (c)  1999 - 2004 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:

  UsbLegacy.c

Abstract:

  Protocol used to get the number of USB devices for a given platform.

--*/

#include "Tiano.h"

#include EFI_PROTOCOL_DEFINITION (UsbLegacy)

EFI_GUID gEfiUsbLegacyProtocolGuid = EFI_USB_LEGACY_PROTOCOL_GUID;

EFI_GUID_STRING (&gEfiUsbLegacyProtocolGuid, "EFI USB Legacy Protocol", "EFI USB Legacy Protocol");
