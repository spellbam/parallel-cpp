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




int isprime(long n)
{

	long  i, m=0, flag=0;   
  	if(n == 1) {
      	flag = 1;
      	std::cout<<"No";
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
      	return 1; 
      	
  	return 0;  

}

int isMagicNumber(long n) {
   long digit_sum = 0;
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


int palindrome(long num)
{
     long  n, digit, rev = 0;
     

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
  
  
  
  long n=100000000019;
  int first=isMagicNumber(n);
  int second=palindrome(n);
  int third=isprime(n);
  long n1=100000000003;
  int fourth=isMagicNumber(n1);
  int fifth=palindrome(n1);
  int sixth=isprime(n1);
  long n2=100123456789;
  int seventh=isprime(n2);
  long n3=101975911298;
  int eighth=isprime(n3);
  long n4=105840677923;
  int ninth=isprime(n4);
  
  
  
  if(sixth==1)
  std::cout<<"yes2";
  
  if(third==1)
  std::cout<<"yes";
  
  
  

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
