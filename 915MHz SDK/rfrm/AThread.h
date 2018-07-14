#pragma once

namespace techwin
{
	//////////////////////////////////////////////////////////////////////////
	// Worker Thread Class #4
	// Programmed by Youngho Kim  [2007/08/09]
	//////////////////////////////////////////////////////////////////////////

	class AThread
	{
	public:
		AThread();
		virtual ~AThread();
		// 내부에서 Stop()을 부름

		BOOL Create();
		// 스레드를 생성하고 돌아가게 한다.

		BOOL Stop();
		// 스레드를 정지시킨다.
		// 강제 종료하지는 않고, 스레드 종료 이벤트를 쌔운 뒤 정지할 때까지 기다리게 된다.
		// (이미 종료했으면 즉시 리턴한다)
		// 쓰레드에서 CheckStop()을 확인하지 않으면 영원히 기다리게 된다;;
		// (워커스레드 내부에서 Stop()을 사용하면 스레드가 종료되지 않고 무한히 블록당하니 주의할 것)

		void NotifyStop();
		// 스레드를 정지시킨다.
		// 강제 종료하지는 않고, 스레드 종료 이벤트를 쌔우기만 한다. 스레드가 끝나기를 기다리진 않는다.
		// 워커스레드 내부에서 종료조건을 설정하고 싶을 때에 사용할 수 있다.

		virtual INT Run() = 0;
		// 이 함수를 오버라이드해서 프로그래밍하면 된다.
		// Create()가 불렸을 때 워커 스레드로 이 함수가 시작된다.

		BOOL IsActive() const;
		// 스레드여, 그대는 아직 돌고 있는가?

		HANDLE GetHandle() const
		{
			return m_hThread;
		}

		DWORD GetThreadID() const
		{ 
			return m_dwThreadID;
		}

		INT GetThreadPriority() const
		{ 
			return ::GetThreadPriority(m_hThread);
		}

		BOOL SetThreadPriority(INT nPriority)
		{
			return ::SetThreadPriority(m_hThread, nPriority);
		}

		DWORD ResumeThread()
		{
			return ::ResumeThread(m_hThread);
		}

		DWORD SuspendThread()
		{
			return ::SuspendThread(m_hThread);
		}

		DWORD KillThread( DWORD code )
		{
			return ::TerminateThread(m_hThread, code);
		}

		void DeleteAfterCompletion( BOOL yesno )
		{
			m_bDeleteMeAfterCompletion = yesno;
		}

//		BOOL IsStopRequest() const;

	public:
		HANDLE		m_hThreadCallEvent;

	protected:
		DWORD		m_dwThreadID;
		HANDLE		m_hThread;
		HANDLE		m_hStopEvent;
//		BOOL		m_bStopRequest;

		BOOL        m_bDeleteMeAfterCompletion;
		BOOL        m_bWaitForThreadToExitWhenStop;

		static DWORD WINAPI ThreadProc(LPVOID lpParam);

		// 외부에서 Stop()을 불렀으면 TRUE가 된다.
		// 스레드가 도는 도중에 주기적으로 확인해 주어야 한다!
		BOOL CheckStop() const
		{
			return(::WaitForSingleObject(m_hStopEvent, 0) == WAIT_OBJECT_0);
		}

	private:
		void operator = ( const AThread& rhs );
		AThread( const AThread& rhs );
	};
}
