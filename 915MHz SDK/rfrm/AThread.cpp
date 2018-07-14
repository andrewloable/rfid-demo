#include "StdAfx.h"
#include "AThread.h"

namespace techwin
{
	AThread::AThread() 
	: m_hThread(NULL)
	, m_dwThreadID(0)
	, m_hStopEvent(NULL)
	, m_bDeleteMeAfterCompletion(FALSE)
	, m_bWaitForThreadToExitWhenStop(TRUE)
	{
	}

	AThread::~AThread()
	{
		Stop();
	}

	BOOL AThread::IsActive() const
	{
		DWORD dwExitCode = 0;
		
		::GetExitCodeThread(m_hThread, &dwExitCode);

		return (dwExitCode == STILL_ACTIVE);
	}
/*
	BOOL AThread::IsStopRequest() const
	{
		return m_bStopRequest;
	}
*/
	BOOL AThread::Create()
	{
		// ���� Ȯ��
		if( IsActive() ) return FALSE;

		// �̺�Ʈ ����
		m_hStopEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
		if( m_hStopEvent == NULL)
		{
			return FALSE;
		}

		// ������ ����
		m_hThread = ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, (LPVOID)this, 0/*CREATE_SUSPENDED*/, &m_dwThreadID);
		if( m_hThread == NULL )
		{
			::CloseHandle(m_hStopEvent);
			return FALSE;
		}

//		m_bStopRequest = FALSE;

		return TRUE;
	}

	BOOL AThread::Stop()
	{
//		DWORD dwRetCode;

		// �����尡 ���� ���� ������, ������ ������ ������ ��ٸ� 
		if( m_bWaitForThreadToExitWhenStop && IsActive() ) 
		{ 
			VERIFY( ::SetEvent(m_hStopEvent) ); 
			::WaitForSingleObject(m_hThread, INFINITE); 
		} 
		
		// �ڿ��� �ȴ´� 
		ResetEvent(m_hStopEvent); 
		::CloseHandle(m_hThread); 
		::CloseHandle(m_hStopEvent); 
		m_hThread    = 0; 
		m_dwThreadID = 0; 
		m_hStopEvent = NULL; 

/*
		// �����尡 ���� ���� ������, ������ ������ ������ ��ٸ�
		if( m_bWaitForThreadToExitWhenStop && IsActive() )
		{
			BOOL res = ::SetEvent(m_hStopEvent);
			assert(res);
//			::WaitForSingleObject(m_hThread, 1000);
stop:
			dwRetCode = ::WaitForSingleObject(m_hThread, 1000);

			switch(dwRetCode)
			{
			case WAIT_OBJECT_0:
				AfxMessageBox(TEXT("���� ����"));
				// the process has exited
				// �����尡 ����� �� �ؾ� �� �۾���
				// �ڿ��� �ȴ´�
				ResetEvent(m_hStopEvent);
				::CloseHandle(m_hThread);
				::CloseHandle(m_hStopEvent);
				m_hThread    = 0;
				m_dwThreadID = 0;
				m_hStopEvent = NULL;

//				m_bStopRequest = FALSE;

				return TRUE;
			case WAIT_TIMEOUT:
				AfxMessageBox(TEXT("Ÿ�Ӿƿ�"));
				// the process is still executing
				GetExitCodeThread(m_hThread, &dwRetCode);
				if (dwRetCode == STILL_ACTIVE){
					BOOL bFlag = TerminateThread(m_hThread, dwRetCode);
				}

				ResetEvent(m_hStopEvent);
				::CloseHandle(m_hThread);
				::CloseHandle(m_hStopEvent);
				m_hThread    = 0;
				m_dwThreadID = 0;
				m_hStopEvent = NULL;

//				m_bStopRequest = FALSE;

				break;
			case WAIT_FAILED:
				AfxMessageBox(TEXT("�������"));

				goto stop;
//				m_bStopRequest = FALSE;
				break;
			}

		}
*/
		return TRUE;
	}

	DWORD WINAPI AThread::ThreadProc(LPVOID lpParam)
	{
//		CoInitializeEx(NULL, COINIT_MULTITHREADED);

		AThread *pThread = static_cast<AThread *>(lpParam);

		INT res;
		if( pThread != NULL )
		{
			res = pThread->Run();
		}
		else
		{
			res = 0xFFFFFFFF;
		}

		if( pThread->m_bDeleteMeAfterCompletion )
		{
			pThread->m_bWaitForThreadToExitWhenStop = FALSE;
			delete pThread;
		}

//		CoUninitialize();

		return res;
	}

	void AThread::NotifyStop()
	{
		::SetEvent(m_hStopEvent);
	}
}