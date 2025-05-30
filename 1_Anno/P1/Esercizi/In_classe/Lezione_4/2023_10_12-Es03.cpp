#include <iostream>
#include <cstdlib>
using namespace std;

int dado();
void riordina (int * n1, int * n2, int * n3);
void punti(int dB, int dR, int * pB, int * pR);

int main(){
    srand(time(NULL));
    int dB1, dB2, dB3, dR1, dR2, dR3, pB=0, pR=0;

    dB1=dado();
    dB2=dado();
    dB3=dado();
    riordina(&dB1,&dB2,&dB3);

    dR1=dado();
    dR2=dado();
    dR3=dado();
    riordina(&dR1,&dR2,&dR3);

    cout<<"DB1: "<<dB1<<" DB2: "<<dB2<<" DB3: "<<dB3<<endl;
    cout<<"DR1: "<<dR1<<" DR2: "<<dR2<<" DR3: "<<dR3<<endl;

    punti(dB1, dR1, &pB, &pR);
    punti(dB2, dR2, &pB, &pR);
    punti(dB3, dR3, &pB, &pR);

    cout<<"Il punteggio finale e' di: "<<pB<<" - "<<pR<<endl;
    
    return 0;
}

int dado(){
    int numero=rand()%6+1;
    return numero;
}

void riordina (int * n1, int * n2, int * n3){
    if((*n1)>(*n2)){
        (*n1)+=(*n2);
        (*n2)=(*n1)-(*n2);
        (*n1)-=(*n2);
    }
    if((*n2)>(*n3)){
        (*n2)+=(*n3);
        (*n3)=(*n2)-(*n3);
        (*n2)-=(*n3);
    }
    if((*n1)>(*n2)){
        (*n1)+=(*n2);
        (*n2)=(*n1)-(*n2);
        (*n1)-=(*n2);
    }
}

void punti(int dB, int dR, int * pB, int * pR){
    if(dB>dR){
        (*pB)++;
    }else{
        (*pR)++;
    }
}