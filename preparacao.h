

#ifndef PREPARACAO_H
#define PREPARACAO_H

    //-----------Funcoes de Inicialização

//Funcao de inicializacao das pessoas
pPessoa InicializaPessoa(int *pPessoa);

//Funcao de inicializacao dos espacos
plocal InicializaEspaco(int *pLocais);

//Funcao que Chama todas as outras e retorna sucesso  ou nao (NULL)
pConjunto Preparacao(int *nLocais);

    //-----------Funções de Criação e verificação de Locais

//Funcao que cria o vetor dinamico de estruturas
plocal CriaVetor(char *nomeFicheiro,int *nLocais);

//Funcao que da print a todos os espacos
void printEspacos(plocal local,int *nLocais);

//Funcao que Verifica as informacoes dos espacos
int VerificaEspaco(plocal Locais,int *nLocais);

    //------------Fuções de Criação e Verificação de pessoas

//Funcao que cria a lista ligada de pessoas
pPessoa CriaLista(char NomeFich[],pPessoa Lista,int *nPessoas);

//Funcao que da print às pessoas
void PrintPessoas(pPessoa Lista);

//Funcao que Verifica os dados das pessoas
int VerificaDados(Pessoa buffer,pPessoa lista);

    //---------Funções de distribuição de pessoas

//Funcao que liberta elimina elementos de uma lista ligada(a partir do fim)
pPessoa FreePessoa(pPessoa p,int elimina);

//Funcao que verifica a capacidade total de todas as salas e o numero de pessoas(retorna a diferença se existirem pessoas a mais)
int Capacidade(plocal Locais,int totalLocais,int *totalPessoas);

//Funcao que associa as pessoas aos espacos
pConjunto Associa(plocal Locais,pPessoa Participantes,int totalLocais,int totalPessoas);

//Funcao que da print a estruturas do tipo Conjuntos
void printConjuntos(pConjunto Salas,int totalLocais);

#endif /* PREPARACAO_H */

