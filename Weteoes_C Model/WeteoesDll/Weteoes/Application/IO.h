#ifdef IOClass_
#else
#define IOClass_
#include <Loading.h>
#include <io.h>

class IOClass
{
public:
	void WriteFile(char* file, char* data);
	char* ReadFile(char* file);
	void CreatePath(char* file);
	bool Exists(char* file);
	void Remove(char* file);
private:

};

#include <fstream>
#include <Shlwapi.h>
#pragma comment(lib,"Shlwapi.lib")

//App
#include <Application/Convert.h>

void IOClass::WriteFile(char* file, char* data) {
	CreatePath(file);
	ofstream a(file, ios::app | ios::out);
	a << data;
	a.close(); a.clear();
}
char* IOClass::ReadFile(char* file) {
	if (!PathFileExists(file)) {
		return NULL;
	}
	ifstream a(file);
	string resultS = "",tempS;
	while (getline(a, tempS)) { resultS += tempS; }
	a.close(); a.clear();
	char *result = ConvertClass().GetChars(resultS);
	return result;
}
void IOClass::CreatePath(char* File) {
	int i = 0;
	string SFile = File;
	while (true)
	{
		int ii = (int)SFile.find("\\", i + 1);
		if (ii < i) { break; }
		else { i = ii; }
		string a = SFile.substr(0, i);
		if (!Exists((char*)a.c_str())) {
			CreateDirectory(a.c_str(), NULL);
		}
	}
}
bool IOClass::Exists(char* Path) {
	if (PathFileExists(Path)) {
		return true;
	}
	return false;
}
void IOClass::Remove(char* File) {
	if (Exists(File)) {
		remove(File);
	}
}
#endif //IOClass_