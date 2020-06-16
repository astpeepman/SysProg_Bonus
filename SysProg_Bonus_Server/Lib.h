#include <afxsock.h>
#include <iostream>
#include <thread>
#include <vector>


using namespace std;

struct messHeader {
	int adress;
	int code;
	int count;
	int size;
};

int Flag;
HANDLE hPipe;
CSocket s;
CSocket Server;


void FlagThread0() {
	ConnectNamedPipe(hPipe, NULL);
	DWORD dwRead;
	int buff;

	ReadFile(hPipe, &buff, sizeof(int), &dwRead, nullptr);

	Flag = buff;
	if (buff == 0) {
		cout << "App connected with Named Pipe" << endl;

		CSocket Local;
		Local.Create();
		Local.Connect("127.0.0.1", 11111);
		Local.Send(&buff, sizeof(int));
		Local.Close();
		return;
	}

	if (buff == 1) {
		DisconnectNamedPipe(hPipe);
		//CloseHandle(hPipe);
		return;
	}
}

void FlagThread1() {

	int buff;

	s.Receive(&buff, sizeof(int));

	Flag = buff;
	if (buff == 1) {
		cout << "App connected with Windows Socket" << endl;

		HANDLE hLocalPipe = CreateFile("\\\\.\\pipe\\MyPipe", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		DWORD dwWrite;
		WriteFile(hLocalPipe, &buff, sizeof(int), &dwWrite, nullptr);
		CloseHandle(hLocalPipe);
		return;
	}
	if (buff == 0) {
		s.Close();
		//Server.Close();
		return;
	}
}

bool CreatePipe()
{
	hPipe = CreateNamedPipe("\\\\.\\pipe\\MyPipe",
		PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES,
		4096, 4096, 0, NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		return false;
	}

}

extern "C" __declspec(dllexport) bool __stdcall initAll() {
	Flag = -1;

	//Ñîêåòû
	AfxSocketInit();

	Server.Create(11111);

	//ÊÀÍÀËÛ
	if (!CreatePipe()) {
		return false;
	}
}

extern "C" __declspec(dllexport) messHeader __stdcall ReadyHeader() {
	thread t1(FlagThread0);
	t1.detach();

	Server.Listen();
	Server.Accept(s);
	FlagThread1();

	messHeader m;

	switch (Flag) {
	case 0: {
		DWORD dwRead;
		ReadFile(hPipe, &m, sizeof(m), &dwRead, NULL);
		break;
	}
	case 1: {
		s.Receive(&m, sizeof(messHeader));
		break;
	}
	}

	return m;
}


string GetMess_Pipe(int size) {
	DWORD dwRead;
	std::string buff(size, ' ');
	ReadFile(hPipe, &buff[0], size, &dwRead, nullptr);
	return buff;
}

string GetMess_Sock(int size) {
	if (size <= 0) {
		cout << "ERROR :: Failed to receive message :: ERROR";
		return string("");
	}
	vector <char> v(size);
	s.Receive(&v[0], size);
	return string(&v[0], size);
}

void SetConfirm() {
	DWORD dwWrite;
	bool ok = true;
	WriteFile(hPipe, &ok, sizeof(bool), &dwWrite, nullptr);
}


extern "C" __declspec(dllexport) string __stdcall GetMessageFromApp(int size) {
	string Message;
	switch (Flag) {
	case 0: {
		SetConfirm();
		Message = GetMess_Pipe(size);
		break;
	}
	case 1: {
		Message = GetMess_Sock(size);
		break;
	}
	}

	return Message;
}

extern "C" __declspec(dllexport) void __stdcall SendThreadCount(int vectsize) {
	switch (Flag) {
	case 0: {
		DWORD dwWrite;
		WriteFile(hPipe, &vectsize, sizeof(int), &dwWrite, nullptr);
		DisconnectNamedPipe(hPipe);
		break;
	}
	case 1: {
		s.Send(&vectsize, sizeof(int));
		s.Close();
		break;
	}
	}
}