
	/*
	vector<int> hundred;

	/* lol, this code is unnecessarily complicated,
	   it's useful to find sum of non multiples.
	
	for (int i=0; i<1000-1; i++){
		int n = i+1;
		if (n % 3 ==0 ^ n % 5 == 0){
			hundred.push_back(n);
		}
		else if (n % 3 ==0 && n % 5 == 0){
			hundred.push_back(n);
			
		}

		/* or we can subtract from total 5050 the non multiples:
		if (n%3 !=0 && n%5 !0){
			hundred.push_back(n)
			}

		
	}

	for (vector<int>::iterator i = hundred.begin();
							   i != hundred.end();
							   ++i)
	{
		cout << *i << " ";
	}

	cout << endl;

	unsigned long int s =0;
	s = std::accumulate(hundred.begin(),hundred.end(),0);
	cout << "Sum of multiples of 3 and 5 under 1000 is " <<  s << endl;
	*/
/*
void fibonacci(){
	int a =1;
	int b =2;
	int t =0;
	long int s = 0;

	vector<int> fibonacci;
	fibonacci.push_back(a);

	while(b<4000000){
		fibonacci.push_back(b);
		t = a;
		a = b;
		b = t + b;
		
	}
		for (vector<int>::iterator i = fibonacci.begin();
							   i != fibonacci.end();
							   ++i)
	{
		cout << *i << " ";
	}
	
	int num= 0;
	/* bad code. Problem with increasing pointer by 1
	for(vector<int>::iterator g = fibonacci.begin()+1; g<fibonacci.end()-1; g+=3){
		num = *g;
		
		s = s + num;
		cout << endl << s << "";
	}

	for(int i = 1; i< fibonacci.size(); i+=3)
		s = s + fibonacci[i];
	
	cout << endl << "Sum of even Fibonacci number below 4 million is " <<  s << endl;
}
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <string>
using namespace std;


vector<long long int> factors;
// the recursive function that returns a vector of factors
vector<long long int> factor(long long int n){
	
	long long int d=2;
	long long int pre_d=2;
	long long int p=1;

	long long int inc_d=0;

	while(n % d != 0){
		//d=pre_d+d;
		++d;
	}
	p= n/d;
	//pre_d=d;
	
	factors.push_back(d);

	if (d<=p)
		factor(p);

	return factors;
}

int main()
{
	/*vector<long long int> factors = factor(2205);
	//factors.erase(factors.begin(),factors.end());
	for(vector<long long int>::iterator i = factors.begin(); i != factors.end(); ++i)
		cout<< *i<< " ";
	*/	
	
	int d=2, sum=1,pre=0, count=0;
	double diff=0;
	double sqroot=0;
	
	vector<long long int> fact;

	
	for(int i=700001; i<800000; i+=2){
		d=2;
		sum=1;
		sqroot=sqrt(i);
		
		//cout<<"\n";
		for(d=2;d<=sqrt(i);d++){
			
			if(i%d==0){
				//cout<<d<<" "<<i/d<<" ";
				sum=sum+d+(i/d);
			}
		}
		if(sum>=i){
			count++;
			cout<<"\n";
			diff=(sum-i)/(double)i;
			cout<<i<<" "<<sum<<" "<<diff<<"\n";
			fact=factor(i);
			
			for(vector<long long int>::iterator t = fact.begin(); t != fact.end(); ++t){
				cout<< *t<< " "<< "";
			}
			//fact.erase(fact.begin(),fact.end());
			factors.erase(factors.begin(),factors.end());
			pre=i;
		}
		
		
		//printf("%2d %5d \n", i, sum);
	}
	cout<<count;
	cin.get();
	return 0;
}