//;******************************************************************************
//;* Copyright (c) 1983-2011, Insyde Software Corporation. All Rights Reserved.
//;*
//;* You may not reproduce, distribute, publish, display, perform, modify, adapt,
//;* transmit, broadcast, present, recite, release, license or otherwise exploit
//;* any part of this publication in any form, by any means, without the prior
//;* written permission of Insyde Software Corporation.
//;*
//;******************************************************************************
//; 
//; Module Name:
//; 
//;   DebugIo.c
//; 

#include "Tiano.h"
#include "Pei.h"

#include EFI_PPI_DEFINITION (DebugIo)

EFI_GUID  gPeiDebugIoPpiGuid = PEI_DEBUG_IO_PPI_GUID;
EFI_GUID_STRING (&gPeiDebugIoPpiGuid, "Debug IO Protocol", "PEI 1.0 Debug IO Protocol");
