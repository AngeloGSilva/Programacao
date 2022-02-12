/*

#include "Headers.h"

void PrintPessoas(pPessoa Lista){
    pPessoa p;
    p=Lista;
    while(p!=NULL){
         printf("%s %d %c %d \n",p->Identificador,p->idade,p->estado,p->dias);
         p=p->prox;
    }
}

int VerificaDados(Pessoa buffer,pPessoa lista){

    pPessoa p=NULL;
    p=lista;
  
    if(buffer.idade < 0){
        return -1;
    } 

    if(buffer.estado != 'S' && buffer.estado != 'D' && buffer.estado != 'I'){
        return -1;
    }

    if(buffer.estado == 'D' && buffer.dias < 0){
        return -1;
    }


    if(p == NULL){
        return 1;
    }
    else{
    while(p!=NULL){
        if(strcmp(buffer.Identificador,p->Identificador) == 0){
            return -1;
        }
        p=p->prox;
        }
    }

    return 1;
}

pPessoa CriaLista(char nomeFicheiro[],pPessoa lista){
    FILE *f = NULL;
    pPessoa atual= NULL;
    pPessoa novo = NULL;
    Pessoa buffer;
    
    if((f = fopen(nomeFicheiro, "rt")) == NULL){
        fprintf(stderr, "\nErro ao abrir o ficheiro %s para leitura\n", nomeFicheiro);
        return lista;
    }
    
    while(fscanf(f," %s %d %c",buffer.Identificador, &buffer.idade, &buffer.estado) == 3){
        
        if(buffer.estado == 'D'){
            fscanf(f," %d",&buffer.dias);
        }else
            buffer.dias = -1;
         buffer.prox=NULL;
        // printf("%s %d %c %d \n",buffer.Identificador, buffer.idade, buffer.estado,buffer.dias);
        if(VerificaDados(buffer,lista) == 1){
            
            novo=malloc(sizeof(Pessoa));
        
            if(novo==NULL){
                free(novo);//free lista
                fclose(f);
                printf("Erro na alocacao de memoria\n");
                return NULL;
            }
            
            (*novo) = buffer;

            if(lista == NULL){
                  lista = novo;
            }else{
                atual=lista;
                while(atual->prox != NULL){
                    atual=atual->prox;
                }
            atual->prox=novo;
            }
        }
    }
    
    printf("-->Ficheiro aberto ,verificando pessoas validas...\n\n");
    fclose(f);
    return lista;
}
*/
