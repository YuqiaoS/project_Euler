/*
string DecToBin(int number)
{
    if ( number == 0 ) return "0";
    if ( number == 1 ) return "1";

    if ( number % 2 == 0 )
        return DecToBin(number / 2) + "0";
    else
        return DecToBin(number / 2) + "1";
}


int BinToDec(string number)
{
    int result = 0, pow = 1;
    for ( int i = number.length() - 1; i >= 0; --i, pow <<= 1 )
        result += (number[i] - '0') * pow;

    return result;
}

string DecToBin2(int number)
{
    string result = "";

    do
    {
        if ( (number & 1) == 0 )
            result += "0";
        else
            result += "1";

        number >>= 1;
    } while ( number );

    reverse(result.begin(), result.end());
    return result;
}
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <string>
using namespace std;

string DecToBin(int number){
	int n=0;
	int remainder=number, rem=number;
	int power2=0;
	string binNum ="";
	
	while( number > pow(2,n)){
		n++;
	}
	
	//rem %=pow(2,n-1);
	
	for(int i=n; i>=0; i--){
		power2=pow(2,i);
		//cout<< remainder/power2<< " ";
		if(remainder/power2==1){
			rem %= power2;
			binNum +="1";
			if(rem==0){
				for(int r=0; r<i; r++){
					binNum+="0";
					//cout<< binNum<< " ";
				}
				return binNum;
			}
		}
		else{
			if(i!=n)
				binNum+="0";
		}
		remainder %= power2;
	}
	return binNum;
}
		
int collatz(int a){
	return a%2==0 ? a/2 : 3*a+1;
	
}
int main(){
	int deci= 8;
	string binNum= DecToBin(8);
	int seq= 1;
	/*
	while(deci!=0){
		cin>>deci;
		bin= DecToBin(deci);
		cout<< bin<<endl;
	}
	*/
	
	//for(int i=2; i<50; i++){
	while(seq!=0){
		cin>>seq;
		while(seq!=1&&seq!=0){
			seq=collatz(seq);
			
			//cout<<bin<<endl;
			if(seq%2!=0){
				binNum= DecToBin(seq);
				printf("%20s \n",binNum.c_str());
			}/*
			binNum= DecToBin(seq);
				printf("%20s \n",binNum.c_str());*/
		}
		
		//cout<< bin<<endl;
	}
		
	
			
		
		
	
return 0;
}