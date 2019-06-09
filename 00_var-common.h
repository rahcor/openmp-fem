#ifndef _VAR_COMMON
#define _VAR_COMMON

	int	nnos;				//número de nós da estrutura
	int	*nno;//nno[NNOMAX];			//índice do nó
	double	*xcord, *ycord;//xcord[NNOMAX], ycord[NNOMAX];	//coordenadas dos nós
	int	*ixcc, *iycc;//ixcc[NNOMAX], iycc[NNOMAX];	//condições de contorno nos nós
	int	nid;				//número total de g.d.l's livres
	double	*fx, *fy;//fx[NNOMAX], fy[NNOMAX];		//carregamento nos nós
	int	ntypnel;			//quantidade de tipos de elementos
	int	itipo;				//tipo de elemento
	int	nitipo;				//número de elementos
	int	nglel;				//número de graus de liberdade por no do elemento
	int	nnoel;				//número de nós do elemento
	int	*nel;//nel[NELMAX];			//índice dos elementos
	double	*elast, *area, *rho;//elast[NELMAX], area[NELMAX], rho[NELMAX]; //propriedades dos elementos: ELAST - Modulo de elasticidade do material, AREA - Area do elemento, RHO - Densidade do material
	int	*noini, *nofin;//noini[NELMAX], nofin[NELMAX];	//NOINI - No inicial do elemento, NOFIN - No final do elemento

	int	nthr;				//numero de threads ideal da maquina

#endif /* _VAR_COMMON */
