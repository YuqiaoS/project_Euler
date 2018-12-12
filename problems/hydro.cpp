/*  hydro.cpp AEP 4340 Final Project
	Solve coupled elliptical equations of two dimensional fluid flow
	with boundary conditions using relaxation methods

	Run on a AMD with gcc 4.6.1

	Yuqiao Shen June-2013
*/
#include <cstdio>
#include <cstdlib>
#include <cmath>
#define ARRAYT_BOUNDS_CHECK
#include "array.hpp"

const int NC = 40, NR = 20, WID =10, THICK=6;
const int PL = 10, PR = PL+THICK-1; 
const int PB = 0, PT = PB+WID-1;
const double RE=1.0, RE4=RE/4.0;
	
int main(){
	/* sets up the grid */
	void prelax(array<double> &, array<double> &, array<char> &);
	void vrelax(array<double> &, array<double> &, array<char> &);
	double viscousF(array<double> &);
	double pressureF(array<double> &);
	
	array<double> p(NC,NR);
	array<double> vort(NC,NR);
	array<char> pflag(NC,NR);
	for(int i=0; i<NC; i++){
		for(int j=0; j<NR; j++){
			p(i, j)= j;
			vort(i,j)= 0;
			if(i==0 || i==NC-1 || j==NR-1 || j==0)
				pflag(i,j)='1';
			else
				pflag(i,j)='0';
		}
	}

	for(int i=0; i<THICK; i++){
		for(int j=0; j<WID; j++){			
			p(PL+i, j)= 0;
			pflag(PL+i, j)= '1';
			
			//p(50+i, j)=0;
			//pflag(50+i,j)='1';
		}
	}

	int iterMax=1000, iter=0; 
	double dpTol =1e-2,dvTol =1e-2;
	bool repeat = true;
	
	array<double> pold(NC,NR);
	array<double> vold(NC,NR);
	//printf("BAD %5d \n", NC);
	while (repeat && iter<iterMax){
		repeat = false;
		pold=p;
		vold=vort;
		prelax(p,vort,pflag);
		//printf("iT %5d \n", iter);
		vrelax(p,vort,pflag);
		//printf("iT %5d \n", iter);
		for(int i=0; i<NC; i++){
			for(int j=0; j<NR; j++){
				if(abs(vold(i,j)-vort(i,j))>dvTol)
					{repeat = true;}
				//if(abs(pold(i,j)-p(i,j))>dpTol)
					
			}
		}
		iter++;
	}
	
	if(repeat)
		printf("Iteration has reached max but max delta phi is still bigger "
		"than specified tolerance");
	else
		printf("Iterated %5d times.\n", iter);
		
	printf("Pressure force for RE = %g is %g. \n", RE, pressureF(vort));
	printf("Viscous force is %g.", viscousF(vort));
		
	FILE* fp;
	fp = fopen( "stream.dat", "w+");
	if( fp == NULL ) {
		printf( "cannot open file\n" );
		return( 0 );
	}

	for(int j=0; j<NR; j++){
		for(int i=0; i<NC; i++){
			fprintf(fp, "%30.20f", p(i,j));
		}
		fprintf(fp, "\n");
	}
	
	fp = fopen( "vorticity.dat", "w+");
	if( fp == NULL ) {
		printf( "cannot open file\n" );
		return( 0 );
	}
	
	for(int j=0; j<NR; j++){
		for(int i=0; i<NC; i++){
			fprintf(fp, "%30.20f", vort(i,j));
		}
		fprintf(fp, "\n");
	}
	
	return( EXIT_SUCCESS);
}

/* Gauss_Seidel iteration to relax stream function */
void prelax(array<double> &p, array<double> &v, array<char> &pflag){
	int c = p.n1(), r = p.n2();
	double wp = .1, wp1=1-wp;
	double pfd;
	
	for(int j=0; j<r; j++){
		for(int i=0; i<c; i++){
			if(pflag(i,j)=='0'){
				/* front edge */
				if(i == 1 && j != r-2){
					pfd=p(1,j+1)+p(1,j-1)+p(2,j)-v(i,j);
					p(1,j)= wp*pfd/3.0+wp1*p(1,j);
					p(0,j)= p(1,j);
				}
				/* rear edge */
				else if( i==c-2 && j!=r-2){
					pfd=p(i,j+1)+p(i,j-1)+p(i-1,j)-v(i,j);
					p(c-2,j)= wp*pfd/3.0+wp1*p(i,j);
					p(c-1,j)= p(i,j);
				}
				/* top edge */
				else if(j==r-2){
					/* top corners */
					if(i==1){
						pfd=p(i+1,j)+p(i,j-1)-v(i,j)+1;
						p(i,j)= wp*.5*pfd+wp1*p(i,j);
						p(i-1,j)=p(i,j);
						p(i-1,j-1)=p(i-1,j);
					}
					else if (i==c-2){
						pfd=p(i-1,j)+p(i,j-1)-v(i,j)+1;
						p(i,j)= wp*.5*pfd+wp1*p(i,j);
						p(c-1,j)=p(i,j);
						//p(c-1,r-1)=p(c-1,c-2);
					}
					/* side */
					else{
						pfd=p(i-1,j)+p(i,j-1)+p(i+1,j)-v(i,j)+1;
						p(i,j)=wp*pfd/3.0 + wp1*p(i,j);
					}
					
					p(i,j+1)=p(i,j)+1;
				}
				
				/* interior points */
				else{
					pfd=p(i-1,j-1)+p(i-1,j+1)+p(i+1,j-1)+p(i+1,j+1)-v(i,j);
					p(i,j)=wp*pfd*.25 + wp1*p(i,j);
				}
			}
		}
	}
}

/* Gauss_Seidel iteration to relax vorticity */	
void vrelax(array<double> &p, array<double> &v, array<char> &pflag){
	double wv=.1, wv1=1.0-wv, vfd;
	
	/* front and back faces boundary conditions for vorticity */ 
	for(int j=0; j<WID; j++){
		v(PL,j)= 2.0*p(PL-1,j);
		v(PR,j)= 2.0*p(PR+1,j);
		
		//v(20,j)= 2.0*p(50-1,j);
		//v(26,j)= 2.0*p(60+1,j);
	}
	int k=0;
	/* top face b.c. */
	for(int i=PL+1; i<=PR-1; i++){
		v(i, PT)= 2.0*p(i, PT+1);
		
		//v(50+k, PT)= 2.0*p(50+k, PT+1);
		//k++;
	}

	for(int j=0; j<NR; j++){
		for(int i=0; i<NC; i++){
			if(pflag(i,j)=='0'){
				/* Rear edge */
				if( i==NC-2 ){
					vfd	= v(i,j+1)+v(i, j-1)+v(i-1,j);
					vfd += RE4*v(i-1,j)*(p(i, j+1)-p(i, j-1));
					vfd += RE4*(v(i, j+1)-v(i, j-1))*(p(i+1,j)-p(i-1, j));
					v(i,j)= wv*vfd/(3.0+RE4*(p(i,j+1)-p(i,j-1)))+wv1*v(i,j);
					v(NC-1, j)= v(i,j);
				}
				else{
					vfd = v(i, j+1) + v(i, j-1)+ v(i+1, j) + v(i-1,j);
					vfd -= RE4*(p(i, j+1)-p(i, j-1))*(v(i+1, j)-v(i-1,j));
					vfd += RE4*(p(i+1, j)-p(i-1, j))*(v(i, j+1)-v(i,j-1));
					v(i,j)= wv*vfd*.25+wv1*v(i,j);
				}
			}
		}
	}
}

/* Integrate for for the viscouse force*/
double viscousF(array<double> &v){
	double fv=v(PL, PT)/2;
	
	for(int i=PL+1; i<=PR; i++)
		fv+=v(i, PT);
		
	fv-=v(PR,PT)/2;
	fv/=RE*(WID-1);

	return fv;
}

double pressureF(array<double> &v){
	double p=0, fp=0;
	/* Left side */
	for(int j=1; j<=PT; j++){
		p-=(v(PL,j)-v(PL-1,j)+v(PL,j-1)-v(PL-1,j-1))/2/RE;
		fp+=p;
	}
	
	/* Top side */
	for(int i=PL+1; i<=PR; i++)
		p-=(v(i,PT+1)-v(i,PT)+v(i-1,PT+1)-v(i-1,PT))/2/RE;
		
	fp-=p/2;
	
	for(int j=PT-1; j>0; j--){
		p+=(v(PR+1,j)-v(PR,j)+v(PR+1,j+1)-v(PR,j+1))/2/RE;
		fp-=p;
	}
	fp/=(WID-1);
	
	return fp;
}
	