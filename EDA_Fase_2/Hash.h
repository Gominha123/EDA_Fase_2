/**
* Author: Gonçalo
* Email: a21666@alunos.ipca.pt
* Date: 11/03/2022
* Desc: Assinatura de Hash tables
*/
///h1: Hash table

#include <stdbool.h>
#include "Listas.h"
#include <stdio.h>

#ifndef HASH
#define HASH
#define SIZE 31

typedef struct hashTable
{
	struct job* tabela;
}hashTable;

static hashTable ht[SIZE];

#pragma region files

void escreveHashFicheiro(job* ht[]);

job** lerHashFile(job* ht[]);

#pragma endregion

#pragma region iniciar/procura

job** iniciaHash(job* ht[]);
int hashKey(int key);

#pragma endregion

#pragma region manipularJob

job** InsertNodeHashInicio(job* item, job* ht[]);

job* jobHashSearch(job* ht[], int cod);

job** removeAll(job* ht[]);

job** alterarHashOp(job* ht[], int cod, int novoCod, int jobCod);

#pragma endregion

#pragma region calculos

void makespan()
{

}

#pragma endregion

#endif