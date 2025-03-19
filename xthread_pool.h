#ifndef XTHREAD_POOL_H
#define XTHREAD_POOL_H

#include<thread>
#include<mutex>
#include<vector>
#include<list>
#include<condition_variable>
#include<functional>
#include<atomic>
#include<future>
class XTask{
	public:
		virtual int Run()=0;
		// 函数指针
		std::function<bool()> is_exit=nullptr;

		auto GetValue(){
			return p_.get_future().get();
		}

		void SetValue(int v){
			p_.set_value(v);
		}
	private:
		// 存储运行结果
		std::promise<int> p_;
};


class XThreadPool{
	private:
		// 线程数量
		int thread_num_=0;
		std::mutex mux_;
		
		// 用于存储线程池中的线程
		// std::vector<std::thread* > threads_;
		std::vector<std::shared_ptr<std::thread>> threads_;

		// 线程池线程的入口函数
		void Run();

		// std::list<XTask* > tasks_;
		std::list<std::shared_ptr<XTask> > tasks_;

		std::condition_variable cv_;

		bool is_exit_=false;

		//正在运行的线程数量，线程安全的 
		std::atomic<int> task_run_count_={0};

	public:
		// 初始化线程数量
		void Init(int num);

		// 启动所有线程
		void Start();

		//添加任务 
		// void AddTask(XTask* task);
		void AddTask(std::shared_ptr<XTask> task);

		// 获取任务
		// XTask* GetTask();
		std::shared_ptr<XTask> GetTask();

		// 线程池的退出
		void Stop();

		// 线程池是否退出
		bool is_exit(){ return is_exit_;}

		// 
		int task_run_count(){return task_run_count_;}
		~XThreadPool(){ Stop();}
};
#endif // XTHREAD_POOL_H