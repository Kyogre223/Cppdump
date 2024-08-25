//
// Created by Lin Kai on 25/8/24.
//

#ifndef CPPDUMP_THREAD_POOL_H
#define CPPDUMP_THREAD_POOL_H


#include <memory>
#include <unistd.h>
#include <iostream>
#include <any>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <functional>
#include <vector>
#include <future>


struct ThreadPool {
    int num_threads_;
    int max_tasks_;
    std::mutex mut_;
    bool stop = false;
    std::vector<std::thread>threads_;
    std::condition_variable cv_;
    std::queue<std::function<void()>>task_queue_;

    ThreadPool(int numThreads, int maxTasks):
            num_threads_(numThreads),
            max_tasks_(maxTasks) {
        for (int i = 0; i < num_threads_; ++i) {
            threads_.emplace_back([&, this]() {
                for (;;) {
                    std::function<void()>task;
                    {
                        std::unique_lock<std::mutex>lk(this->mut_);
                        this->cv_.wait(lk, [&, this](){
                            return this->stop || !this->task_queue_.empty();
                        });
                        if (this->stop || this->task_queue_.empty()) return;
                        auto f = this->task_queue_.front(); this->task_queue_.pop();
                        task = std::move(f);

                    }
                    task();
                }
            });
        }

    }
    ThreadPool(ThreadPool const& other) = delete; // delete copy constructor
    ThreadPool& operator = (ThreadPool const& other) = delete; // delete copy assignment

    // enqueue
    template <typename F, typename... Args>
    auto enqueue(F&& f, Args... args)->std::future<std::invoke_result_t<F, Args...>> {
        using Ret = std::invoke_result_t<F, Args...>;
        std::future<Ret> res;
        auto task = std::make_shared<std::packaged_task<Ret()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        res = task->get_future();
        {
            // enqueue the task
            std::unique_lock<std::mutex>lk(this->mut_);
            this->task_queue_.emplace([task](){(*task)();});

        }
        this->cv_.notify_one();

        return res;
    }
    ~ThreadPool() {
        {
            std::unique_lock<std::mutex>lk(this->mut_);
            this->stop = true;
        }
        this->cv_.notify_all();
        for (int i = 0; i < num_threads_; ++i) this->threads_[i].join();
    }

};

int add(int x, int y) {
    std::cout << "inside add!\n";

    return x + y;
}

int minus(int x, int y) {
    std::cout << "inside minus!\n";

    return x - y;
}


#endif //CPPDUMP_THREAD_POOL_H
