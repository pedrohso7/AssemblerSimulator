#ifndef ASSEMBLER_FUNCTIONS_H_INCLUDED
#define ASSEMBLER_FUNCTIONS_H_INCLUDED

#define TRegistrador 0
#define TImediato 1

#define TRUE 1
#define FALSE 0

#define MaxBits 16

#define REG 0
#define OPCODE 1
#define SHAMT 0
#define FUNCTION 1
#define ENDERECO 2


void defineOperacao(char *segmento,int *opcode,int *shamt,int *Function,int *Tinstrucao);
int retornaReg(char *segmento,int *deslocou,int opcode);
int* retornaBinario(int n,int *contPosicoes);
void geraInstrucaoBinaria(FILE *arqSaida,int n,int TCadeia);
void retornaSaida(FILE *arqSaida,int opcode,int *reg,int Shamt,int Function,int Tinstrucao);
#endif // ASSEMBLER_FUNCTIONS_H_INCLUDED
