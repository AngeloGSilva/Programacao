#include "Headers.h"
//MENU
#define MENU_AVANCAR 1
#define MENU_ESTATISTICA 2
#define MENU_ADICIONA_DOENTE 3
#define MENU_TRANSFERE_PESSOA 4
#define MENU_VOLTA_ATRAS 5
#define MENU_TERMINAR 6

int MenuOpt(){
    char c;
    int i;
    do{
        printf("-------Menu------\n");
        printf("1.Avancar 1 dia na simulacao\n");
        printf("2.Mostrar estatisticas do dia atual\n");
        printf("3.Adicionar Doente a simulacao\n");
        printf("4.Transferir Pessoa\n");
        printf("5.Voltar atras [1-3] iteracoes\n");
        printf("6.Terminar\n");
        printf("Escolha uma das opcoes:");
        fseek(stdin,0,SEEK_END);
        i=scanf("%d",&c);
        if( c < MENU_AVANCAR || c > MENU_TERMINAR){  
            system("cls");                                    
        }
      }while(c < MENU_AVANCAR || c > MENU_TERMINAR);
      return c;
}

int main(int argc, char** argv) {
    
    initRandom();
    int nLocais,nIteracoes=0,iterD=0;//interD não é utilizado
    pConjunto Salas;
    //pLConj Lista=NULL;      //Não esta a ser usada
    Salas=Preparacao(&nLocais);
    if (Salas== NULL){
        printf("Preparacao Falhou\n");
        return -1;
    }
    
    int opt;
    do{
        switch(opt=MenuOpt()){
            case MENU_AVANCAR:
                    Salas=AvancaDia(Salas,nLocais);
                    nIteracoes++;
                break;
            case MENU_ESTATISTICA:
                    MostraEstatisticas(Salas,nLocais);
                break;
            case MENU_ADICIONA_DOENTE:
                    Salas=addDoente(Salas,nLocais);
                break;
            case MENU_TRANSFERE_PESSOA:
                    Salas=TransferePessoas(Salas,nLocais);
                break;
            case MENU_VOLTA_ATRAS:
                do{
                    printf("Quantas iteracoes deseja voltar atras [1-3]:");
                    scanf("%d",&iterD);
                }while(iterD<0 || iterD>3);
                
                printf("---->Por Implementar! :(\n");
                system("pause");
                break;
            case MENU_TERMINAR:
                ImprimeFinal(Salas,nLocais,nIteracoes);
                FreeConjuntos(Salas,nLocais);
                system("pause");
                break;
        }   
        system("cls");
    }while(opt != MENU_TERMINAR);
    return (EXIT_SUCCESS);
}

