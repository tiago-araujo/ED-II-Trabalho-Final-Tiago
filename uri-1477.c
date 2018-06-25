#include <stdio.h>
#include <stdlib.h>
typedef struct player
{
	int simb[3];//, 
		//estrategia;
} Player;

Player* novoPlayer(){
	Player* novo = (Player*) malloc(sizeof(Player));
	for (int i = 0; i < 3; ++i){
		novo->simb[i] = 0;
	}
	//novo->estrategia = 0;
}

/*Player* alteraEstrategia(Player *p, int a){
	p->estrategia+=a;
	p->estrategia%=3;
}*/

Player* soma(Player* a, Player* b){
	Player* novo = (Player*) malloc(sizeof(Player));
	printf("h = %i + %i\n",a->simb[0], b->simb[0] );
	printf("e = %i + %i\n",a->simb[1], b->simb[1] );
	printf("r = %i + %i\n",a->simb[2], b->simb[2] );
	novo->simb[0] = a->simb[0] + b->simb[0];
	novo->simb[1] = a->simb[1] + b->simb[1];
	novo->simb[2] = a->simb[2] + b->simb[2];
	return novo;
}

void buildSegTree(Player* vet[], int ini, int fim, Player* segTree[], int lazy[], int pos){
	printf("[%i-%i] %i\n", ini, fim, pos);
	int fe = 2*pos+1;
	int fd = 2*pos+2;
	if (ini==fim){
		segTree[pos]=vet[ini];
		lazy[pos] = 0;
		return;
	}
	int meio = (ini+fim)/2;
	buildSegTree(vet,ini,meio,segTree,lazy, fe);
	buildSegTree(vet,meio+1,fim,segTree,lazy, fd);
	printf("[%i-%i] %i\n", ini, fim, pos);
	lazy[pos]=0;
	segTree[pos] = soma(segTree[fe], segTree[fd]);
}

void mudarEstrategia(int lazy[], Player* segTree[], int ini, int fim, int qIni, int qFim, int pos){
	printf("[%i-%i] %i\n", ini, fim, pos);
	int fe = 2*pos+1,
		fd = 2*pos+2;

	if (lazy[pos]!=0){ //if lazy é diferente de 0, então precisa atualizar
		printf("encontrou alteraçao\n");
		lazy[pos] = lazy[pos]%3;
		
		int aux=segTree[pos]->simb[0]; 
		segTree[pos]->simb[0]=segTree[pos]->simb[2]; 
		segTree[pos]->simb[2]=segTree[pos]->simb[1]; 
		segTree[pos]->simb[1]=aux; 
		
		if (ini!=fim){ // se não é folha propaga o lazy para os filhos
			lazy[fe] += lazy[pos];
			lazy[fd] += lazy[pos];
		}
		lazy[pos]=0; //zera o lazy
	}
	if (ini > fim || ini > qFim || fim < qIni){ //se não está no range [qIni-qFim]
		printf("fora do range\n");
		return; //não me interessa
	}
	if (ini >= qIni && fim <= qFim){ //se é toda ou parte da solução
		printf("mudarEstrategia\n");
		int aux=segTree[pos]->simb[0]; 

		printf("h %i << %i\n", segTree[pos]->simb[0], segTree[pos]->simb[2]);
		segTree[pos]->simb[0]=segTree[pos]->simb[2];
		printf("r %i << %i\n", segTree[pos]->simb[2], segTree[pos]->simb[1]);
		segTree[pos]->simb[2]=segTree[pos]->simb[1]; 
		printf("e %i << %i\n", segTree[pos]->simb[1], aux);
		segTree[pos]->simb[1]=aux;
		printf("alterou\n");
		if (ini!=fim){ // se não é folha propaga o lazy para os filhos
			printf("propaga\n");
			lazy[fe] += lazy[pos];
			lazy[fd] += lazy[pos];
		}
		lazy[pos]=0; //zera o lazy 
		/*lazy[pos]++; //altera estrategia*/
		return; // não quero saber do resto
	}else{

	}
	int meio = (ini+fim)/2;
	printf("meio %i\n", meio);
	mudarEstrategia(lazy,segTree,ini,meio,qIni,qFim,fe);
	mudarEstrategia(lazy,segTree,meio+1,fim,qIni,qFim,fd);
	segTree[pos] = soma(segTree[fe],segTree[fd]);
	for (int i = 0; i < 3; ++i){
		printf("%i-", segTree[pos]->simb[i]);
	}
	printf("\n");
	printf("voltando\n");
	//to chegando perto, continua procurando
}
void alteraEstrategia(Player* segTree[],int pos, int n){
	if(n>2) n=n%3;
	if(n==0) return;
	int aux=segTree[pos]->simb[0]; 
	if(n==1){
		segTree[pos]->simb[0]=segTree[pos]->simb[2]; 
		segTree[pos]->simb[2]=segTree[pos]->simb[1]; 
		segTree[pos]->simb[1]=aux; 
	}else{
		segTree[pos]->simb[1]=segTree[pos]->simb[2]; 
		segTree[pos]->simb[0]=segTree[pos]->simb[1]; 
		segTree[pos]->simb[2]=aux; 
	}


}
Player* contaOp(int lazy[], Player* segTree[], int ini, int fim, int qIni, int qFim, int pos){
	if (lazy[pos]!=0){ //if lazy é diferente de 0, então precisa atualizar
		lazy[pos] = lazy[pos]%3;
		int aux=segTree[pos]->simb[0]; 
		segTree[pos]->simb[0]=segTree[pos]->simb[2]; 
		segTree[pos]->simb[2]=segTree[pos]->simb[1]; 
		segTree[pos]->simb[1]=aux; 
		
		if (ini!=fim){ // se não é folha propaga o lazy para os filhos
			lazy[2*pos+1] += lazy[pos];
			lazy[2*pos+2] += lazy[pos];
		}
		lazy[pos]=0; //zera o lazy
	}
	if (ini > fim || ini > qFim || fim < qIni){
		return novoPlayer();
	}
	if (ini >= qIni && fim <= qFim){
		return segTree[pos];
	}
	int meio = (ini+fim)/2;
	Player* a = contaOp(lazy,segTree,ini,meio,qIni,qFim,2*pos+1);
	Player* b = contaOp(lazy,segTree,meio+1,fim,qIni,qFim,2*pos+2);

	return soma(a,b);
}

void init(Player* segTree[],int n){
	for (int i = 0; i < n; ++i){
		segTree[i]=novoPlayer();
		segTree[i]->simb[0]=1;
	}
}

void mostra(Player* p){
	for (int i = 0; i < 3; ++i){
		printf("%i-", p->simb[i]);
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
	
	int lazy[ns];
	Player *vet[n], *segTree[ns], *l[ns];

	init(vet, n);
	buildSegTree(vet,0,n-1,segTree,lazy,0);
	printf("MUDANDO ESTRATEGIA \n");
	mudarEstrategia(lazy,segTree,0,n-1,1-1,2-1,0);
	printf("Certo\n");

	/*contaOp(lazy,segTree,0,ns,0,10,0);
	for (int i = 0; i < n; ++i){
	}
	for (int i = 0; i < ns; ++i){
		lazy[i]=0;
	}
	for (int i = 0; i < n; ++i){
		mostra(vet[i]);
	}

	mostra(contaOp(lazy,segTree,0,n,3,3,0));
	buildSegTree(vet,0,7,segTree,0);*/
	/*mostra(vet,8);*/
	return 0;
}