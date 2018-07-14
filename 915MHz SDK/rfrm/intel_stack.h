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
 *   This file contains the prototype for a simple stack.
 *
 *   NOTE - this is not bulletproof code, but is instead a simple stack for
 *   demonstrating nonvolatile memory update.
 *
 ******************************************************************************/

#ifndef INTEL_STACK_H_INCLUDED
#define INTEL_STACK_H_INCLUDED

#include <stdlib.h>
#include "rfid_types.h"

typedef void * STACK_HANDLE;

#define INVALID_STACK_HANDLE NULL

/******************************************************************************
 * Name: StackCreate
 *
 * Description:
 *   Creates a new stack.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   INVALID_STACK_HANDLE if creation failed, non-NULL otherwise.
 ******************************************************************************/
STACK_HANDLE StackCreate(
     void
     );

/******************************************************************************
 * Name: StackPush
 *
 * Description:
 *   Pushes an item on the stack
 *
 * Parameters:
 *   stack - stack onto which item will be pushed
 *   pValue - the item to push onto the stack
 *
 * Returns:
 *   0 - success, !0 - failure
 ******************************************************************************/
INT32S StackPush(
    STACK_HANDLE    stack,
    void*           pValue
    );

/******************************************************************************
 * Name: StackPop
 *
 * Description:
 *   Pops the top item from the stack
 *
 * Parameters:
 *   stack - stack from which item will be popped
 *
 * Returns:
 *   The value on top of the stack.
 ******************************************************************************/
void* StackPop(
    STACK_HANDLE    stack
    );

/******************************************************************************
 * Name: StackTop
 *
 * Description:
 *   Returns (but doesn't pop) the top item from the stack
 *
 * Parameters:
 *   stack - stack from which the to item will be returned
 *
 * Returns:
 *   The value on top of the stack.
 ******************************************************************************/
void* StackTop(
    STACK_HANDLE    stack
    );

/******************************************************************************
 * Name: StackEmpty
 *
 * Description:
 *   Determines if the stack is empty
 *
 * Parameters:
 *   stack - stack to test for emptiness
 *
 * Returns:
 *   0 - not empty, !0 - empty
 ******************************************************************************/
int StackEmpty(
    STACK_HANDLE    stack
    );

/******************************************************************************
 * Name: StackDestroy
 *
 * Description:
 *   Destroys the stack
 *
 * Parameters:
 *   stack - stack to destroy
 *
 * Returns:
 *   Nothing
 ******************************************************************************/
void StackDestroy(
    STACK_HANDLE    stack
    );

#endif /* #ifndef INTEL_STACK_H_INCLUDED */
