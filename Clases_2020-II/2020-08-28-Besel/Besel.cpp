#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

double F(double t , int Alpha , double x){
  double f;
  f=cos(Alpha*t - x*sin(t));
  return f;
}

double Integral(double a,double b , int n, int Alpha , double x){
  int i;
  double h,integral;
  n=n*4; //multiplo de 4
  h=(b-a)/n;
  integral=0;
  for (i=0;i <= (n-2)/2;i++){
    integral += (h/3)*(F((a+2*i*h),Alpha,x) + 4*F((a+(2*i*h)+h),Alpha,x) + F((a + 2*i*h + 2*h),Alpha,x));   
    }
  return integral;
}

double Besel(int n,int Alpha, double x){
  
  return (1/M_PI)*Integral(0,M_PI,n,Alpha,x);
  
}

int main(int argc, char *argv[]){
  int n,Alpha;
  double x;
  cout.precision(5);
  cout.setf(ios::fixed);
  n=atoi(argv[1]);
  for(x=0;x<=10;x+=0.1)
    {
      cout<<x<<"\t";
      for(Alpha=0;Alpha<=3;Alpha++)
	{
	  cout<<Besel(n,Alpha,x)<<"\t";

	}
      cout<<"\n";

    }
  
   return 0;
}

  

