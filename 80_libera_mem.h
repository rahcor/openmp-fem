#ifndef	_LIBERA_MEM_H
#define _LIBERA_MEM_H

void libera_mem (void)
{
	// Libera a memória
	printf("Liberando memoria local CG...");
	free(nno);
	free(xcord);
	free(ycord);
	free(ixcc);
	free(iycc);
	free(fx);
	free(fy);
	free(nel);
	free(elast);
	free(area);
	free(rho);
	free(noini);
	free(nofin);
	printf("[OK]\n");
}
#endif
