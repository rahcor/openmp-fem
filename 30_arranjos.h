/* Subrotina para mintagem dos arranjos ID, IEN e LM */

#ifndef _ARRANJOS_H
#define	_ARRANJOS_H

void arranjos(int *id, int *ien, int *lm)
{
	FILE	*ofp;

	int	con;		//con = contador

	/* -----------------MONTAGAEM DO ARRANJO ID COM C.C----------------- */
	ofp = fopen("outtxt_30_arrayoutput.txt", "w");

	/* Escrita, no arquivo de saída, dos dados de entrada */
	fprintf(ofp, "NNOS\n");
	fprintf(ofp, "%5d\n", nnos);
	fprintf(ofp, "CONDICOES DE CONTORNO\n");
	fprintf(ofp, "NNO     IXCC     IYCC\n");
	for (con = 0; con < nnos; ++con)
		fprintf(ofp, "%5d   %5d   %5d\n", nno[con], ixcc[con], iycc[con]);

	/* Montagem do arranjo ID com cc */
	for (con = 0; con < nnos*2; con++)
		 id[con] = 0;			//Zerando matriz id
	nid = 1;
	for (con = 0; con < nnos; ++con) {
		if (ixcc[con] != 0) {
			id[con*2] = nid;
			nid++;
		}
		if (iycc[con] != 0) {
			id[con*2+1] = nid;
			nid++;
		}
	}
	nid=nid-1;				//Correção sobre nid para utilizá-lo como parâmetro da dimensão dos vetores e matrizes (k, f, u, etc...)

	/* Escrevendo o arranjo ID no arquivo de saída */
	fprintf(ofp, "   GL    NNO    ARRANJO ID COM C.C.\n");
	for (con = 0; con < nnos; ++con) {
		fprintf(ofp, "%5d   %5d   %5d\n", con*2+1, con+1, id[con*2]);
		fprintf(ofp, "%5d   %5d   %5d\n", con*2+2, con+1, id[con*2+1]);
	}

	/* -----------------MONTAGAEM DO ARRANJO IEN-------------------- */
	/* Escrita, no arquivo de saída, dos dados de entrada */
	fprintf(ofp, "NUMERO DE ELEMENTOS\n");
	fprintf(ofp, "%5d\n", nitipo);
	fprintf(ofp, "INCIDENCIA\n");
	for (con = 0; con < nitipo; ++con)
		fprintf(ofp, "%5d   %5d   %5d\n", nel[con], noini[con], nofin[con]);

	/* Montagem do arranjo IEN */
	for (con = 0; con < nitipo; ++con) {
		ien[2*con]=noini[con];
		ien[2*con+1]=nofin[con];
	}

	/* Escrevendo o arranjo IEN no arquivo de saída*/
	fprintf(ofp, "NOLOCAL   NEL   ARRANJO IEN\n");
	for (con = 0; con < nitipo; ++con) {
		fprintf(ofp, "%5d   %5d   %5d\n", 1, con+1, ien[2*con]);
		fprintf(ofp, "%5d   %5d   %5d\n", 2, con+1, ien[2*con+1]);
	}

	/*----------------MONTAGEM DO ARRANJO LM COM C.C.------------------*/
	for (con = 0; con < nitipo; con++) {
		lm[con*4+0] = id[(ien[con*2]-1)*2];
		lm[con*4+1] = id[(ien[con*2]-1)*2+1];
		lm[con*4+2] = id[(ien[con*2+1]-1)*2];
		lm[con*4+3] = id[(ien[con*2+1]-1)*2+1];
	}

	/* Escrevendo o arranjo LM no arquivo de saída */
	fprintf(ofp, "  GL   NOLOCAL   NEL     ARRANJO LM COM C.C.\n");
	for (con = 0; con < nitipo; con++) {
		fprintf(ofp, "%5d   %5d   %5d   %5d\n", 1, 1, con+1, lm[con*4+0]);
		fprintf(ofp, "%5d   %5d   %5d   %5d\n", 2, 1, con+1, lm[con*4+1]);
		fprintf(ofp, "%5d   %5d   %5d   %5d\n", 1, 2, con+1, lm[con*4+2]);
		fprintf(ofp, "%5d   %5d   %5d   %5d\n", 2, 2, con+1, lm[con*4+3]);
	}

	fclose(ofp);
	printf("Montagem dos arranjos concluida!\n");
}
#endif
