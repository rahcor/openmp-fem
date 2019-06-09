#ifndef _MATRIZ_ELEMENTO_H
#define	_MATRIZ_ELEMENTO_H

void matriz_elemento(int idel, double elmat[4][4])
{
	FILE	*ofp;

	/**
	 *
	 * Declaração das variáveis
	 *
	 * c - Cálculo do cos(x)
	 * s - Cálculo do sen(x)
	 * teta - ângulo formado entre o eixo x positivo e o elemento
	 * ang - anglulo auxiliar
	 * ta - tangente do ângulo auxiliar
	 * l - comprimento do elemento
	 * x1 - Coordenada x do nó inicial
	 * x2 - Coordenada x do nó final
	 * y1 - Coordenada y do nó inicial
	 * y2 - Coordenada y do nó final
	 * mat - Matriz auxiliar para montagem de elmat
	 *
	 **/

	double	c;
	double	s;
	double	teta;
	double	ang, ta;

	double	l[nitipo];
	int	noi, nof;
	double	x1, x2, y1, y2;
	double	deltax, deltay;

	double	mat[4][4];

	int	i, j;

	/* Nó inicial do elemento */
	noi = noini[idel];
	x1 = xcord[noi-1];
	y1 = ycord[noi-1];

	/* Nó final do elemento */
	nof = nofin[idel];
	x2 = xcord[nof-1];
	y2 = ycord[nof-1];

	/* Comprimento do elemento */
	l[idel] = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));

	/* Cálculo do ângulo teta */
	deltax = x2 - x1;
	deltay = y2 - y1;

	if (deltax == 0 && deltay > 0) {
		teta = M_PI/2;
		c = 0; s = 1;
	}
	if (deltax == 0 && deltay < 0) {
		teta = 3 * M_PI/2;
		c = 0; s = -1;
	}
	if (deltax != 0) {
		ta = deltay / deltax;
		ang = atan(ta);
		if (deltax < 0)
			teta = ang + M_PI;
		else if (deltax > 0 && deltay >= 0)
			teta = ang;
		else if (deltax > 0 && deltay <= 0)
			teta = ang + 2 * M_PI;
		c = cos(teta);
		s = sin(teta);
	}

	/* Elementos da matriz de rigidez do elemento */
	mat[0][0] = c * c;
	mat[0][1] = c * s;
	mat[0][2] = -c * c;
	mat[0][3] = -c * s;
	mat[1][0] = c * s;
	mat[1][1] = s * s;
	mat[1][2] = -c * s;
	mat[1][3] = -s * s;
	mat[2][0] = -c * c;
	mat[2][1] = -c * s;
	mat[2][2] = c * c;
	mat[2][3] = c * s;
	mat[3][0] = -c * s;
	mat[3][1] = -s * s;
	mat[3][2] = c * s;
	mat[3][3] = s * s;

	/* Montagem da matriz de rigidez do elemento */
	#pragma omp for private(j)
	for (i = 0; i < 4; ++i)
		for (j = 0; j < 4; ++j)
			elmat[i][j] = area[idel] * elast[idel] / l[idel] * mat[i][j];

	/* Imprimindo no arquivo a matriz de rigidez do elemento */
	ofp = fopen("outtxt_45_matriz-kelemento.txt", "a");

	fprintf(ofp, "matriz de rigidez do elemento %d\n", idel+1);
	for (i = 0; i < 4; ++i)
		for (j = 0; j < 4; ++j) {
			fprintf(ofp, "    %15.6e", elmat[i][j]);
			if (j == 3)
				fprintf(ofp, "\n");
		}

	fclose(ofp);
	printf("\rMontagem da matriz de rigidez do elemento %d concluida!",idel);
}
#endif
