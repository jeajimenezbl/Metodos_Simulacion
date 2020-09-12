//Programa que implementa el Metodo de Runge-Kutt-4 para integrar una ecuacion diferencia acoplada

#include <iostream> //incluye la libreria iostream permite recibir datos del teclado y sacarla por pantella
#include <cmath>
using namespace std; // espacio de nombres. Se va a utilizar el standar.

const double Beta=0.35;
const double Gamma=0.08;
//funcion

///////////////////////////7////////////////////////////////////////////////////////7

double f1(double t, double S, double I){
  return -Beta*S*I;
  }

double f2(double t, double S, double I){
  return Beta*S*I-Gamma*I;
  }
void UnPasoRK4(double & t, double & S, double & I, double dt){//PAso por referencia se agrega & a la variable
  double dS1, dS2,dS3,dS4; double dI1, dI2,dI3,dI4;
  
  dS1=dt*f1(t,S,I);      dI1=dt*f2(t,S,I);

  
  dS2=dt*f1(t+dt*0.5,S+dS1*0.5,I+dI1*0.5); dI2=dt*f2(t+dt*0.5,S+dS1*0.5,I+dI1*0.5);
  
  dS3=dt*f1(t+dt*0.5,S+dS2*0.5,I+dI2*0.5); dI3=dt*f2(t+dt*0.5,S+dS2*0.5,I+dI2*0.5);
  
  dS4=dt*f1(t+dt*0.5,S+dS3*0.5,I+dI3*0.5); dI4=dt*f2(t+dt*0.5,S+dS3*0.5,I+dI3*0.5);
  
  S+=1/6.0*(dS1+2*(dS2+dS3)+dS4);
  I+=1/6.0*(dI1+2*(dI2+dI3)+dI4);
  t+=dt;
}

//////////////////////////////////7////////////////////////////////////////////////////
//%%%%%%%%MAIN

int main(void)
{
  double t,S,I,r;
  double dt=1.0,tfinal=120.0;

  //Valores iniciales
  S=0.999;
  I=0.001;
  
  
  //

  for(t=0;t<tfinal;)
    {
      r=1.0-S-I;
      cout<<t<<" "<<S<<" "<<I<<" "<<r<<endl;
      UnPasoRK4(t,S,I,dt);
    } 

  return 0; //Retorna 0 para avisar que todo funciono bien
}
