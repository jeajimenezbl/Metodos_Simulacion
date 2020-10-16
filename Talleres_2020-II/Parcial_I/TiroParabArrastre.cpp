#include <iostream>
#include <cmath>
#include "Vector.h"

using namespace std;

//---- declarar constantes ---

const double g=9.81;
const double Ca=0.5;
const double rho=1.224;
const double A=M_PI*0.22*0.22;


const double epsilon=0.1786178958448091e00;
const double lambda=-0.2123418310626054e00;
const double chi=-0.6626458266981849e-1;
const double lambda2=(1.0-2.0*lambda)/2.0;
const double chiepsilon=1.0-2.0*(chi+epsilon);


//---- clase cuerpo ---
class Cuerpo
{
    private:
        vector3D r,V,F;
        double m,R;
    public:
        void Inicie(double x0,double y0,double z0,double Vx0,double Vy0,double Vz0,double m0,double R0);
        void CalculeFuerza(void);
        //void BorreFuerza(){F.cargue(0,0,0);};
        //void AdicioneFuerza(vector3D F0){F+=F0;};
        void Mueva_r(double dt, double Coeficiente);
        void Mueva_V(double dt, double Coeficiente);
        void Dibujese(void);
        double Getx(void){return r.x();}; //inline
        double Gety(void){return r.y();}; //inline
        double Getz(void){return r.z();}; //inline
        
};
void Cuerpo::Inicie(double x0,double y0,double z0,double Vx0,double Vy0,double Vz0,double m0,double R0){
  r.cargue(x0,y0,z0); V.cargue(Vx0,Vy0,Vz0);  m=m0;  R=R0; 
} 

void Cuerpo::CalculeFuerza(void)
{
  vector3D Fg,Fa,Fmagnus, Ftotal;
  double ka,km;
  ka=-0.5*Ca*rho*A;
  Fg.cargue(0,0,-m*g);
  Fa=ka*V;
  Ftotal=Fg+Fa;
}

void Cuerpo::Mueva_r(double dt, double Coeficiente){
    r+=V*(Coeficiente*dt);
}

void Cuerpo::Mueva_V(double dt, double Coeficiente){
  V+=F*(Coeficiente*dt/m);
}


void Cuerpo::Dibujese(void){
  cout<<" , "<<r.x()<<"+"<<R<<"*cos(t),"<<r.z()<<"+"<<R<<"*sin(t)";
}


//----------------- Funciones de Animacion ----------
void InicieAnimacion(void){
  cout<<"set terminal gif animate"<<endl; 
  cout<<"set output 'TiroParabolico.gif'"<<endl;
  cout<<"unset key"<<endl;
  cout<<"set xrange[0:30]"<<endl;
  cout<<"set yrange[0:5]"<<endl;
  cout<<"set size ratio -1"<<endl;
  cout<<"set parametric"<<endl;
  cout<<"set trange [0:7]"<<endl;
  cout<<"set isosamples 12"<<endl;  
}
void InicieCuadro(void){
    cout<<"plot 0,0 ";
}
void TermineCuadro(void){
    cout<<endl;
}

//-----------  Programa Principal --------------  
int main(void){
  int i;
  Cuerpo Balon;
  
  double gamma,V0;
  V0=20;
  gamma=0.35; //angulo en radianes
  
  double m=0.43, R=0.22;
  double x0,y0,z0,Vx0,Vy0,Vz0;
  x0=0;
  y0=0;
  z0=0;
  Vx0=V0*cos(gamma);
  Vy0=0;
  Vz0=V0*sin(gamma);
  
  double t,tdibujo,tvuelo,tcuadro=tvuelo/1000,dt=0.01;
  tvuelo=2*Vz0/g; //tiempo total de vuelo

  //InicieAnimacion(); //Dibujar

  Balon.Inicie(x0, y0,z0,Vx0,Vy0,Vz0, m,R);

  for(t=0,tdibujo=0 ; t<tvuelo ; t+=dt,tdibujo+=dt){

      //Dibujar
     /* 
    if(tdibujo>tcuadro){
    
      InicieCuadro();
       
      Balon.Dibujese();            
          
      TermineCuadro();
      tdibujo=0;
    }
    */
   
    cout<<Balon.Getx()<<"\t"<<Balon.Gety()<<"\t"<<Balon.Getz()<<endl;
    //--- Muevase por PEFRL ---
    
    Balon.Mueva_r(dt,epsilon);
    Balon.CalculeFuerza();
    
    Balon.Mueva_V(dt,lambda2);
    Balon.Mueva_r(dt,chi);
    Balon.CalculeFuerza();
     
    
    Balon.Mueva_V(dt,lambda);
    Balon.Mueva_r(dt,chiepsilon);
    Balon.CalculeFuerza();
    
    
    Balon.Mueva_V(dt,lambda);
    Balon.Mueva_r(dt,chi);
    Balon.CalculeFuerza();
    
    Balon.Mueva_V(dt,lambda2);
    Balon.Mueva_r(dt,epsilon);  

  }   

  
  return 0;
}

  
