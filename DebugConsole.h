#pragma once

struct {
	HANDLE m_hConsole;
	FILE* m_fCout;

	HANDLE Get_HCONS() { return m_hConsole; }

	// �ܼ�â�� ����մϴ�.
	bool Get_Console()
	{
		if (!AllocConsole())
		{
			return false;
		}
		else
		{
			SetConsoleTitle(TEXT("Debug Console"));
			m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			_wfreopen_s(&m_fCout, L"CONOUT$", L"w", stdout);
			Log("Get_Console : Ok");
			return true;
		}
	}

	// �ܼ�â�� �ݽ��ϴ�.
	bool Close_Console()
	{
		if (!FreeConsole())
		{
			return false;
		}
		else
		{
			fclose(m_fCout);
		}
		return true;
	}

	// �ܼ� â�� ���ڸ� ����մϴ�.
	bool Log(const char* _log)
	{
		if (printf_s(_log) <= 0) return false;
		else
		{
			printf_s("\n");
			return true;
		}
	}
	bool Log(std::string _log)
	{
		if (printf_s(_log.c_str()) <= 0) return false;
		else
		{
			printf_s("\n");
			return true;
		}
	}
}Debug;

