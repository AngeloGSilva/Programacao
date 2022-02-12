#include "Headers.h"

//Funcao que adiciona um dia a todos os doentes
pConjunto AdicionaDias(pConjunto Salas,int nSalas){
    pPessoa aux;
    
    for(int i=0;i<nSalas;i++){          //Por sala,verifica se a pessoa atual é doente,
        aux=Salas[i].Participantes;     
        while(aux!=NULL){               
            if(aux->estado== 'D'){     //Se é doente os dias sao incrementados por 1
            aux->dias= aux->dias + 1;
            }
            aux=aux->prox;             //Senao passa para a proxima pessoa
        }
    }
    return Salas;
}

//Quando um doente se cura por probabilidade
pConjunto ProbSaudavel(pConjunto Salas,int nSalas){
    //Probabilidade de recuperação e taxa de imunidade
    pPessoa aux;
    int probCurar=0,probImune=0;
    for(int i=0;i<nSalas;i++){              //Percorre salas
        aux=Salas[i].Participantes;
        while(aux!=NULL){                  //Percorre pessoas
            if(aux->estado == 'D'){         //Se forem doentes
                probCurar=probEvento((float)1/(*aux).idade);//calcula prob de se curar
                if(probCurar == 1){         //Se o doente se cura
                    probImune=probEvento(0.20);//calcula prob de serimune
                    if(probImune== 1){      //Se a prob é concedida fica I
                        aux->estado = 'I';
                        aux->dias= -1;
                    }else{                  //Caso contrario fica saudavel
                        aux->estado = 'S';
                        aux->dias= -1;
                    }
                }
            }
            aux=aux->prox;              
        }
    }
    return Salas;
}

//Quando o limite de dias doente é alcançado
pConjunto LimiteDias(pConjunto Salas,int nSalas){
    //Duração máxima da infeção e taxa de imunidade
    int probImune = 0;

    pPessoa aux = NULL;
    int resto = 0;

    for(int i = 0; i<nSalas; i++){    //Percorre Salas
        aux = Salas[i].Participantes;
        while(aux != NULL){         //Percorre pessoas
            if(aux->estado == 'D'){
            resto = aux->idade / 10;
            resto = resto + 5;
            if (resto <= aux->dias){       //Se os dias de doença alcançaram o limite Este é curado
                probImune = probEvento (0.20);  //Prob de ficar imune
                if(probImune == 1){        //Se é concedida
                    aux->estado = 'I';      //Fica IMUNE
                    aux->dias= -1;
                }else{                      //Senao
                    aux->estado = 'S';      //Fica Saudavel
                    aux->dias = -1;
                } 
            }
          }
        aux = aux->prox;
       }
    }
    return Salas;
}

//Infetar pessoas na mesma sala quando possivel
pConjunto TaxaDissemminacao(pConjunto Salas,int nSalas){
    
    int nDoentes[nSalas];
    int probInfetar[nSalas]; //Declaração int pois não existem pessoas e meio
    int indice;
    pPessoa p=NULL;
    
    for(int k=0;k<nSalas;k++){ //Por os dois arrays todos a 0
        nDoentes[k]=0;
        probInfetar[k]=0;
    }
    for(int i=0;i<nSalas;i++){//Calculo do numero de doentes e probabilidade de infetar por sala
        p=Salas[i].Participantes;
        probInfetar[i]=Salas[i].PessoasLocal*0.05;//Se for maior que 1 cada doente infeta 1 pessoa
        while(p != NULL){
            if(p->estado == 'D'){
                nDoentes[i]+=1;
            }
            p=p->prox;
        }
    }
    //Mostra numero de doentes e a prob Infetar por sala
    for(int i=0;i<nSalas;i++){
        printf("==>Sala %d ",i+1);
        printf("Doentes");
        printf("%d    ",nDoentes[i]);
        printf("Cada doente infeta:");
        printf("%d",probInfetar[i]);
        putchar('\n');
    }
    
    pPessoa aux=NULL;
    for(int k=0;k<nSalas;k++){                      //Percorre Salas
        if(nDoentes[k] > 0 && probInfetar[k] > 0){  //Se existem doentes e este teem probabilidade de infetar
            for(int i=0;i<probInfetar[k];i++){      //Faz ciclo 1 vezes ate "infetar" i pessoas
                while(nDoentes[k]!=0){              //Faz por doente
                indice=intUniformRnd(0,Salas[k].PessoasLocal-1); //Indice random
                //printf("%d\n",indice);
                aux=Salas[k].Participantes;     
                for(int k=1;k < indice;k++)//percorre lista indice vezes
                    aux=aux->prox;
                if(aux->estado == 'D' || aux->estado== 'I'){ //Se alcançaum doente/Imune nao faz nada
                    
                }else{               //Se é um saudavel Infeta-o
                    aux->estado='D';
                    aux->dias=0;
                }
                printf("NDoentes %d\n",nDoentes[k]);
                nDoentes[k]=nDoentes[k]-1;
            }
        }
      }
    }
    return Salas;
}

//Funcao que avanca um dia na simulacao
pConjunto AvancaDia(pConjunto Salas,int nSalas){
    /*
    int nDoentes[nSalas];
    int probInfetar[nSalas]; //DECLARADO EM INT PORQUE UMA PESSOA È UMA UNIDADE
    int indice;
    pPessoa p=NULL;
    
    for(int k=0;k<nSalas;k++){
        nDoentes[k]=0;
        probInfetar[k]=0;
    }
     */
    /*
    //Duração máxima da infeção e taxa de imunidade
    Salas=LimiteDias(Salas,nSalas);

    printConjuntos (Salas, nSalas);
    
    for(int i=0;i<nSalas;i++){
        p=Salas[i].Participantes;
        probInfetar[i]=Salas[i].PessoasLocal*0.05;
        while(p != NULL){
            if(p->estado == 'D'){
                nDoentes[i]+=1;
            }
            p=p->prox;
        }
    }
    */
    /*
    for(int i=0;i<nSalas;i++){
        printf("Doentes");
        printf("%d",nDoentes[i]);
        printf("Probabilidade");
        printf("%d",probInfetar[i]);
        putchar('\n');
    }
    
    pPessoa aux=NULL;
    for(int k=0;k<nSalas;k++){                      //CICLO SALAS
        if(nDoentes[k] > 0 && probInfetar[k] > 0){
            for(int i=0;i<probInfetar[k];i++){
                while(nDoentes[k]!=0){
                indice=intUniformRnd(0,Salas[k].PessoasLocal-1);
                printf("...........-.-.--------------------.,\n");
                printf("%d\n",indice);
                aux=Salas[k].Participantes;
                for(int k=1;k < indice;k++)
                    aux=aux->prox;
                if(aux->estado == 'D' || aux->estado== 'I'){
                    
                }else{
                    aux->estado='D';
                    aux->dias=0;
                }
                printf("NDoentes %d\n",nDoentes[k]);
                nDoentes[k]=nDoentes[k]-1;
            }
        }
      }
    }
    printConjuntos(Salas,nSalas);
    */
    /*
    //Probabilidade de recuperação e taxa de imunidade
    pPessoa aux2;
    int probCurar=0,probImune=0;
    for(int i=0;i<nSalas;i++){
        aux2=Salas[i].Participantes;
        while(aux2!=NULL){
            if(aux2->estado == 'D'){
                probCurar=probEvento((float)1/(*aux2).idade);
                if(probCurar == 1){
                    probImune=probEvento(0.20);
                    if(probImune== 1){
                        aux2->estado = 'I';
                        aux2->dias= -1;
                    }else{
                        aux2->estado = 'S';
                        aux2->dias= -1;
                    }
                }
            }
            aux2=aux2->prox;
        }
    }
     * */
    /*
    //Aumenta dias das pessoas;
    pPessoa aux4;
    
    for(int i=0;i<nSalas;i++){
        aux4=Salas[i].Participantes;
        while(aux4!=NULL){
            if(aux4->estado== 'D'){
            aux4->dias= aux4->dias + 1;
            }
            aux4=aux4->prox;
        }
    }
     */
    //Funcao chamada pela main que simula o avanço de um dia
    printf("-->Dia Avancado!\n\n");
    
    Salas=LimiteDias(Salas,nSalas);
    
    Salas=TaxaDissemminacao(Salas,nSalas);
    
    Salas=ProbSaudavel(Salas,nSalas);
    
    Salas=AdicionaDias(Salas,nSalas);
    
    system("pause");
    return Salas;   
}

//Mostra as estatisticas
void MostraEstatisticas(pConjunto Salas,int nSalas){
    
    int nDoentes[nSalas],nImunes[nSalas],nSaudaveis[nSalas];
    int totalDoentes=0,totalImunes=0,totalSaudaveis=0;
    float perDoentes=0,perImunes=0,perSaudaveis=0;
    int totalP=0;
    pPessoa p=NULL;
    
    for(int k=0;k<nSalas;k++){
        nDoentes[k]=0;
        nSaudaveis[k]=0;
        nImunes[k]=0;
    }
    //calcular numero de doentes/imunes/saudaveis por sala
    for(int i=0;i<nSalas;i++){
        p=Salas[i].Participantes;
        totalP=totalP+Salas[i].PessoasLocal;
        while(p!=NULL){
            if(p->estado=='D')
                nDoentes[i]=nDoentes[i]+1;
            if(p->estado=='S')
                nSaudaveis[i]=nSaudaveis[i]+1;
            if(p->estado=='I')
                nImunes[i]=nImunes[i]+1;
            p=p->prox;
        }
    }
    //Calcular numero de doentes/Imunes/Sudaveis por sala
    for(int m=0;m<nSalas;m++){
        totalDoentes=totalDoentes+nDoentes[m];
        totalSaudaveis=totalSaudaveis+nSaudaveis[m];
        totalImunes=totalImunes+nImunes[m];
    }
    
    int r=1;
    perDoentes=(float)totalDoentes/totalP;
    perImunes=(float)totalImunes/totalP;
    perSaudaveis=(float)totalSaudaveis/totalP;
    
    printf("\n\n");
    printf("----------Estatisticas da iteracao atual:----------\n");
    printf("-->Para um total de %d pessoas Participantes:\n",totalP);
    printf("->Pessoas Doentes: %d   Percentagem de doentes:%.2f por cento.\n",totalDoentes,perDoentes*100);
    printf("->Pessoas Imunes: %d   Percentagem de doentes:%.2f por cento.\n",totalImunes,perImunes*100);
    printf("->Pessoas Saudaveis: %d   Percentagem de doentes:%.2f por cento.\n",totalSaudaveis,perSaudaveis*100);
    printf("-----------------------------------------------------\n");
    
    printf("\n\n->Estatisticas por sala:\n\n");
    
    for(int i=0;i<nSalas;i++){
        printf("-------------------------Sala %d-------------------------\n",i+1);
        printEspacos(&Salas[i].Atual,&r);
        printf(">Pessoas no espaco de id %d:",i+1);
        printf(" %d\n",Salas[i].PessoasLocal);
        PrintPessoas(Salas[i].Participantes);
        printf("\n");
        printf("->Pessoas Doentes: %d\n",nDoentes[i]);
        printf("->Pessoas Imunes: %d\n",nImunes[i]);
        printf("->Pessoas Saudaveis: %d\n",nSaudaveis[i]);
        printf("\n");
    }
    system("pause");
}

//Adiciona doente a uma determinada sala
pConjunto addDoente(pConjunto Salas,int nSalas){
    
    int id=0,flagID=0;
    pPessoa aux=NULL,novo=NULL;
    
    do{
    printf("Indique o id da sala de destino:");
    scanf("%d",&id);
    if(id<=0){
        printf("[ID's devem ser positivos!]\n");
    }
    }while(id<=0);
        
    for(int i=0;i<nSalas;i++){
        if(id==Salas[i].Atual.id)
            flagID=1;
    }
    
    if(flagID==0){
        printf("ID nao existe!\n");
        system("pause");
        return Salas;
    }
    
    int j=0;
    while(id!=Salas[j].Atual.id)
        j++;
    
    aux=Salas[j].Participantes;
    
    if(Salas[j].PessoasLocal < Salas[j].Atual.capacidade){//Se existe espaco
        novo=malloc(sizeof(Pessoa));
        
        if(novo == NULL){
            printf("Erro ao alocar memoria!");
            free(novo);
            return Salas;
        }
        
        printf("Identificador:");
        scanf("%s",novo->Identificador);
        printf("Idade:");
        scanf("%d",&novo->idade);
        printf("Dias de doenca:");
        scanf("%d",&novo->dias);
        novo->estado='D';
        novo->prox=NULL;
        for(int k=0;k<nSalas;k++){
        //Se o utilizador tiver campos invalidos ou ja existe
        if(VerificaDados(*novo,Salas[k].Participantes) == -1){
            printf("Campos de utilizador Invalidos!\n");
            system("pause");
            return Salas;
         }
        }
        
        if(Salas[j].Participantes==NULL){   //Se a sala esta vazia
            Salas[j].Participantes=novo; 
        }else{
        while(aux->prox!=NULL){             //Percorre ate ultimo da lista ligada
            aux=aux->prox;
        }           
        aux->prox=novo;
        }
        Salas[j].PessoasLocal=Salas[j].PessoasLocal+1;      //Incrementa numero de pessoas na sala
        return Salas;
    }else{
        printf("Nao existe espaco na sala de id %d",id);
        return Salas;
    }    
}

//Transfere pessoas de uma sala para outra
pConjunto TransferePessoas(pConjunto Salas,int nSalas){
    
    int idOri=0,idDest=0,flagOri=0,flagDest=0,Num=0,flagLiga=0;
    
    printf("Insira o ID de origem:\n");
    fseek(stdin,0,SEEK_END);                //Evitar letras
    scanf("%d",&idOri);
    printf("Insira o ID de destino:\n");
    fseek(stdin,0,SEEK_END);                //Evitar letras
    scanf("%d",&idDest);
    
    for(int i=0;i<nSalas;i++){  //Verifica se id origem existe
        if(idOri==Salas[i].Atual.id)
            flagOri=1;
    }
    
    for(int i=0;i<nSalas;i++){  //Verifica se id destino existe
        if(idDest==Salas[i].Atual.id)
            flagDest=1;
    } 
    
    if(flagOri != 1 || flagDest!=1){ //Se um deles nao existir
        if(flagOri!=1)
            printf("Id de Origem nao existe![%d]\n",idOri);
        if(flagDest!=1)
            printf("Id de Destino nao existe[%d]\n",idDest);
        system("pause");
        return Salas;
    }
    
    if(idOri==idDest){//Se id forem iguais
        printf("IDs sao iguais!\n");
        system("pause");
        return Salas;
    }
    //Ciclos que vao arranjar o indice no Salas a que o id da sala corresponde
    int LenOri=0,LenDest=0;
    
    while(idOri!=Salas[LenOri].Atual.id)
        LenOri++;
    
    while(idDest!=Salas[LenDest].Atual.id)
        LenDest++;
    //So é preciso verificar um lado,pois as verificações de ligações comuns foi realizada
    for(int k=0;k<3;k++){
        if(Salas[LenOri].Atual.liga[k] == idDest)
            flagLiga=1;
    }
    
    if(flagLiga == 0){
        printf("As salas nao estao ligadas!\n");
        system("pause");
        return Salas;
    }
    
    if(Salas[LenDest].PessoasLocal >= Salas[LenDest].Atual.capacidade){//Sala de destino ja esta cheia
        printf("Sala de destino esta preenchida");
        system("pause");
        return Salas;
    }
    
    do{
    printf("Insira o numero de pessoas a transferir:");
    scanf("%d",&Num);
    //mensagens informativas
    if(Num<0)
        printf("Numero de transferencia invalido[Negativo]\n");
    if(Num==0){
        printf("0 pessoas movidas com sucesso!");
        system("pause");
        return Salas;
    }
    if(Salas[LenDest].Atual.capacidade< Num)
        printf("A sala de destino nao tem essa capacidade!\n");

    }while(Salas[LenDest].Atual.capacidade < Num);
    
    
    if(Salas[LenOri].PessoasLocal < Num){//Origem nao tem pessoas suficientes
        printf("Local de origem nao tem pessoas suficientes\n");
        system("pause");
        return Salas;
    }
    
    if(Salas[LenDest].PessoasLocal + Num > Salas[LenDest].Atual.capacidade){//Destino na tem espaço suficiente
        printf("Local de destino nao tem espaco suficiente!\n");
        system("pause");
        return Salas;
    }
    //Retirar N pessoas
    pPessoa aux=NULL,removido=NULL;
    
    int indice=0,flag;
    pPessoa auxR=NULL,antesR=NULL;
    
    for(int k=0;k<Num;k++){//Enquanto nao retirar suficientes
        antesR=NULL;
        auxR=Salas[LenOri].Participantes;
        indice = intUniformRnd(0,Salas[LenOri].PessoasLocal-1); // Vai buscar uma aleatoria
        flag=indice;
                
        while(flag!=0){     //no correspondente ao indice
            antesR=auxR;
            auxR=auxR->prox;
            flag--;
        }
        
        if(indice==0 && auxR->prox==NULL){          //Retira do inicio de uma lista sem nada
            Salas[LenOri].Participantes = NULL;
            removido=auxR;
        }else if(indice == 0 && auxR->prox!=NULL){  //Retira do inicio de uma lista com mais elementos
            Salas[LenOri].Participantes=auxR->prox;
            removido=auxR;
        }else if (indice !=0 && auxR->prox!=NULL){  //Retira do meio de uma lista de elementos
            antesR->prox=auxR->prox;
            removido=auxR;
        }else{                                      //Retira do fim da lista
            antesR->prox=NULL;
            removido=auxR;        
        }
    //Posicionar na lista de destino
        aux=Salas[LenDest].Participantes;
        if(aux==NULL){//Se destino nao tem pessoas
            Salas[LenDest].Participantes=removido;
        }else{
        while(aux->prox!=NULL){//enquanto nao esta no fim
            aux=aux->prox;
            }
        aux->prox=removido;//o no removido e inserido no campo prox do ultimo no da lista de destino
    }
        removido->prox=NULL;
        Salas[LenOri].PessoasLocal=Salas[LenOri].PessoasLocal-1;//Atualizar numero de pessoasnas salas
        Salas[LenDest].PessoasLocal=Salas[LenDest].PessoasLocal+1;
    }
   return Salas;
}

/*
pLConj GuardaListaLigada(pLConj Linked,pConjunto Conjunto){
        pLConj aux,novo;
        aux=Linked;
        while(aux!=NULL){
            aux=aux->prox;
        }
        novo=malloc(sizeof(pLConj));
        
        *novo=*Conjunto;
        aux=novo;
    return Linked;
}
*/

//No final da simulacao imprime um ficheiro de pessoas e o relatorio
void ImprimeFinal(pConjunto Salas,int nSalas,int iteracoes){
    FILE *f=NULL,*r=NULL;
    int indice=0;
    char nomeFicheiro[NOMEFICH];
    pPessoa aux;
    //Populacao na ultima iteracao
    printf("Nome do ficheiro que vai guardar populacao:");
    scanf("%s",&nomeFicheiro);
    
    f=fopen(nomeFicheiro,"wt");//Cria e escreve
    fprintf(f,"----População final:----\n\n");
    for(int i=0;i<nSalas;i++){
        aux=Salas[i].Participantes;
        while(aux!=NULL){
            fprintf(f,"Pessoa %d:\n",indice+1);
            fprintf(f,"Identificador:");
            fprintf(f,"%s\n",aux->Identificador);
            fprintf(f,"Idade:");
            fprintf(f,"%d\n",aux->idade);
            fprintf(f,"Estado:");
            fprintf(f,"%c\n",aux->estado);
            if(aux->estado=='D'){
                fprintf(f,"Dias de doente:");
                fprintf(f," %d\n",aux->dias);
            }
                fprintf(f,"\n");
         aux=aux->prox;
         indice++;
        }
    }
    fprintf(f,"Total de Pessoas:%d",indice);
    fclose(f);
    
    
    
    //Relatorio FINAL
    r=fopen("report.txt","wt");
    
    fprintf(f,"--------Relatorio Final--------");
        int nDoentes[nSalas],nImunes[nSalas],nSaudaveis[nSalas];
    int totalDoentes=0,totalImunes=0,totalSaudaveis=0;
    int totalP=0;
    pPessoa p=NULL,p1=NULL;
    
    for(int k=0;k<nSalas;k++){
        nDoentes[k]=0;
        nSaudaveis[k]=0;
        nImunes[k]=0;
    }
    
    for(int i=0;i<nSalas;i++){
        p=Salas[i].Participantes;
        totalP=totalP+Salas[i].PessoasLocal;
        while(p!=NULL){
            if(p->estado=='D')
                nDoentes[i]=nDoentes[i]+1;
            if(p->estado=='S')
                nSaudaveis[i]=nSaudaveis[i]+1;
            if(p->estado=='I')
                nImunes[i]=nImunes[i]+1;
            p=p->prox;
        }
    }
    
    for(int m=0;m<nSalas;m++){
        totalDoentes=totalDoentes+nDoentes[m];
        totalSaudaveis=totalSaudaveis+nSaudaveis[m];
        totalImunes=totalImunes+nImunes[m];
    }
    
    fprintf(f,"\n\n");
    fprintf(f,"==========Estatisticas da iteracao %d:==========\n",iteracoes);
    fprintf(f,"-->Para um total de %d pessoas Participantes:\n",totalP);
    fprintf(f,"->Pessoas Doentes: %d\n",totalDoentes);
    fprintf(f,"->Pessoas Imunes: %d\n",totalImunes);
    fprintf(f,"->Pessoas Saudaveis: %d\n",totalSaudaveis);
    
    for(int i=0;i<nSalas;i++){
        fprintf(f,"-------------------------Sala %d-------------------------\n",i+1);
        //Specs da sala
        fprintf(f," Espaco:\n");
        fprintf(f,"--------------------\n");
        fprintf(f,  "  ID Local:%d\n",Salas[i].Atual.id);
        fprintf(f,"  Capacidade Local:%d\n",Salas[i].Atual.capacidade);
        fprintf(f,"  Ligacoes:%d %d %d\n",Salas[i].Atual.liga[0],Salas[i].Atual.liga[1],Salas[i].Atual.liga[2]);
        fprintf(f,"--------------------\n");
        fprintf(f,">Pessoas no espaco de id %d:",Salas[i].Atual.id);
        fprintf(f," %d\n",Salas[i].PessoasLocal);
        //pessoas na sala
        p1=Salas[i].Participantes;
        if(p1!=NULL){
            while(p1!= NULL){
                fprintf(f,"  Identificador:%s    Idade:%d    Estado:%c",p1->Identificador,p1->idade,p1->estado);
                 if(p1->dias == -1){
                    fprintf(f,"\n");
                 }else{
                    fprintf(f,"  Dias:%d\n",p1->dias);
                        }
                p1=p1->prox;
            }
    }else
        fprintf(f,"\n-->Lista Vazia\n");
        fprintf(f,"\n");
        fprintf(f,"==Estatisticas da sala %d==\n",i);
        fprintf(f,"->Pessoas Doentes: %d\n",nDoentes[i]);
        fprintf(f,"->Pessoas Imunes: %d\n",nImunes[i]);
        fprintf(f,"->Pessoas Saudaveis: %d\n",nSaudaveis[i]);
        fprintf(f,"\n");
    }
    fclose(r);
    
}

//Liberta todos os elementos de um Conjunto
void FreeConjuntos(pConjunto Salas,int nSalas){
    for (int i=0;i<nSalas;i++){
        Salas[i].Participantes=FreePessoa(Salas[i].Participantes,Salas[i].PessoasLocal);//Liberta as pessoas da sala i
    }
    free(Salas);//Liberta as Salas
}