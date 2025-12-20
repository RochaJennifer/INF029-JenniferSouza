#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

typedef struct {
    int *aux;          
    int tamanho;       
    int quantidade;  
} EstruturaPrincipal;

EstruturaPrincipal vetorPrincipal[TAM];

void ordenar(int vetor[], int n) {
    int i, j, aux;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/



int criarEstruturaAuxiliar(int posicao, int tamanho) {
    if (ehPosicaoValida(posicao) != SUCESSO) return POSICAO_INVALIDA;
    if (tamanho < 1) return TAMANHO_INVALIDO;
    
    int idx = posicao - 1;
    if (vetorPrincipal[idx].aux != NULL) return JA_TEM_ESTRUTURA_AUXILIAR;

    vetorPrincipal[idx].aux = (int *)malloc(tamanho * sizeof(int));
    if (!vetorPrincipal[idx].aux) return SEM_ESPACO_DE_MEMORIA;

    vetorPrincipal[idx].tamanho = tamanho;
    vetorPrincipal[idx].quantidade = 0;

    return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor) {
    if (ehPosicaoValida(posicao) != SUCESSO) return POSICAO_INVALIDA;
    
    int idx = posicao - 1;
    if (vetorPrincipal[idx].aux == NULL) return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[idx].quantidade >= vetorPrincipal[idx].tamanho) return SEM_ESPACO;

    vetorPrincipal[idx].aux[vetorPrincipal[idx].quantidade] = valor;
    vetorPrincipal[idx].quantidade++;
    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao) {
    if (ehPosicaoValida(posicao) != SUCESSO) return POSICAO_INVALIDA;
    
    int idx = posicao - 1;
    if (vetorPrincipal[idx].aux == NULL) return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[idx].quantidade == 0) return ESTRUTURA_AUXILIAR_VAZIA;

    vetorPrincipal[idx].quantidade--;
    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
    if (ehPosicaoValida(posicao) != SUCESSO) return POSICAO_INVALIDA;
    
    int idx = posicao - 1;
    if (vetorPrincipal[idx].aux == NULL) return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[idx].quantidade == 0) return ESTRUTURA_AUXILIAR_VAZIA;

    int encontrado = -1;
    for (int i = 0; i < vetorPrincipal[idx].quantidade; i++) {
        if (vetorPrincipal[idx].aux[i] == valor) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) return NUMERO_INEXISTENTE;

    // Shift para manter a integridade (remover a primeira ocorrência) [cite: 41, 42]
    for (int i = encontrado; i < vetorPrincipal[idx].quantidade - 1; i++) {
        vetorPrincipal[idx].aux[i] = vetorPrincipal[idx].aux[i + 1];
    }
    vetorPrincipal[idx].quantidade--;
    return SUCESSO;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    if (ehPosicaoValida(posicao) != SUCESSO) return POSICAO_INVALIDA;
    
    int idx = posicao - 1;
    if (vetorPrincipal[idx].aux == NULL) return SEM_ESTRUTURA_AUXILIAR;

    for (int i = 0; i < vetorPrincipal[idx].quantidade; i++) {
        vetorAux[i] = vetorPrincipal[idx].aux[i];
    }
    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    int ret = getDadosEstruturaAuxiliar(posicao, vetorAux);
    if (ret == SUCESSO) {
        ordenar(vetorAux, vetorPrincipal[posicao - 1].quantidade);
    }
    return ret;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{

    int retorno = 0;
    return retorno;
}int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int k = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].aux != NULL) {
            for (int j = 0; j < vetorPrincipal[i].quantidade; j++) {
                vetorAux[k++] = vetorPrincipal[i].aux[j];
            }
        }
    }
    return (k == 0) ? TODAS_ESTRUTURAS_AUXILIARES_VAZIAS : SUCESSO;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int k = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].aux != NULL) {
            for (int j = 0; j < vetorPrincipal[i].quantidade; j++) {
                vetorAux[k++] = vetorPrincipal[i].aux[j];
            }
        }
    }
    if (k == 0) return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    ordenar(vetorAux, k);
    return SUCESSO;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) {
    if (ehPosicaoValida(posicao) != SUCESSO) return POSICAO_INVALIDA;
    
    int idx = posicao - 1;
    if (vetorPrincipal[idx].aux == NULL) return SEM_ESTRUTURA_AUXILIAR;

    int tamanhoFinal = vetorPrincipal[idx].tamanho + novoTamanho;
    if (tamanhoFinal < 1) return NOVO_TAMANHO_INVALIDO;

    int *temp = (int *)realloc(vetorPrincipal[idx].aux, tamanhoFinal * sizeof(int));
    if (!temp) return SEM_ESPACO_DE_MEMORIA;

    vetorPrincipal[idx].aux = temp;
    vetorPrincipal[idx].tamanho = tamanhoFinal;
    if (vetorPrincipal[idx].quantidade > tamanhoFinal) 
        vetorPrincipal[idx].quantidade = tamanhoFinal;

    return SUCESSO;
}


/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao) {
    if (ehPosicaoValida(posicao) != SUCESSO) return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1].aux == NULL) return SEM_ESTRUTURA_AUXILIAR;
    return vetorPrincipal[posicao - 1].quantidade;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote() {
    No *cabecote = (No *)malloc(sizeof(No));
    cabecote->prox = NULL;
    No *atual = cabecote;

    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].aux != NULL) {
            for (int j = 0; j < vetorPrincipal[i].quantidade; j++) {
                No *novo = (No *)malloc(sizeof(No));
                novo->conteudo = vetorPrincipal[i].aux[j];
                novo->prox = NULL;
                atual->prox = novo;
                atual = novo;
            }
        }
    }
    if (cabecote->prox == NULL) {
        free(cabecote);
        return NULL;
    }
    return cabecote;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]) {
    No *atual = inicio->prox;
    int i = 0;
    while (atual != NULL) {
        vetorAux[i++] = atual->conteudo;
        atual = atual->prox;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio) {
    No *atual = *inicio;
    while (atual != NULL) {
        No *tmp = atual;
        atual = atual->prox;
        free(tmp);
    }
    *inicio = NULL;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar() {
    for (int i = 0; i < TAM; i++) {
        vetorPrincipal[i].aux = NULL;
        vetorPrincipal[i].tamanho = 0;
        vetorPrincipal[i].quantidade = 0;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar() {
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].aux != NULL) {
            free(vetorPrincipal[i].aux);
            vetorPrincipal[i].aux = NULL;
        }
    }
}
