#include <iostream>
#include <cmath>

using namespace std;

//---- declarar constantes ---
const int N=3;
const double g=980;               //[cm/s²]
const double K=0.1e9;            //Constante elástica[kg/cm^0.5 s²]


//-------------Constantes del PEFRL------------------
const double epsilon=0.1786178958448091e00;
const double lambda=-0.2123418310626054e00;
const double chi=-0.6626458266981849e-1;
const double lambda2=(1.0-2.0*lambda)/2.0;
const double chiepsilon=1.0-2.0*(chi+epsilon);

//--- declarar clases -----
class Cuerpo;
class Colisionador;

//---- interface e implementacion de clases ----
//---- clase cuerpo ---
class Cuerpo{
private:
  double Theta,Omega,Tau; 
  double m,R,I,L,x0;
public:
  void Inicie(double Theta0,double Omega0,double m0,double R0,double L0,double x00);
  void BorreTorque(){Tau=0;};
  void AdicioneTorque(double Tau0){Tau+=Tau0;};
  void Mueva_Theta(double dt, double Coeficiente);
  void Mueva_Omega(double dt, double Coeficiente);
  void Dibujese(void);
  double GetX(void){return x0+L*sin(Theta);};
  double GetY(void){return -L*cos(Theta);};
  double GetTheta(void){return Theta;};
  double GetTau(void){return Tau;}; //inline
  friend class Colisionador;
};
void Cuerpo::Inicie(double Theta0,double Omega0,double m0,double R0, double L0 ,double x00){
  Theta=Theta0; Omega=Omega0;   m=m0;  R=R0; L=L0; I=m*L*L; x0=x00;
} 

void Cuerpo::Mueva_Theta(double dt, double Coeficiente){
  Theta+=Omega*(Coeficiente*dt);
}

void Cuerpo::Mueva_Omega(double dt, double Coeficiente){
  Omega+=Tau*(Coeficiente*dt/I);
}

void Cuerpo::Dibujese(void){
  cout<<" , "<<GetX()<<"+"<<R<<"*cos(t),"<<GetY()<<"+"<<R<<"*sin(t),"<<x0<<"+("<<GetX()-x0<<")*t/7,"<<GetY()<<"*t/7";
}

//--- clase Colisionador ----
class Colisionador{
private:
public:
  void CalculeFuerzas(Cuerpo * Pendulo);
  void CalculeFuerzaEntre(Cuerpo & Pendulo1, Cuerpo & Pendulo2);
};

void Colisionador::CalculeFuerzas(Cuerpo * Pendulo)
{
  int i,j;
  //--- Borrar todas las fuerzas ---
  for(i=0; i<N;i++){
    Pendulo[i].BorreTorque();
  }
  //----Adicionar fuerzas individuales-----
  for(i=0; i<N;i++){
    Pendulo[i].AdicioneTorque(-Pendulo[i].L*Pendulo[i].m*g*sin(Pendulo[i].Theta));
  }

  //--- Calcular Fuerzas entre pares de Pendulos ---
  for(i=0; i<N-1;i++){
    CalculeFuerzaEntre(Pendulo[i], Pendulo[i+1]);
  }
}

void Colisionador::CalculeFuerzaEntre(Cuerpo & Pendulo1, Cuerpo & Pendulo2){

  double s=(Pendulo1.GetX()+Pendulo1.R )-(Pendulo2.GetX()-Pendulo2.R);
  if(s>0){
    double F=K*pow(s,1.5);
    double T2=F*Pendulo2.L;
  Pendulo1.AdicioneTorque(-T2);
  Pendulo2.AdicioneTorque(T2);
  }
  /*vector3D r21=Pendulo2.r-Pendulo1.r;
  double aux=G*Pendulo2.m*Pendulo1.m*pow(norma2(r21),-1.5);
  vector3D F1=r21*aux;
  Pendulo1.AdicioneFuerza(F1);   Pendulo2.AdicioneFuerza(F1*(-1)); 
  */ 

}

//----------------- Funciones de Animacion ----------
void InicieAnimacion(void)
{
  cout<<"set terminal gif animate"<<endl; 
  cout<<"set output 'CunaDeNewton.gif'"<<endl;
  cout<<"unset key"<<endl;
  cout<<"set xrange[-10:20]"<<endl;
  cout<<"set yrange[-18:0]"<<endl;
  cout<<"set size ratio -1"<<endl;
  cout<<"set parametric"<<endl;
  cout<<"set trange [0:7]"<<endl;
  cout<<"set isosamples 12"<<endl;  
}

void InicieCuadro(void)
{
    cout<<"plot 0,0 ";
}

void TermineCuadro(void){
    cout<<endl;
}

//-----------  Programa Principal --------------  
int main(void){
  int i;
  Cuerpo Pendulo[N];
  Colisionador Newton;
  double m0=0.100,R0=1.5, L0=12;
  double T=2*M_PI*sqrt(L0/g);  
  double t,tdibujo,tmax=3*T,tcuadro=T/50,dt=0.000001;

  //InicieAnimacion(); //Dibujar

  //---------------(Theta0,Omega0,m0,R0, L0, x00)
  Pendulo[0].Inicie(-0.26, 0,m0,R0,L0,R0);
  for(i=1;i<N;i++){
    Pendulo[i].Inicie(0, 0,m0,R0,L0,(2*i+1)*R0);
  }

  for(t=0,tdibujo=0 ; t<tmax ; t+=dt,tdibujo+=dt){
    //Dibujar
    /*if(tdibujo>tcuadro){
    
      InicieCuadro();
        
      for (i=0;i<N;i++)
        {
            Pendulo[i].Dibujese();            
        }
      TermineCuadro();
      
      tdibujo=0;
      }*/
    if(t>0.17455 && t<0.17505)
    {
      cout<<t<<"\t"<<Pendulo[1].GetTau()<<endl;
    }
    //--- Muevase por PEFRL ---
    
    for(i=0;i<N;i++)Pendulo[i].Mueva_Theta(dt,epsilon);
    Newton.CalculeFuerzas(Pendulo);
    for(i=0;i<N;i++)Pendulo[i].Mueva_Omega(dt,lambda2);
    for(i=0;i<N;i++)Pendulo[i].Mueva_Theta(dt,chi);
    Newton.CalculeFuerzas(Pendulo);
    for(i=0;i<N;i++)Pendulo[i].Mueva_Omega(dt,lambda);
    for(i=0;i<N;i++)Pendulo[i].Mueva_Theta(dt,chiepsilon);
    Newton.CalculeFuerzas(Pendulo);
    for(i=0;i<N;i++)Pendulo[i].Mueva_Omega(dt,lambda);
    for(i=0;i<N;i++)Pendulo[i].Mueva_Theta(dt,chi);
    Newton.CalculeFuerzas(Pendulo);
    for(i=0;i<N;i++)Pendulo[i].Mueva_Omega(dt,lambda2);
    for(i=0;i<N;i++)Pendulo[i].Mueva_Theta(dt,epsilon);  

  }   
  for (i=0;i<N;i++)Pendulo[i].Mueva_Theta(dt, chi);
  for (i=0;i<N;i++)Pendulo[i].Mueva_Theta(dt, epsilon);
  

  
  return 0;
}
