/**
* Author: Gonçalo
* Email: a21666@alunos.ipca.pt
* Date: 11/03/2022
* Desc: Assinatura de Listas
* ???
*/

#include <stdbool.h>
#ifndef HEADER
#define HEADER

#pragma region structs
/**
 * Lista de máquina e tempo.
 * maquina codigo da maquina
 * tempo tempo da maquina a fazer determinada operação
 * apontador para outra máquina
 */

typedef struct maqTempo
{
	int maquina;
	int tempo;
	struct maqTempo* seguinte;
}maqTempo;

/**
 * Lista de operações
 * cod codigo da operação
 * apontador para uma máquina
 * apontador para outra operação
 */
typedef struct operacao
{
	int cod;
	struct maqTempo* MaqTemp;
	struct operacao* seguinte;
}operacao;

/**
*Lista de jobs
* cod codigo do job
* apontador para uma operaçao
* apontador para outro job
*/
typedef struct job
{
	int cod;
	struct job* seguinte;
	struct operacao* operacao;
}job;


#pragma endregion

#pragma region inserir

job* insereAll(int jobCod, int operCod, int maq, int temp, job* headlist);
job* insereJob(job* processo, job* headlist);
job* criaJob(int jobCod, job* headlist);
job* inserirOper(operacao* op, job* processo);
job* criaOper(int operCod, job* processo);
operacao* insereMaquina(operacao* op, maqTempo* maq);
operacao* criaMaq(int maq, int tempo, operacao* op);

#pragma endregion

#pragma region files
void escreveFile(job* processo);
job* lerFile();

#pragma endregion

#pragma region alterar
job* alterarOp(job* p, int cod, int novoCod);
job* alterarMaq(job* p, int opCod, int maq, int novamaq, int novotempo);

#pragma endregion

#pragma region procura
job* searchJob(job* job, int jobCod);
operacao* searchOp(operacao* oper, int operCod);
maqTempo* searchMaq(maqTempo* maq, int maquina);

#pragma endregion

#pragma region calculos
int maximo(job* processo);
int minimo(job* processo);
maqTempo* tempoMin(operacao* op);
float calculaMedia(operacao* op);

#pragma endregion

#pragma region remover

void removeAllJob(job* processo);
job* removeJob(job* job);
operacao* removeOp(operacao* op);
maqTempo* removeMaq(maqTempo* maq);

#pragma endregion

#endif



