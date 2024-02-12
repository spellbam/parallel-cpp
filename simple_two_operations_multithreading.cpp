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

// Aligned type to avoid atomics on the same cache line
//struct AlignedAtomic {
  //alignas(64) std::atomic<int> val = 0;
//};


int one=0;
int two=0;
int three=0;
int four=0;
int five=0;

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

  //int a =3;
  //int b=2;

  // Work function for our threads
  //auto work = [](AlignedAtomic &atomic){
    //  for(int i = 0; i < (1 << 20); i++) atomic.val++;
  //};
  
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
  
  
  
  std::vector<int> magic;
  std::vector<int> palin;
  std::vector<int> tushar;
  
  
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
  
       
  
 // long n=100000000019;
 //  int first=isMagicNumber(n);
 // int second=palindrome(n);
 // int third=isprime(n);
 // long n1=100000000003;
 // int fourth=isMagicNumber(n1);
 // int fifth=palindrome(n1);
 // int sixth=isprime(n1);
  
  std::thread t0(work, std::ref(a));
  std::thread t1(work, std::ref(b));
  std::thread t2(work, std::ref(c));
  std::thread t3(work, std::ref(d));
  std::thread t4(work, std::ref(e));
  
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
