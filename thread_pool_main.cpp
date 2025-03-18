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
			for(int i=0;i<10;i++){
				if(is_exit()){
					break;
				}
				cout<<"."<<flush;
				this_thread::sleep_for(500ms);
			}
			return 0;
		}
	string name;
};


int main(){

	XThreadPool pool;
	pool.Init(16);
	pool.Start();

	// MyTask task1;
	// task1.name="Test name 001";
	// pool.AddTask(&task1);
	
	// MyTask task2;
	// task2.name="Test name 002";
	// pool.AddTask(&task2);
	// this_thread::sleep_for(1s);
	
	//智能指针版本 
	shared_ptr<MyTask> task3 = make_shared<MyTask>();
	task3->name="test shared 003";
	pool.AddTask(task3);

	shared_ptr<MyTask> task4 = make_shared<MyTask>();
	task4->name="test shared 004";
	pool.AddTask(task4);
	int result=task4->GetValue();
	cout<<"task4.GetValue() return = "<<result<<endl;


	this_thread::sleep_for(3s);
	pool.Stop();
	cout<<"task running count :"<<pool.task_run_count()<<endl;
	return 0;
}