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
#include "intel_stack.h"
#include "intel_list.h"

typedef struct
{
    LIST_HANDLE list;
} STACK;

/******************************************************************************
 * Name: StackCreate
 *
 * Description:
 *   Creates a new stack.
 ******************************************************************************/
STACK_HANDLE StackCreate(
    void
    )
{
    STACK*  pStack = (STACK *) malloc(sizeof(STACK));
    if (NULL == pStack)
    {
        goto EXIT;
    }

    pStack->list = ListCreate();
    if (INVALID_LIST_HANDLE == pStack->list)
    {
        goto CLEANUP;
    }

    goto EXIT;

CLEANUP:
    free(pStack);

EXIT:
    return (STACK_HANDLE) pStack;
} /* StackCreate */

/******************************************************************************
 * Name: StackPush
 *
 * Description:
 *   Pushes an item on the stack
 ******************************************************************************/
INT32S StackPush(
    STACK_HANDLE    stack,
    void*           pValue
    )
{
    assert(INVALID_STACK_HANDLE != stack);

    return ListAddEnd(((STACK *) stack)->list, pValue);
} /* StackPush */

/******************************************************************************
 * Name: StackPop
 *
 * Description:
 *   Pops the top item from the stack
 ******************************************************************************/
void* StackPop(
    STACK_HANDLE    stack
    )
{
    assert(INVALID_STACK_HANDLE != stack);
    assert(!StackEmpty(stack));

    return ListRemoveEnd(((STACK *) stack)->list);
} /* StackPop */

/******************************************************************************
 * Name: StackTop
 *
 * Description:
 *   Returns (but doesn't pop) the top item from the stack
 ******************************************************************************/
void* StackTop(
    STACK_HANDLE    stack
    )
{
    assert(INVALID_STACK_HANDLE != stack);
    assert(!StackEmpty(stack));

    return ListEnd(((STACK *) stack)->list);
} /* StackTop */

/******************************************************************************
 * Name: StackEmpty
 *
 * Description:
 *   Determines if the stack is empty
 ******************************************************************************/
int StackEmpty(
    STACK_HANDLE    stack
    )
{
    assert(INVALID_STACK_HANDLE != stack);

    return ListEmpty(((STACK *) stack)->list);
} /* StackEmpty */

/******************************************************************************
 * Name: StackDestroy
 *
 * Description:
 *   Destroys the stack
 ******************************************************************************/
void StackDestroy(
    STACK_HANDLE    stack
    )
{
    assert(INVALID_STACK_HANDLE != stack);

    ListDestroy(((STACK *) stack)->list);
    free((STACK *) stack);
} /* StackDestroy */

