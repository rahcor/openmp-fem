#ifndef _GRADIENTE_CONJUGADO_H
#define	_GRADIENTE_CONJUGADO_H

//Funcao que multiplica um vetor por uma matriz de ordem dim x dim
void multmatvet(double *matriz, double *device_vector, double *res_mult, int dim)
{	
	int con, con2;
	for(con = 0; con < dim; con++ ){
		float sum = 0.0f;
		for(con2 = 0; con2 < dim; con2++)
			sum += matriz[con*dim+con2]*device_vector[con2]; 
		res_mult[con]=sum;
	}
}

//Produto escalar de 2 vetores
double prod_esc(double *vet, double *vet2, int dim){						
	int	con;
	double	ans = 0.0f;
	for (con=0; con<dim ; con++)
		ans += vet[con]*vet2[con];
	return ans;
}

//Main
void solver_gradconj(double *A, double *b, double *v_k)
{
	int	con, conit, itmax, dim=nid;
	double	errotrgt, erro, q_k, alfa_kmn1, aux[dim];
	double	v_kmn1[dim], Av_kmn1[dim];
	double	p_kmn1[dim], p_k[dim], Ap_k[dim];	
	double	r_kmn2[dim], r_kmn1[dim], r_k[dim];

/*
//Alocação de memória
	int len = nid*sizeof(double);
	double *u= (double*)malloc(len); 
*/

	for (con=0; con < dim; con++)
		v_kmn1[con]=0.001;	//inicializa o vetor para a primeira iteração
	errotrgt = 0.000000001;	//define o valor do erro do critério de parada	
	itmax = 10000;		//define o valor do numero máximo de iteracoes do critério de parada

	printf("Calculo do vetor u pelo metodo dos gradientes conjugados iniciado!\n");
//Primeira iteração
	multmatvet(A, v_kmn1, Av_kmn1, dim);
	for (con=0; con<dim; con++) {
		r_kmn1[con] = Av_kmn1[con] + b[con];		
		p_k[con] = (-1)*r_kmn1[con];
	}
	multmatvet(A, p_k, Ap_k, dim);
	q_k = prod_esc(r_kmn1,r_kmn1,dim)/prod_esc(Ap_k,p_k,dim);
	for (con=0; con<dim; con++) {
		v_k[con] = v_kmn1[con] + q_k*p_k[con];
		r_k[con] = r_kmn1[con] + q_k*Ap_k[con];
	}
	for (con=0; con<dim; con++)
		aux[con] = v_k[con]-v_kmn1[con];
	erro=sqrt(prod_esc(aux,aux,dim)/prod_esc(v_k,v_k,dim));
	conit = 1;
	printf("It = %5d Erro = %.9f",conit, erro);
//

//Iterações segintes
	while (erro > errotrgt && conit < itmax) {
		for (con=0; con<dim; con++) {
			r_kmn2[con] = r_kmn1[con];
			r_kmn1[con] = r_k[con];
			p_kmn1[con] = p_k[con];	
			v_kmn1[con] = v_k[con];
		}
		alfa_kmn1 = prod_esc(r_kmn1, r_kmn1, dim)/prod_esc(r_kmn2, r_kmn2, dim);
		for (con=0; con<dim; con++)
			p_k[con] = (-1)*r_kmn1[con] + alfa_kmn1*p_kmn1[con];
		multmatvet (A, p_k, Ap_k, dim);
		q_k = prod_esc(r_kmn1,r_kmn1,dim)/prod_esc(Ap_k,p_k,dim);
		for (con=0; con<dim; con++) {
			v_k[con] = v_kmn1[con] + q_k*p_k[con];
			r_k[con] = r_kmn1[con] + q_k*Ap_k[con];
		}
		for (con=0; con<dim; con++)
			aux[con] = v_k[con]-v_kmn1[con];
		erro=sqrt(prod_esc(aux,aux,dim)/prod_esc(v_k,v_k,dim));
		conit++;
		printf("\rIt = %5d Erro = %.10f",conit, erro);		
	}
	for (con=0; con<dim; con++)
			v_k[con] = -v_k[con];

	printf("\n");	
	if (conit == itmax)
		printf("O metodo nao convergiu para o erro desejado dentro do numero maximo de iteracoes definidas.\n");
	else
		printf("Calculo do vetor u pelo metodo dos gradientes conjugados concluido!\nProblema resolvido!\n");


/*
	printf("\nLiberando memoria local CG...");
	free(r);
	printf("[OK]\n");
*/
	
}
#endif	/* _GRADIENTECONJUGADO */

