#ifndef _INPDATA_H
#define	_INPDATA_H

// Subrotina para leitura do arquivo de dados


void   readln(FILE *ifp, char line[], int max_size); /**
 * Função auxiliar para ler uma linha inteira do arquivo de entrada, usada nas funções:
 * inpdata()
 *
 * Lê no máximo max_size caracteres de uma linha no arquivo apontado por ifp,
 * e retorna a linha em line, terminada por '\0'
 **/



void inpdata()
{
	// Início da declaração de variáveis
	char	filenamein[51];
	FILE	*ifp, *ofp;
	char	tit[30][101];
	int	ino, iel, iinc;
	int	param, lenint, lendb;		//variáveis para alocacao de memória
	// Fim da declaração de variáveis


/*	printf("Write the input file name\n");
	scanf("%s", filenamein);
	filenamein[50] = '\0';

	ifp = fopen(filenamein, "r");
	if (ifp == NULL)
		printf("No input file!\n");
*/	
//	ifp = fopen("TRIANGen9el.txt", "r");
//	ifp = fopen("TRIANGexpg218.txt", "r");
	ifp = fopen("TRIANGen9el_big.txt", "r");
	if (ifp == NULL)
		printf("No input file!\n");

	ofp = fopen("outtxt_20_input_data.txt", "w");		//Arquivo que reescreve o arquivo de entrada

	// Leitura do número de nós
	readln(ifp, tit[0], 100);
	readln(ifp, tit[1], 100);
	fscanf(ifp, "%d\n", &nnos);
	// Escrevendo no arquivo de saída o número de nós
	fprintf(ofp, "%s\n", tit[0]);
	fprintf(ofp, "%s\n", tit[1]);
	fprintf(ofp, "%d\n", nnos);

	// Alocacao de memória para as váriaveis cuja dimensao depende de nnos
	param = nnos;
	lenint = param*sizeof(int);
	lendb = param*sizeof(double);
	nno = (int*)malloc(lenint);
	xcord = (double*)malloc(lendb);
	ycord = (double*)malloc(lendb);
	ixcc = (int*)malloc(lenint);
	iycc = (int*)malloc(lenint);
	fx = (double*)malloc(lendb);
	fy = (double*)malloc(lendb);

	// Leitura das coordenadas dos nós
	readln(ifp, tit[2], 100);
	readln(ifp, tit[3], 100);
	for (ino = 0; ino < nnos; ++ino)
		fscanf(ifp, "%d %lf %lf\n", &nno[ino], &xcord[ino], &ycord[ino]);
	// Escrevendo no arquivo de saída as coordenadas dos nós
	fprintf(ofp, "%s\n", tit[2]);
	fprintf(ofp, "%s\n", tit[3]);
	for (ino = 0; ino < nnos; ++ino)
		fprintf(ofp, "%4d    %6.1lf  %6.1lf\n", nno[ino], xcord[ino], ycord[ino]);

	// Leitura das condições de contorno dos nós
	readln(ifp, tit[4], 100);
	readln(ifp, tit[5], 100);
	for (ino = 0; ino < nnos; ++ino)
		fscanf(ifp, "%d %d %d\n", &nno[ino], &ixcc[ino], &iycc[ino]);
	//Escrevendo no arquivo de saída as condições de contorno dos nós
	fprintf(ofp, "%s\n", tit[4]);
	fprintf(ofp, "%s\n", tit[5]);
	for (ino = 0; ino < nnos; ++ino)
		fprintf(ofp, "%5d   %5d   %5d\n", nno[ino], ixcc[ino], iycc[ino]);

	//Leitura dos carregamentos nos nós
	readln(ifp, tit[6], 100);
	readln(ifp, tit[7], 100);
	for (ino = 0; ino < nnos; ++ino)
		fscanf(ifp, "%d %lf %lf\n", &nno[ino], &fx[ino], &fy[ino]);
	// Escrevendo no arquivo de saída os carregamentos nos nós
	fprintf(ofp, "%s\n", tit[6]);
	fprintf(ofp, "%s\n", tit[7]);
	for (ino = 0; ino < nnos; ++ino)
		fprintf(ofp, "%4d    %6.1lf  %6.1lf\n", nno[ino], fx[ino], fy[ino]);

	//Leitura da quantidade de tipos de elementos
	readln(ifp, tit[8], 100);
	fscanf(ifp, "%d\n", &ntypnel);
	//Escrevendo no arquivo de saída a quantidade de tipos de elementos
	fprintf(ofp, "%s\n", tit[8]);
	fprintf(ofp, "%5d\n", ntypnel);

	//Leitura do tipo de elemento
	readln(ifp, tit[9], 100);
	fscanf(ifp, "%d\n", &itipo);
	//Escrevendo no arquivo de saída o tipo de elemento
	fprintf(ofp, "%s\n", tit[9]);
	fprintf(ofp, "%5d\n", itipo);

	//Leitura do número de elementos do tipo
	readln(ifp, tit[10], 100);
	fscanf(ifp, "%d\n", &nitipo);
	//Escrevendo no arquivo de saída o número de elementos do tipo
	fprintf(ofp, "%s\n", tit[10]);
	fprintf(ofp, "%5d\n", nitipo);

	// Alocacao de memória para as váriaveis cuja dimensao depende de nitipo
	param = nitipo;
	lenint = param*sizeof(int);
	lendb = param*sizeof(double);
	nel = (int*)malloc(lenint);
	elast = (double*)malloc(lendb);
	area = (double*)malloc(lendb);
	rho = (double*)malloc(lendb);
	noini = (int*)malloc(lenint);
	nofin = (int*)malloc(lenint);

	//Leitura das propriedades do material
	readln(ifp, tit[11], 100);
	readln(ifp, tit[12], 100);
	fscanf(ifp, "%d\n", &nglel);
	readln(ifp, tit[13], 100);
	fscanf(ifp, "%d\n", &nnoel);
	readln(ifp, tit[14], 100);
	for (iel = 0; iel < nitipo; ++iel)
		fscanf(ifp, "%d %lf %lf %lf\n", &nel[iel], &elast[iel], &area[iel], &rho[iel]);
	//Escrevendo no arquivo de saída as propriedades do material
	fprintf(ofp, "%s\n", tit[11]);
	fprintf(ofp, "%s\n", tit[12]);
	fprintf(ofp, "%5d\n", nglel);
	fprintf(ofp, "%s\n", tit[13]);
	fprintf(ofp, "%5d\n", nnoel);
	fprintf(ofp, "%s\n", tit[14]);
	for (iel = 0; iel < nitipo; ++iel)
		fprintf(ofp, "%5d    %12.6e  %12.6e  %12.6e\n",
					nel[iel], elast[iel], area[iel], rho[iel]);

	//Leitura de comentario no arquivo de entrada
	readln(ifp, tit[15], 100);
	fprintf(ofp, "%s\n", tit[15]);

	//Leitura da incidência dos nós
	readln(ifp, tit[16], 100);
	readln(ifp, tit[17], 100);
	for (iinc = 0; iinc < nitipo; ++iinc)
		fscanf(ifp, "%d %d %d\n", &nel[iinc], &noini[iinc], &nofin[iinc]);
	//Escrevendo no arquivo de saída a incidência dos nós
	fprintf(ofp, "%s\n", tit[16]);
	fprintf(ofp, "%s\n", tit[17]);
	for (iinc = 0; iinc < nitipo; ++iinc)
		fprintf(ofp, "%5d   %5d   %5d\n", nel[iinc], noini[iinc], nofin[iinc]);

	//Leitura de comentário do arquivo de entrada
	readln(ifp, tit[18], 100);
	fprintf(ofp, "%s\n", tit[18]);

	fclose(ifp);
	fclose(ofp);
	printf("Leitura dos dados concluida!\n");
}

void readln(FILE *ifp, char line[], int max_size)
{
	int   i;

	for (i = 0; i < max_size + 1; ++i) {
		fscanf(ifp, "%c", &line[i]);
		if (line[i] == '\n') {
			line[i] = '\0';
			return;
		}
	}
}
#endif
