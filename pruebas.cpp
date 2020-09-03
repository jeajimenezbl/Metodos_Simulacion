#include<iostream>
#include<cmath>
using namespace std;
 int main(){
   int octal,decimal,n,a,i,c,res;
   cout<<"ingrese el número en base octal"<<endl;
   cin>>octal;
   n=octal/10;
   res=octal%10;
   i=0;
   c=res*pow(8,i);
  
   while(n!=0){
     res=n%10;
     n=n/10;
     c=c+res*pow(8,i+1);
     i++;

   }
   cout<<"Octal \t"<<octal<<"\t Decimal \t"<<c<<endl;

  

   return 0;
 }
