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

#include <stdio.h>
#include <ctype.h>
#include "intel_utility.h"

/******************************************************************************
 * Name: PrintRadioUniqueId
 *
 * Description:
 *   Prints out the unique ID for a radio.  The unique ID is printed in hex and
 *   ASCII with an indent of 4 spaces.
 *
 * Parameters:
 *   idLength - length, in bytes, of the unique ID
 *   pUniqueId - pointer to buffer that contains the unique ID
 *
 * Returns:
 *   Nothing
 ******************************************************************************/
void PrintRadioUniqueId(
    INT32U          idLength,
    const INT8U*    pUniqueId
    )
{
    INT32U  offset;
    for (offset = 0; offset < idLength; offset += 16)
    {
        INT32U  index;
        INT32U  padding;
        printf("   ");
        for (index = 0; index < 16 && ((index + offset) < idLength); ++index)
        {
            printf("%s%.2x", index % 4 ? "" : " ", pUniqueId[offset + index]);
        }

        padding = 
            (((16 - index) % 4) * 2) + 1 +
            ((((16 - index) / 4) + 1) * 9);
        printf("%*s|", padding, "");

        for (index = 0; index < 16 && ((index + offset) < idLength); ++index)
        {
            printf(
                "%c",
                isprint(pUniqueId[offset + index]) ? 
                    pUniqueId[offset + index] : ' ');
        }

        printf("%*s|\n", 16 - index, "");
    }

    fflush(stdout);
} /* PrintRadioUniqueId */

