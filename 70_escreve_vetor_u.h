#ifndef _ESCREVE_VETOR_U_H
#define	_ESCREVE_VETOR_U_H

/* Subrotina para escrita do vetor u completo */
void escreve_u(double *u, int *id)
{
	FILE	*ofp;
	int	con, aux=0;

	// Escrevendo o vetor deslocamento
	ofp = fopen("outtxt_70_resultado_vetor_u.txt", "w");
	fprintf(ofp, "INDICE          U(INDICE)\n");
	for (con = 0; con < 2*nnos; ++con) {
		if (id[con]==0)
			fprintf(ofp, "%5d     0.000000e-00\n", con+1);
		else {
			fprintf(ofp, "%5d  %15.6e\n", con+1, u[aux]);
			aux++;
		}
	}

	fclose(ofp);
	printf("Escrita do vetor u no arquivo concluida!\n");
}
#endif
