#include <cstdio>
#include <cstdlib>
#include "array.hpp"

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

int quadratic(int a, int b, int n){
	return n*n+a*n+b;
}

void initArray(array<int> & old, array<int> & init, int length){
	for(int i=0; i<=length; i++){
		init(i)=old(i);
	}
}
	
bool inPrimes(int test, array<int> & primes){
	int length=primes.n1(),pos=0;
	
	for(int pos =0; pos<length; pos++){
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

int main(){
	//int * prime=primes();
	int plength=10000;
	int length=0;
	array<int> rawNums(10000);

	
	plength=prime(rawNums);

	array<int> primes(plength);
	initArray(rawNums, primes, plength);

	int maxN=0, maxprime=0, maxa=0, maxb=0;
	int a=-1000,b=-1000,n=0,pos=0,eval=0;

	for(a=-999; a<1000; a++){
		
		for(b=-999; b<1000; b++){
			//pos=0;
			n=0;
			eval=quadratic(a, b, n);
			
			while(eval>1){
				if(inPrimes(eval,primes)){
					eval=quadratic(a, b, n);
					n++;
					//printf("Evaluated: %d %d %d %d\n", a, b, n, eval);
				}
				else
					break;
			}
			if(n-1>maxN){
				maxN=n-1;
				maxa=a;
				maxb=b;
				printf("Greatest number of consecutive  primes: %i %d %d\n", maxN, maxa, maxb);
			}
		}
	}
	printf("Greatest number of consecutive  primes: %i %d %d\n", quadratic(maxa, maxb,maxN+1), maxa, maxb);
	
	// To see the primes: 
	/*
	for(int n=0; n<maxN; n++){
		printf("Primes: %d %d\n", n, quadratic(maxa,maxb,n));
	}
	*/
		
}