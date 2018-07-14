/*******************************************************************************
 *  INTEL CONFIDENTIAL
 *  Copyright 2007 Intel Corporation All Rights Reserved.
 *
 *  The source code contained or described herein and all documents related to
 *  the source code ("Material") are owned by Intel Corporation or its suppliers
 *  or licensors. Title to the Material remains with Intel Corporation or its
 *  suppliers and licensors. The Material may contain trade secrets and
 *  proprietary and confidential information of Intel Corporation and its
 *  suppliers and licensors, and is protected by worldwide copyright and trade
 *  secret laws and treaty provisions. No part of the Material may be used,
 *  copied, reproduced, modified, published, uploaded, posted, transmitted,
 *  distributed, or disclosed in any way without Intel's prior express written
 *  permission. 
 *  
 *  No license under any patent, copyright, trade secret or other intellectual
 *  property right is granted to or conferred upon you by disclosure or delivery
 *  of the Materials, either expressly, by implication, inducement, estoppel or
 *  otherwise. Any license under such intellectual property rights must be
 *  express and approved by Intel in writing.
 *
 *  Unless otherwise agreed by Intel in writing, you may not remove or alter
 *  this notice or any other notice embedded in Materials by Intel or Intel's
 *  suppliers or licensors in any way.
 ******************************************************************************/

/******************************************************************************
 *
 * Description:
 *   This file contains the prototype for a functions to map and unmap files
 *   onto/from memory.
 *
 *   NOTE - this is not bulletproof code, but simply a way to expose file
 *   mapping across platforms.  If you pass bad parameters to the functions,
 *   bad things could happen.
 *
 ******************************************************************************/

#ifndef MAPFILE_H_INCLUDED
#define MAPFILE_H_INCLUDED

#include <stdlib.h>
#include "rfid_types.h"

typedef void * MEMMAP_HANDLE;

#define INVALID_MEMMAP_HANDLE NULL

/******************************************************************************
 * Name: MapFileOntoMemory
 *
 * Description:
 *   Maps a file onto memory.
 *
 * Parameters:
 *   pFileName - the name of the file that will be mapped onto memory
 *
 * Returns:
 *   Returns INVALID_MEMMAP_HANDLE if the mapping failed.  Otherwise, returns
 *   the handle the file mapping.
 ******************************************************************************/
MEMMAP_HANDLE MapFileOntoMemory(
    const char* pFileName
    );

/******************************************************************************
 * Name: GetFileMappingStartAddress
 *
 * Description:
 *   Returns the starting address for the file mapping.
 *
 * Parameters:
 *   handle - the handle to the memory mapping for which the starting address is
 *     required.  The handle is returned from a successfull call to
 *     MapFileOntoMemory.
 *
 * Returns:
 *   Returns NULL if the handle is not valid.  Otherwise returns the starting
 *   address for the file mapping.
 ******************************************************************************/
void* GetFileMappingStartAddress(
    MEMMAP_HANDLE   handle
    );

/******************************************************************************
 * Name: GetFileMappingSize
 *
 * Description:
 *   Returns the size, in bytes, for the file mapping.
 *
 * Parameters:
 *   handle - the handle to the memory mapping for which the size is
 *     required.  The handle is returned from a successfull call to
 *     MapFileOntoMemory.
 *
 * Returns:
 *   Returns the size of the file mapping.
 ******************************************************************************/
INT32U GetFileMappingSize(
    MEMMAP_HANDLE   handle
    );

/******************************************************************************
 * Name: UnmapFileFromMemory
 *
 * Description:
 *   Unmaps a file from memory.
 *
 * Parameters:
 *   handle - the handle to the memory mapping to unmap.  The handle is returned
 *     from a successfull call to MapFileOntoMemory.
 *
 * Returns:
 *   Returns INVALID_MEMMAP_HANDLE if the mapping failed.  Otherwise, returns
 *   the handle the memory mapping.
 ******************************************************************************/
void UnmapFileFromMemory(
    MEMMAP_HANDLE   handle
    );

#endif /* #ifndef MAPFILE_H_INCLUDED */
