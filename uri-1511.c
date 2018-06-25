#include <stdio.h>
#include <stdlib.h>

typedef struct cordenada{
	int x;
	int y;
}Cord;

int min(int a, int b){
	if(a<=b)return a; return b;
}

void buildSegTree(int vet[][], Cord ini, Cord fim, int segTree[][], int pos){
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

void init(int segTree[],int n){
	for (int i = 0; i < n; ++i){
		segTree[i]=40000000;
	}
	printf("\n");
}

void mostra(int segTree[],int n){
	for (int i = 0; i < n; ++i){
		printf("%i-", segTree[i]);
	}
	printf("\n");
}

int main(int argc, char const *argv[])
{
	int vet[][] = {	{4 ,7 ,12,3 ,44,32,5 ,15},
					{6 ,8 ,13,9 ,45,33,10,16},
					{14,17,18,19,46,34,11,20},
					{54,27,22,63,47,35,55,71},
					{64,57,58,73,48,36,56,76},
					{74,77,24,83,49,37,59,87},
					{84,67,92,93,50,38,60,98},
					{94,75,72,23,51,39,61,25}	}, n=2*8-1, segTree[n][n];
	init(segTree,n);
	buildSegTree(vet,0,7,segTree,0);
	mostra(segTree,n);
	mostra(vet,8);
	return 0;
}