#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Carro {
    char chassi[20];
    int ano;
    struct Carro *prox;
} Carro;

// função para adicionar um carro na lista
// reserva um espaço de memoria antes de cadastrar um novo carro.
Carro* adicionarCarro(Carro *lista) {
    Carro *novo = (Carro*) malloc(sizeof(Carro));
    if (!novo) {
        printf("Erro de memória!\n");
        exit(1);
    }

    printf("Digite o chassi do carro: ");
    scanf("%19s", novo->chassi);  // Pra deixar o espço do /n de fora
    printf("Digite o ano do carro: ");
    scanf("%d", &novo->ano);

    novo->prox = NULL;

    if (lista == NULL) { //lista vazia
        return novo; // cadastra como primeiro carro da lista
    } else {
        Carro *atual = lista; // percorre até o final da lista para cadastrar o novo carro no fim da lista
        while (atual->prox != NULL) {
            atual = atual->prox; 
        }
        atual->prox = novo; 
        return lista;
    }
}

// função para listar todos os carros cadastrados
void mostrarCarros(Carro *lista) { // inicio da lista
    Carro *atual = lista; //marcador para percorrer a lista sem perder o inicio
    while (atual != NULL) {
        printf("Chassi: %s | Ano: %d\n", atual->chassi, atual->ano); // mostra o carro atual
        atual = atual->prox; // avança para o próximo carro até o final da lista
    }
}

int main() {
    Carro *lista = NULL;
    int qtd, i;

    printf("Quantos carros deseja cadastrar? ");
    scanf("%d", &qtd);

    for (i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do carro %d ---\n", i + 1);
        lista = adicionarCarro(lista);
    }

    printf("\n== Carros cadastrados ==\n");
    mostrarCarros(lista);

    return 0;
}
