#include <iostream>
#include <cmath>

using namespace std;

const double g=9.81;

class Cuerpo{
private:
  double x,y,Vx,Vy,Fx,Fy,m,R;
public:
  void iniciar(double,double,double,double,double,double);
  void calcule_fuerza();
  void move(double dt);
  void paint();
  double Getx(){return x;}
  double Gety(){return y;}
};

void Cuerpo::iniciar(double x0, double y0, double Vx0, double Vy0, double m0, double R0){
  x=x0;y=y0;
  Vx=Vx0;Vy=Vy0;
  m=m0;R=R0;
}

void Cuerpo::calcule_fuerza(){
  Fx=0;
  Fy=-m*g;
}
void Cuerpo::move(double dt){
  x+=Vx*dt;
  y+=Vy*dt;
  Vx+=Fx*dt/m;
  Vy+=Fy*dt/m;
}
void Cuerpo::paint(){
  cout<<" , "<<x<<"+"<<R<<"*cos(t),"<<y<<"+"<<R<<"*"<<"sin(t)";
}


//funciones de Animacion

void InicieAnimacion(void){
  cout<<"set terminal gif animate" <<endl;
  cout<<"set output 'balon.gif'"<<endl;
  cout<<"unset key"<<endl;
  cout<<"set xrange [-1:21]"<<endl;
  cout<<"set yrange [-3:5]"<<endl;
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

int main(){

  double t, tmax,dt;

  tmax=2.0;
  dt=0.001;

  Cuerpo balon;
  // x0,y0,Vx0,Vy0,m0,R0
  balon.iniciar(0,0,10,8,0.5,0.25);

  InicieAnimacion();
  
  for(t=0.0;t<=tmax;t+=dt)
    {
      InicieCuadro();
      balon.paint();
      TermineCuadro();
      cout<<t<<" "<<balon.Getx()<<" "<<balon.Gety()<<endl;
      balon.calcule_fuerza();
      balon.move(dt);
      
    }
    
  return 0;
}
