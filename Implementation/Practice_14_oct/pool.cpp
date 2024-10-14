//
// Created by Lin Kai on 14/10/24.
//


#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <bits/stdc++.h>

class ThreadPool {
public:
    ThreadPool(int max_worker_thread, int max_tasks):max_worker_thread_{max_worker_thread},
                                                     max_tasks_(max_tasks) {
        for (int i = 0; i < max_worker_thread_; ++i) {
            workers_.emplace_back([&, this]() {
                std::function<void()>task;
                for (;;) {
                    {
                        std::unique_lock<std::mutex>lk(this->mut_);
                        cv_.wait(lk, [&, this](){
                            return this->stop || !this->task_queue_.empty();
                        });
                        if (this->stop && this->task_queue_.empty()) return;
                        auto f = task_queue_.front(); task_queue_.pop();
                        task = std::move(f);

                    }

                    task();
                }

            });
        }
    }

    template <typename F, typename... Args>
    auto enqueue(F&& callable, Args... args) -> std::future<std::invoke_result_t<F, Args...>> {
        using ReturnType = std::invoke_result_t<F, Args...>;

        auto task = std::make_shared<std::packaged_task<ReturnType()>>(std::bind(std::forward<F>(callable), std::forward<Args>(args)...));

        auto ret = task->get_future();
        {
            std::lock_guard<std::mutex>lk(this->mut_);
            this->task_queue_.emplace([task]() {
                (*task)();
            });
        }
        this->cv_.notify_one();


        return ret;

    }


    ~ThreadPool() noexcept {
        {
            std::lock_guard<std::mutex>lk(this->mut_);
            stop = true;
        }
        this->cv_.notify_all();
        for (int i = 0; i< max_worker_thread_; ++i) workers_[i].join();
    }


    std::queue<std::function<void()>>task_queue_;
    bool stop = false;
    std::mutex mut_;
    std::condition_variable cv_;
    std::vector<std::thread>workers_;
    int max_worker_thread_;
    int max_tasks_;

};

int foo(int a, int b) {return a + b;}

void bar() {
    std::cout << "Hello laila!\n";
}
int main() {
    ThreadPool pool(4, 4);
    auto r = pool.template enqueue(foo, 2, 3);
    pool.template enqueue(bar);

    std::cout << r.get() << '\n';





    return 0;
}