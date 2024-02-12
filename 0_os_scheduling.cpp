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


void hello()
{
   std::cout<<"hello";

}


int isMagicNumber(int n) {
   int digit_sum = 0;
   while (n > 0 || digit_sum > 9) {
      if (n == 0) {
         n = digit_sum;
         digit_sum = 0;
      }
      digit_sum += n % 10;
      n /= 10;
   }
   return (digit_sum == 1);
}


int palindrome(int num)
{
     int  n, digit, rev = 0;
     

     n = num;

     do
     {
         digit = num % 10;
         rev = (rev * 10) + digit;
         num = num / 10;
     } while (num != 0);

     if (n == rev)
         return 1;
         
    return 0;
}






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
  
  auto work = [](int &a)
  {
         for(int i = 0; i < (1 << 20); i++) a++;
  };
  
  
  
  std::vector<int> magic;
  std::vector<int> palin;
  std::vector<int> tushar;
  
  for(int i = 0; i < (1 << 20); i++) 
  {
  
      int first=isMagicNumber(i);
      int second=palindrome(i);
      if(first==1)
      magic.push_back(i);
      if(second==1)
      palin.push_back(i);
      
      if(first==1 && second==1)
      tushar.push_back(i);
      
  
  }
  
  std::cout<<"list of magic numbers";
  for(int i=0;i<magic.size();i++)
  {
     std::cout<<magic[i]<<" ";
  }
  
  
    std::ofstream output_file("./example.txt");

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
