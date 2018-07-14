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
 *   This file contains the implementation for a simple stack.
 *
 ******************************************************************************/
#include "StdAfx.h"

#include <assert.h>
#include "intel_list.h"

typedef struct listNode
{
    struct listNode*    pNext;
    struct listNode*    pPrevious;
    void*               pValue;
} LIST_NODE;

typedef struct
{
    LIST_NODE* pFront;
    LIST_NODE* pEnd;
} LIST;

/******************************************************************************
 * Name: ListCreate
 *
 * Description:
 *   Creates a new stack.
 ******************************************************************************/
LIST_HANDLE ListCreate(
    void
    )
{
    LIST* pList = (LIST *) malloc(sizeof(LIST));
    if (NULL != pList)
    {
        pList->pFront = pList->pEnd = NULL;
    }

    return (LIST_HANDLE) pList;
} /* ListCreate */

/******************************************************************************
 * Name: ListAddFront
 *
 * Description:
 *   Puts an item onto the front of a list
 ******************************************************************************/
INT32S ListAddFront(
    LIST_HANDLE list,
    void*       pValue
    )
{
    LIST*      pList  = (LIST *) list;
    LIST_NODE* pNode;
    
    assert(INVALID_LIST_HANDLE != list);

    pNode = (LIST_NODE *) malloc(sizeof(LIST_NODE));
    if (NULL != pNode)
    {
        pNode->pNext            = pList->pFront;
        pNode->pPrevious        = NULL;
        pNode->pValue           = pValue;
        if (NULL != pList->pFront)
        {
            pList->pFront->pPrevious = pNode;
        }
        pList->pFront           = pNode;
        if (NULL == pList->pEnd)
        {
            pList->pEnd = pNode;
        }
    }

    return NULL == pNode;
} /* ListAddFront */

/******************************************************************************
 * Name: ListAddEnd
 *
 * Description:
 *   Puts an item onto the end of a list
 ******************************************************************************/
INT32S ListAddEnd(
    LIST_HANDLE list,
    void*       pValue
    )
{
    LIST*      pList  = (LIST *) list;
    LIST_NODE* pNode;
    
    assert(INVALID_LIST_HANDLE != list);

    pNode = (LIST_NODE *) malloc(sizeof(LIST_NODE));
    if (NULL != pNode)
    {
        pNode->pNext            = NULL;
        pNode->pPrevious        = pList->pEnd;
        pNode->pValue           = pValue;
        if (NULL != pList->pEnd)
        {
            pList->pEnd->pNext = pNode;
        }
        pList->pEnd            = pNode;
        if (NULL == pList->pFront)
        {
            pList->pFront = pNode;
        }
    }

    return NULL == pNode;
} /* ListAddEnd */

/******************************************************************************
 * Name: ListRemoveFront
 *
 * Description:
 *   Removes the item from the front of the list
 ******************************************************************************/
void* ListRemoveFront(
    LIST_HANDLE list
    )
{
    LIST*   pList   = (LIST *) list;
    void*   pValue  = NULL;

    assert(INVALID_LIST_HANDLE != list);
    assert(!ListEmpty(list));

    if (NULL != pList->pFront)
    {
        LIST_NODE* pNode = pList->pFront;
        pList->pFront = pNode->pNext;
        if (NULL == pList->pFront)
        {
            pList->pEnd = NULL;
        }
        else
        {
            pList->pFront->pPrevious = NULL;
        }
        pValue = pNode->pValue;
        free(pNode);
    }

    return pValue;
} /* ListRemoveFront */

/******************************************************************************
 * Name: ListRemoveEnd
 *
 * Description:
 *   Removes the item from the front of the list
 ******************************************************************************/
void* ListRemoveEnd(
    LIST_HANDLE list
    )
{
    LIST*   pList   = (LIST *) list;
    void*   pValue  = NULL;

    assert(INVALID_LIST_HANDLE != list);
    assert(!ListEmpty(list));

    if (NULL != pList->pEnd)
    {
        LIST_NODE* pNode = pList->pEnd;
        pList->pEnd = pNode->pPrevious;
        if (NULL == pList->pEnd)
        {
            pList->pFront = NULL;
        }
        else
        {
            pList->pEnd->pNext = NULL;
        }
        pValue = pNode->pValue;
        free(pNode);
    }

    return pValue;
} /* ListRemoveEnd */

/******************************************************************************
 * Name: ListFront
 *
 * Description:
 *   Returns (but doesn't remove) the item at the front of the list
 ******************************************************************************/
void* ListFront(
    LIST_HANDLE list
    )
{
    assert(INVALID_LIST_HANDLE != list);
    assert(!ListEmpty(list));

    return ((LIST *) list)->pFront->pValue;
} /* ListFront */

/******************************************************************************
 * Name: ListEnd
 *
 * Description:
 *   Returns (but doesn't remove) the item at the front of the list
 ******************************************************************************/
void* ListEnd(
    LIST_HANDLE list
    )
{
    assert(INVALID_LIST_HANDLE != list);
    assert(!ListEmpty(list));

    return ((LIST *) list)->pEnd->pValue;
} /* ListEnd */

/******************************************************************************
 * Name: ListEmpty
 *
 * Description:
 *   Determines if the stack is empty
 ******************************************************************************/
int ListEmpty(
    LIST_HANDLE list
    )
{
    assert(INVALID_LIST_HANDLE != list);

    return NULL == ((LIST *) list)->pEnd;
} /* ListEmpty */

/******************************************************************************
 * Name: ListDestroy
 *
 * Description:
 *   Destroys the stack
 ******************************************************************************/
void ListDestroy(
    LIST_HANDLE list
    )
{
    assert(INVALID_LIST_HANDLE != list);

    /* Empty out the stack first                                              */
    while (!ListEmpty(list))
    {
        ListRemoveFront(list);
    }

    free((LIST *) list);
} /* ListDestroy */

