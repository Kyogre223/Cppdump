//
// Created by Lin Kai on 9/9/24.
//

#ifndef CPPDUMP_POOL_H
#define CPPDUMP_POOL_H


#include <bits/stdc++.h>

// threadpool imeplmentation

struct ThreadPool {
    std::vector<std::thread>workers_;
    int num_workers_;
    int max_tasks_;
    std::condition_variable cv_;
    std::mutex mutex_;
    bool stop = false;
    std::queue<std::function<void()>>queue_;

    ThreadPool(int num_workers, int max_tasks) {
        num_workers_ = num_workers;
        max_tasks_ = max_tasks;
        for (int i = 0; i < num_workers_; ++i) {
            this->workers_.emplace_back([&, this](){
                for (;;) {
                    std::function<void()>task;
                    {
                        std::unique_lock<std::mutex>lk(this->mutex_);
                        this->cv_.wait(lk, [&, this](){
                            return stop || !this->queue_.empty();
                        });
                        if (this->queue_.empty()) return;
                        auto f = queue_.front(); queue_.pop();
                        task = std::move(f);
                    }
                    task();
                }

            });
        }

    }

    template <typename F, typename... Args>
    auto enqueue(F&& f, Args... args) ->std::future<std::invoke_result_t<F, Args...>> {
        using ReturnType = std::invoke_result_t<F, Args...>;
        std::future<ReturnType> ret;
        auto task = std::make_shared<std::packaged_task<ReturnType()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        ret = task->get_future();
        {
            std::unique_lock lk(this->mutex_);
            this->queue_.push([task](){
                (*task)();
            });
        }
        return ret;
    }

    ~ThreadPool() noexcept {
        {
            std::lock_guard<std::mutex>lk(this->mutex_);
            stop = true;
        }
        this->cv_.notify_all();
        for (int i = 0; i < workers_.size(); ++i) {
            workers_[i].join();

        }
    }


};


int foo(int x, int y) {

    return x + y;
}

void bar() {
    std::cout << "BAR BAR BLACKSHEEP!\n";
}


#endif //CPPDUMP_POOL_H
