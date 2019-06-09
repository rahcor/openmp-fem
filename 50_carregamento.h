#ifndef _CARREGAMENTO_H
#define	_CARREGAMENTO_H

/* Subrotina para montagem do vetor carregamento */
void carregamento(double *f, int *id)
{
	FILE	*ofp;
	int	con;

	/*---------------------MONTANDO O VETOR CARREGAMENTO COM C.C.------------------------*/
	for (con=0; con<nid; con++)
		f[con]=0;
	for (con = 0; con<nnos; con++) {
		if (id[con*2]!=0)
			f[id[con*2]-1]=fx[con];
		if (id[con*2+1]!=0)
			f[id[con*2+1]-1]=fy[con];
		}

	// Escrevendo o vetor carregamento no arquivo
	ofp = fopen("outtxt_50_vetorcarga_com_cc.txt", "w");
	fprintf(ofp, "INDICE          F(INDICE)\n");
		for (con = 0; con < nid; ++con)
			fprintf(ofp, "%5d  %15.6e\n", con+1, f[con]);

	fclose(ofp);
	printf("Montagem do vetor carregamento com c.c. concluido!\n");
}
#endif
