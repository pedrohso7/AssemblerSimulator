#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Assembler_Functions.h"

void defineOperacao(char *segmento,int *opcode,int *shamt,int *Function,int *Tinstrucao){

    /* Formato R: op(6) rs(5) rt(5) rd(5) shamt(5) funct(6) */
    /* Tipo R: Opcode=0, retorna Function */

    /* Operações aritméticas */
    if(strcmp(segmento,"add")==0){
        *Function = 32;
        *opcode = 0;
        *shamt = 0;
        *Tinstrucao = TRegistrador;
    }
    if(strcmp(segmento,"sub")==0){
        *Function = 34;
        *opcode = 0;
        *shamt = 0;
        *Tinstrucao = TRegistrador;
    }
    /* Operações lógicas */
    if(strcmp(segmento,"and")==0){
        *Function = 36;
        *opcode = 0;
        *shamt = 0;
        *Tinstrucao = TRegistrador;
    }
    if(strcmp(segmento, "or")==0){
        *Function = 37;
        *opcode = 0;
        *shamt = 0;
        *Tinstrucao = TRegistrador;
    }
    if(strcmp(segmento,"nor")==0){
        *Function = 39;
        *opcode = 0;
        *shamt = 0;
        *Tinstrucao = TRegistrador;
    }
    /* Operações logicas de deslocamento */
    if(strcmp(segmento,"sll")==0){
        *Function = 0;
        *opcode = 0;
        *Tinstrucao = TRegistrador;
    }
    if(strcmp(segmento,"srl")==0){
        *Function = 2;
        *opcode = 0;
        *Tinstrucao = TRegistrador;
    }
    /* Formato I: op(6) rs(5) rt(5) endereço(16) */
    /* Tipo I: retorna Opcode */

    /* Operações bit a bit */
    if(strcmp(segmento,"addi")==0){
        *opcode = 8;
        *shamt = 0;
        *Function = 0;
        *Tinstrucao = TImediato;
    }
    if(strcmp(segmento,"andi")==0){
        *opcode = 12;
        *shamt = 0;
        *Function = 0;
        *Tinstrucao = TImediato;
    }
    if(strcmp(segmento, "ori")==0){
        *opcode = 13;
        *shamt = 0;
        *Function = 0;
        *Tinstrucao = TImediato;
    }
}

int retornaReg(char *segmento,int *deslocou,int opcode){

    /* $t0 a $t7 são mapeados nos registradores 8 a 15 */
    if((strcmp(segmento,"t0")) == 0)    return 8;
    if((strcmp(segmento,"t1")) == 0)    return 9;
    if((strcmp(segmento,"t2")) == 0)    return 10;
    if((strcmp(segmento,"t3")) == 0)    return 11;
    if((strcmp(segmento,"t4")) == 0)    return 12;
    if((strcmp(segmento,"t5")) == 0)    return 13;
    if((strcmp(segmento,"t6")) == 0)    return 14;
    if((strcmp(segmento,"t7")) == 0)    return 15;
    /* $s0 a $s7 são mapeados nos registradores 16 a 23 */
    if((strcmp(segmento,"s0")) == 0)    return 16;
    if((strcmp(segmento,"s1")) == 0)    return 17;
    if((strcmp(segmento,"s2")) == 0)    return 18;
    if((strcmp(segmento,"s3")) == 0)    return 19;
    if((strcmp(segmento,"s4")) == 0)    return 20;
    if((strcmp(segmento,"s5")) == 0)    return 21;
    if((strcmp(segmento,"s6")) == 0)    return 22;
    if((strcmp(segmento,"s7")) == 0)    return 23;

    if(opcode == 0){//Registrador (tem deslocamento)
        *deslocou = TRUE;
        return atoi(segmento);
    }else//Imediata (constante)
        return atoi(segmento);

    return -1;
}

int* retornaBinario(int n,int *contPosicoes){
    int i, j, k=0, quociente[80], resto[80], *cadeiaBinaria;

    cadeiaBinaria = (int *)malloc(sizeof(int) * MaxBits);

	for(i=0;i<MaxBits;i++)
        cadeiaBinaria[i] = 0;

    if(n == 0)
        return cadeiaBinaria;
    else if(n == 1){
        cadeiaBinaria[MaxBits-1] = 1;
        return cadeiaBinaria;
    }

    while (n != 1){     // enquanto o quociente for diferente de 1, o programa continuará calculando
        quociente[*contPosicoes] = n / 2;  //array que calcula e armazena os quocientes
        resto[*contPosicoes] = n % 2; //array que calcula e armazena os restos
        n = quociente[*contPosicoes];  //atribuindo novo valor para q[i], pra que seja possível a continuação do cálculo
        (*contPosicoes)++;
	}

	j = *contPosicoes-1;

	/*montando a cadeia binária*/
	if(*contPosicoes + 1 < MaxBits)
        k = MaxBits - (*contPosicoes+1);

	for(i=0+k;i<*contPosicoes+1+k;i++){
        if(i == 0 + k)
            cadeiaBinaria[i] = quociente[j];
        else{
            cadeiaBinaria[i] = resto[j];
            j--;
        }
	}

    return cadeiaBinaria;
}

void geraInstrucaoBinaria(FILE *arqSaida,int n,int TCadeia){
    int i, contPosicoes = 0, *cadeiaBinaria;

    cadeiaBinaria = retornaBinario(n,&contPosicoes);


    if(TCadeia == OPCODE || TCadeia == FUNCTION){//6 bits
        for(i=10;i<16;i++)
            fprintf(arqSaida,"%d",cadeiaBinaria[i]);
    }
    if(TCadeia == REG || TCadeia == SHAMT){//5 bits
        for(i=11;i<16;i++)
            fprintf(arqSaida,"%d",cadeiaBinaria[i]);
    }
    if(TCadeia == ENDERECO){//16 bits
        for(i=0;i<16;i++)
            fprintf(arqSaida,"%d",cadeiaBinaria[i]);
    }

    fprintf(arqSaida," ");

    free(cadeiaBinaria);
}

void retornaSaida(FILE *arqSaida,int opcode,int *reg,int Shamt,int Function,int Tinstrucao){

    if(Tinstrucao == TRegistrador){//TIPO REGISTRADOR

        geraInstrucaoBinaria(arqSaida,opcode,OPCODE);//opcode
        geraInstrucaoBinaria(arqSaida,reg[1],REG);//rs
        geraInstrucaoBinaria(arqSaida,reg[2],REG);//rt
        geraInstrucaoBinaria(arqSaida,reg[0],REG);//rd
        geraInstrucaoBinaria(arqSaida,Shamt,SHAMT);//shamt
        geraInstrucaoBinaria(arqSaida,Function,FUNCTION);//function

    }else if(Tinstrucao == TImediato){// TIPO IMEDIATO
        geraInstrucaoBinaria(arqSaida,opcode,OPCODE);//opcode
        geraInstrucaoBinaria(arqSaida,reg[1],REG);//rs
        geraInstrucaoBinaria(arqSaida,reg[0],REG);//rt
        geraInstrucaoBinaria(arqSaida,reg[2],ENDERECO);//Endereço
    }
}
