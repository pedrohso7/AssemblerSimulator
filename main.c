#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Assembler_Functions.h"

int main()
{
    FILE *arqEntrada, *arqSaida;
    char c, *segmento, instrucao[30];
    int i, j, contaInstrucao=0, opcode, reg[3], Function, shamt, Tinstrucao,deslocou;

    arqEntrada = fopen("Entrada.txt","r");
    arqSaida = fopen("Saida.txt","w");

    /*Contando a quantidade total de instruções*/
    while((c = fgetc(arqEntrada)) != EOF){
        if(c == '\n'){
            contaInstrucao++;
        }
    }

    rewind(arqEntrada);

    for(i=0;i<contaInstrucao;i++){
        fscanf(arqEntrada," %[^\n]", instrucao); /* Lê uma linha(instrução) do arquivo */
        //printf("%s",instrucao);
        j=0; /* Inicia o vetor de registradores */
        deslocou = FALSE; /* Verifica se acontecem deslocamentos */
        /*Divide a instrução*/
        segmento = strtok(instrucao," ,$");
        defineOperacao(segmento,&opcode,&shamt,&Function,&Tinstrucao);

        /* Assembly do MIPS: add $t0,$s1,$s2    sll $t1,$s0,4 */
        while(segmento != NULL){
            segmento = strtok(NULL," ,$");

            if (segmento == NULL)
                break;
            reg[j] = retornaReg(segmento,&deslocou,opcode);
            j++;
        }
        if(deslocou == TRUE){
            shamt = reg[2];
            reg[2] = reg[1];
            reg[1] = 0;
        }
        retornaSaida(arqSaida,opcode,reg,shamt,Function,Tinstrucao);
        fprintf(arqSaida,"\n");
    }

    fclose(arqEntrada);
    fclose(arqSaida);

    return 0;
}
