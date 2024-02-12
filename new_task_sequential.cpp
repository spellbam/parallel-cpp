

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
  
   	hello();
   	
  
  
  std::cout<<"i am below hello"<<endl;
   	std::cout<<"size of the list "<<numbers.size()<<endl;
   	for(int i=0;i<numbers.size();i++)
  	{
  		std::cout<<numbers[i]<<" ";
  		isPrime(numbers[i]);
  	}
  	  
}

// OS scheduling benchmark 
static void os_scheduling(benchmark::State& s) {
  while (s.KeepRunning()) {
    os_scheduler();
    
  }
}
BENCHMARK(os_scheduling)->UseRealTime()->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();


