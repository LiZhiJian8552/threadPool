#include "xthread_pool.h"
#include<iostream>
#include<string>
#include"xvideo_task.h"
using namespace std;


// 命令行视频转化工具
//ffmpeg
//输入视频源，输出视频尺寸
//在线程池中执行转码任务
//转码任务调用ffmepg
//ffmpeg -y -i test.mp4 -s 400x300 400.mp4 >log.txt 2>&1


int main(){

	XThreadPool pool;
	pool.Init(16);
	pool.Start();

	// auto vtask1 =make_shared<XVideoTask>();
	// vtask1->in_path="test.mp4";
	// vtask1->out_path="640.mp4";
	// vtask1->width=640;
	// vtask1->height=480;

	// pool.AddTask(vtask1);
	// vtask1->GetValue();

	this_thread::sleep_for(200ms);
	for(;;){
		this_thread::sleep_for(200ms);
		cout<<"==================================="<<endl;
		auto task =make_shared<XVideoTask>();
		cout<<"请输入命令(v e l): ";
		string cmd;
		cin>>cmd;
		if(cmd=="e"){
			break;
		}else if(cmd=="l"){
			cout<<"task run count = "<<pool.task_run_count()<<endl;
			continue;
		}else{
			cout<<"请输入视频源： ";
			cin>>task->in_path;
			// cout<<task->in_path;
			cout<<"目标： ";
			cin>>task->out_path;
			cout<<"输入宽：";
			cin>>task->width;
			cout<<"输入高：";
			cin>>task->height;
			pool.AddTask(task);
		}
	}
	pool.Stop();

	return 0;
}