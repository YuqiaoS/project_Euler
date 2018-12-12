#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <string>
using namespace std;


/*
int palindrome(){
	bool pali;
	int num;
	int palindrome=0;
	for(int i = 600; i<1000; i++){

		for(int j=i; j<1000; j++){
			num = i*j;
			pali = isPalindrome(convertInt(num));
			if(pali==true && palindrome < num){
				palindrome = num;
			}
		}
	}

	return palindrome;
}
*/

// palindrome
string convertInt(long long int number)
{
   stringstream su;//create a stringstream
   su << number;//add number to the stream
   return su.str();//return a string with the contents of the stream
}
// brute force from 950
bool isPalindrome(string num){
	//string pali = (string) n;
	//for(int i=0; i<n/2; i++)
	bool p = false;
	
	int i =0;
	while(num[i]==num[num.size()-1-i] && i<num.size()/2){
		if(i+1 == num.size()/2)
			p = true;
		++i;
	}
	return p;
}

long long int reverseadd(long long int number){
	long long int remainder=number, temp=number, num=number;
	int pp=0;
	int n=0,i=0;
	while(num!=0){
		num/=10;
		n++;
	}
	i=n-1;
	while(i>=0){
		//pp=pow(10,i);
		pp=(remainder%10);
		for(int j=0;j<i; j++){
			pp*=10;
		}
		temp+=pp;
		remainder/=10;
		
		i--;
		
	}
		
		//temp+=number;
	return temp;
}
	
int main(){
	long long int palin=1; 
	string temp;
	
	while(palin!=0){
		cin>>palin;
		temp=convertInt(palin);
		//cout<<"aa"<<endl;
		while(isPalindrome(temp)!=true){
			palin=reverseadd(palin);
			temp=convertInt(palin);
			//cout<<palin<<endl;
			printf("%20s \n",temp.c_str());
		}
	}
	/*
	while(palin!=0){
		cin>>palin;
		temp=convertInt(palin);
		cout<<isPalindrome(temp);
	}
	
	palin=reverseadd(123);
	cout<<palin<<endl;*/
	
	return 0;
}