# include <iostream>
# include <cmath>
using namespace std;

double F(double x){
  return sin(x);
}

double Integral_Rect(double a,double b,int n){
  int i;
  double h,integral;
  h=(b-a)/n;
  integral=0;
  for (i=1;i<=n;i++){
    integral += h*F(a+i*h);    
    }
  return integral;
}

double Integral_Trap(double a,double b, int n){
  int i;
  double h,integral;
  h=(b-a)/n;
  integral=0;
  for (i=1;i<=n;i++){
    integral += (h/2)*(F(a+i*h) + F(a+i*h-h));    
    }
  return integral;
}


double Integral_Parab(double a,double b , int n){
  int i;
  double h,integral;
  n=n*4; //multiplo de 4
  h=(b-a)/n;
  integral=0;
  for (i=0;i <= (n-2)/2;i++){
    integral += (h/3)*(F(a+2*i*h) + 4*F(a+(2*i*h)+h) + F(a + 2*i*h + 2*h));   
    }
  return integral;
}

int main(){
  int n;
  double a,b;
  a=0;
  b=M_PI;
  cout <<"n : ";
  cin>>n;
  cout <<"Integral \t"<<Integral_Rect(a,b,n)<<endl;
  cout <<"Integral \t"<<Integral_Trap(a,b,n)<<endl;
  cout <<"Integral \t"<<Integral_Parab(a,b,n)<<endl;

  return 0;
}
