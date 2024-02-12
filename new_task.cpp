// A simple example of OS scheduling
// By: Nick from CoffeeBeforeArch

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

using namespace std;

std::vector <long> numbers;


void hello()
{

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
    
}



void os_scheduler() {
  

  // Work function for our threads
  //auto work = [](AlignedAtomic &atomic){
    //  for(int i = 0; i < (1 << 20); i++) atomic.val++;
  //};
  
  cpu_set_t cpu_set_0;
  cpu_set_t cpu_set_1;

  // Zero them out
  CPU_ZERO(&cpu_set_0);
  CPU_ZERO(&cpu_set_1);

  // And set the CPU cores we want to pin the threads too
  CPU_SET(0, &cpu_set_0);
  CPU_SET(1, &cpu_set_1);
  
  
  
  
  long a=2l;
  auto work = [](long x)
  {      
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
         
  };
  
  
  long b=3l;
  
  auto workfile = [](long x)
  {  
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
         
  };
  
  
  
  
  
   	//hello();
   	
  	
  
  
 //std::thread t0(work, std::ref(a));
  std::thread t1(workfile, std::ref(b));
  
  assert(pthread_setaffinity_np(t1.native_handle(), sizeof(cpu_set_t),
                               &cpu_set_0) == 0);
  
  //t0.join();
  
  t1.join();
  
  
  std::cout<<"i am below hwllo"<<endl;
   	std::cout<<"size of the list "<<numbers.size()<<endl;
   	for(int i=0;i<numbers.size();i++)
  	{
  		std::cout<<numbers[i]<<" ";
  	}
  	
    	ofstream fout;
	fout.open("prime_numbers_print.txt");
	for(int i=0;i<numbers.size();i++)
		fout<<numbers[i]<<endl;
	fout.close();
  
        for(int i=0;i<numbers.size();i++)
  	{
  		std::cout<<numbers[i]<<" ";
  	}
  
 // std::cout<<numbers.size();
  
  
}

// OS scheduling benchmark 
static void os_scheduling(benchmark::State& s) {
  while (s.KeepRunning()) {
    os_scheduler();
    
  }
}
BENCHMARK(os_scheduling)->UseRealTime()->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();


