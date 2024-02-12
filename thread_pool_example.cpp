#include <iostream>
#include <thread>
#include <vector>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>

class ThreadPool {
public:
    ThreadPool(int numThreads) {
        for (int i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(queueMutex);

                        // Wait for work if the task queue is empty
                        condition.wait(lock, [this] {
                            return stop || !tasks.empty();
                        });

                        if (stop && tasks.empty()) {
                            return;
                        }

                        task = tasks.front();
                        tasks.pop();
                    }

                    task(); // Execute the task
                }
            });
        }
    }

    // Add a task to the thread pool
    template <class F>
    void addTask(F&& func) {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            tasks.emplace(std::forward<F>(func));
        }
        condition.notify_one();
    }

    // Wait for all threads to finish and stop the pool
    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();

        for (std::thread& worker : workers) {
            worker.join();
        }
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable condition;

    bool stop = false;
};

int main() {
    // Create a thread pool with 4 threads
    ThreadPool pool(4);

    // Add lambda functions to the thread pool
    for (int i = 0; i < 8; ++i) {
        pool.addTask([i] {
            std::cout << "Task " << i << " executed by thread " << std::this_thread::get_id() << std::endl;
        });
    }

    // The main thread continues to execute other tasks

    // The ThreadPool destructor will wait for all tasks to complete and then join the threads

    return 0;
}

