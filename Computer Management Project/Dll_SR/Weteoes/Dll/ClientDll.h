#pragma once
#include <Windows.h>

class ClientDll
{
private:
	typedef bool(__stdcall *Fun1)(char*);

public:
	bool Loading();
	static Fun1 Client_Entrance; //Èë¿Ú
};
