#include <Weteoes/Loading.h>

#ifdef RegeditClass_
#else
#define RegeditClass_
class RegeditClass {
public:
	struct RegeditValueArray { //注册表自定义类型-Value
		char* title;
		char* value;
		DWORD type;
		bool IsNum;  //是否为数字
		int Weteoes; //0跳过 1替换 2追加
	};
	struct RegeditMainArray { //注册表自定义类型-文件夹
		char* FileTitle;
		std::list<RegeditMainArray> MainArray; //文件夹
		std::list<RegeditValueArray> ValueArray; //内容
	};
	struct RegeditMainPathArray { //注册表自定义类型-目录
		HKEY MainPath;
		char* Path;
		std::list<RegeditMainArray> MainArray; //文件夹
		std::list<RegeditValueArray> ValueArray; //内容
	};
public:
	void Loading(); //Loading
	void CreateRegedit(std::list<RegeditMainPathArray> MainPathArray); //递归创建注册表
	void RegeditListPath(std::list<RegeditMainArray> RegeditMain, HKEY Key); //用于注册表递归Path
	void RegeditListValue(std::list<RegeditValueArray> RegeditValue, HKEY Key); //用于注册表递归Value
};
#endif // RegeditClass_
