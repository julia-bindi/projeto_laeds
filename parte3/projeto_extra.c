#include <stdlib.h>
#include <stdio.h>
#include<math.h>

/* código retirado do site: http://www2.dcc.ufmg.br/livros/algoritmos/implementacoes-03.php
referente ao livro de NIVIO ZIVIANI */

/* ========================================================================= */

typedef struct {
    int Chave;
    int Tipo;
    int NumElementos;
    int PontoMedio;
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
    TipoItem Item;
    TipoApontador Prox;
} TipoCelula;

typedef struct {
    TipoApontador Primeiro, Ultimo;
} TipoLista;

void FLVazia(TipoLista *Lista){ 
    Lista -> Primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
    Lista -> Ultimo = Lista -> Primeiro;
    Lista -> Primeiro -> Prox = NULL;
}

int Vazia(TipoLista Lista){
    return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista){ 
    Lista -> Ultimo -> Prox = (TipoApontador) malloc(sizeof(TipoCelula));
    Lista -> Ultimo = Lista -> Ultimo -> Prox;
    Lista -> Ultimo -> Item = x;
    Lista -> Ultimo -> Prox = NULL;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item){
/*  --- Obs.: o item a ser retirado é o seguinte ao apontado por p --- */
    TipoApontador q;
    if (Vazia(*Lista) || p == NULL || p -> Prox == NULL) {
        printf(" Erro Lista vazia ou posicao nao existe\n");
        return;
    }
    q = p -> Prox;
    *Item = q -> Item;
    p -> Prox = q -> Prox;
    if (p -> Prox == NULL) Lista -> Ultimo = p;
    free(q);
}

void Imprime(TipoLista Lista){
    TipoApontador Aux;
    Aux = Lista.Primeiro -> Prox;
    while (Aux != NULL){ 
        printf("%d\n", Aux -> Item.Chave);
        Aux = Aux -> Prox;
    }
}

/* ========================================================================== */

/* código referente ao exercício de tipos de segmentos adaptado para este problema */

/* ========================================================================== */

void imprimeResultado(int quantidade, int pontosMedios[], int N){
    int descarte = 0;
    for(int i=0; i<quantidade; i++){
        if(pontosMedios[i] == -1){
            descarte++;
        }
    }
    if(((float)descarte)/quantidade > 0.3){
        printf("Resultado: Formato da pista nao estimado.\n");
    }
    else{
        int diferenca[quantidade-1];
        int q = 0;
        for(int i=0; i<quantidade-1; i++){
            if(pontosMedios[i] != -1){
                if(pontosMedios[i+1] == -1){
                    diferenca[i] = pontosMedios[i+2] - pontosMedios[i];
                }
                else{
                    diferenca[i] = pontosMedios[i+1] - pontosMedios[i];
                } 
                q++;
            }           
        }
        int aumentou = 0;
        int diminuiu = 0;
        int permaneceu = 0;
        int dif;
        for(int i=0; i<q; i++){
            dif = diferenca[i+1] - diferenca[i];
            if(dif > 0)
                aumentou++;
            else if(dif < 0)
                diminuiu++;
            else
                permaneceu ++;          
        }
        float erro = 0.3 * (aumentou + diminuiu + permaneceu);
        if(aumentou - diminuiu >= (-1 * erro) && aumentou - diminuiu <= erro){
            printf("Resultado: Pista em linha reta.\n");
        }
        else if(aumentou > diminuiu){
            printf("Resultado: Curva a direita.\n");
        }
        else{
            printf("Resultado: Curva a esquerda.\n");
        }
    }
}

void imprimeResultadoFaixa(int quantidade, int pontosMedios[], int N){
    int faixa = 0;
    for(int i=0; i<quantidade; i++){
        if(pontosMedios[i] == -2){
            faixa++;
        }
    }
    if(faixa > 0){
        printf("Resultado: Pista com faixa de pedestres\n");
    }
    else{
        printf("Resultado: Pista sem faixa de pedestres\n");
    }
}

TipoLista ordemCrescente(int numeroSegmentos, TipoLista lista){
    int ordem[numeroSegmentos];
    ordem[0] = lista.Primeiro->Prox->Item.Tipo;
    int numerosDistintos = 1;
    TipoApontador apontador = lista.Primeiro->Prox;
    for(int i=1;i<numeroSegmentos;i++){
        apontador = apontador->Prox;
        for(int controle=0;controle<numerosDistintos;controle++){
            if(apontador->Item.Tipo == ordem[controle])
                break;
            if(controle == numerosDistintos-1){
                numerosDistintos++;
                ordem[numerosDistintos-1] = apontador->Item.Tipo;
            }
        }
    }
    for(int i=0;i<numerosDistintos;i++){
        for (int controle=0;controle<numerosDistintos-1;controle++){
            if(ordem[controle] > ordem[controle+1]){
                int aux = ordem[controle];
                ordem[controle] = ordem[controle+1];
                ordem[controle+1] = aux;
            }
        }
    }
    apontador = lista.Primeiro;
    for(int i=0;i<numeroSegmentos;i++){
        apontador = apontador->Prox;
        for(int controle=0;controle<numerosDistintos;controle++){
            if(apontador->Item.Tipo == ordem[controle]){
                apontador->Item.Tipo = controle+1;
                break;
            }
        }
    }
    return lista;
}


TipoLista segmentaVetor(int quantidade, int valores[]){
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
    int valor[2];
    valor[0] = 0;
    apontador = lista.Primeiro->Prox;
    int repeticao = 0;
    for(int i=0; i<quantidade;i++){
        repeticao ++;
        if(valores[i+1] != apontador->Item.Tipo){
            valor[1] = i;
            apontador->Item.NumElementos = repeticao;
            apontador->Item.PontoMedio = (valor[0] + valor[1]) / 2;
            apontador = apontador->Prox;
            valor[0] = i + 1;
            repeticao = 0;
        }
    }
    lista = ordemCrescente(numeroSegmentos,lista);
    return lista;
}

/* ========================================================================== */

void pontosMedios(int quantidade, TipoLista linhas[], int N){
    int pontosMedios[quantidade];
    int sequencia_pista[] = {1, 3, 2, 3, 1};
    int tamanho_pista = 5;
    int sequencia_faixa[] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};
    int tamanho_faixa = 11;
    int pontoMedio;
    int controle_pista = 0;
    int controle_faixa = 0;
    for(int i = 0; i < quantidade; i++){
        TipoApontador apontador = linhas[i].Primeiro;
        for(int j=0; j<linhas[i].Ultimo->Item.Chave; j++){
            apontador = apontador->Prox;
            if(apontador->Item.Tipo == sequencia_pista[controle_pista]){
                controle_pista++;
                if(controle_pista == ceil(tamanho_pista/2)){
                    pontoMedio = apontador->Item.PontoMedio;
                }
                if(controle_pista == tamanho_pista){
                    break;
                }
            }
            else if(apontador->Item.Tipo == sequencia_faixa[controle_faixa]){
                controle_faixa++;
                if(controle_faixa == tamanho_faixa){
                    pontoMedio = -2;
                    break;
                }
            }
            else if(apontador->Item.Tipo == sequencia_pista[0]){
                controle_pista = 1;
                controle_faixa = 1;
            }
            else{
                controle_pista = 0;
                controle_faixa = 0;
            }
        }
        if(controle_pista == tamanho_pista || controle_faixa == tamanho_faixa){
            pontosMedios[i] = pontoMedio;
        }
        else{
            pontosMedios[i] = -1;
        }
    }
    imprimeResultadoFaixa(quantidade, pontosMedios, N);
}

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
    TipoLista linhas[quantidade];
    int N;
    for(int i=0; i<quantidade;i++){
        fscanf(file,"%d",&N);
        int valores[N];
        for(int j=0; j<N; j++){
            fscanf(file,"%d",&valores[j]);
        }
        linhas[i] = segmentaVetor(N,valores);
    }
    pontosMedios(quantidade, linhas, N);
}