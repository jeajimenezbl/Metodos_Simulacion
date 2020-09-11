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

void Paso_RungeKutta(double t, double &x, double &y, double dt)
{
  double dx1,dy1,dx2,dy2,dx3,dy3,dx4,dy4,dx,dy;
  dx1=dt*F1(t,x,y);dy1=dt*F2(t,x,y);
  dx2=dt*F1(t+0.5*dt,x+0.5*dx1,y+0.5*dy1);dy2=dt*F2(t+0.5*dt,x+0.5*dx1,y+0.5*dy1);
  dx3=dt*F1(t+0.5*dt,x+0.5*dx2,y+0.5*dy2);dy3=dt*F2(t+0.5*dt,x+0.5*dx2,y+0.5*dy2);
  dx4=dt*F1(t+dt,x+dx3,y+dy3);dy4=dt*F2(t+dt,x+dx3,y+dy3);
  dx=(dx1+2*dx2+2*dx3+dx4)/6;
  dy=(dy1+2*dy2+2*dy3+dy4)/6;
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
      Paso_RungeKutta(t,x,y,dt);
    }

  return 0;
}
