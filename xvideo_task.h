#include "xthread_pool.h"

class XVideoTask:public XTask{
public:
	std::string in_path;
	std::string out_path;
	int width;
	int height;
private:
	int Run();
};