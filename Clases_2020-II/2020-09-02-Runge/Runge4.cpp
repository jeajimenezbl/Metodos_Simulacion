#include <iostream>
#include <cmath>
using namespace std;

double F(double t, double x)
{
  return x/2;
}

void RungeKutta4(double t, double &x, double dt)
{
  double dx1,dx2,dx3,dx4,dx;
  dx1=dt*F(t,x);
  dx2=dt*F(t+0.5*dt,x+0.5*dx1);
  dx3=dt*F(t+0.5*dt,x+0.5*dx2);
  dx4=dt*F(t+dt,x+dx3);
  dx=(dx1+2*dx2+2*dx3+dx4)/6;
  x+=dx;
  
}

int main()
{
  double x,t0,t,dt;
  dt=0.1;
  x=1;
  t0=0;
    for(t=t0;t<=10;t+=dt)
      {
       cout<<t<<"\t"<<x<<endl;
       RungeKutta4(t,x,dt);
      }
  return 0;
}
