#include "xthread_pool.h"
#include<iostream>
using namespace std;


void XThreadPool::Init(int num){
	unique_lock<mutex> lock(mux_);
	this->thread_num_=num;
	cout<<"Thread Pool Init "<<thread_num_<<endl;
}


void XThreadPool::Start(){
	unique_lock<mutex> lock(mux_);
	// 判断线程是否初始化
	if(this->thread_num_<=0){
		cerr<<"Please Init XthreadPool"<<endl;
		return;
	}
	// 判断线程池是否已经启动，仅允许启动一次
	if(!threads_.empty()){
		cerr<<"thread Pool has started!"<<endl;
		return;
	}

	// 启动线程池
	for(int i=0;i<thread_num_;i++){
		auto th=new thread(&XThreadPool::Run,this);
		threads_.push_back(th);
	}
}

void XThreadPool::Run(){
	cout<<"begin XThreadPool "<<this_thread::get_id()<<endl;
	while(true){
		// 获取任务
		auto task = GetTask();
		// 判断任务是否为空
		if(task==nullptr){
			continue;
		}

		try{
			// 执行任务
			task->Run();	
		}catch(...){

		}
	}
	cout<<"end XThreadPool "<<this_thread::get_id()<<endl;
}


void XThreadPool::AddTask(XTask* task){
	unique_lock<mutex> lock(mux_);
	tasks_.push_back(task);
	// 不添加唤醒吗？
	// cv_.notify_one();
}

XTask* XThreadPool::GetTask(){
	unique_lock<mutex> lock(mux_);
	// 判断任务池是否为空
	if(tasks_.empty()){
		// 阻塞
		cv_.wait(lock);
	}
	if(tasks_.empty()){
		return nullptr;
	}
	auto task=tasks_.front();
	tasks_.pop_front();
	return task;
}