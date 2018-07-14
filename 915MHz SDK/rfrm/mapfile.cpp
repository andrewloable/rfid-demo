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
 *   This file contains the Windows implementation of the functions to map and
 *   unmap files onto/from memory.
 *
 ******************************************************************************/
#include "StdAfx.h"

#include <assert.h>
#include "mapfile.h"

typedef struct
{
    HANDLE  fileHandle;
    HANDLE  mappingHandle;
    LPVOID  startAddress;
    INT32U  size;
} MEMMAP_CONTROL;

/******************************************************************************
 * Name: MapFileOntoMemory
 *
 * Description:
 *   Maps a file onto memory.
 ******************************************************************************/
MEMMAP_HANDLE MapFileOntoMemory(
    const char* pFileName
    )
{
	wchar_t         wpath[MAX_PATH + 1];
	MEMMAP_CONTROL* pControl;

	assert(NULL != pFileName);

	/* Create the structure to keep information about the mapping             */
	pControl = (MEMMAP_CONTROL *) malloc(sizeof(MEMMAP_CONTROL));
	if (NULL == pControl)
	{
		pControl = INVALID_MEMMAP_HANDLE;
		goto EXIT;
	}

	/* Since CE is strictly Unicode, we'll use it for both CE and XP.  So,
	let's convert the file name                                            */
	mbstowcs(wpath, pFileName, MAX_PATH);
	wpath[MAX_PATH] = L'\0';

    /* To map a file onto memory in Win32, the following steps are taken:
       1.  Open the file.
       2.  Create a file mapping using the file handle.
       3.  Map a view of the file using the handle from step 2.               */
    pControl->fileHandle =
#if _WIN32_WCE
        CreateFileForMapping
#else
        CreateFile
#endif
        (
        wpath,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (INVALID_HANDLE_VALUE == pControl->fileHandle)
    {
        goto FREE_MEMORY;
    }

    pControl->size = GetFileSize(pControl->fileHandle, NULL);
    if (INVALID_FILE_SIZE == pControl->size)
    {
        goto CLOSE_FILE;
    }

    pControl->mappingHandle = CreateFileMapping(
        pControl->fileHandle,
        NULL,
        PAGE_READONLY,
        0, 
        pControl->size, 
        NULL
    );
    if (NULL == pControl->mappingHandle)
    {
        goto CLOSE_FILE;
    }

    pControl->startAddress = MapViewOfFile( 
        pControl->mappingHandle,
        FILE_MAP_READ, 
        0,
        0,
        0
        );
    if (NULL == pControl->startAddress)
    {
        goto CLOSE_MAPPING;
    }

    goto EXIT;

CLOSE_MAPPING:
    CloseHandle(pControl->mappingHandle);

CLOSE_FILE:
    CloseHandle(pControl->fileHandle);

FREE_MEMORY:
    free(pControl);
    pControl = INVALID_MEMMAP_HANDLE;

EXIT:
    return (MEMMAP_HANDLE) pControl;
} /* MapFileOntoMemory */

/******************************************************************************
 * Name: GetFileMappingStartAddress
 *
 * Description:
 *   Returns the starting address for the file mapping.
 ******************************************************************************/
void* GetFileMappingStartAddress(
    MEMMAP_HANDLE   handle
    )
{
    assert(INVALID_MEMMAP_HANDLE != handle);

    return ((MEMMAP_CONTROL *) handle)->startAddress;
} /* GetFileMappingStartAddress */

/******************************************************************************
 * Name: GetFileMappingSize
 *
 * Description:
 *   Returns the size, in bytes, for the file mapping.
 ******************************************************************************/
INT32U GetFileMappingSize(
    MEMMAP_HANDLE   handle
    )
{
    assert(INVALID_MEMMAP_HANDLE != handle);

    return ((MEMMAP_CONTROL *) handle)->size;
} /* GetFileMappingSize */

/******************************************************************************
 * Name: UnmapFileFromMemory
 *
 * Description:
 *   Unmaps a file from memory.
 ******************************************************************************/
void UnmapFileFromMemory(
    MEMMAP_HANDLE   handle
    )
{
    MEMMAP_CONTROL* pControl = (MEMMAP_CONTROL *) handle;

    assert(INVALID_MEMMAP_HANDLE != handle);

    /* Unmap the file and close all handles                                   */
    UnmapViewOfFile(pControl->startAddress);
    CloseHandle(pControl->mappingHandle);
    CloseHandle(pControl->fileHandle);
} /* UnmapFileFromMemory */
