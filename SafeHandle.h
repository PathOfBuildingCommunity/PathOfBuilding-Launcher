#pragma once

class SafeHandle
{
public:
	SafeHandle() noexcept : m_hHandle(INVALID_HANDLE_VALUE) {}
	SafeHandle(HANDLE hHandle) noexcept : m_hHandle(hHandle) {}
	SafeHandle(const SafeHandle &o) = delete;
	SafeHandle(SafeHandle &&o) noexcept : m_hHandle(o.m_hHandle)
	{
		o.m_hHandle = INVALID_HANDLE_VALUE;
	}

	~SafeHandle() noexcept
	{
		Close();
	}

	SafeHandle &operator =(const SafeHandle &o) = delete;
	SafeHandle &operator =(SafeHandle &&o) noexcept
	{
		m_hHandle = o.m_hHandle;
		o.m_hHandle = INVALID_HANDLE_VALUE;
	}
	SafeHandle &operator =(HANDLE hHandle) noexcept
	{
		m_hHandle = hHandle;
	}

	bool IsValid() noexcept { return m_hHandle != INVALID_HANDLE_VALUE; }
	HANDLE Get() noexcept { return m_hHandle; }
	void Close() noexcept
	{
		if (IsValid())
		{
			CloseHandle(m_hHandle);
			m_hHandle = INVALID_HANDLE_VALUE;
		}
	}

private:
	HANDLE m_hHandle = INVALID_HANDLE_VALUE;
};
