//;******************************************************************************
//;* Copyright (c) 1983-2011, Insyde Software Corporation. All Rights Reserved.
//;*
//;* You may not reproduce, distribute, publish, display, perform, modify, adapt,
//;* transmit, broadcast, present, recite, release, license or otherwise exploit
//;* any part of this publication in any form, by any means, without the prior
//;* written permission of Insyde Software Corporation.
//;*
//;******************************************************************************
//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/*++

 Copyright (c) 2005, Intel Corporation. All rights reserved
 This software and associated documentation (if any) is furnished
 under a license and may only be used or copied in accordance
 with the terms of the license. Except as permitted by such
 license, no part of this software or documentation may be
 reproduced, stored in a retrieval system, or transmitted in any
 form or by any means without the express written consent of
 Intel Corporation.

 Module Name:

    LightIsaIo.h

 Abstract:

    EFI_LIGHT_ISA_IO_PROTOCOL

 Revision History

--*/

#ifndef _EFI_LIGHT_ISA_IO_H
#define _EFI_LIGHT_ISA_IO_H

#include EFI_PROTOCOL_DEFINITION(IsaAcpi)

//
// Global ID for the Light ISA I/O Protocol
//

#define EFI_LIGHT_ISA_IO_PROTOCOL_GUID \
  { 0x7cc7ed80, 0x9a68, 0x4781, 0x80, 0xe4, 0xda, 0x16, 0x99, 0x10, 0x5a, 0xfe }

EFI_FORWARD_DECLARATION (EFI_LIGHT_ISA_IO_PROTOCOL);

//
// Prototypes for the Light ISA I/O Protocol
//
typedef enum {
  EfiIsaIoWidthUint8,
  EfiIsaIoWidthUint16,
  EfiIsaIoWidthUint32,
  EfiIsaIoWidthReserved,
  EfiIsaIoWidthFifoUint8,
  EfiIsaIoWidthFifoUint16,
  EfiIsaIoWidthFifoUint32,
  EfiIsaIoWidthFifoReserved,
  EfiIsaIoWidthFillUint8,
  EfiIsaIoWidthFillUint16,
  EfiIsaIoWidthFillUint32,
  EfiIsaIoWidthFillReserved,
  EfiIsaIoWidthMaximum
} EFI_ISA_IO_PROTOCOL_WIDTH;

//
// Attributes for common buffer allocations
//
#define EFI_ISA_IO_ATTRIBUTE_MEMORY_WRITE_COMBINE  0x080    // Map a memory range so write are combined
#define EFI_ISA_IO_ATTRIBUTE_MEMORY_CACHED         0x800    // Map a memory range so all r/w accesses are cached
#define EFI_ISA_IO_ATTRIBUTE_MEMORY_DISABLE        0x1000   // Disable a memory range

//
// Channel attribute for DMA operations
//
#define EFI_ISA_IO_SLAVE_DMA_ATTRIBUTE_SPEED_COMPATIBLE  0x001
#define EFI_ISA_IO_SLAVE_DMA_ATTRIBUTE_SPEED_A           0x002
#define EFI_ISA_IO_SLAVE_DMA_ATTRIBUTE_SPEED_B           0x004
#define EFI_ISA_IO_SLAVE_DMA_ATTRIBUTE_SPEED_C           0x008
#define EFI_ISA_IO_SLAVE_DMA_ATTRIBUTE_WIDTH_8           0x010
#define EFI_ISA_IO_SLAVE_DMA_ATTRIBUTE_WIDTH_16          0x020
#define EFI_ISA_IO_SLAVE_DMA_ATTRIBUTE_SINGLE_MODE       0x040
#define EFI_ISA_IO_SLAVE_DMA_ATTRIBUTE_DEMAND_MODE       0x080
#define EFI_ISA_IO_SLAVE_DMA_ATTRIBUTE_AUTO_INITIALIZE   0x100

typedef enum {
  EfiIsaIoOperationBusMasterRead,
  EfiIsaIoOperationBusMasterWrite,
  EfiIsaIoOperationBusMasterCommonBuffer,
  EfiIsaIoOperationSlaveRead,
  EfiIsaIoOperationSlaveWrite,
  EfiIsaIoOperationMaximum
} EFI_ISA_IO_PROTOCOL_OPERATION;

typedef
EFI_STATUS
(EFIAPI *EFI_LIGHT_ISA_IO_PROTOCOL_IO_MEM) (
  IN     EFI_LIGHT_ISA_IO_PROTOCOL  *This,
  IN     EFI_ISA_IO_PROTOCOL_WIDTH    Width,
  IN     UINT32                       Offset,
  IN     UINTN                        Count,
  IN OUT VOID                         *Buffer
  )
/*++

Routine Description:

  Performs an ISA I/O Read/Write Cycle
  EFI_LIGHT_ISA_IO_PROTOCOL doesn't verfiy access for I/O operation.

Arguments:

  This                  - A pointer to the EFI_ISA_IO_PROTOCOL or EFI_LIGHT_ISA_IO_PROTOCOL instance.
  Width                 - Signifies the width of the I/O operation.
  Offset                - The offset in ISA I/O space to start the I/O operation.
  Count                 - The number of I/O operations to perform.
  Buffer                - The source/destination buffer

Returns:

  EFI_SUCCESS           - The data was read from or written to the device sucessfully.
  EFI_UNSUPPORTED       - The Offset is not valid for this device.
  EFI_INVALID_PARAMETER - Width or Count, or both, were invalid.
  EFI_OUT_OF_RESOURCES  - The request could not be completed due to a lack of resources.

--*/
;

typedef struct {
  EFI_LIGHT_ISA_IO_PROTOCOL_IO_MEM  Read;
  EFI_LIGHT_ISA_IO_PROTOCOL_IO_MEM  Write;
} EFI_LIGHT_ISA_IO_PROTOCOL_ACCESS;


typedef
EFI_STATUS
(EFIAPI *EFI_LIGHT_ISA_IO_PROTOCOL_MAP) (
  IN     EFI_LIGHT_ISA_IO_PROTOCOL    *This,
  IN     EFI_ISA_IO_PROTOCOL_OPERATION  Operation,
  IN     UINT8                          ChannelNumber      OPTIONAL,
  IN     UINT32                         ChannelAttributes,
  IN     VOID                           *HostAddress,
  IN OUT UINTN                          *NumberOfBytes,
  OUT    EFI_PHYSICAL_ADDRESS           *DeviceAddress,
  OUT    VOID                           **Mapping
  )
/*++

Routine Description:

  Maps a memory region for DMA, EFI_LIGHT_ISA_IO_PROTOCOL only supports
  Slave read/write operation to save code size.

Arguments:

  This                  - A pointer to the EFI_LIGHT_ISA_IO_PROTOCOL instance.
  Operation             - Indicates the type of DMA (slave or bus master), and if
                          the DMA operation is going to read or write to system memory.
  ChannelNumber         - The slave channel number to use for this DMA operation.
                          If Operation and ChannelAttributes shows that this device
                          performs bus mastering DMA, then this field is ignored.
                          The legal range for this field is 0..7.
  ChannelAttributes     - The attributes of the DMA channel to use for this DMA operation
  HostAddress           - The system memory address to map to the device.
  NumberOfBytes         - On input the number of bytes to map.  On output the number
                          of bytes that were mapped.
  DeviceAddress         - The resulting map address for the bus master device to use
                          to access the hosts HostAddress.
  Mapping               - A resulting value to pass to EFI_ISA_IO.Unmap().

Returns:

  EFI_SUCCESS           - The range was mapped for the returned NumberOfBytes.
  EFI_INVALID_PARAMETER - The Operation or HostAddress is undefined.
  EFI_UNSUPPORTED       - The HostAddress can not be mapped as a common buffer.
  EFI_DEVICE_ERROR      - The system hardware could not map the requested address.
  EFI_OUT_OF_RESOURCES  - The memory pages could not be allocated.

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_LIGHT_ISA_IO_PROTOCOL_UNMAP) (
  IN EFI_LIGHT_ISA_IO_PROTOCOL  *This,
  IN  VOID                         *Mapping
  )
/*++

Routine Description:

  Unmaps a memory region for DMA

Arguments:

  This             - A pointer to the EFI_ISA_IO_PROTOCOL or EFI_LIGHT_ISA_IO_PROTOCOL instance.
  Mapping          - The mapping value returned from EFI_ISA_IO.Map().

Returns:

  EFI_SUCCESS      - The range was unmapped.
  EFI_DEVICE_ERROR - The data was not committed to the target system memory.

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_LIGHT_ISA_IO_PROTOCOL_FLUSH) (
  IN EFI_LIGHT_ISA_IO_PROTOCOL  *This
  )
/*++

Routine Description:

  Flushes a DMA buffer

Arguments:

  This             - A pointer to the EFI_ISA_IO_PROTOCOL or EFI_LIGHT_ISA_IO_PROTOCOL instance.

Returns:

  EFI_SUCCESS      - The buffers were flushed.
  EFI_DEVICE_ERROR - The buffers were not flushed due to a hardware error.

--*/
;

//
// Interface structure for the Light ISA I/O Protocol
//
typedef struct _EFI_LIGHT_ISA_IO_PROTOCOL {
  EFI_LIGHT_ISA_IO_PROTOCOL_ACCESS     Io;
  EFI_LIGHT_ISA_IO_PROTOCOL_MAP        Map;
  EFI_LIGHT_ISA_IO_PROTOCOL_UNMAP      Unmap;
  EFI_LIGHT_ISA_IO_PROTOCOL_FLUSH      Flush;
  EFI_ISA_ACPI_RESOURCE_LIST           *ResourceList;
  UINT32                               RomSize;
  VOID                                 *RomImage;
} EFI_LIGHT_ISA_IO_PROTOCOL;

extern EFI_GUID gEfiLightIsaIoProtocolGuid;

#endif
