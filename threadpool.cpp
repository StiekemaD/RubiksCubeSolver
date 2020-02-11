#include "threadpool.h"

ThreadPool::ThreadPool(size_t threads) : stop_running(false)
{
    unsigned int check_threads = std::thread::hardware_concurrency();

    if(threads > check_threads && check_threads != 0) {
        threads = check_threads;
    }
    
    for(size_t i = 0; i < threads; ++i) {
        workers.push_back(std::thread(&ThreadPool::doWork, this));
    }
}
/*
template<class F, class... Args>
auto ThreadPool::addWork (F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>
{
   using return_type = typename std::result_of<F(Args...)>::type;
   auto task = std::make_shared<std::packaged_task<return_type()>>(
       std::bind(std::forward<F>(f), std::forward<Args>(args)...));

   std::future<return_type> res = task->get_future();
   {
       std::unique_lock<std::mutex> lock(queue_mutex);
       if(stop_running) {
           throw std::runtime_error("enqueue on stopped Threadpool");
       }

       tasks.emplace([task](){ (*task)(); });
   }
   c_v.notify_one();
   return res;
}
*/
void ThreadPool::addWork(Task task)
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if(stop_running) {
            return;
        }
        tasks.emplace(task);
    }
    c_v.notify_one();
}

void ThreadPool::doWork()
{
    std::unique_lock<std::mutex> ul(queue_mutex);
    while(!quit)
    {
        if(!tasks.empty() && !stop_running) {
            Task task = tasks.front();
            this->tasks.pop();
            ul.unlock();
            task.function(task.path);
            ul.lock();
        } else {
            c_v.wait(ul);
        }
    }
}

void ThreadPool::abort()
{
    if(quit)
        return;
    {
        std::lock_guard<std::mutex> lg(queue_mutex);
        quit = true;
    }
    c_v.notify_all();
    for(std::thread &worker : workers)
    {
        worker.join();
    }
    clearTasks();
}

Task::Task(Function f, Path p):
    path(p)
{
    function = f;
}
