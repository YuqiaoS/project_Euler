#include <cstdio>
#include <cstdlib>
#include "array.hpp"

bool isPrime(int n){
	int half=n/2;
	
	for(int i=2; i<=half; i++){
		if(n%i==0){
			return true;
		}
	}
	return false;
}

int prime(array<int> & p){
	p(0)=2;
	int length=p.n1();
	for(int i=1, n=3; i<length; i++, n+=2){
		p(i)=n;
	}
	
	for(int i=1; i<length; i++){
		if(p(i)!=0){
			for(int j=i+p(i); j<length; j+=p(i)){
				if(p(j)%p(i)==0){
					p(j)=0;
				}
			}
		}
	}
	int pos=3;
	for(int i=4; i<length; i++){
		if(p(i)!=0){
			p(pos)=p(i);
			pos++;
		}
	}
	return pos;
}

bool inPrimes(int test, array<int> & primes, int upperb){
	int length=primes.n1(),pos=0;
	
	for(int pos =0; pos<=upperb; pos++){
		if(test==primes(pos)){
			return true;
		}
		else if(test<primes(pos)){
			return false;
		}
	}
	
	printf("The number is bigger than the largest prime in the array: %d \n", test);
	return false;
}

bool matchDigits(int a, int b){
	int adigits[]={a/1000,(a/100)%10, (a/10)%10, a%10};
	int bdigits[]={b/1000,(b/100)%10, (b/10)%10, b%10};
	//bool match=false;
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(adigits[i]==bdigits[j]){
				bdigits[j]=-1;
				break;
			}
			else if(j==3){
				return false;
			}
		}
	}
			
	
	
	return true;
}
	
	
int main(){
	int digits [4] = {0};

	array<int> raw (5000);
	
	array<int> primes(5000);
	int length=prime(primes);
	int init=0;
	
	while(primes(init)<1000){
		init++;
	}
	
	int third=0;
	
	for(int i =init; i<length; i++){
		for(int j=i+1; j<length; j++){
			if(matchDigits(primes(i), primes(j))){
				third=primes(j)-primes(i)+primes(j);
				if(matchDigits(primes(i), third)&&inPrimes(third,primes, length)){
					printf("%d %d %d for match \n", primes(i), primes(j), third);	
					break;
				}
			}
		}
	}
	
	return 0;
}
	
	