#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <conio.h>

#define MAX 20000000

void preencherVetores(int *vet, int tam);
int maxValor(int *v, int n);
int maxValor2(int A[], int p, int r);

int main(){
    int t1=100,t2=5000,t3=15000;
    double ct1[2],ct2[2],ct3[2];
    int i,v1,v2,v3;

    v1 = (int *) malloc(t1 * sizeof(int));
    v2 = (int *) malloc(t2 * sizeof(int));
    v3 = (int *) malloc(t3 * sizeof(int));

    int m1[2],m2[2],m3[2]; //Maiores valores

    preencherVetores(v1,t1);
    preencherVetores(v2,t2);
    preencherVetores(v3,t3);

    /*printf("\n Vetor 1 : \n");
    for(i=0;i<t1;i++){
        printf("%d",v1[i]);
    }
    printf("\n Vetor 2 : \n ");
    for(i=0;i<t2;i++){
        printf("%d",v2[i]);
    }
    printf("\n Vetor 3 :\n ");
    for(i=0;i<t3;i++){
        printf("%d ",v3[i]);
    }*/

    /*Testar 3 vetores de tamanho diferente para o Algoritmo 1 (n-1) para encontrar o maior elemento*/

    printf("\n\tAlgoritmo de Busca 1 :\n");
    clock_t Ticks[12];
    Ticks[0] = clock();
    m1[0] = maxValor(v1,t1);
    Ticks[1] = clock();
    ct1[0] = (Ticks[1] - Ticks[0]) *1000 / CLOCKS_PER_SEC;
    printf("\nMaior Valor = %d e o Tempo gasto (%d elementos existentes): %lf s.\n\n", m1[0],t1, ct1[0]);

    Ticks[2] = clock();
    m2[0] = maxValor(v2,t2);
    Ticks[3] = clock();
    ct2[0] = (Ticks[3] - Ticks[2]) *1000 / CLOCKS_PER_SEC;
    printf("\nMaior Valor = %d e o Tempo gasto (%d elementos existentes): %lf s.\n\n", m2[0],t2, ct2[0]);

    Ticks[4] = clock();
    m3[0] = maxValor(v3,t3);
    Ticks[5] = clock();
    ct3[0] = (Ticks[5] - Ticks[4]) *1000 / CLOCKS_PER_SEC;
    printf("\nMaior Valor = %d e o Tempo gasto (%d elementos existentes): %lf s.\n\n", m3[0],t3, ct3[0]);



    /*Testar 3 vetores de tamanho diferente para o Algoritmo 2 para encontrar o maior elemento*/
    printf("\n\tAlgoritmo de Busca 2 :\n");    
    Ticks[6] = clock();
    m1[1] = maxValor2(v1,0,t1);
    Ticks[7] = clock();
    ct1[1] = (Ticks[7] - Ticks[6]) *1000 / CLOCKS_PER_SEC;
    printf("\nMaior Valor = %d e o Tempo gasto (%d elementos existentes): %lf s.\n\n", m1[1],t1, ct1[1]);

    Ticks[8] = clock();
    m2[1] = maxValor2(v2,0,t2);
    Ticks[9] = clock();
    ct2[1] = (Ticks[9] - Ticks[8]) *1000 / CLOCKS_PER_SEC;
    printf("\nMaior Valor = %d e o Tempo gasto (%d elementos existentes): %lf s.\n\n", m2[1],t2, ct2[1]);


    Ticks[10] = clock();
    m3[1] = maxValor2(v3,0,t3);
    Ticks[11] = clock();
    ct3[1] = (Ticks[11] - Ticks[10]) *1000 / CLOCKS_PER_SEC;
    printf("\nMaior Valor = %d e o Tempo gasto (%d elementos existentes): %lf s.\n\n", m3[1],t3, ct3[1]);
   

    return 0;

}


void preencherVetores(int *vet, int tam){

    int i;
    for(i=0;i<tam;i++){
        vet[i] = rand()%MAX;
    }

	for (i = 0; i < tam; i++){
		int r = rand() % tam;

		int temp = vet[i];
		vet[i] = vet[r];
		vet[r] = temp;
	}
} 

/*Encontrar o valor máximo do vetor utilizando Abordagem n-1*/
int maxValor(int *v, int n){ 
    if (n == 1) 
         return v[0];
   else{
      int x;
      x = maxValor(v, n-1);
        if (x > v[n-1]) 
            return x;
        else 
            return v[n-1]; 
   }
}

/*Encontrar o valor máximo do vetor utilizando Abordagem Busca Binária*/
int maxValor2(int A[], int p, int r){   
    int u, v; 
    int m = (p + r)/2; 
        
    if (p == r) 
        return A[p];
    
    u = maxValor2(A, p, m);
    v = maxValor2(A, m+1, r);
    
    if (u > v) 
        return u; 
    else
        return v;
}