#include <benchmark/benchmark.h>
#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include <atomic>
#include <cassert>
#include <thread>
#include <fstream>
#include <iterator>
#include <iostream>
#include <future>
#include <queue>
#include <chrono>
#include "thread_pool.hpp"
#include "lf_queue.h"

using namespace std;
using namespace Common;

struct MyStruct {
  long d;
};


void Checksum(const std::uint32_t num, std::atomic_uint64_t* checksum)
{
    *checksum += num;
    cout<<"hello"<<endl;
}


void os_scheduler()
{

 	
 auto work = [](LFQueue<MyStruct>* lfq)
  { 
  
        while(lfq->size()) 
        {
   		 const auto d = lfq->getNextToRead();
    		lfq->updateReadIndex();

    		std::cout << "consumeFunction read elem:" << d << " lfq-size:" << lfq->size() <<endl;

    		//std::this_thread::sleep_for(1s);
  	}

  	std::cout << "consumeFunction exiting." << std::endl;     
  };	
 	
 
 
    ThreadPool thread_pool{4};
    std::queue<std::future<void>> results;
    std::atomic_uint64_t checksum{0};
    std::uint64_t localChecksum{0};
    
    
    LFQueue<MyStruct> lfq(20);
    
    std::thread t0(work, &lfq);
   	 
    t0.join();
    
    
    for(auto i = 0; i < 50; ++i) {
    const MyStruct d{i};
    *(lfq.getNextToWriteTo()) = d;
    lfq.updateWriteIndex();
    }

    for (std::uint32_t n = 0; n < 1000; ++n)
    {
        results.emplace(thread_pool.AddTask(Checksum, n, &checksum));
        localChecksum += n;
    }
    while (results.size())
    {
        results.front().get();
        results.pop();
    }
}

static void os_scheduling(benchmark::State& s) {
  while (s.KeepRunning()) {
    os_scheduler();
    
  }
}
BENCHMARK(os_scheduling)->UseRealTime()->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();


