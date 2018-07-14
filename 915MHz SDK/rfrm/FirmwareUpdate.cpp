// ../FirmwareUpdate.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "FirmwareUpdate.h"

#include "Util.h"
#include "intel_stack.h"
// CFirmwareUpdate

const char*     ROOT_TAG_NAME       = "blocks";
const char*     BLOCK_TAG_NAME      = "block";
const char*     ADDRESS_TAG_NAME    = "address";
const char*     FILE_TAG_NAME       = "file";


CFirmwareUpdate::CFirmwareUpdate(RFID_RADIO_HANDLE handle) 
: m_pBlocks(NULL)
, m_bSkipTestMode(FALSE)
, m_bTestModeOnly(TRUE)
, m_pRoot(NULL)
, m_bStopRequest(FALSE)
, m_pThread(NULL)
, m_strFileName(TEXT(""))
, m_rfidHandle(handle)
, m_pParent(NULL)
{
	m_rfidHandle = handle;
}

CFirmwareUpdate::CFirmwareUpdate(RFID_RADIO_HANDLE handle, BOOL skipTestMode, BOOL testModeOnly)
: m_pBlocks(NULL)
, m_pRoot(NULL)
, m_bStopRequest(FALSE)
, m_pThread(NULL)
, m_strFileName(TEXT(""))
, m_rfidHandle(handle)
, m_bSkipTestMode(skipTestMode)
, m_bTestModeOnly(testModeOnly)
, m_pParent(NULL)
{
// 	m_rfidHandle = handle;
// 	m_bSkipTestMode = skipTestMode;
// 	m_bTestModeOnly = testModeOnly;
}

CFirmwareUpdate::CFirmwareUpdate(RFID_RADIO_HANDLE handle, LPCTSTR filename, BOOL skipTestMode, BOOL testModeOnly)
: m_pBlocks(NULL)
, m_pRoot(NULL)
, m_bStopRequest(FALSE)
, m_pThread(NULL)
, m_strFileName(filename)
, m_rfidHandle(handle)
, m_bSkipTestMode(skipTestMode)
, m_bTestModeOnly(testModeOnly)
, m_pParent(NULL)
{

}

CFirmwareUpdate::CFirmwareUpdate(RFID_RADIO_HANDLE handle, LPCTSTR filename, BOOL skipTestMode, BOOL testModeOnly, CWnd* pParent)
: m_pBlocks(NULL)
, m_pRoot(NULL)
, m_bStopRequest(FALSE)
, m_pThread(NULL)
, m_strFileName(filename)
, m_rfidHandle(handle)
, m_bSkipTestMode(skipTestMode)
, m_bTestModeOnly(testModeOnly)
, m_pParent(pParent)
{

}

CFirmwareUpdate::CFirmwareUpdate(RFID_RADIO_HANDLE handle, LPCTSTR filename, RFID_RADIO_FIRMWARE_MODE mode, CWnd* pParent)
: m_pBlocks(NULL)
, m_pRoot(NULL)
, m_bStopRequest(FALSE)
, m_pThread(NULL)
, m_strFileName(filename)
, m_rfidHandle(handle)
, m_pParent(pParent)
{
	switch(mode)
	{
	case RFID_RADIO_FIRMWARE_UPDATE_ALL:
		m_bSkipTestMode = FALSE;
		m_bTestModeOnly = FALSE;
		break;
	case RFID_RADIO_FIRMWARE_TEST_ONLY:
		m_bSkipTestMode = FALSE;
		m_bTestModeOnly = TRUE;

		break;
	case RFID_RADIO_FIRMWARE_SKIP_TEST:
		m_bSkipTestMode = TRUE;
		m_bTestModeOnly = FALSE;
		break;
	default:
		m_bSkipTestMode = FALSE;
		m_bTestModeOnly = FALSE;
		break;
	}
}


CString RFIDStatusToString(
							   RFID_STATUS status
							   )
{
	CString pString;

	switch(status)
	{
	case RFID_STATUS_OK:
		pString.LoadString(IDS_STRING_RFID_STATUS_OK);
		break;

	case RFID_ERROR_ALREADY_OPEN:
		pString.LoadString(IDS_STRING_RFID_ERROR_ALREADY_OPEN);
		break;

	case RFID_ERROR_BUFFER_TOO_SMALL:
		pString.LoadString(IDS_STRING_RFID_ERROR_BUFFER_TOO_SMALL);
		break;

	case RFID_ERROR_CURRENTLY_NOT_ALLOWED:
		pString.LoadString(IDS_STRING_RFID_ERROR_CURRENTLY_NOT_ALLOWED);
		break;

	case RFID_ERROR_FAILURE:
		pString.LoadString(IDS_STRING_RFID_ERROR_FAILURE);
		break;

	case RFID_ERROR_DRIVER_LOAD:
		pString.LoadString(IDS_STRING_RFID_ERROR_DRIVER_LOAD);
		break;

	case RFID_ERROR_DRIVER_MISMATCH:
		pString.LoadString(IDS_STRING_RFID_ERROR_DRIVER_MISMATCH);
		break;

	case RFID_ERROR_EMULATION_MODE:
		pString.LoadString(IDS_STRING_RFID_ERROR_EMULATION_MODE);
		break;

	case RFID_ERROR_INVALID_ANTENNA:
		pString.LoadString(IDS_STRING_RFID_ERROR_INVALID_ANTENNA);
		break;

	case RFID_ERROR_INVALID_HANDLE:
		pString.LoadString(IDS_STRING_RFID_ERROR_INVALID_HANDLE);
		break;

	case RFID_ERROR_INVALID_PARAMETER:
		pString.LoadString(IDS_STRING_RFID_ERROR_INVALID_PARAMETER);
		break;
	case RFID_ERROR_NO_SUCH_RADIO:
		pString.LoadString(IDS_STRING_RFID_ERROR_NO_SUCH_RADIO);
		break;

	case RFID_ERROR_NOT_INITIALIZED:
		pString.LoadString(IDS_STRING_RFID_ERROR_NOT_INITIALIZED);
		break;

	case RFID_ERROR_NOT_SUPPORTED:
		pString.LoadString(IDS_STRING_RFID_ERROR_NOT_SUPPORTED);
		break;

	case RFID_ERROR_OPERATION_CANCELLED:
		pString.LoadString(IDS_STRING_RFID_ERROR_OPERATION_CANCELLED);
		break;

	case RFID_ERROR_OUT_OF_MEMORY:
		pString.LoadString(IDS_STRING_RFID_ERROR_OUT_OF_MEMORY);
		break;

	case RFID_ERROR_RADIO_BUSY:
		pString.LoadString(IDS_STRING_RFID_ERROR_RADIO_BUSY);
		break;

	case RFID_ERROR_RADIO_FAILURE:
		pString.LoadString(IDS_STRING_RFID_ERROR_RADIO_FAILURE);
		break;

	case RFID_ERROR_RADIO_NOT_PRESENT:
		pString.LoadString(IDS_STRING_RFID_ERROR_RADIO_NOT_PRESENT);
		break;

	case RFID_ERROR_RADIO_NOT_RESPONDING:
		pString.LoadString(IDS_STRING_RFID_ERROR_RADIO_NOT_RESPONDING);
		break;

	case RFID_ERROR_NONVOLATILE_INIT_FAILED:
		pString.LoadString(IDS_STRING_RFID_ERROR_NONVOLATILE_INIT_FAILED);
		break;

	case RFID_ERROR_NONVOLATILE_OUT_OF_BOUNDS:
		pString.LoadString(IDS_STRING_RFID_ERROR_NONVOLATILE_OUT_OF_BOUNDS);
		break;

	case RFID_ERROR_NONVOLATILE_WRITE_FAILED:
		pString.LoadString(IDS_STRING_RFID_ERROR_NONVOLATILE_WRITE_FAILED);
		break;

	default:
		pString.LoadString(IDS_STRING_RFID_ERROR_UNKNOWN);
		break;
	}

	return pString;
} /* RFIDStatusToString */


CFirmwareUpdate::~CFirmwareUpdate()
{
//	UnmapFileFromMemory();
}

XML_NODE* CFirmwareUpdate::CreateXmlTree( const char* pFileStream,
										  INT32U      length)
{
//	XML_NODE*       pRoot = NULL;
	STACK_HANDLE    stack = INVALID_STACK_HANDLE;

	/* Create a stack that is used during process of XML text                 */
	stack = StackCreate();
	if (INVALID_STACK_HANDLE == stack)
	{
		goto EXIT;
	}

	while (1)
	{
		/* Get rid of any whitespace and if we are at the end of the file data*/
		/* then we are done.                                                  */
		for ( ; length && isspace(*pFileStream); --length, ++pFileStream);
		if (!length)
		{
			break;
		}

		/* If we are at a tag, then we need to figure out the tag name        */
		if ('<' == *pFileStream)
		{
			/* Find the tag's closing >                                       */
			const char* pStartTag = ++pFileStream;
			for (--length;
				length && ('>' != *pFileStream);
				--length, ++pFileStream);
			if (pStartTag == pFileStream)
			{
				fprintf(stderr, "ERROR: Found an empty XML begin tag\n");
				goto DESTROY_XML_TREE;
			}

			/* If this is a begin tag, then we'll create a new tree node and  */
			/* push it onto the stack.                                        */
			if ('/' != *pStartTag)
			{
				/* Allocate and initialize a new node.                        */
				XML_NODE* pNewNode = (XML_NODE *) malloc(sizeof(XML_NODE));
				if (NULL == pNewNode)
				{
					fprintf(stderr, "ERROR: Failed to allocate memory\n");
					goto DESTROY_XML_TREE;
				}
				pNewNode->pNextSibling  = NULL;
				pNewNode->pFirstChild   = NULL;
				pNewNode->pLastChild    = NULL;
				pNewNode->pValue        = NULL;
				pNewNode->pName         = NULL;

				/* If the stack is empty, then this tag is the root           */
				if (StackEmpty(stack))
				{
					if (NULL != m_pRoot)
					{
						fprintf(
							stderr,
							"ERROR: Found a second root tag named %.*s\n",
							pFileStream - pStartTag,
							pStartTag);
						free(pNewNode);
						goto DESTROY_XML_TREE;
					}
					m_pRoot = pNewNode;
				}
				/* Otherwise, the tag is a child of the node that is on top   */
				/* of the stack.  Additionally, if the top node already has   */
				/* children, then this child is a sibling to that(those)      */
				/* node(s)                                                    */
				else
				{
					XML_NODE* pTop = (XML_NODE *) StackTop(stack);
					if (NULL == pTop->pFirstChild)
					{
						pTop->pFirstChild = pNewNode;
					}
					else
					{
						pTop->pLastChild->pNextSibling = pNewNode;
					}
					pTop->pLastChild = pNewNode;
				}

				if (StackPush(stack, pNewNode))
				{
					fprintf(stderr, "ERROR: Failed to push value on stack\n");
					free(pNewNode);
					goto DESTROY_XML_TREE;
				}

				/* Copy the tag's name                                        */
				pNewNode->pName     = 
					(char *) malloc(pFileStream - pStartTag + 1);
				if (NULL == pNewNode->pName)
				{
					fprintf(stderr, "ERROR: Failed to allocate memory\n");
					goto DESTROY_XML_TREE;
				}
				strncpy(pNewNode->pName, pStartTag, pFileStream - pStartTag);
				pNewNode->pName[pFileStream - pStartTag] = '\0';
			}
			/* Otherwise, since this is an end tag, then we need to ensure    */
			/* it matches the tag on top of the stack and then pop the stack. */
			else
			{
				/* Verify that the end tag is not empty                       */
				if (++pStartTag == pFileStream)
				{
					fprintf(stderr, "ERROR: Found an empty XML end tag\n");
					goto DESTROY_XML_TREE;
				}

				/* Verify that the end tag name matches the name of the tag  */
				/* that is on top of the stack.                              */
				if (StackEmpty(stack))
				{
					fprintf(
						stderr,
						"ERROR: Found an end tag, but no start tag\n");
					goto DESTROY_XML_TREE;
				}
				if (strncmp(
					((XML_NODE *) StackTop(stack))->pName,
					pStartTag,
					pFileStream - pStartTag))
				{
					fprintf(
						stderr,
						"ERROR: End tag </%.*s> doesn't match begin tag <%s>\n",
						pFileStream - pStartTag,
						pStartTag,
						((XML_NODE *) StackTop(stack))->pName);
					goto DESTROY_XML_TREE;
				}

				/* Since we have found the matching end tag, we can pop the   */
				/* tag off of the stack                                       */
				StackPop(stack);
			}

			/* Move past the tag closing >                                    */
			--length;
			++pFileStream;
		}
		/* Otherwise, we are at a data value                                  */
		else
		{
			const char* pStartValue = pFileStream;
			XML_NODE*   pNode;

			/* Ensure that there is actually a tag on top of the stack        */
			if (StackEmpty(stack))
			{
				fprintf(
					stderr,
					"ERROR: Found a tag value, but not inside of tag\n");
				goto DESTROY_XML_TREE;
			}

			/* Find the end of the value                                      */
			for ( ; length && ('<' != *pFileStream); --length, ++pFileStream);
			if (!length)
			{
				fprintf(
					stderr,
					"ERROR: Reached end of file in middle of tag value\n");
				goto DESTROY_XML_TREE;
			}

			/* Copy the value into the XML node                               */
			pNode           = (XML_NODE *) StackTop(stack);
			pNode->pValue   = (char *) malloc(pFileStream - pStartValue + 1);
			if (NULL == pNode->pValue)
			{
				fprintf(stderr, "ERROR: Failed to allocate memory\n");
				goto DESTROY_XML_TREE;
			}
			strncpy(pNode->pValue, pStartValue, pFileStream - pStartValue);
			pNode->pValue[pFileStream - pStartValue] = '\0';
		}
	}

	/* At this point, the stack should be empty - meaning that the file has   */
	/* been completely processed and an opening/closing tag should have been  */
	/* found.                                                                 */
	if (!StackEmpty(stack))
	{
		fprintf(stderr,
			"ERROR: Found additional non-whitespace after closing tag\n");
		goto DESTROY_XML_TREE;
	}

	goto DESTROY_STACK;

DESTROY_XML_TREE:
	DestroyXmlTree(m_pRoot);
	m_pRoot = NULL;

DESTROY_STACK:
	while (!StackEmpty(stack))
	{
		StackPop(stack);
	}
	StackDestroy(stack);

EXIT:
	return m_pRoot;
} /* CreateXmlTree */


void CFirmwareUpdate::DestroyXmlTree(
					XML_NODE*   pRoot
					)
{
	if (pRoot)
	{
		DestroyXmlTree(pRoot->pFirstChild);
		DestroyXmlTree(pRoot->pNextSibling);
		if (pRoot->pName)
		{
			free(pRoot->pName);
		}
		if (pRoot->pValue)
		{
			free(pRoot->pValue);
		}
		free(pRoot);
	}
} /* DestroyXmlTree */


INT32S CFirmwareUpdate::ProcessXmlTree(
					  const XML_NODE*                 pRoot,
					  RFID_NONVOLATILE_MEMORY_BLOCK** ppBlocks,
					  MEMMAP_HANDLE**                 ppHandles,
					  INT32U*                         pNumberBlocks
					  )
{
	INT32S                          result      = -1;
	XML_NODE*                       pNode;
	RFID_NONVOLATILE_MEMORY_BLOCK*  pBlocks     = NULL;
	MEMMAP_HANDLE*                  pHandles    = NULL;
	INT32U                          numberBlocks;
	INT32U                          blockNumber;

	*ppBlocks       = NULL;
	*ppHandles      = NULL;
	*pNumberBlocks  = 0;

	/* Verify that the root of the tree is named properly.                    */
	if (strcmp(pRoot->pName, ROOT_TAG_NAME))
	{
		TRACE2("ERROR: XML root tag is named <%s> instead of <%s>\n", pRoot->pName, ROOT_TAG_NAME);
		goto EXIT;
	}

	/* Verify that there are update blocks                                    */
	if (NULL == pRoot->pFirstChild)
	{
		fprintf(
			stderr,
			"ERROR: Update file must contain at least one update block\n");
		goto EXIT;
	}

	/* Process each block to create the update block array                    */
	for (pNode = pRoot->pFirstChild, numberBlocks = 0;
		pNode != NULL;
		pNode = pNode->pNextSibling, ++numberBlocks)
	{
		RFID_NONVOLATILE_MEMORY_BLOCK*  pNewBlocks;
		MEMMAP_HANDLE*                  pNewHandles;
		XML_NODE*                       pChild;
		INT32U                          addressSet = 0;

		if (strcmp(pNode->pName, BLOCK_TAG_NAME))
		{
			fprintf(
				stderr,
				"ERROR: Found XML tag named <%s>, but expected <%s>\n",
				pNode->pName,
				BLOCK_TAG_NAME);
			goto CLEANUP;
		}

		/* Expand the array of nonvolatile memory blocks and file mapping     */
		/* handles.                                                           */
		pNewBlocks = 
			(RFID_NONVOLATILE_MEMORY_BLOCK *) realloc(
			pBlocks,
			(numberBlocks + 1) * sizeof(RFID_NONVOLATILE_MEMORY_BLOCK));
		if (NULL == pNewBlocks)
		{
			fprintf(stderr, "ERROR: Failed to allocate memory\n");
			goto CLEANUP;
		}
		pBlocks = pNewBlocks;
		pBlocks[numberBlocks].pData = NULL;
		pBlocks[numberBlocks].flags = 0;

		pNewHandles = 
			(MEMMAP_HANDLE *) realloc(
			pHandles,
			(numberBlocks + 1) * sizeof(MEMMAP_HANDLE));
		if (NULL == pNewHandles)
		{
			fprintf(stderr, "ERROR: Failed to allocate memory\n");
			goto CLEANUP;
		}
		pHandles = pNewHandles;
		pHandles[numberBlocks] = INVALID_MEMMAP_HANDLE;

		/* Process the children to get the address and the update file        */
		for (pChild = pNode->pFirstChild;
			NULL != pChild;
			pChild = pChild->pNextSibling)
		{
			/* Convert the address string to the update address               */
			if (!strcmp(pChild->pName, ADDRESS_TAG_NAME))
			{
				char* endString;

				if (addressSet)
				{
					fprintf(
						stderr,
						"ERROR: Tag <address> appears more than once in "
						"<block>\n");
					goto CLEANUP;
				}

				if (NULL == pChild->pValue)
				{
					fprintf(
						stderr, "ERROR: Tag <address> does not have a value\n");
					goto CLEANUP;
				}

				pBlocks[numberBlocks].address =
					strtoul(pChild->pValue, &endString, 0);
				if (*endString)
				{
					fprintf(
						stderr,
						"ERROR: \"%s\" is an invalid address\n",
						pChild->pValue);
					goto CLEANUP;
				}

				addressSet = 1;
			}
			/* Map the update file onto memory so we can use it               */
			else if (!strcmp(pChild->pName, FILE_TAG_NAME))
			{
				if (NULL != pBlocks[numberBlocks].pData)
				{
					fprintf(
						stderr,
						"ERROR: Tag <file> appears more than once in "
						"<block>\n");
					goto CLEANUP;
				}

				if (NULL == pChild->pValue)
				{
					fprintf(
						stderr, "ERROR: Tag <file> does not have a value\n");
					goto CLEANUP;
				}

				pHandles[numberBlocks] = 
					MapFileOntoMemory(pChild->pValue);
				if (INVALID_MEMMAP_HANDLE == pHandles[numberBlocks])
				{
					fprintf(
						stderr,
						"ERROR: Failed to open update file \"%s\"\n",
						pChild->pValue);
					goto CLEANUP;
				}

				pBlocks[numberBlocks].pData     =(INT8U*)
					GetFileMappingStartAddress(pHandles[numberBlocks]);
				pBlocks[numberBlocks].length    =
					GetFileMappingSize(pHandles[numberBlocks]);
			}
			else
			{
				fprintf(
					stderr,
					"ERROR: Encountered unexpected tag <%s>\n",
					pChild->pName);
				goto CLEANUP;
			}
		}
	}

	result          = 0;
	*ppBlocks       = pBlocks;
	*ppHandles      = pHandles;
	*pNumberBlocks  = numberBlocks;

	goto EXIT;

CLEANUP:
	for (blockNumber = 0; blockNumber < numberBlocks; ++blockNumber)
	{
		if (INVALID_MEMMAP_HANDLE != pHandles[blockNumber])
		{
			UnmapFileFromMemory(pHandles[blockNumber]);
		}
	}

	free(pHandles);
	free(pBlocks);

EXIT:
	return result;
} /* ProcessXmlTree */

BOOL CFirmwareUpdate::FirmwareUpate()
{
	m_bStopRequest = FALSE;

	CUtil							util;
	CString							strResult;
	MEMMAP_HANDLE                   memmap;
	char*                           pFileStart;
	INT32U                          fileSize;
	XML_NODE*						pRoot;
	MEMMAP_HANDLE*                  pUpdateHandles = NULL;

	m_pParent->PostMessage(WM_FIRMWARE_MSG, (WPARAM)TEXT("File Loading"), (LPARAM)TEXT("Initialize"));

	/* Map the configuration file onto memory...this will make life a little  */
	/* simpler                                                                */
	memmap = ::MapFileOntoMemory(util.WCharToChar(m_strFileName));
	if (INVALID_MEMMAP_HANDLE == memmap)
	{
		///////////////////////// Send Message ///////////////////////////////
		strResult.Format(TEXT("Unable to open file \"%s\"\n"), m_strFileName);

#ifdef _DEBUG
		TRACE(strResult); 
#endif
		m_pParent->PostMessage(WM_FIRMWARE_MSG, (WPARAM)TEXT("File Loading"), (LPARAM)(LPCTSTR)strResult);

	}
	else
	{
		///////////////////////// Send Message ///////////////////////////////
		strResult.Format(TEXT("Success to open file \"%s\"\n"), m_strFileName);

#ifdef _DEBUG
		TRACE(strResult); 
#endif
		m_pParent->PostMessage(WM_FIRMWARE_MSG, (WPARAM)TEXT("File Loading"), (LPARAM)(LPCTSTR)strResult);
	}

	pFileStart  = (char *) ::GetFileMappingStartAddress(memmap);

	///////////////////////// Send Message ///////////////////////////////
	strResult.Format(TEXT("%s"), pFileStart);
	m_pParent->PostMessage(WM_FIRMWARE_MSG, (WPARAM)TEXT("Start File"), (LPARAM)(LPCTSTR)strResult);

	fileSize    = ::GetFileMappingSize(memmap);

	///////////////////////// Send Message ///////////////////////////////
	strResult.Format(TEXT("%u"), fileSize);
	m_pParent->PostMessage(WM_FIRMWARE_MSG, (WPARAM)TEXT("File Size"), (LPARAM)(LPCTSTR)strResult);

	///////////////////////// Send Message ///////////////////////////////
	m_pParent->PostMessage(WM_FIRMWARE_MSG, (WPARAM)TEXT("XML Parsing"), (LPARAM)TEXT("Initialize"));
	/* Create the XML tree that represents the file.                          */
	if (NULL == 
		(pRoot = CreateXmlTree(pFileStart, fileSize)))
	{
		///////////////////////// Send Message ///////////////////////////////
		m_pParent->PostMessage(WM_FIRMWARE_MSG, (WPARAM)TEXT("XML Parsing"), (LPARAM)TEXT("File to parsing XML"));

		::UnmapFileFromMemory(memmap);
	}
	else
	{
		///////////////////////// Send Message ///////////////////////////////
		m_pParent->PostMessage(WM_FIRMWARE_MSG, (WPARAM)TEXT("XML Parsing"), (LPARAM)TEXT("Success to parsing XML"));
	}


	///////////////////////// Send Message ///////////////////////////////
	m_pParent->PostMessage(WM_FIRMWARE_MSG, (WPARAM)TEXT("XML Parsing"), (LPARAM)TEXT("Memory Allocation"));
	/* Process the XML tree to create the nonvolatile memory blocks and map   */
	/* the update files into memory                                           */
	if (ProcessXmlTree(pRoot, &m_pBlocks, &pUpdateHandles, &m_numberBlocks))
	{
		///////////////////////// Send Message ///////////////////////////////
		strResult.Format(_T("ERROR: Contents of configuration file were invalid\n"));
		m_pParent->PostMessage(WM_FIRMWARE_MSG, (WPARAM)TEXT("XML Parsing"), (LPARAM)(LPCTSTR) strResult);
#ifdef _DEBUG		
		TRACE(strResult);
#endif
		DestroyXmlTree(pRoot);
	}
	else
	{
		m_pParent->PostMessage(WM_FIRMWARE_MSG, (WPARAM)TEXT("XML Parsing"), (LPARAM)TEXT("Success to create XML Tree"));
	}

	m_pThread = ::AfxBeginThread((AFX_THREADPROC)FirmwareUpdateThreadProc, (LPVOID)this, 0, 0,  CREATE_SUSPENDED, 0);

	if( !m_pThread )
	{
		TRACE( TEXT("Cannot start Firmware Update thread!\n") );
		return FALSE;
	}

//	m_pThread->m_bAutoDelete = FALSE; 
	m_pThread->ResumeThread();


	return TRUE;
}

DWORD WINAPI CFirmwareUpdate::FirmwareUpdateThreadProc(LPVOID pParam)
{
	CString strResult;
	CFirmwareUpdate* pFirmware = static_cast<CFirmwareUpdate *>(pParam);

	pFirmware->GetParent()->SendMessage(WM_FIRMWARE_UPDATE_START);

	if(pFirmware->GetHandle())
	{
		RFID_STATUS   status;
		pFirmware->GetParent()->PostMessage(WM_FIRMWARE_MSG, (WPARAM)TEXT("Firmware Updating"), (LPARAM)TEXT("Initialize"));

		if (!pFirmware->GetSkipTestMode())
		{
			pFirmware->GetParent()->PostMessage(WM_FIRMWARE_MSG, (WPARAM)TEXT("Firmware Test Update for Radio"), (LPARAM)TEXT("Initialize"));
#ifdef _DEBUG
			TRACE(TEXT("\nTest update for radio\n"));
#endif
			
			RFID_NONVOLATILE_MEMORY_BLOCK*  pBlocks = pFirmware->GetBlocks();

			for (unsigned __int32 blockNumber = 0; blockNumber < pFirmware->GetNumberofBlocks(); ++blockNumber)
			{
				pFirmware->GetParent()->PostMessage(WM_FIRMWARE_MSG, (WPARAM)TEXT("Firmware Test Update for Radio"), (LPARAM)TEXT("Initialize"));

				strResult.Format(TEXT("Block %d:\nStart address:\t0x%.8x\nNumber of bytes:\t%u\n"), 
					blockNumber + 1, 
					pBlocks[blockNumber].address,
					pBlocks[blockNumber].length);
				pFirmware->GetParent()->PostMessage(WM_FIRMWARE_MSG, (WPARAM)TEXT("Firmware Test Update for Radio"), (LPARAM)(LPCTSTR)strResult);

#ifdef _DEBUG
				TRACE(TEXT("  Block %d:\n"), blockNumber + 1);
				TRACE(TEXT("    Start address: 0x%.8x\n"), pBlocks[blockNumber].address);
				TRACE(TEXT("    Number of bytes: %u\n"), pBlocks[blockNumber].length);
#endif
				if(RFID_STATUS_OK != 
					(status =
					RFID_MacUpdateNonvolatileMemory(
					pFirmware->GetHandle(),
					1,
					pBlocks + blockNumber,
					RFID_FLAG_NVMEM_UPDATE_TEST)))
				{
					strResult.Format(TEXT("Test Error : %s\n"), RFIDStatusToString(status)); 
					pFirmware->GetParent()->PostMessage(WM_FIRMWARE_MSG, (WPARAM)TEXT("Firmware Test Update for Radio"), (LPARAM)(LPCTSTR)strResult);

#ifdef _DEBUG
					TRACE(strResult);
#endif
//					return 0L;
				}
			}

			pFirmware->GetParent()->PostMessage(WM_FIRMWARE_MSG, (WPARAM)TEXT("Firmware Test Update for Radio"), (LPARAM)TEXT("Update Test Success"));
#ifdef _DEBUG
			TRACE(TEXT("Update Test Success"));
#endif
		}

		/* If "test mode only" was not specified, then do the real update.    */
		if (!pFirmware->GetTestOnlyMode())
		{
			strResult.Format(TEXT("WARNING - DO NOT UNPLUG RADIO DURING UPDATE !!\n"));
			pFirmware->GetParent()->PostMessage(WM_FIRMWARE_MSG, (WPARAM)TEXT("Firmware Test Update for Radio"), (LPARAM)(LPCTSTR)strResult);

#ifdef _DEBUG
			TRACE(strResult);
#endif

			if (RFID_STATUS_OK !=
				(status = RFID_MacUpdateNonvolatileMemory( pFirmware->GetHandle(),
				pFirmware->GetNumberofBlocks(),
				pFirmware->GetBlocks(),
				0)))
			{
				strResult.Format(TEXT("Test Error : %s\n"), RFIDStatusToString(status)); 
				pFirmware->GetParent()->PostMessage(WM_FIRMWARE_MSG, (WPARAM)TEXT("Firmware Test Update for Radio"), (LPARAM)(LPCTSTR)strResult);
#ifdef _DEBUG
				TRACE(strResult);
#endif
//				return 0L;
			}

			pFirmware->GetParent()->PostMessage(WM_FIRMWARE_MSG, (WPARAM)TEXT("Firmware Test Update for Radio"), (LPARAM)TEXT("\nNonvolatile memory update on radio succeeded\n"));

			TRACE(TEXT("\nNonvolatile memory update on radio succeeded\n"));

			pFirmware->GetParent()->PostMessage(WM_FIRMWARE_UPDATE_END);
			AfxGetMainWnd()->PostMessage(WM_RADIO_RESET);
		}
	}
//	::AfxEndThread(0, FALSE); 

	return 0L;
}

// CFirmwareUpdate member functions
