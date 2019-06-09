#ifndef _INPDATA_RESULT_H
#define	_INPDATA_RESULT_H

// Subrotina para leitura do arquivo de dados

void verif_result()
{
	// Início da declaração de variáveis
	FILE	*ifp, *ifp2;
	char	char1, char2;
	int	con=0;
	// Fim da declaração de variáveis

	ifp = fopen("serial_outtxt_70_resultado_vetor_u.txt", "r");
	if (ifp == NULL)
		printf("No input file!\n");

	ifp2 = fopen("outtxt_70_resultado_vetor_u.txt", "r");
	if (ifp2 == NULL)
		printf("No input file!\n");

	// Verificação de erro por comparação dos arquivos de saída do serial vs paralelo
	while (ifp==!EOF && ifp2==!EOF)	{
		fscanf(ifp, "%c", &char1);
		fscanf(ifp2, "%c", &char2);
		if (char1!=char2)
			con++;
	}
	printf("\n\t\tnumero de erros=%d\n\n",con);

	fclose(ifp);
	fclose(ifp2);
	printf("Comparação dos arquivos de saída concluida!\n");
}
#endif
