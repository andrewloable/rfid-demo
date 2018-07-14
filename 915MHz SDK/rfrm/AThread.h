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
		// ���ο��� Stop()�� �θ�

		BOOL Create();
		// �����带 �����ϰ� ���ư��� �Ѵ�.

		BOOL Stop();
		// �����带 ������Ų��.
		// ���� ���������� �ʰ�, ������ ���� �̺�Ʈ�� �ؿ� �� ������ ������ ��ٸ��� �ȴ�.
		// (�̹� ���������� ��� �����Ѵ�)
		// �����忡�� CheckStop()�� Ȯ������ ������ ������ ��ٸ��� �ȴ�;;
		// (��Ŀ������ ���ο��� Stop()�� ����ϸ� �����尡 ������� �ʰ� ������ ��ϴ��ϴ� ������ ��)

		void NotifyStop();
		// �����带 ������Ų��.
		// ���� ���������� �ʰ�, ������ ���� �̺�Ʈ�� �ؿ�⸸ �Ѵ�. �����尡 �����⸦ ��ٸ��� �ʴ´�.
		// ��Ŀ������ ���ο��� ���������� �����ϰ� ���� ���� ����� �� �ִ�.

		virtual INT Run() = 0;
		// �� �Լ��� �������̵��ؼ� ���α׷����ϸ� �ȴ�.
		// Create()�� �ҷ��� �� ��Ŀ ������� �� �Լ��� ���۵ȴ�.

		BOOL IsActive() const;
		// �����忩, �״�� ���� ���� �ִ°�?

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

		// �ܺο��� Stop()�� �ҷ����� TRUE�� �ȴ�.
		// �����尡 ���� ���߿� �ֱ������� Ȯ���� �־�� �Ѵ�!
		BOOL CheckStop() const
		{
			return(::WaitForSingleObject(m_hStopEvent, 0) == WAIT_OBJECT_0);
		}

	private:
		void operator = ( const AThread& rhs );
		AThread( const AThread& rhs );
	};
}
