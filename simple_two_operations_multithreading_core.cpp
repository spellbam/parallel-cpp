// This program shows off setting thread affinity
// By: Nick from CoffeeBeforeArch

#include <benchmark/benchmark.h>
#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include <atomic>
#include <cassert>
#include <thread>
#include <stdio.h>
#include <iostream>
#include <vector>

// Aligned type to avoid atomics on the same cache line


int one=0;
int two=0;
int three=0;
int four=0;
int five=0;



void thread_affinity() {
  

  // Create cpu sets for threads 0,1 and 2,3
  cpu_set_t cpu_set_0;
  cpu_set_t cpu_set_1;

  // Zero them out
  CPU_ZERO(&cpu_set_0);
  CPU_ZERO(&cpu_set_1);

  // And set the CPU cores we want to pin the threads too
  CPU_SET(0, &cpu_set_0);
  CPU_SET(1, &cpu_set_1);

  // Work function for our threads
  auto work = [](long *a)
  {
         long n=a[1];
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
      		if(a[0]==0)
      		one=1;
      		else if(a[0]==1)
      		two=1;
      		else if(a[0]==2)
      		three=1;
      		else if(a[0]==3)
      		four=1;
      		else
      		five=1;
      	}
      	
         
         
  };
  
  
  	long n=100000000019;
	long n1=100000000003;
	long n2=100123456789;
        long n3=101975911298;
        long n4=105840677923;
	//int sixth=0;
	//int third=0;
	long int a[2];
	long int b[2];
	long int c[2];
	long int d[2];
 	long int e[2];	
	a[0]=0l;
	a[1]=n;

	
	b[0]=1l;
	b[1]=n1;
	
	c[0]=2l;
	c[1]=n2;
	
	d[0]=3l;
	d[1]=n3;
	
	e[0]=4l;
	e[1]=n4;
  
  
  
  
     
  
  
  
  
  // Create thread 0 and 1, and pin them to core 0 and 1 respectively
  std::thread t0(work, std::ref(a));
  std::thread t1(work, std::ref(b));
  std::thread t2(work, std::ref(c));
  std::thread t3(work, std::ref(d));
  std::thread t4(work, std::ref(e));
  
  assert(pthread_setaffinity_np(t1.native_handle(), sizeof(cpu_set_t),
                                &cpu_set_0) == 0);
  assert(pthread_setaffinity_np(t2.native_handle(), sizeof(cpu_set_t),
                                &cpu_set_0) == 0);
                                
  
  assert(pthread_setaffinity_np(t3.native_handle(), sizeof(cpu_set_t),
                                &cpu_set_1) == 0);
  assert(pthread_setaffinity_np(t4.native_handle(), sizeof(cpu_set_t),
                                &cpu_set_1) == 0);
  
                                

  // Join the threads
 t0.join();
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  
  if(one==1)
  std::cout<<"100000000019 is prime ";
  else
  std::cout<<"100000000019 is not prime";
  
  if(two==1)
  std::cout<<"100000000003 is prime ";
  else
  std::cout<<"100000000003 is not prime";
  
  if(three==1)
  std::cout<<"1548008755920 is prime ";
  else
  std::cout<<"1548008755920 is not prime";
  
  if(four==1)
  std::cout<<"1597233891353 is prime ";
  else
  std::cout<<"1597233891353 is not prime";
  
  if(five==1)
  std::cout<<"60818091990661 is prime ";
  else
  std::cout<<"60818091990661 is not prime";
  
}

// Thread affinity benchmark
static void thread_affinity(benchmark::State& s) {
  for(auto _ : s) {
    thread_affinity();
  }
}
BENCHMARK(thread_affinity)->UseRealTime()->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
