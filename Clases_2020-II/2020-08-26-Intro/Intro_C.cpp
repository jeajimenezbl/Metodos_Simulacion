#include<iostream>
#include<cmath>
using namespace std;
double F(double x){
  return sin(x)/x;
}
int main(){
  double x;
  for(x=0.1; x<10;x+=0.1){
    cout << x <<"\t"<<F(x)<<endl;
  }

  return 0;
}
