#include <stdio.h>
#include <stdlib.h>
 typedef struct player
 {
 	int simb[3], 
 		escolha;
 } Player;

int min(int a, int b){
	if(a<=b)return a; return b;
}

void buildSegTree(Player vet[], int ini, int fim, Player segTree[], int pos){
	if (ini==fim){
		segTree[pos]=vet[ini];
		return;
	}
	int meio = (ini+fim)/2;
	buildSegTree(vet,ini,meio,segTree, 2*pos+1);
	buildSegTree(vet,meio+1,fim,segTree, 2*pos+2);
	segTree[pos] = min(segTree[2*pos+1], segTree[2*pos+2]);
}

int buscaMinino( int segTree[], int ini, int fim, int qIni, int qFim, int pos){
	if (qIni <= ini && qFim >= fim){
		return segTree[pos];
	}
	if (qIni > fim || qFim < ini){
		return 40000000;
	}
	int meio = (ini+fim)/2;
	return min(buscaMinino(segTree,ini,meio,qIni,qFim,2*pos+1),buscaMinino(segTree,meio+1,fim,qIni,qFim,2*pos+2));
}

void init(Player segTree[],int n){
	for (int i = 0; i < n; ++i){
		segTree[i]->homem=0;
		segTree[i]->elefante=0;
		segTree[i]->rato=0;
	}
}

void mostra(int segTree[],int n){
	for (int i = 0; i < n; ++i){
		printf("%i-", segTree[i]);
	}
	printf("\n");
}

int getPow2(int n){
	int k=2;
	while(n>k)k*=2;
	return k;
}

int main(int argc, char const *argv[])
{
	int n, m, ns;
	scanf("%i", &n);
	ns=2*getPow2(n)-1;
	int laze[];
	Player vet[n], segTree[ns];
	

	init(segTree,n);
	buildSegTree(vet,0,7,segTree,0);
	mostra(segTree,n);
	mostra(vet,8);
	return 0;
}