#include <iostream>
#include <cmath>


using namespace std;

const double beta = 0.35;
const double gama= 0.08;
const double tau=1/gama;

double F1(double t, double s, double i) // derivada de s respecto a t
{
  return -beta*s*i;
}

double F2(double t, double s, double i) // derivada de i respecto a t
{
  return beta*s*i-gama*i;
}

double F3(double t, double i) //derivada de r respecto a t
{
  return gama*i;
}

void Paso_RungeKutta(double t, double &s, double &i,double r, double dt)
{
  double ds1,di1,dr1,ds2,di2,dr2,ds3,di3,dr3,ds4,di4,dr4,ds,di,dr;
  ds1=dt*F1(t,s,i);
  di1=dt*F2(t,s,i);
  //dr1=dt*F3(t,i);
  
  ds2=dt*F1(t+0.5*dt,s+0.5*ds1,i+0.5*di1);
  di2=dt*F2(t+0.5*dt,s+0.5*ds1,i+0.5*di1);
  //dr2=dt*F3(t+0.5*dt,i+0.5*di1);

  ds3=dt*F1(t+0.5*dt,s+0.5*ds2,i+0.5*di2);
  di3=dt*F2(t+0.5*dt,s+0.5*ds2,i+0.5*di2);
  //dr3=dt*F3(t+0.5*dt,i+0.5*di2);

  ds4=dt*F1(t+dt,s+ds3,i+di3);
  di4=dt*F2(t+dt,s+ds3,i+di3);
  //dr4=dt*F3(t+dt,i+di3);

  ds=(ds1+2*ds2+2*ds3+ds4)/6;
  di=(di1+2*di2+2*di3+di4)/6;
  //dr=(dr1+2*dr2+2*di3+di4)/6;
  s+=ds;
  i+=di;
  //r+=dr;
}

int main()
{
  double s,i,r,t,t0,dt;
  int T;
  s=0.999;
  i=0.001;
  
  t0=0;
  dt=0.1;
  T=120;
  for(t=t0;t<=T;t+=dt)
  {
    r=1-s-i;
    cout<<t<<"\t"<<s<<"\t"<<i<<"\t"<<r<<endl;
    Paso_RungeKutta(t,s,i,r,dt);
    }

  return 0;
}
