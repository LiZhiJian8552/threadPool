#include<thread>
#include<mutex>
#include<vector>
#include<list>
#include<condition_variable>



class XTask{
public:
	virtual int Run()=0;
};


class XThreadPool{
	private:
		// 线程数量
		int thread_num_=0;
		std::mutex mux_;
		// 用于存储线程池中的线程
		std::vector<std::thread* > threads_;
		// 线程池线程的入口函数
		void Run();

		std::list<XTask* > tasks_;

		std::condition_variable cv_;

		bool is_exit_=false;

	public:
		// 初始化线程数量
		void Init(int num);

		// 启动所有线程
		void Start();

		//添加任务 
		void AddTask(XTask* task);
		// 获取任务
		XTask* GetTask();

		// 线程池的退出
		void Stop();

		// 线程池是否退出
		bool is_exit(){ return is_exit_;}
};