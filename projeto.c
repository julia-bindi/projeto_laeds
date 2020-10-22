#include <stdlib.h>
#include <stdio.h>

/* código retirado do site: http://www2.dcc.ufmg.br/livros/algoritmos/implementacoes-03.php
referente ao livro de NIVIO ZIVIANI */

/* ========================================================================= */

typedef int TipoChave;

typedef struct {
  int Chave;
  int Tipo;
  int NumElementos;
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct {
  TipoApontador Primeiro, Ultimo;
} TipoLista;

void FLVazia(TipoLista *Lista)
{ Lista -> Primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Primeiro;
  Lista -> Primeiro -> Prox = NULL;
}

int Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista)
{ Lista -> Ultimo -> Prox = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Ultimo -> Prox;
  Lista -> Ultimo -> Item = x;
  Lista -> Ultimo -> Prox = NULL;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{ /*  ---   Obs.: o item a ser retirado e  o seguinte ao apontado por  p --- */
  TipoApontador q;
  if (Vazia(*Lista) || p == NULL || p -> Prox == NULL) 
  { printf(" Erro   Lista vazia ou posi  c   a o n  a o existe\n");
    return;
  }
  q = p -> Prox;
  *Item = q -> Item;
  p -> Prox = q -> Prox;
  if (p -> Prox == NULL) Lista -> Ultimo = p;
  free(q);
}

void Imprime(TipoLista Lista)
{ TipoApontador Aux;
  Aux = Lista.Primeiro -> Prox;
  while (Aux != NULL) 
    { printf("%d\n", Aux -> Item.Chave);
      Aux = Aux -> Prox;
    }
}

/* ========================================================================== */

/* código referente ao exercício de tipos de segmentos */

/* ========================================================================== */

void imprimiResultado(int numeroSegmentos, TipoLista lista){
   
}

void ordemCrescente(int numeroSegmentos, TipoLista lista){
    int ordem[numeroSegmentos];
    ordem[0] = lista.Primeiro->Prox->Item.Tipo;
    int numerosDistintos = 1;
    TipoApontador apontador = lista.Primeiro->Prox;
    for(int i=1;i<numeroSegmentos;i++){
        apontador = apontador->Prox;
        for(int j=0;j<numerosDistintos;j++){
            if(apontador->Item.Tipo == ordem[j])
                break;
            if(j == numerosDistintos-1){
                numerosDistintos++;
                ordem[numerosDistintos-1] = apontador->Item.Tipo;
            }
        }
    }
    for(int i=0;i<numerosDistintos;i++){
        for (int j=0;j<numerosDistintos-1;j++){
            if(ordem[j] > ordem[j+1]){
                int aux = ordem[j];
                ordem[j] = ordem[j+1];
                ordem[j+1] = aux;
            }
        }
        
    }
    apontador = lista.Primeiro;
    for(int i=0;i<numeroSegmentos;i++){
        apontador = apontador->Prox;
        for(int j=0;j<numerosDistintos;j++){
            if(apontador->Item.Tipo == ordem[j]){
                apontador->Item.Tipo = j+1;
            }
        }
    }
    imprimiResultado(numeroSegmentos,lista);
}


void segmentaVetor(int quantidade, int valores[]){
    int numeroSegmentos=1;
    TipoLista lista;
    TipoItem item;
    TipoApontador apontador;
    FLVazia(&lista);
    int valorAtual = valores[0];
    item.Chave = numeroSegmentos;
    item.Tipo = valores[0];
    Insere(item,&lista);
    for(int i=1;i<quantidade;i++){
        if(valores[i] != valorAtual){
            valorAtual = valores[i];
            numeroSegmentos++;
            item.Chave = numeroSegmentos;
            item.Tipo = valorAtual;
            Insere(item, &lista);
        }
    }
    apontador = lista.Primeiro;
    int repeticao = 0;
    for(int i=0, j=0; i<quantidade;i++){
        repeticao ++;
        if(valores[i+1] != apontador->Item.Tipo){
            j++;
            apontador->Item.NumElementos = repeticao;
            apontador->Prox;
            repeticao = 0;
        }
    }
    ordemCrescente(numeroSegmentos,lista);
}

/* ========================================================================== */

int main(){ 
    FILE *file;
    char NomeArquivo[50];
    printf("Digite o nome do arquivo: ");
    scanf("%s",NomeArquivo);
    if(!(file=fopen(NomeArquivo,"r"))){
        printf("Não foi possível abrir o arquivo\n");
        return 0;
    }
    int quantidade;
    fscanf(file,"%d", &quantidade);
    int valores[quantidade];
    for(int i=0; i<quantidade;i++){
        fscanf(file,"%d",&valores[i]);
    }
    segmentaVetor(quantidade,valores);
    
}