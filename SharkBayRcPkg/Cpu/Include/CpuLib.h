//;******************************************************************************
//;* Copyright (c) 1983-2012, Insyde Software Corp. All Rights Reserved.
//;*
//;* You may not reproduce, distribute, publish, display, perform, modify, adapt,
//;* transmit, broadcast, present, recite, release, license or otherwise exploit
//;* any part of this publication in any form, by any means, without the prior
//;* written permission of Insyde Software Corporation.
//;*
//;******************************************************************************
/*

Module Name:

  CpuLib.c
  
Abstract:
  
  Provide cpu version extract considering extended family & model ID.
  
--*/

#ifndef _CPU_LIB_H
#define _CPU_LIB_H
//[-start-120419-IB03530357-remove]//
//#include "Tiano.h"
//[-end-120419-IB03530357-remove]//
#define EFI_CPUID_VERSION_INFO                0x1
#define EFI_CPUID_THERMAL_AND_POWER_INFO      0x6
#define EFI_CPUID_EXT_MODEL                   0x000F0000
#define EFI_CPUID_FAMILY                      0x0F00
#define EFI_CPUID_MODEL                       0x00F0
#define CPUID_FAMILY_MODEL_NEHALEM            0x206A0    // A1:206A0 B0:206A1 the lowest 4 bit will be masked
#define CPUID_NEHALEM_FAMILY_MODEL            0x0FFF0FF0
#define IED_SIZE                              0x400000
typedef enum {
  ProcessorNehalem,
  ProcessorSandyBridgeA1,
  ProcessorSandyBridgeB0,
  ProcessorSandyBridgeB1,
  ProcessorSandyBridgeB2,
  ProcessorSandyBridgeC0,
} CHECK_PROCESSOR_TYPE;

typedef struct {
   UINT32  RegEax;
   UINT32  RegEbx;
   UINT32  RegEcx;
   UINT32  RegEdx;
} EFI_NEHALEM_CPUID_REGISTER;

#define MTRR_PHYS_BASE_7      0x020E
#define MTRR_PHYS_MASK_7      0x020F

UINT64
NehalemReadMsr (
  IN   UINT32  Index
  );

VOID
NehalemWriteMsr (
  IN   UINT32  Index,  
  IN   UINT64  Value   
  );

VOID
NehalemCpuid (
  IN  UINT32                 RegisterInEax,
  OUT EFI_NEHALEM_CPUID_REGISTER     *Regs
  );

BOOLEAN
CheckProcessor (
  IN  CHECK_PROCESSOR_TYPE    CheckType,
  OUT UINT32                  *FamilyModel,
  OUT UINT8                   *Stepping
  );

BOOLEAN
IsNehalem (
  UINT8 *Stepping,
  UINT32 *FamilyModel  
  );


VOID
NehalemCpuVersion (
  IN  OUT UINT16  *FamilyId,    OPTIONAL
  IN  OUT UINT8   *Model,       OPTIONAL
  IN  OUT UINT8   *SteppingId,  OPTIONAL
  IN  OUT UINT8   *Processor    OPTIONAL
  );
EFI_STATUS
 GetTheadCoreCount(   
   IN OUT   UINT8   *ThreadCount, OPTIONAL
   IN OUT   UINT8   *CoreCount    OPTIONAL    
  );
 BOOLEAN
 IsSupportHT(   
   VOID
 );
 UINT8
 GetThreadcountMax(   
   VOID
 );

 UINT32
 GetNumberOfMtrr(   
   VOID
 );

 UINT64
 GetValidMtrrAddress(   
   VOID
 );
 
 UINT64
 EFIAPI
 GetNextPowerOfTwo64 (
  IN      UINT64                    Operand
 );
  
 UINT64
 EFIAPI
 GetOnePowerOfTwo64 (
  IN      UINT64                    Operand
 );
VOID
NehalemCpuidFunB (
  IN  UINT32                 Index,
  OUT EFI_NEHALEM_CPUID_REGISTER     *Regs
  );

#endif

