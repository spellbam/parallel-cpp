
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

std::vector <long> numbers;

int endfile=0;


//For storing a structure in a lock free queue
struct MyStruct {
  long d;
};


void isPrime(long n)
{
	std::cout<<"i am in prime number function checking the primess for "<< n <<endl;
        long  i, m=0, flag=0;   
  	if(n == 1) {
      	flag = 1;
      	//std::cout<<"No";
  	}
  	for(i = 2; i <= n/2; i++)  
  	{  
      		if(n % i == 0)  
      		{	  
          		//cout<<"NO"<<endl;  
          		flag=1;  
          		break;  
      		}  
  	}  
  	if (flag==0)  
      	{
      		std::cout<<"this number is prime "<< n<<endl;
      	}

}



void os_scheduler() {
  
  auto work = [](LFQueue<MyStruct>* lfq)
  { 
  
  	 ThreadPool thread_pool{50};
         std::queue<std::future<void>> results;
  	//std::this_thread::sleep_for(5s);
  	std::cout<<"i am in thread"<<endl;
        while(lfq->size()) 
        {
   		// const auto d = lfq->getNextToRead();
   		 //long d = (long) lfq->getNextToRead();
   		 const MyStruct* ptr = lfq->getNextToRead(); 
                 long dAsLong = static_cast<long>(ptr->d);
    		lfq->updateReadIndex();
    		
    		
    		
    		results.emplace(thread_pool.AddTask(isPrime,dAsLong));

    		std::cout << "consumeFunction read elem:" << dAsLong << " lfq-size:" << lfq->size() <<endl;

    		//std::this_thread::sleep_for(1s);
  	}
  	

  	std::cout << "consumeFunction exiting." << std::endl;
  	
  	
  	while (results.size())
        {
            results.front().get();
            results.pop();
        }
  	
  	
  	
  	     
  };
  
  	    //hello();
   	    
   	    
   	    
   	     LFQueue<MyStruct> lfq(20);
   	     
   	     
   	     // Create cpu sets for threads 0,1 and 2,3
		  cpu_set_t cpu_set_0;
		  cpu_set_t cpu_set_1;

		  // Zero them out
		  CPU_ZERO(&cpu_set_0);
		  CPU_ZERO(&cpu_set_1);

		  // And set the CPU cores we want to pin the threads too
		  CPU_SET(0, &cpu_set_0);
		  CPU_SET(1, &cpu_set_1);
   	    
   	    
   	     std::thread t0(work, &lfq);
   	     
   	     assert(pthread_setaffinity_np(t0.native_handle(), sizeof(cpu_set_t),
                                &cpu_set_0) == 0);
   	 
   	    
   	     
   	     
   	     std::fstream FileName; 
	    int flag=0;                  
	    FileName.open("prime_numbers.txt");         
	    if (!FileName) {                        
		std::cout<<"File doesn’t exist.";          
	    }
	    else {
		long x;                     
		while (1) {         
		    FileName>>x;              
		    if(FileName.eof()) 
		    {
		    	flag=1;         
		        break;
		    }              
		    std::cout<<x<<"number from file"<<endl;;  
		    numbers.push_back(x);
		    const MyStruct d{x};
   		    *(lfq.getNextToWriteTo()) = d;
    		    lfq.updateWriteIndex();
		    std::cout<<"numbers in the list "<<endl;
		    for(int i=0;i<numbers.size();i++)
		    {
		       std::cout<<numbers[i]<<" ";
		    }  
		    std::cout<<endl;              
		}
	    }
	    getchar();
	    FileName.close(); 
	    std::cout<<"size of list "<<numbers.size()<<endl;
	    
	    
   	    t0.join();
   	    std::cout<<"size of lfq queue"<< lfq.size() <<endl;
   	     
   	     
   	
}


// OS scheduling benchmark 
static void os_scheduling(benchmark::State& s) {
  while (s.KeepRunning()) {
    os_scheduler();
    
  }
}
BENCHMARK(os_scheduling)->UseRealTime()->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();


