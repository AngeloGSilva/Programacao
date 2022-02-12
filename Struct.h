
#ifndef STRUCT_H
#define STRUCT_H

//Struct de Pessoas
typedef struct pessoa Pessoa,*pPessoa;
struct pessoa{
    char Identificador[20];//identificador unico
    int idade;//Idade da pessoa
    char estado;//estado da pessoa
    int dias;//dias de doença
    pPessoa prox;
};

//Struct de Espaços
typedef struct sala local, *plocal;
struct sala{
 int id; // id numérico do local
 int capacidade; // capacidade máxima
 int liga[3]; // id das ligações (-1 nos casos não usados)
};

//Struct de junçao das pessoas e espaços
typedef struct Conjunto Conjunto,*pConjunto;
struct Conjunto{
    local Atual;
    pPessoa Participantes;
    int PessoasLocal;
};

//Guardar a informação das salas em listas ligadas.
typedef struct ConjuntoLigado LConj,*pLConj;
struct ConjuntoLigado{
    pConjunto E;
    pLConj prox;
};

#endif /* STRUCT_H */

