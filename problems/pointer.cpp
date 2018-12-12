#include <stdio.h>

int* primes(){
	int  primes[]={10,2};
	int * pointer;
	return pointer*; //wrong:can't return primes;
}

int main(){
	//int * prime=primes();
	int * prime;
	int p[1+1]={8,9};
	prime=p; // pointer = array; array!= pointer-->   p!=prime;
	printf("prime 1 is %d", prime[0]); // prime[0] = *p; prime[x] = *(p+x);
	
	/*(
	int * p1, * p2;
	int firstvalue=2, secondvalue=4,t1=0, t2=0;
	p1= &firstvalue;
	firstvalue=3;
	p2=&secondvalue;
	*p2 = *p1;
	int prime[5];
	t1=*p1;
	t2=*p2;
	
	printf("prime 1 is %d %d", *p1, t2 );
	*/
	
	
	int firstvalue = 5, secondvalue = 15;
  int * p1, * p2;

  p1 = &firstvalue;  // p1 = address of firstvalue
  p2 = &secondvalue; // p2 = address of secondvalue
  *p1 = 10;          // value pointed to by p1 = 10
  *p2 = *p1;         // value pointed to by p2 = value pointed by p1
  p1 = p2;           // p1 = p2 (value of pointer is copied)
  *p1 = 20;          // value pointed by p1 = 20
  
  cout << "firstvalue is " << firstvalue << '\n';
  cout << "secondvalue is " << secondvalue << '\n';
  return 0;
	
}