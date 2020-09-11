#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

double F(double t, double x)
{
  return -x/2;
}

void Paso_Euler(double &t, double &x,double dt)
{
  double dx;
  dx=F(t,x)*dt;
  x+=dx;
}
int main(int argc, char *argv[])
{
  double t,x,dt;
  x=1;
  dt=0.01;
  for (t=0;t<=10;t+=dt)
    {
      cout<<t<<"\t"<<x<<endl;
      Paso_Euler(t,x,dt);
    }

  return 0;
}
