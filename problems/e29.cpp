#include <cstdio>

int main(){
	int numbers2 [600]={0}, numbers3 [600]={0};;
	int length2=0,length3=0, value=1, pos=0;
	
	for(int i=1; i<=6; i++){
		for(int j=2; j<=100; j++){
			value=i*j;
			pos=0;
			while(value!=numbers2[pos]&&pos<length2){
				pos++;
			}			
			if(pos==length2){
				numbers2[pos]=value;
				length2++;
			}
		}
	}
	
	length3=0;
	for(int i=1; i<=4; i++){
		for(int j=2; j<=100; j++){
			value=i*j;
			pos=0;
			while(value!=numbers3[pos]&&pos<length3){
				pos++;
			}			
			if(pos==length3){
				numbers3[pos]=value;
				length3++;
			}
		}
	}
	
	for(int i=0; i<length2; i++){
		printf("%d ", numbers2[i]);
	}
	
	printf("\n Number of powers of 2 and 3: %d, %d ", length2, length3);
	
	printf("\n Result %d ", length2+length3+(99-18)*(99)+149*4);
}