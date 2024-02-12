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

// Aligned type to avoid atomics on the same cache line
//struct AlignedAtomic {
  //alignas(64) std::atomic<int> val = 0;
//};


  std::vector<int> magic;
  std::vector<int> palin;
  std::vector<int> tushar;
  int k[2];
  int p[2];


void os_scheduler() {
  // Aligned atomics
  //AlignedAtomic a;
  //AlignedAtomic b;

  int a =3;
  int b=2;

  // Work function for our threads
  //auto work = [](AlignedAtomic &atomic){
    //  for(int i = 0; i < (1 << 20); i++) atomic.val++;
  //};
  
  auto work = [](int *a)
  {
  	
  	int ch=a[0];
  	//std::cout<<"i am here";
  	if (ch==1)
  	{
  	   int n=a[1];
  	   int digit_sum = 0;
  	   while (n > 0 || digit_sum > 9) 
  	   {
          	if (n == 0) 
          	{
          		n = digit_sum;
          		digit_sum = 0;
          	}
          	digit_sum += n % 10;
          	n /= 10;
      	   }
          if(digit_sum == 1)	
  	   magic.push_back(n);	
  	
  	}
  	
  	else if(ch==2)
  	{
  	   int num=a[1];
  	   int  n, digit, rev = 0;
     	   n = num;
     	   do
    	   {
         	digit = num % 10;
         	rev = (rev * 10) + digit;
         	num = num / 10;
     	   } 	while (num != 0);

     	  if (n == rev)
          palin.push_back(num);
  	
  	
  	}
  	
         
  };
  
  
  
 
  for(int i = 0; i < (1 << 20); i++) 
  {
      k[0]=1;
      k[1]=i;
      int magic_size=magic.size();
      int palin_size=palin.size();
      std::thread t0(work, std::ref(k));
      p[0]=2;
      p[1]=i;
      std::thread t1(work, std::ref(p));
      
      t0.join();
      t1.join();
      
       if((magic.size()==(magic_size+1)) && (palin.size()==(palin_size+1)))
      tushar.push_back(i);
      
      
  
  }
  
  std::cout<<"list of magic numbers";
  for(int i=0;i<magic.size();i++)
  {
     std::cout<<magic[i]<<" ";
  }
  
  
    std::ofstream output_file("./example2.txt");

    std::ostream_iterator<int> output_iterator(output_file, "\n");
    std::copy(std::begin(tushar), std::end(tushar), output_iterator);
  
  std::cout<<"list of tushar numbers";
  for(int i=0;i<tushar.size();i++)
  {
    std::cout<<tushar[i]<<" ";
  }
  
  
  

   //hello();

  // Create four threads and use lambda to launch work
  //std::thread t0(work, std::ref(a));
 // std::thread t1(work, std::ref(a));
 // std::thread t2(work, std::ref(b));
 // std::thread t3(work, std::ref(b));

  // Join the threads
  //t0.join();
  //t1.join();
  //t2.join();
  //t3.join();
}

// OS scheduling benchmark 
static void os_scheduling(benchmark::State& s) {
  while (s.KeepRunning()) {
    os_scheduler();
  }
}
BENCHMARK(os_scheduling)->UseRealTime()->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
