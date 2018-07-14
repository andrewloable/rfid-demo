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
 *   This file contains the prototype for a simple linked list.
 *
 *   NOTE - this is not bulletproof code, but is instead a simple linked list
 *   for demonstrating sample code.
 *
 ******************************************************************************/

#ifndef INTEL_LIST_H_INCLUDED
#define INTEL_LIST_H_INCLUDED

#include <stdlib.h>
#include "rfid_types.h"

typedef void * LIST_HANDLE;

#define INVALID_LIST_HANDLE NULL

/******************************************************************************
 * Name: ListCreate
 *
 * Description:
 *   Creates a new List.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   INVALID_LIST_HANDLE if creation failed, non-NULL otherwise.
 ******************************************************************************/
LIST_HANDLE ListCreate(
     void
     );

/******************************************************************************
 * Name: ListAddFront
 *
 * Description:
 *   Adds an item to the front of a list
 *
 * Parameters:
 *   list - list to which item will be added to front
 *   pValue - the item to add to the list
 *
 * Returns:
 *   0 - success, !0 - failure
 ******************************************************************************/
INT32S ListAddFront(
    LIST_HANDLE list,
    void*       pValue
    );

/******************************************************************************
 * Name: ListAddEnd
 *
 * Description:
 *   Adds an item to the end of a list
 *
 * Parameters:
 *   list - list to which item will be added to end
 *   pValue - the item to add to the list
 *
 * Returns:
 *   0 - success, !0 - failure
 ******************************************************************************/
INT32S ListAddEnd(
    LIST_HANDLE list,
    void*       pValue
    );

/******************************************************************************
 * Name: ListRemoveFront
 *
 * Description:
 *   Removes the item from the front of the list
 *
 * Parameters:
 *   list - list from which item will be removed
 *
 * Returns:
 *   The value at the front of the List.
 ******************************************************************************/
void* ListRemoveFront(
    LIST_HANDLE list
    );

/******************************************************************************
 * Name: ListRemoveEnd
 *
 * Description:
 *   Removes the item from the end of the list
 *
 * Parameters:
 *   list - list from which item will be removed
 *
 * Returns:
 *   The value at the end of the List.
 ******************************************************************************/
void* ListRemoveEnd(
    LIST_HANDLE list
    );

/******************************************************************************
 * Name: ListFront
 *
 * Description:
 *   Returns (but doesn't remove) the item at the front of the list
 *
 * Parameters:
 *   list - list from which the front item will be returned
 *
 * Returns:
 *   The value at the front of the List.
 ******************************************************************************/
void* ListFront(
    LIST_HANDLE list
    );

/******************************************************************************
 * Name: ListEnd
 *
 * Description:
 *   Returns (but doesn't remove) the item at the end of the list
 *
 * Parameters:
 *   list - list from which the end item will be returned
 *
 * Returns:
 *   The value at the end of the List.
 ******************************************************************************/
void* ListEnd(
    LIST_HANDLE list
    );

/******************************************************************************
 * Name: ListEmpty
 *
 * Description:
 *   Determines if the list is empty
 *
 * Parameters:
 *   list - list to test for emptiness
 *
 * Returns:
 *   0 - not empty, !0 - empty
 ******************************************************************************/
int ListEmpty(
    LIST_HANDLE list
    );

/******************************************************************************
 * Name: ListDestroy
 *
 * Description:
 *   Destroys the list
 *
 * Parameters:
 *   list - list to destroy
 *
 * Returns:
 *   Nothing
 ******************************************************************************/
void ListDestroy(
    LIST_HANDLE list
    );

#endif /* #ifndef INTEL_LIST_H_INCLUDED */
