#include "Headers.h"

//Funcao que liberta elimina elementos de uma lista ligada(a partir do fim)
pPessoa FreePessoa(pPessoa p,int elimina){
   
    pPessoa atual,antes=NULL;
    
    while(elimina !=0){//Percorre o ciclo elimina vezes
        atual=p;
     while(atual->prox != NULL){
        antes = atual;
        atual = atual->prox;
    }
    if(atual == p){  //retira o inicio
        p=NULL;
        free(p);    //lista ligada é libertada
        return NULL;
    }
    else            //Retira do fim
        antes->prox = atual->prox; // Ou antes->prox = NULL;

    free(atual);     //no atual é libertado
    elimina--;
  }
    return p;
 }
    
//Funcao que cria o vetor dinamico de estruturas
plocal CriaVetor(char nomeFicheiro[],int *nLocais){
    FILE *f;
    *nLocais = 0;
    plocal Locais = NULL;
    plocal aux =NULL;
    local novo;
    
    f=fopen(nomeFicheiro,"rb");     //Abrir ficheiro para leitura
    
    while(fread(&novo,sizeof(local),1,f)==1){   //Enquanto le uma struct local
        aux=realloc(Locais,sizeof(local) * (*nLocais + 1)); //realocar memoria
        
        if(aux == NULL){//Alocaçao memoria falhou
             fclose(f);
             free(Locais);
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

//Funcao que da print a todos os espacos
void printEspacos(plocal Locais,int *nLocais){
    int i=0;
    if(*nLocais==1){
        printf("  Espaco:\n");
    }else
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

//Funcao que Verifica as informacoes dos espacos
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
                 if(i!=k && Locais[i].liga[j]==Locais[k].id){       //Locais[i].liga[j]==Locais[j].liga[0] || Locais[i].liga[j]==Locais[j].liga[1] || Locais[i].liga[j]==Locais[j].liga[2]
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

//Funcao que da print às pessoas
void PrintPessoas(pPessoa Lista){
    pPessoa p;
    p=Lista;
    if(p!=NULL){
        while(p!= NULL){
         printf("  %s %d %c",p->Identificador,p->idade,p->estado);
         if(p->dias == -1){
             printf("\n");
         }else{
             printf(" %d\n",p->dias);
         }
         p=p->prox;
        }
    }else
        printf("\n-->Lista Vazia\n");
}

//Funcao que Verifica os dados das pessoas
int VerificaDados(Pessoa buffer,pPessoa lista){

    pPessoa p=NULL;
    p=lista;
  
    if(buffer.idade < 0 || buffer.idade>120){
        printf("\nIdade deve estar em [0 <-> 120]!\n");
        return -1;
    }   

    if(buffer.estado != 'S' && buffer.estado != 'D' && buffer.estado != 'I'){
        printf("O estado do doente deve ser S[Saudave],D[Doente] ou I[Imune]!\n");
        return -1;
    }

    if(buffer.estado == 'D' && buffer.dias < 0){
        printf("Dias de doente devem ser positivos!\n");
        return -1;
    }

    if(p == NULL){
        return 1;
    }
    else{
    while(p!=NULL){
        if(strcmp(buffer.Identificador,p->Identificador) == 0){
            printf("Identificador ja existe!\n");
            return -1;
        }
        p=p->prox;
        }
    }
    return 1;
}

//Funcao que cria a lista ligada de pessoas
pPessoa CriaLista(char nomeFicheiro[],pPessoa lista,int *nPessoas){
    
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
            if(fscanf(f," %d",&buffer.dias) != 1){
                buffer.dias=0;
            }
        }else
            buffer.dias = -1;
         buffer.prox=NULL;
        // printf("%s %d %c %d \n",buffer.Identificador, buffer.idade, buffer.estado,buffer.dias);
        if(VerificaDados(buffer,lista) == 1){//manda lista atualizada até ao momento
            (*nPessoas)++;
            novo=malloc(sizeof(Pessoa));
        
            if(novo==NULL){//falha a alocacao
                free(novo);//free lista
                fclose(f);
                printf("Erro na alocacao de memoria\n");
                return NULL;
            }
            
            (*novo) = buffer; //passa conteudos de buffer para onde novo aponta

            if(lista == NULL){//Se for primeiro elemento
                  lista = novo;
            }else{
                atual=lista;
                while(atual->prox != NULL){//Percorre lista ate fim
                    atual=atual->prox;
                }
            atual->prox=novo;//Insere no fim
            }
        }else{
            //PrintPessoas(lista);
            lista=FreePessoa(lista,*nPessoas);//Se a informacao nao for verificada,a até ao momento é toda libertada
            return NULL;
        }
    }
    printf("\n-->Ficheiro aberto ,verificando pessoas...\n\n");
    fclose(f);
    return lista;
}

//Funcao de inicializacao dos espacos
plocal InicializaEspaco(int *total){
    char ficheiro[NOMEFICH];
    FILE *f;
    int Verifica=0;
    int nLocais = 0;
    
    do{
    printf("----Fase de Preparacao----\n");
    printf("Introduza o nome do ficheiro de espacos:\n");
    scanf("%s",&ficheiro);
    f = fopen(ficheiro,"rb");//abre para leitura binaria
    if(f==NULL){
        printf("-->Este nao e um ficheiro existente.\n\n");
        system("pause");
        system("cls");
    }
    }while(f == NULL);//testa se é um ficheiro valido
    fclose(f);
    
    plocal Locais = NULL;
    
    Locais=CriaVetor(ficheiro,&nLocais);//Cria vetor dinamico
    
    //se Locais for NULL,a função termina
    if(Locais==NULL){
        return NULL;
    }else
        printf("-->Ficheiro aberto corretamente e informacao guardada , nao verificada\n\n");
 
    Verifica=VerificaEspaco(Locais,&nLocais);//Verifica dados
   
    printEspacos(Locais,&nLocais);//Print dos espaços
    
    if(Verifica == -1){//Verificaçao falha
        free(Locais);
        return NULL;
    }
    *total=nLocais;
    printf("-->Informacao de espacos validada");
    return Locais;
}

//Funcao de inicializacao das pessoas
pPessoa InicializaPessoa(int *total){
    FILE *f;
    char ficheiro[20];
    int nPessoas=0;
    
    do{
    printf("----Fase de Preparacao----\n");
    printf("Introduza o nome do ficheiro de Pessoas:\n");
    scanf("%s",&ficheiro);
    f =fopen(ficheiro,"rt");//Leitura texto
    if(f==NULL){
        printf("-->Este nao e um ficheiro existente.\n\n");
        system("pause");
        system("cls");
    }
    }while(f == NULL);//testa ficheiro valido
    fclose(f);
    
    pPessoa Lista = NULL;
    //Cria a listra ligada
    Lista=CriaLista(ficheiro,Lista,&nPessoas);
    *total=nPessoas;
    
    if(Lista==NULL){//Se a lista é NULL
        printf("Ficheiro Invalido\n");
        return NULL;
    }
    //Print das pessoas na lista
    PrintPessoas(Lista);
    printf("\n-->Informacoes de Pessoas validada\n");
    return Lista;
}

//Funcao que verifica a capacidade total de todas as salas e o numero de pessoas(retorna a diferença se existirem pessoas a mais)
int Capacidade(plocal Locais,int totalLocais,int *totalPessoas){
    
    int CapTotal=0,flag=0,elim=0;
    
    for(int i=0;i<totalLocais;i++){//Capacidade total de todos os espaços
        CapTotal+=Locais[i].capacidade;
    }
    if(CapTotal==0){//Se capacidade total for 0 programa acaba
        printf("Nao existe capacidade nas salas[0].\n");
        return -1;
    }
    if(*totalPessoas > CapTotal){
        elim=(*totalPessoas-CapTotal);
        return elim;  //Retorna Quantas pessoas a eliminar
    }
    else return 0;//Retorna 0
}

//Funcao que associa as pessoas aos espacos
pConjunto Associa(plocal Locais,pPessoa Incluidos,int totalLocais,int totalPessoas){
    
    pConjunto Salas;
    int i,k,indice;
    
    Salas = malloc(sizeof(Conjunto)*totalLocais);//Alocar espaço suficiente para as estruturas do tipo Conjunto
    
    if(Salas==NULL){//Se alocação falhou
        free(Salas);
        printf("Erro na alocacao de memoria\n");
        return NULL;
    }
    
    for(int k=0;k<totalLocais;k++){//Inicializar parametros das estruturas a NULL e 0
        Salas[k].Participantes=NULL;
        Salas[k].PessoasLocal=0;
    }
    
    for(i=0;   i<totalLocais;  i++){//para cada Local nos Conjuntos(Salas[i]),preencher os seus campos
        Salas[i].Atual.capacidade=Locais[i].capacidade;
        Salas[i].Atual.id=Locais[i].id;
        for(k=0;k<3;k++)
        Salas[i].Atual.liga[k]=Locais[i].liga[k];
    }

    pPessoa novo,aux;
    pPessoa temp;
    aux=Incluidos;//Para nao perder inicio da lista  "Incluidos"
    
    for(int j=0;j<totalPessoas;j++){//Para o total de pessoas existentes
        
        novo=malloc(sizeof(Pessoa));//Alocar memoria para as pessoas
        
            if(novo==NULL){//Se alocação falhou
                free(novo);
                printf("Erro na alocacao de memoria\n");
                return NULL;
            }
        
            *novo=*aux; //Copiar conteudo 
            aux=aux->prox;
            novo->prox=NULL;
            //printf("  %s %d %c %d ",novo->Identificador,novo->idade,novo->estado,novo->dias);
 
          do{  
              indice=intUniformRnd(0, (totalLocais-1));
          
          }while(Salas[indice].PessoasLocal >= Salas[indice].Atual.capacidade);//enquanto nos é dado um indice de uma sala cheia,gerar outro
            Salas[indice].PessoasLocal+=1;//Incrementar pessoas na sala Correspondente ao indice
            
            temp=Salas[indice].Participantes;//Nao perder acesso ao inicio(usa-se um ponteiro auxiliar)
            
            if(Salas[indice].Participantes == NULL){//Se é o primeiro elemento
                Salas[indice].Participantes = novo;
            }else{
            while(temp->prox != NULL){//percorre ate chegar ao fim
                temp=temp->prox;
            }
            temp->prox=novo;//Ultimo elemento->nova pessoa;
           // printf("  %s %d %c %d \n",temp->Identificador,temp->idade,temp->estado,temp->dias);
            }
    }
    return Salas;
  }

//Funcao que da print a estruturas do tipo Conjuntos
void printConjuntos(pConjunto Salas,int totalLocais){
    /*PRINT SEM UTILIZAR FUNCOES
    pPessoa p;
    int i;
    for(i=0;i<totalLocais;i++){
        p=Salas[i].Participantes;
        printf("\n       Espaco:\n");
        printf("--------------------\n");
        printf("ID: %d \n",Salas[i].Atual.id);
        printf("CAP: %d \n",Salas[i].Atual.capacidade);
        printf("Liga Com:");
        for(int k=0;k<3;k++)
            printf(" %d ",Salas[i].Atual.liga[k]);
        printf("\n--------------------\n");
        while(p!=NULL){
            printf(" %s %d %c %d ",p->Identificador,p->idade,p->estado,p->dias);
            p=p->prox;
           }
        putchar('\n');
    }*/
    int r=1;
    for(int i=0;i<totalLocais;i++){
        printEspacos(&Salas[i].Atual,&r);//Funcao printEspacos
        printf(" Numero de Pessoas:%d \n",Salas[i].PessoasLocal);//Pessoas por local
        PrintPessoas(Salas[i].Participantes);//Funcao printPessoas
        printf("\n");
    }
}

//Funcao que Chama todas as outras e retorna sucesso  ou nao (NULL)
pConjunto Preparacao(int *nLocais){
    int totalLocais=0,totalPessoas=0,flag_elim=0;
    plocal Locais;
    
    Locais=InicializaEspaco(&totalLocais);//Inicializa Espaços

    if(Locais == NULL)//acaba Programa
        return NULL;
    
    printf("\nNumero de locais: %d\n",totalLocais);
    system("pause");
    system("cls");
    
    pPessoa Pessoas;
    Pessoas=InicializaPessoa(&totalPessoas);//Inicializa Pessoas
    
    if(Pessoas == NULL)//Acaba Programa
        return NULL;
    
    printf("\nNumero de Pessoas: %d\n",totalPessoas);
    system("pause");
    system("cls");
    
    flag_elim=Capacidade(Locais,totalLocais,&totalPessoas);//Quantas pessoas tem de eliminar
    
    if(flag_elim == -1){//Capacidade total dos espacos é 0
        Pessoas=FreePessoa(Pessoas,totalPessoas);
        return NULL;
    }else if(flag_elim != 0){//Elimina flag_elim pessoas do fim da lista ligada de pessoas
        printf("-->Nao existe espaco para todas as pessoas,deve eliminar %d\n",flag_elim);
        Pessoas=FreePessoa(Pessoas,flag_elim);
        totalPessoas=totalPessoas-flag_elim;         //Atualiza numero de pessoas
        PrintPessoas(Pessoas);
        printf("\n->Ultimas %d pessoas eliminadas",flag_elim);
    }else {//Continua com a execução
        printf("\n-->Existe espaco suficiente para todas a pessoas!\n");
        PrintPessoas(Pessoas);
    }
    //Associar Pessoas às salas
    pConjunto Salas;
    Salas=Associa(Locais,Pessoas,totalLocais,totalPessoas);//Associa as pessoas às salas
    printf("\n\n-->Pessoas associadas a salas!\n\n");
        system("pause");
        system("cls");
    //Dar free á memória anteriomente alocada(Pessoas e locais)
    Pessoas=FreePessoa(Pessoas,totalPessoas);//Da Free As Pessoas
    free(Locais);   //Da Free Aos Locais
    *nLocais=totalLocais; //Numero de locais
     return Salas;
}




