#include <iostream>
#include <cmath>

using namespace std;

//_____________Definición de las Constantes_______________

const double ERROR=1.0e-5;

const double TDATOS=155.0;
const double A=1.03;

const double dt=0.1;
const double Tmax=300;

//____________Ecuaciones Diferenciales  acopladas____________

double F1(double t, double s, double i, double Gamma) // derivada de s respecto a t
{
  double Beta=log(A)+Gamma;

  return -Beta*s*i;
}

double F2(double t, double s, double i, double Gamma) // derivada de i respecto a t
{  
  double Beta=log(A)+Gamma;
  return Beta*s*i-Gamma*i;
}

//_______________Paso de Runge Kutta___________________________
void Paso_RungeKutta(double t, double &s, double &i, double dt, double Gamma)
{
  double ds1,di1,ds2,di2,ds3,di3,ds4,di4,ds,di;
  ds1=dt*F1(t,s,i,Gamma);
  di1=dt*F2(t,s,i,Gamma); 
 
  ds2=dt*F1(t+0.5*dt,s+0.5*ds1,i+0.5*di1,Gamma);
  di2=dt*F2(t+0.5*dt,s+0.5*ds1,i+0.5*di1,Gamma); 

  ds3=dt*F1(t+0.5*dt,s+0.5*ds2,i+0.5*di2,Gamma);
  di3=dt*F2(t+0.5*dt,s+0.5*ds2,i+0.5*di2,Gamma);
 

  ds4=dt*F1(t+dt,s+ds3,i+di3,Gamma);
  di4=dt*F2(t+dt,s+ds3,i+di3,Gamma);
 
  ds=(ds1+2*ds2+2*ds3+ds4)/6;
  di=(di1+2*di2+2*di3+di4)/6;
 
  s+=ds;
  i+=di;
 
}


//_________Derivada de una función___________

double Derivada(double f0, double f1)
{  
  return (f1-f0)/dt;
}


//______Esta función determina la derivada de I punto a punto______

double F_Deriv(double tf, double s, double i, double Gamma)
{
  double Df,t;
  double I0,I1;
  I0=0;
  I1=0;
  for(t=0;t<=tf;t+=dt)
  {
    Df=Derivada(I0, I1);
    I0=i;
    Paso_RungeKutta(t+dt,s,i,dt,Gamma);
    I1=i;
  }
  return Df;  
}

//_____________Método de Bisección Aplicado a la Derivada______________________

double Biseccion(double ta, double tb,double s, double i, double Gamma)
{
  double tm,fa,fm;
  fa=F_Deriv(ta,s,i,Gamma);
  while ((tb-ta)>ERROR)
  {
    tm=(ta+tb)/2;
    fm=F_Deriv(tm,s,i,Gamma);
    if(0 < fa*fm)
    {
      ta=tm;
      fa=fm;
    }
    else
    {
      tb=tm;
    }
  }  
  return tm;
}

//___________Función F de Gamma_________________________

double Fgamma(double s, double i,double Gamma)
{
  double tsim;
  tsim=Biseccion(1.0, Tmax-1.0 ,s,i,Gamma);

  return tsim -TDATOS;
}

//___________Bisección de la Funcion F de Gamma__________

double Biseccion_Gamma(double s, double i, double ga, double gb)
{
  double gm,fa,fm;
  fa=Fgamma(s,i,ga);
  while ((gb-ga)>ERROR)
  {
    gm=(ga+gb)/2;
    fm=Fgamma(s,i,gm);
    if(0 < fa*fm)
    {
      ga=gm;
      fa=fm;
    }
    else
    {
      gb=gm;
    }
  }  
  return gm;
}

//______________Función Principal__________________

int main()
{
  cout.precision(15);
  cout.setf(ios::fixed);
      
  double s,i,r,t,t0;
  double gamma;
  
  s=0.999;
  i=0.001;

  for(gamma=0.05;gamma<=1.0;gamma+=0.005)
  {
    cout<<gamma<<"\t"<<Fgamma(s,i,gamma)<<endl;
  }
  //cout<<Biseccion_Gamma(s,i,0.05, 1.0)<<endl;
  
  return 0;
}
