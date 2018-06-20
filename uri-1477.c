#include <stdio.h>
#include <stdlib.h>
 typedef struct player
 {
 	int simb[3], 
 		estrategia;
 } Player;

Player* alteraEstrategia(Player *p, int a){
	p->estrategia+=a;
	p->estrategia%=3;
}

Player* soma(Player* a, Player* b){
	Player *aux = (Player*) malloc(sizeof(Player));
	aux->simb[0] = a->simb[0] + b->simb[0];
	aux->simb[1] = a->simb[1] + b->simb[1];
	aux->simb[2] = a->simb[2] + b->simb[2];
}

void buildSegTree(Player vet[], int ini, int fim, Player segTree[], int pos){
	if (ini==fim){
		segTree[pos]=vet[ini];
		return;
	}
	int meio = (ini+fim)/2;
	buildSegTree(vet,ini,meio,segTree, 2*pos+1);
	buildSegTree(vet,meio+1,fim,segTree, 2*pos+2);
	segTree[pos] = soma(segTree[2*pos+1], segTree[2*pos+2]);
}

void mudarEstrategia(int lazy[], Player segTree[] int ini, int fim, int qIni, int qFim, int pos){
	/*if (lazy[pos]!=0){ //if lazy é diferente de 0, então precisa atualizar
		segTree[pos]->estrategia+=lazy[pos]; 
		segTree[pos]->estrategia%=3;

		if (ini!=fim){ // se não é folha propaga o lazy para os filhos
			lazy[2*pos+1] = lazy[pos];
			lazy[2*pos+2] = lazy[pos];
		}
		lazy[pos]=0; //zera o lazy
	}*/

	if (ini > fim || ini > qFim || fim < qIni){ //se não está no range [qIni-qFim]
		return;
	}
	if(ini >= qIni && fim <= qFim){ //ta dentro do range
		if (ini!=fim){ //se não é folha
			lazy[2*pos+1]++;
			lazy[2*pos+2]++;	
		}
	}
	mudarEstrategia()
}

int buscaMinino( int segTree[], int ini, int fim, int qIni, int qFim, int pos){
	if (qIni <= ini && qFim >= fim){
		return segTree[pos];
	}
	if (qIni > fim || qFim < ini){
		return 40000000;
	}
	int meio = (ini+fim)/2;
	return soma(buscaMinino(segTree,ini,meio,qIni,qFim,2*pos+1),buscaMinino(segTree,meio+1,fim,qIni,qFim,2*pos+2));
}

void init(Player segTree[],int n){
	for (int i = 0; i < n; ++i){
		segTree[i]->simb[0]=0;
		segTree[i]->simb[1]=0;
		segTree[i]->simb[2]=0;
		segTree[i]->estrategia=0;
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
	int lazy[];
	Player vet[n], segTree[ns];
	

	init(segTree,n);
	buildSegTree(vet,0,7,segTree,0);
	mostra(segTree,n);
	mostra(vet,8);
	return 0;
}