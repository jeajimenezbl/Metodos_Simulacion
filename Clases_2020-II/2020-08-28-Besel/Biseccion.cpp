# include<iostream>
#include <cmath>

using namespace std;
const double error=1e-7;

double F(double x){
  return sin(x)/x ;
}

double CerosPorBiseccion(double a, double b){
  double m,fa,fb,fm;
  fa= F(a);
  while((b-a) >error){
    m=(b+a)/2;
    fm=F(m);
    if(0 < fa*fm ){
      a=m;
      fa=fm;
    }
    else{
      b=m;
    }
  }
  return m;
}

int main(){
  double a,b;
  a=4;
  b=8; //a<b
  cout<<"la raiz de la función es x="<<CerosPorBiseccion(a,b) <<endl;

  return 0;
}
