#include <iostream>
using namespace std;

int main(){
    int numero;
    int rip_0=0, rip_1=0, rip_2=0,rip_3=0, rip_4=0, rip_5=0, rip_6=0, rip_7=0, rip_8=0, rip_9=0;

    cout<<"Inserire un numero intero: ";
    cin>>numero;

    while((numero/10)>=1){
        int ultimacifra=numero%10;
        switch(ultimacifra){
            case 0:
                rip_0+=1;
                break;
            case 1:
                rip_1+=1;
                break;
            case 2:
                rip_2+=1;
                break;
            case 3:
                rip_3+=1;
                break;
            case 4:
                rip_4+=1;
                break;
            case 5:
                rip_5+=1;
                break;
            case 6:
                rip_6+=1;
                break;
            case 7:
                rip_7+=1;
                break;
            case 8:
                rip_8+=1;
                break;
            case 9:
                rip_9+=1;
                break;
        }
    numero-=(numero%10);
        numero/=10;
    }

    switch(numero){
        case 0:
            rip_0+=1;
            break;
        case 1:
            rip_1+=1;
            break;
        case 2:
            rip_2+=1;
            break;
        case 3:
            rip_3+=1;
            break;
        case 4:
            rip_4+=1;
            break;
        case 5:
            rip_5+=1;
            break;
        case 6:
            rip_6+=1;
            break;
        case 7:
            rip_7+=1;
            break;
        case 8:
            rip_8+=1;
            break;
        case 9:
            rip_9+=1;
            break;
    }

    cout<<"Frequenza 0: "<<rip_0<<endl;
    cout<<"Frequenza 1: "<<rip_1<<endl;
    cout<<"Frequenza 2: "<<rip_2<<endl;
    cout<<"Frequenza 3: "<<rip_3<<endl;
    cout<<"Frequenza 4: "<<rip_4<<endl;
    cout<<"Frequenza 5: "<<rip_5<<endl;
    cout<<"Frequenza 6: "<<rip_6<<endl;
    cout<<"Frequenza 7: "<<rip_7<<endl;
    cout<<"Frequenza 8: "<<rip_8<<endl;
    cout<<"Frequenza 9: "<<rip_9<<endl;
    return 0;
}