/*
#include "Headers.h"

plocal CriaVetor(char nomeFicheiro[],int *nLocais){
    FILE *f;
    *nLocais = 0;
    plocal Locais = NULL;
    plocal aux =NULL;
    local novo;
    
    f=fopen(nomeFicheiro,"rb");
    
    while(fread(&novo,sizeof(local),1,f)==1){
        aux=realloc(Locais,sizeof(local) * (*nLocais + 1));
        
        if(aux == NULL){
            free(Locais);
             fclose(f);
             printf("Erro na alocacao de memoria\n");
             *nLocais=0;
            return NULL;
        }else{
            Locais = aux;
            Locais [*nLocais]= novo;
            *nLocais += 1;
         }
    }
    fclose(f);
    return(Locais);
}

void printEspacos(plocal Locais,int *nLocais){
    int i=0;
    printf("  Espacos:\n");
    printf("--------------------\n");
    while(i < *nLocais){
        printf("  ID Local:%d\n",Locais[i].id);
        printf("  Capacidade Local:%d\n",Locais[i].capacidade);
        printf("  Ligacoes:%d %d %d\n",Locais[i].liga[0],Locais[i].liga[1],Locais[i].liga[2]);
        printf("--------------------\n");
        i++;
    }

}

int VerificaEspaco(plocal Locais,int *nLocais){
    //Verificar repetições de ID
    for(int i=0;i< *nLocais;i++){
        if( Locais[i].id > 0){
            for(int j=1;j<*nLocais;j++){
                if(Locais[j].id > 0){
                    if(i!=j && Locais[i].id == Locais[j].id ){//SE IDS IGUAIS TERMINA
                        printf("Erro na verificacao(IDS devem ser distintos)\n");
                        return -1;
                    }
                }else{
                    printf("Erro na verificacao(ID deve ser positivo)\n");
                    return -1;
                }
            }
        }else{
            printf("Erro na verificacao(ID deve ser positivo)\n");
            return -1;
            }
    }
   
    //Verifica Ligações
   
    for(int i=0;i< *nLocais;i++){
        for(int j=0;j < 3;j++){
           if(Locais[i].liga[j] != -1){
                for(int k=0;k<*nLocais;k++){
                 if(i!=k && Locais[i].liga[j]==Locais[k].id){//Locais[i].liga[j]==Locais[j].liga[0] || Locais[i].liga[j]==Locais[j].liga[1] || Locais[i].liga[j]==Locais[j].liga[2]
                     if(Locais[i].id==Locais[k].liga[0] || Locais[i].id==Locais[k].liga[1] || Locais[i].id==Locais[k].liga[2]){
                                
                             }else{
                         printf("Erro na verificacao(Ligacoes Incorretas entre espacos de id %d e %d)\n",Locais[i].id,Locais[k].id);
                                return -1;
                            }
                    }   
               }
           }
        }
      }
    return 1;
}
*/

