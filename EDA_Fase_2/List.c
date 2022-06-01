/**
* Author: Gon�alo
* Email: a21666@alunos.ipca.pt
* Date: 11/03/2022
* Desc: Metodos para manipular Lista Ligadas
* ???
*/


#include "Listas.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


#pragma region ficheiros

/**
*@brief escreve a lista de jobs num ficheiro .txt
* @param[in]	processo	lista de tipo job
*/
void escreveFile(job* processo)
{
	FILE* fj;

	fj = fopen("Job.txt", "w");

	while (processo)
	{
		while (processo->operacao)
		{
			while (processo->operacao->MaqTemp)
			{
				fprintf(fj, "%d;%d;%d;%d\n", processo->cod, processo->operacao->cod, processo->operacao->MaqTemp->maquina, processo->operacao->MaqTemp->tempo);
				processo->operacao->MaqTemp = processo->operacao->MaqTemp->seguinte;
			}
			processo->operacao = processo->operacao->seguinte;
		}
		processo = processo->seguinte;
	}

	fclose(fj);
}

/// <summary>
/// L� ficheiro .txt com as listas guardadas
/// </summary>
/// <returns>lista de jobs</returns>
job* lerFile()
{
	FILE* fj;
	int jobCod, opCod, maq, tem;

	job* processo = NULL;

	fj = fopen("Job.txt", "r");


	if (fj)
	{
		do
		{
			fscanf(fj, "%d;%d;%d;%d", &jobCod, &opCod, &maq, &tem);
			processo = insereAll(jobCod, opCod, maq, tem,processo);
			if (feof(fj))
			{
				break;
			}
		} while (1);
	}
	/*
	//if (fj)
	//{
	//	do
	//	{

	//		if (!processo)
	//		{
	//			fscanf(fj, "%d;%d;%d;%d", &jobCod, &opCod, &maq, &tem);

	//			processo = criaJob(jobCod);
	//			processo->operacao = criaOper(opCod);
	//			processo->operacao->MaqTemp = criaMaq(maq, tem);
	//		}
	//		else
	//		{
	//			fscanf(fj, "%d;%d;%d;%d", &jobCod, &opCod, &maq, &tem);

	//			aux = criaJob(jobCod);
	//			aux->operacao = criaOper(opCod);
	//			aux->operacao->MaqTemp = criaMaq(maq, tem);
	//			processo = insereJob(processo, aux);
	//			processo = inserirOper(processo, aux->operacao);
	//			processo->operacao = insereMaquina(processo->operacao, aux->operacao->MaqTemp);
	//		}

	//		if (feof(fj))
	//		{
	//			break;
	//		}

	//	} while (1);
	//	fclose(fj);
	//}
	//return processo;*/
}

#pragma endregion

#pragma region inserir
/// <summary>
/// Cria uma maquina,uma opera��o e um job e insere tudo dentro do job
/// </summary>
/// <param name="jobCod"> codigo do job</param>
/// <param name="operCod">codigo da opera��o</param>
/// <param name="maq">c�digo da maquina</param>
/// <param name="temp"> tempo da m�quina</param>
/// <param name="headlist">lista onde vai ser inserido o job</param> 
/// <returns>job com tudo inserido</returns>
job* insereAll(int jobCod, int operCod, int maq, int temp, job* headlist)
{
	headlist = criaJob(jobCod, headlist);
	headlist = criaOper(operCod, headlist);
	headlist->operacao = criaMaq(maq, temp, headlist->operacao);

	return headlist;
}

/*
		* @brief Insere um novo job no in�cio da estrutura
		* @param[in] headlist    Inicio da Lista
		* @param[in] processo    Novo job a inserir
		* @return    Lista de jobs
*/
job* insereJob(job* processo, job* headlist)
{
	if (!headlist) return processo;
	if (!processo) return headlist;
	if (existeJob(headlist, processo->cod) == 1) return headlist; //se ja existir, nao insere

	processo->seguinte = headlist;
	headlist = processo;
	return headlist;
}

/*
* @brief cria um job, insere o inteiro recebido na estrutura job e retorna a mesma
* @param[in] jobCod		Codigo do job a inserir
* @return    estrutura job onde inserido o novo job
*/
job* criaJob(int jobCod, job* headlist)
{
	job* novojob = (job*)malloc(sizeof(job));

	if (!novojob) return NULL; //n�o existe mem�ria dispon�vel

	novojob->cod = jobCod;
	novojob->operacao = NULL;
	novojob->seguinte = NULL;

	return insereJob(novojob, headlist);
}

/*
* @brief		Insere uma opera�ao dentro de um job
* @param[in]	processo Lista de jobs onde vai ser inserida a opera�ao
* @param[in]	op		 Opera�ao a inserir
* @return		Estrutura job onde foi inserida a opera��o
*/
job* inserirOper(operacao* op, job* processo)	//insere uma opera�ao no inicio da lista job
{
	if (!processo) return NULL;

	if (!op) return NULL;
	if (!processo->operacao)		//se n�o existir nenhuma opera�ao no job,insere a opera�ao recebida
	{
		processo->operacao = op;
		return processo;
	}
	if (existeOper(processo->operacao, op->cod) == 1) return processo; //se ja existir a opera�ao no job, nao insere

	op->seguinte = processo->operacao;
	processo->operacao = op;			//insere no inicio da lista a nova opera�ao

	return processo;
}

/*
		* @brief cria uma opera��o, insere o inteiro recebido na estrutura opera��o e retorna a mesma
		* @param[in] operCod		Codigo da opera��o a inserir
		* @param[in] processo		job onde vai ser inserida a opera��o
		* @return    estrutura job onde inserida a nova opera�ao
*/
job* criaOper(int operCod, job* processo)		//cria uma opera��o, insere o inteiro recebido na estrutura operacao e retorna a mesma
{
	operacao* novaoper = (operacao*)malloc(sizeof(operacao));

	if (!novaoper) return NULL; //n�o existe mem�ria dispon�vel

	novaoper->cod = operCod;
	novaoper->MaqTemp = NULL;
	novaoper->seguinte = NULL;

	return inserirOper(novaoper, processo);
}

/*
* @brief		Insere uma maquina dentro de uma opera��o
* @param[in]	op Lista de opera��es onde vai ser inserida a maquina
* @param[in]	maq		 maquina a inserir
* @return		Estrutura opera��o onde foi inserida a maquina
*/
operacao* insereMaquina(operacao* op, maqTempo* maq)
{
	if (!op) return NULL;
	if (!maq) return op;
	if (!op->MaqTemp)			//se n�o existir nenhuma maquina na opera�ao,insere a maquina e respetivo tempo
	{
		op->MaqTemp = maq;
		return op;
	}

	if (existeMaq(op->MaqTemp, maq->maquina) == 1)	return op; //se j� existir a maquina na oper�ao, nao insere

	maq->seguinte = op->MaqTemp;
	op->MaqTemp = maq;
	return op;
}

/*
		* @brief cria uma maquina, insere os inteiros, maquina e tempo, recebidos na estrutura opera��o e retorna a mesma
		* @param[in] operCod		Codigo da opera��o a inserir
		* @return    estrutura opera�ao onde foi inserido a maquina e o tempo
*/
operacao* criaMaq(int maq, int tempo, operacao* op)		//cria uma maquina, codigo da maq
{
	maqTempo* novamaq = (maqTempo*)malloc(sizeof(maqTempo));

	if (!novamaq) return NULL; //n�o existe mem�ria dispon�vel

	novamaq->maquina = maq;
	novamaq->tempo = tempo;
	novamaq->seguinte = NULL;

	return insereMaquina(novamaq, op);
}

#pragma endregion

#pragma region search
/*
* @brief fun��o de pesquisa de opera��es
* @param[in] oper	estrutura onde se vai procurar a opera��o
* @param[in] operCod	codigo da opera�ao a ser pesquisada
* return	estrutura da opera�ao a ser pesquisada(se n�o for encontrada retorna NULL)
*/
operacao* searchOp(operacao* oper, int operCod)
{
	if (!oper || oper->cod == operCod)	//retorna a opera�ao pedida ou NULL se n�o encontrar o pretendido
		return oper;
	else
		return searchOp(oper->seguinte, operCod); // caso a posi�ao em que a lista est� nao seja a pedida, chama a fun�ao com a posi�ao seguinte
}

/*
* @brief fun��o de pesquisa de maquinas
* @param[in] maq	estrutura onde se vai procurar a maquina
* @param[in] maquina	codigo da maquina a ser pesquisada
* return	estrutura da maquina a ser pesquisada(se n�o for encontrada retorna NULL)
*/
maqTempo* searchMaq(maqTempo* maq, int maquina)
{
	if (!maq || maq->maquina == maquina)	//retorna a maquina pedida ou NULL se n�o encontrar o pretendido
		return maq;
	else
		return searchMaq(maq->seguinte, maquina);	//caso a posi�ao em que a lista est� nao seja a pedida, chama a fun�ao com a posi�ao seguinte
}

/// <summary>
/// Fun��o de pesquisa de Jobs
/// </summary>
/// <param name="job"> lista de jobs</param>
/// <param name="jobCod"> codigo do job a ser pesquisado</param>
/// <returns> estrutura do job a ser pesquisado(caso n�o seja encontrado retorna NULL)</returns>
job* searchJob(job* job, int jobCod)
{
	if (!job || job->cod == jobCod)	//retorna a maquina pedida ou NULL se n�o encontrar o pretendido
		return job;
	else
		return searchJob(job->seguinte, jobCod);	//caso a posi�ao em que a lista est� nao seja a pedida, chama a fun�ao com a posi�ao seguinte
}

#pragma endregion

#pragma region remover
/// <summary>
/// remove a lista de jobs toda
/// </summary>
/// <param name="processo"> lista a ser removida</param>
void removeAllJob(job* processo)
{
	job* aux = processo;
	while (aux != NULL)
	{
		job* aux2 = aux;
		aux = aux2->seguinte;
		removeJob(aux2);
	}
}
/// <summary>
/// fun��o auxiliar de remo��o de jobs
/// </summary>
/// <param name="processo"> job a ser removido</param>
/// <returns> lista sem o job a ser removido</returns>
job* removeJob(job* processo)
{
	operacao* aux = processo->operacao;
	job* toDelete = processo;
	processo = toDelete->seguinte;
	while (aux != NULL)
	{
		operacao* aux2 = aux;
		aux->seguinte = aux2->seguinte;
		removeOp(aux2);

	}
	free(toDelete);

	return processo;

}
/// <summary>
/// fun��o auxiliar de remo��o de opera��es
/// </summary>
/// <param name="op"> opera��o a ser removido</param>
/// <returns> lista sem o opera��o a ser removido</returns>
operacao* removeOp(operacao* op)
{
	maqTempo* aux = op->MaqTemp;
	operacao* toDelete = op;
	op = toDelete->seguinte;
	while (aux != NULL)
	{
		maqTempo* aux2 = aux;
		aux->seguinte = aux2->seguinte;
		removeMaq(aux2);

	}
	free(toDelete);

	return op;
}
/// <summary>
/// fun��o auxiliar de remo��o de m�quinas
/// </summary>
/// <param name="maq"> maquina a ser removida</param>
/// <returns> lista sem a m�quina a ser removida</returns>
maqTempo* removeMaq(maqTempo* maq)
{
	maqTempo* toDelete = maq;
	maq = toDelete->seguinte;
	free(toDelete);

	return maq;
}

#pragma endregion

#pragma region existe

/*
* @brief	confirma a existencia de um job na lista
* @param[in] processo lista de jobs
* @param[in] codigo codigo do job
* return 1 se existe,0 se n�o existe
*/
int existeJob(job* processo, int codigo)
{
	if (processo == NULL) return 0;
	job* aux = processo;
	while (aux != NULL)
	{
		if (aux->cod == codigo)
			return 1;
		aux = aux->seguinte;
	}
	return 0;
}

/*
* @brief	confirma a existencia de uma opera�ao na lista
* @param[in] op			Lista de opera��es
* @param[in] codigo		Codigo da opera��o
* return 1 se existe,0 se n�o existe
*/
int existeOper(operacao* op, int codigo)
{
	operacao* aux = op;

	if (op == NULL) return 0;

	while (aux)
	{
		if (aux->cod == codigo)
			return 1;
		else
		{
			aux = aux->seguinte;
		}
	}

	return 0;
}

/*
* @brief	confirma a existencia de uma maquina na lista
* @param[in] maq		Lista de maquina
* @param[in] codigo		Codigo da maquina
* return 1 se existe,0 se n�o existe
*/
int existeMaq(maqTempo* maq, int maquina)
{
	maqTempo* aux = maq;

	if (maq == NULL) return 0;

	while (aux != NULL)
	{
		if (aux->maquina == maquina)
		{
			return 1;
		}
		else
		{
			aux = aux->seguinte;
		}
	}

	return 0;
}

#pragma endregion

#pragma region modificar

/*
* @brief altera uma opera�ao da lista de jobs
* @param[in]	p	Lista de jobs
* @param[in]	cod			Codigo da opera��o a alterar
* @param[in]	novoCod		Novo codigo para alterar
* return	lista de jobs com o codigo da opera�ao alterada
*/
job* alterarOp(job* p, int cod, int novoCod)
{
	operacao* aux;

	if (!p) return NULL;

	aux = searchOp(p->operacao, cod);
	aux->cod = novoCod;

	return p;
}

/*
* @brief altera uma opera�ao da lista de jobs
* @param[in]	p				Lista de jobs
* @param[in]	maq				Codigo da maquina a alterar
* @param[in]	novamaq			Nova maquina para alterar
* @param[in]	novotempo		Novo tempo para alterar
* return	lista de jobs com o codigo da opera�ao alterada
*/
job* alterarMaq(job* p, int opCod, int maq, int novamaq, int novotempo)
{
	maqTempo* aux;
	operacao* aux2;

	if (!p) return NULL;

	aux2 = searchOp(p->operacao, opCod);
	aux = searchMaq(aux2->MaqTemp, maq);

	if (aux)
	{
		aux->maquina = novamaq;
		aux->tempo = novotempo;
	}

	return p;
}

#pragma endregion

#pragma region calculos

/*
* @brief	retorna a maquina que o menor tempo
*/
maqTempo* tempoMin(operacao* op)
{

	if (!op) return NULL;

	if (!op->MaqTemp)
	{
		return NULL;
	}
	maqTempo* aux = op->MaqTemp;
	maqTempo* aux2 = op->MaqTemp->seguinte;

	while (aux2)
	{
		if (aux->tempo > aux2->tempo)		//se o valor seguinte for menor, aux fica com o mesmo valor
		{
			aux = aux2;
		}
		aux2 = aux2->seguinte;
	}
	return aux;			//retorna o menor valor
}

/*
* @brief	retorna a maquina que demora o maior tempo
*/
maqTempo* tempoMax(operacao* op)
{

	if (!op) return NULL;


	if (!op->MaqTemp)
	{
		return NULL;
	}
	maqTempo* aux = op->MaqTemp;
	maqTempo* aux2 = op->MaqTemp->seguinte;

	while (aux2)
	{
		if (aux->tempo < aux2->tempo)		//se o valor seguinte for maior, aux fica com o maior valor
		{
			aux = aux2;
		}
		aux2 = aux2->seguinte;
	}
	return aux;			//retorna o maior valor
}

/*
* @brief	calcula o tempo m�dio para realizar uma opera�ao
* @param[in]	op	opera��es
* return	tempo m�dio
*/
float calculaMedia(operacao* op)
{
	float media = 0, x = 0;
	if (!op) return 0;

	while (op->MaqTemp)
	{
		media += op->MaqTemp->tempo;
		op->MaqTemp = op->MaqTemp->seguinte;
		x++;
	}

	media = media / x;

	return media;
}

/*
* @brief	determina��o de quantidade m�nima de unidades de tempo para realizar todas as opera��es de um job
* @param[in]	processo	job
* return	tempo minimo a realizar todas as opera�oes do job
*/
int minimo(job* processo)
{
	maqTempo* aux;
	job* aux2 = processo;

	int soma = 0;

	if (!processo) return 0;

	while (aux2->operacao)
	{
		aux = tempoMin(aux2->operacao);	//determina a maquina que demora o menor tempo a efetuar a opera�ao
		if (aux)
		{
			//mostraMaquina(aux, aux2->operacao->cod);		//escreve a opera�ao em causa e a maquina que demora o maior tempo a efetuar a opera�ao
			soma += aux->tempo;
		}
		aux2->operacao = aux2->operacao->seguinte;	//passa para a opera�ao seguinte
	}

	return soma;
}

/*
* @brief	determina��o de quantidade maxima de unidades de tempo para realizar todas as opera��es de um job
* @param[in]	processo	job
* return	tempo maximo a realizar todas as opera�oes do job
*/
int maximo(job* processo)
{
	maqTempo* aux;
	job* aux2 = processo;
	int soma = 0;

	if (!processo) return 0;

	while (aux2->operacao)
	{
		aux = tempoMax(aux2->operacao);	//determina a maquina que demora o maior tempo a efetuar a opera�ao
		if (aux)
		{
			mostraMaquina(aux, aux2->operacao->cod);		//escreve a opera�ao em causa e a maquina que demora o maior tempo a efetuar a opera�ao
			soma += aux->tempo;
		}
		aux2->operacao = aux2->operacao->seguinte;	//passa para a opera�ao seguinte
	}

	return soma;
}

//void medio(job* processo)
//{
//	int media;
//	operacao* aux = processo->operacao;
//
//	while (aux)
//	{
//		media = calculaMedia(aux);
//		aux = aux->seguinte;
//	}
//}

#pragma endregion

/*
* @brief	escreve na consola um opera��o,maquina e respetivo tempo
* @param[in]	maq	maquina que vai ser escrita
* @param[in]	cod	codigo da opera�ao onde a maquina est� inserida
*/
//void mostraMaquina(maqTempo* maq, int cod)
//{
//	if (maq)
//	{
//		printf("Operacao: %d\t", cod);
//		printf("Maquina: %d\t", maq->maquina);
//		printf("Tempo: %d\n", maq->tempo);
//	}
//}

//