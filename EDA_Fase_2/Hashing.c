/**
* Author: Gonçalo
* Email: a21666@alunos.ipca.pt
* Date: 11/03/2022
* Desc: Metodos para manipular Hash tables
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

#pragma region IniciarHash

/// <summary>
/// Inicia a tabela hash
/// </summary>
/// <param name="ht"> </param>
/// <returns></returns>
job** iniciaHash(job* ht[])
{
	int i;
	for (i = 0; i < SIZE; i++)
	{
		ht[i] = NULL;
	}
	return *ht;
}

int hashKey(int key)
{
	if (key > 0)
		return (key % SIZE);
	return 0;
}

#pragma endregion

job** InsertNodeHashInicio(job* processo, job* ht[])
{
	int pos = hashKey(processo->cod);

	processo->seguinte = ht[pos];
	ht[pos] = processo;

	return *ht;
}

job* jobHashSearch(job* ht[], int cod)
{
	if (!ht) return NULL;

	int pos = hashKey(cod);
	if (ht[pos] == NULL) return NULL;
	return (searchJob);
}

#pragma region modificar
job** removeAll(job* ht[])
{
	if (!ht) return NULL;

	job* head, t;
	for (int i = 0; i < SIZE; i++)
		if (ht[i] != NULL)
		{
			head = ht[i];
			removeAllJob(head);
			ht[i] = NULL;
		}
	return *ht;
}

job** removeHashJob(job* ht[], int cod)
{
	if (!ht) return NULL;

	job* aux = jobHashSearch(ht, cod);
	if (aux == NULL) return *ht;
	ht = removeJob(aux);
	return *ht;
}

job** alterarHashOp(job* ht[], int cod, int novoCod, int jobCod)
{
	if (!ht) return NULL;

	job* aux = jobHashSearch(ht, jobCod);
	ht = alterarOp(aux, cod, novoCod);

	return *ht;
}

#pragma endregion

#pragma region files
void escreveHashFicheiro(job* ht[])
{
	FILE* fj;

	fj = fopen("Job.txt", "w");

	for (int i = 0; i < SIZE; i++)
	{
		escreveFile(ht[i]);
	}

	fclose(fj);
}

job** lerHashFile(job* ht[])
{
	FILE* fj;
	int jobCod = 0, opCod = 0, maq = 0, tem = 0;

	ht = iniciaHash(ht);

	fj = fopen("Job.txt", "r");

	if (fj)
	{
		do
		{
			fscanf("%d,%d,%d,%d", jobCod, opCod, maq, tem);
			int pos = hashKey(jobCod);
			ht[pos] = insereAll(jobCod, opCod, maq, tem, ht[pos]);

			if (feof(fj))
			{
				break;
			}

		} while (1);
		fclose(fj);
	}
	return *ht;
}

#pragma endregion