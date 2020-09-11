#include <iostream>
#include <cmath>

using namespace std;

const double T=2*M_PI;
const double Omega=2*M_PI/T;

double F1(double t, double x, double y)
{
  return -Omega*Omega*y;
}

double F2(double t, double x, double y)
{
  return x;
}

void Paso_Euler(double t, double &x, double &y, double dt)
{
  double dx,dy;
  dx=dt*F1(t,x,y);
  dy=dt*F2(t,x,y);
  x+=dx;
  y+=dy;
}

int main()
{
  double x,y,t,t0,dt;
  x=1;
  y=0;
  t0=0;
  dt=0.1;
  for(t=t0;t<=T;t+=dt)
    {
      cout<<t<<"\t"<<x<<"\t"<<y<<endl;
      Paso_Euler(t,x,y,dt);
    }

  return 0;
}
