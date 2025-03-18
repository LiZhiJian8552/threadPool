#include "xthread_pool.h"
#include<iostream>
#include<string>
using namespace std;


class MyTask:public XTask{
	public:
		int Run() override{
			cout<<"===================="<<endl;
			cout<<this_thread::get_id()<<" MyTask "<<name<<endl;
			cout<<"===================="<<endl;
			return 0;
		}
	string name;
};


int main(){

	XThreadPool pool;
	pool.Init(16);
	pool.Start();

	MyTask task1;
	task1.name="Test name 001";

	pool.AddTask(&task1);
	getchar();
	return 0;
}