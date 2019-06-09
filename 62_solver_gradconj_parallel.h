#ifndef _GRADIENTE_CONJUGADO_PARALLEL_H
#define	_GRADIENTE_CONJUGADO_PARALLEL_H

//Funcao que multiplica um vetor por uma matriz de ordem dim x dim
void multmatvet_p(double *matriz, double *device_vector, double *res_mult, int dim)
{	
	int con, con2;
	
#pragma omp parallel for private(con, con2) shared(dim, matriz, device_vector, res_mult)
	for(con = 0; con < dim; con++ ){
		float sum = 0.0f;
		for(con2 = 0; con2 < dim; con2++)
			sum += matriz[con*dim+con2]*device_vector[con2]; 
		res_mult[con]=sum;
	} //end parallel for
}



//Produto escalar de 2 vetores
double prod_esc_p(double *vet, double *vet2, int dim){						
	int	con = 0;
	double	ans = 0;

/*	double	ansv[nthr];
	for (con=0; con<nthr; con++)
			ansv[con]= 0;
	#pragma omp parallel for num_threads(2)
	for (con=0; con<dim; con++)
		ansv[omp_get_thread_num()] += vet[con]*vet2[con];
	//end parallel for
      	for (con=0; con<nthr; con++)
		ans += ansv[con];	
*/

	for (con=0; con<dim; con++)
		ans += vet[con]*vet2[con];

	return ans;
}



//Main
void solver_gradconj_p(double *A, double *b, double *v_k)
{
	int	con, conit, itmax, dim=nid;
	double	errotrgt, erro, q_k, alfa_kmn1, aux[dim];
	double	v_kmn1[dim], Av_kmn1[dim];
	double	p_kmn1[dim], p_k[dim], Ap_k[dim];	
	double	r_kmn2[dim], r_kmn1[dim], r_k[dim];


	for (con=0; con < dim; con++)
		v_kmn1[con]=0.001;	//inicializa o vetor para a primeira iteração
	errotrgt = 0.000000001;	//define o valor do erro do critério de parada	
	itmax = 10000;		//define o valor do numero máximo de iteracoes do critério de parada

	printf("Calculo do vetor u pelo metodo dos gradientes conjugados (paralelo) iniciado!\n");
//Primeira iteração
	multmatvet_p(A, v_kmn1, Av_kmn1, dim);
	#pragma omp for
	for (con=0; con<dim; con++) {
		r_kmn1[con] = Av_kmn1[con] + b[con];		
		p_k[con] = (-1)*r_kmn1[con];
	}
	multmatvet_p(A, p_k, Ap_k, dim);
	q_k = prod_esc_p(r_kmn1,r_kmn1,dim)/prod_esc_p(Ap_k,p_k,dim);
	#pragma omp for
	for (con=0; con<dim; con++) {
		v_k[con] = v_kmn1[con] + q_k*p_k[con];
		r_k[con] = r_kmn1[con] + q_k*Ap_k[con];
	}
	#pragma omp for
	for (con=0; con<dim; con++)
		aux[con] = v_k[con]-v_kmn1[con];
	erro=sqrt(prod_esc_p(aux,aux,dim)/prod_esc_p(v_k,v_k,dim));
	conit = 1;
	printf("It = %5d Erro = %.9f",conit, erro);
//

//Iterações segintes
	while (erro > errotrgt && conit < itmax) {
		#pragma omp for
		for (con=0; con<dim; con++) {
			r_kmn2[con] = r_kmn1[con];
			r_kmn1[con] = r_k[con];
			p_kmn1[con] = p_k[con];	
			v_kmn1[con] = v_k[con];
		}
		alfa_kmn1 = prod_esc_p(r_kmn1, r_kmn1, dim)/prod_esc_p(r_kmn2, r_kmn2, dim);
		#pragma omp for
		for (con=0; con<dim; con++)
			p_k[con] = (-1)*r_kmn1[con] + alfa_kmn1*p_kmn1[con];
		multmatvet_p (A, p_k, Ap_k, dim);
		q_k = prod_esc_p(r_kmn1,r_kmn1,dim)/prod_esc_p(Ap_k,p_k,dim);
		#pragma omp for
		for (con=0; con<dim; con++) {
			v_k[con] = v_kmn1[con] + q_k*p_k[con];
			r_k[con] = r_kmn1[con] + q_k*Ap_k[con];
		}
		#pragma omp for
		for (con=0; con<dim; con++)
			aux[con] = v_k[con]-v_kmn1[con];
		erro=sqrt(prod_esc_p(aux,aux,dim)/prod_esc_p(v_k,v_k,dim));
		conit++;
		printf("\rIt = %5d Erro = %.10f",conit, erro);		
	}
	#pragma omp for
	for (con=0; con<dim; con++)
			v_k[con] = -v_k[con];

	printf("\n");	
	if (conit == itmax)
		printf("O metodo nao convergiu para o erro desejado dentro do numero maximo de iteracoes definidas.\n");
	else
		printf("Calculo do vetor u pelo metodo dos gradientes conjugados concluido!\nProblema resolvido!\n");


}
#endif	/* _GRADIENTECONJUGADO */

