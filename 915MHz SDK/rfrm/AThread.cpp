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
		// 동작 확인
		if( IsActive() ) return FALSE;

		// 이벤트 생성
		m_hStopEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
		if( m_hStopEvent == NULL)
		{
			return FALSE;
		}

		// 스레드 생성
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

		// 스레드가 아직 돌고 있으면, 완전히 정지할 때까지 기다림 
		if( m_bWaitForThreadToExitWhenStop && IsActive() ) 
		{ 
			VERIFY( ::SetEvent(m_hStopEvent) ); 
			::WaitForSingleObject(m_hThread, INFINITE); 
		} 
		
		// 자원을 걷는다 
		ResetEvent(m_hStopEvent); 
		::CloseHandle(m_hThread); 
		::CloseHandle(m_hStopEvent); 
		m_hThread    = 0; 
		m_dwThreadID = 0; 
		m_hStopEvent = NULL; 

/*
		// 스레드가 아직 돌고 있으면, 완전히 정지할 때까지 기다림
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
				AfxMessageBox(TEXT("종료 성공"));
				// the process has exited
				// 쓰레드가 종료된 후 해야 할 작업들
				// 자원을 걷는다
				ResetEvent(m_hStopEvent);
				::CloseHandle(m_hThread);
				::CloseHandle(m_hStopEvent);
				m_hThread    = 0;
				m_dwThreadID = 0;
				m_hStopEvent = NULL;

//				m_bStopRequest = FALSE;

				return TRUE;
			case WAIT_TIMEOUT:
				AfxMessageBox(TEXT("타임아웃"));
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
				AfxMessageBox(TEXT("종료실패"));

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