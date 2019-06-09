#ifndef _RIGIDEZ_H
#define	_RIGIDEZ_H

#include "45_matriz_elemento.h"

/* Subrotina para montagem da matriz de rigidez K */
void rigidez(double *k, int *lm)
{
	FILE	*ofp;
	int	inel, con, con2;

	/*-------------------MONTAGEM DA MATRIZ DE RIGIDEZ COM C.C.-------------------*/
	#pragma omp for
	for (con=0; con < nid*nid; con++)	//zera a matriz k
		k[con]=0;
	
	for (inel = 0; inel < nitipo; ++inel) {
		double	elmat[4][4];
		matriz_elemento(inel, elmat); 	//Chama-se a subrotina de montagem da matriz do elemento

		for (con=0; con < 4 ; con++){		//Varre-se a coluna do arranjo lm. A cada elemento da coluna corresponde uma linha da matriz do elemento.
			if (lm[inel*4+con]!=0){		//Se o elemento da coluna de lm não for zero,
				for (con2=0; con2 < 4; con2++) { //varre-se novamente os elementos da coluna para alocar a linha da matriz do elemento coluna a coluna.
					if (lm[inel*4+con2]!=0) //Se o elemento da coluna de lm não for zero, incrementa-se o valor de rigidez na matriz global correspondente ao gdl da matriz do elemento.
						k[(lm[inel*4+con]-1)*nid+(lm[inel*4+con2]-1)]+=elmat[con][con2];
				}
			}
		}
	} 

	/* Escrevendo a matriz global de rigidez com cc no arquivo */
	ofp = fopen("outtxt_40_matriz-kglobal_com_cc.txt", "w");
	fprintf(ofp, "INDICE1  INDICE2         K(INDICE1,INDICE2)\n");
	fprintf(ofp, "\n");
	for (con = 0; con < nid; ++con)
		for (con2 = 0; con2 < nid; ++con2)
			fprintf(ofp, "%5d    %5d     %15.6e\n", con+1, con2+1, k[con*nid+con2]);

	fclose(ofp);
	printf("\rMontagem da matriz global de rigidez com c.c. concluida!\n");
}
#endif
