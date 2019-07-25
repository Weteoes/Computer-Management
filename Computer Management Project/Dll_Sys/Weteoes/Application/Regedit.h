#include <Weteoes/Loading.h>

#ifdef RegeditClass_
#else
#define RegeditClass_
class RegeditClass {
public:
	struct RegeditValueArray { //ע����Զ�������-Value
		char* title;
		char* value;
		DWORD type;
		bool IsNum;  //�Ƿ�Ϊ����
		int Weteoes; //0���� 1�滻 2׷��
	};
	struct RegeditMainArray { //ע����Զ�������-�ļ���
		char* FileTitle;
		std::list<RegeditMainArray> MainArray; //�ļ���
		std::list<RegeditValueArray> ValueArray; //����
	};
	struct RegeditMainPathArray { //ע����Զ�������-Ŀ¼
		HKEY MainPath;
		char* Path;
		std::list<RegeditMainArray> MainArray; //�ļ���
		std::list<RegeditValueArray> ValueArray; //����
	};
public:
	void Loading(); //Loading
	void CreateRegedit(std::list<RegeditMainPathArray> MainPathArray); //�ݹ鴴��ע���
	void RegeditListPath(std::list<RegeditMainArray> RegeditMain, HKEY Key); //����ע���ݹ�Path
	void RegeditListValue(std::list<RegeditValueArray> RegeditValue, HKEY Key); //����ע���ݹ�Value
};
#endif // RegeditClass_
