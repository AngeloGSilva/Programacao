

#ifndef SIMULACAO_H
#define SIMULACAO_H
//Funcao que avanca um dia na simulacao
pConjunto AvancaDia(pConjunto Salas,int nSalas);

//Funcao que adiciona um dia a todos os doentes
pConjunto AdicionaDias(pConjunto Salas,int nSalas);

//Quando um doente se cura por probabilidade
pConjunto ProbSaudavel(pConjunto Salas,int nSalas);

//Quando o limite de dias doente é alcançado
pConjunto LimiteDias(pConjunto Salas,int nSalas);

//Infetar pessoas na mesma sala quando possivel
pConjunto TaxaDissemminacao(pConjunto Salas,int nSalas);

//Mostra as estatisticas
void MostraEstatisticas(pConjunto Salas,int nSalas);

//Adiciona doente a uma determinada sala
pConjunto addDoente(pConjunto Salas,int nSalas);

//Transfere pessoas de uma sala para outra
pConjunto TransferePessoas(pConjunto Salas,int nSalas);

//Liberta todos os elementos de um Conjunto
void FreeConjuntos(pConjunto Salas,int nSalas);

//No final da simulacao imprime um ficheiro de pessoas e o relatorio
void ImprimeFinal(pConjunto Salas,int nLocais,int iteracoes);


#endif /* SIMULACAO_H */

