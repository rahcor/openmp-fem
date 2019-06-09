#ifndef _GAUSS_SEIDEL_H
#define	_GAUSS_SEIDEL_H

void solver_gauss_seidel(double *matrizL, double *vet_b, double *vet_x)
{
	int	conl=0, conc=0, aux=0, conit=0, itmax=100000;
	double	matrizR[nid][nid];
	double	vet_ant[nid];
	double	erro_lido, erro, maior_kmais1,maior_k, acm=0;

	erro_lido=0.00001;

//verifica os dados lidos
//for(conl=0;conl<nid;conl++)
//   {
//    for (conc=0;conc<nid;conc++)
//           printf("elemento a%d%d : %lf\n", conl+1, conc+1,matriz[conl][conc]);
//   }
//for (conl=0;conl<nid;conl++)
//     printf("elemento b%d : %lf\n", conl+1,vet_b[conl]);
//printf("erro : %lf",erro_lido);

	printf("Calculo do vetor u pelo metodo Gauss-Seidel iniciado!\n");
////////////Método
//Faz b*
for(aux=0;aux<nid;aux++)
    vet_b[aux]=vet_b[aux]/matrizL[aux*nid+aux];

//Faz L* e R* na mesma matrir L
for(conl=0;conl<nid;conl++)
  {
    for(conc=0;conc<nid;conc++) 
       {
        if(conl!=conc)  
            matrizL[conl+conc*nid]=matrizL[conl+conc*nid]/matrizL[conl+conl*nid];
       }
  }


/*//////
for(conl=0;conl<nid;conl++)
   {
    for (conc=0;conc<nid;conc++)
           printf("elemento a%d%d : %lf\n", conl+1, conc+1,matrizL[conl][conc]);
   }
for (conl=0;conl<nid;conl++)
     printf("elemento b%d : %lf\n", conl+1,vet_b[conl]);
//////*/



//Copia L p/ R
for(conl=0;conl<nid;conl++)
  {
    for(conc=0;conc<nid;conc++) 
            matrizR[conl][conc]=matrizL[conl+conc*nid];
  }

//Zerar os coef alheios de L* e R*
for(conl=0;conl<nid;conl++)
  {
    for(conc=0;conc<nid;conc++) 
           {
            if (conl<=conc)
                matrizL[conl+conc*nid]=0;
           }
  }
for(conl=0;conl<nid;conl++)
  {
    for(conc=0;conc<nid;conc++) 
           {
            if (conl>=conc)
                matrizR[conl][conc]=0;
           }
  }

erro=erro_lido+1;
//Iteração 0: vet_x=(0,0,0)
for (aux=0;aux<nid;aux++)
         vet_x[aux] = vet_b[aux];

while (erro>erro_lido && conit < itmax)
{
   //Toma o maior valor do vetor para o calculo do erro
   maior_k=vet_x[0];
   for (aux=0;aux<nid;aux++)
     {
      vet_ant[aux]=vet_x[aux];

      if (vet_ant[aux] > maior_k)
         maior_k = vet_ant[aux];
     }

   //processo iterativo
   for (conl=0;conl<nid;conl++)
     {
       acm=0;
       for (conc=0;conc<nid;conc++)
          {
            if (conl>conc)
               acm = acm - matrizL[conl+conc*nid]*vet_x[conc];
            if (conl<conc)
               acm = acm - matrizR[conl][conc]*vet_ant[conc];
          }
       vet_x[conl] = acm + vet_b[conl];
     }

  //Toma o maior valor do vetor para o calculo do erro
  maior_kmais1= (vet_x[0] - vet_ant[0]);
  for (aux=0;aux<nid;aux++)
   {
    if ((vet_x[aux]-vet_ant[aux]) > maior_kmais1)
       maior_kmais1 = (vet_x[aux] - vet_ant[aux]);
   }


//printf("maior_kmais1 : %lf\n",maior_kmais1);

   erro = fabs(maior_kmais1) / fabs(maior_k);
//   printf("erro: %lf\n",erro);
	conit++;
	printf("\rIt = %5d Erro = %.10lf",conit, erro);
}
	printf("\n");	
	if (conit == itmax)
		printf("O metodo nao convergiu para o erro desejado dentro do numero maximo de iteracoes definidas.");
	else
		printf("Calculo do vetor u pelo metodo Gauss-Seidel concluida!\nProblema resolvido!\n");
}
#endif
