#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include "00_var-common.h"
#include "20_inpdata.h"
#include "30_arranjos.h"
#include "40_rigidez.h"
#include "50_carregamento.h"
#include "61_solver_gauss_seidel.h"
#include "62_solver_gradconj.h"
#include "62_solver_gradconj_parallel.h"
#include "70_escreve_vetor_u.h"
#include "75_verif_result.h"
#include "80_libera_mem.h"

int main(void)
{
//	int	metodo=0;
	#pragma omp parallel	//Abertura de seçao paralela para leitura do numero de threads que pode ser gerado para declaração de sumv
	{
	nthr=omp_get_num_threads();
	}//end parallel

	// Chamando subrotina que faz a leitura do arquivo de dados
	inpdata();

	//Declaração de variáveis
	int	id[nnos*2];		//matriz do arranjo id
	int	ien[nnos*nitipo];	//matriz do arranjo IEN
	int	lm[(nnos*2)*nitipo];	//matriz do arranjo LM

	// Chamando a subrotina para montagem dos arranjos ID, LM, IEN
	arranjos(id, ien, lm);

	// Subrotina para montagem da matriz de rigidez global do sistema
	double	k[nid*nid];		//matriz global de rigidez com c.c.
	rigidez(k, lm);

	// Subrotina para montagem do vetor carregamento
	double	f[nid];
	carregamento(f, id);

	//Subrotina para resolver o sistema linear para a matriz k e vetor f
	double	us[nid];
	double  up[nid];

//	solver_gradconj(k, f, us);

	solver_gradconj_p(k, f, up);

	// Subrotina para escrever o vetor u completo no arquivo
	escreve_u(up, id);

	// Verificação de erro por comparação dos arquivos de saída do serial vs paralelo - leitura dos arquivos
	verif_result();

	// Subrotina para liberar a memoria local alocada
	libera_mem();

	printf("Execucao do programa concluida!\n");
	return 0;
}
