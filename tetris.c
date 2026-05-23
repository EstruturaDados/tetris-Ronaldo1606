#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5

/* Estrutura que representa uma peça do jogo */
typedef struct {
    char nome; // Tipo da peça: I, O, T, L
    int id;    // Identificador único
} Peca;

/* Estrutura da fila circular */
typedef struct {
    Peca fila[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

/* Protótipos das funções */
void inicializarFila(Fila *f);
Peca gerarPeca(int id);
int enfileirar(Fila *f, Peca p);
int desenfileirar(Fila *f);
void exibirFila(Fila *f);

/* Função principal */
int main() {
    Fila fila;
    int opcao;
    int contadorId = 0;

    srand(time(NULL)); // Inicializa gerador aleatório
    inicializarFila(&fila);

    /* Inicializa a fila com 5 peças */
    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(&fila, gerarPeca(contadorId++));
    }

    do {
        printf("\n============================\n");
        printf("Fila de peças futuras\n");
        exibirFila(&fila);

        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (!desenfileirar(&fila)) {
                    printf("Fila vazia! Nenhuma peça para jogar.\n");
                }
                break;

            case 2:
                if (!enfileirar(&fila, gerarPeca(contadorId++))) {
                    printf("Fila cheia! Não é possível inserir nova peça.\n");
                }
                break;

            case 0:
                printf("Encerrando o jogo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

/* Inicializa a fila */
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

/* Gera uma nova peça automaticamente */
Peca gerarPeca(int id) {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}

/* Insere uma peça no final da fila */
int enfileirar(Fila *f, Peca p) {
    if (f->quantidade == TAM_FILA) {
        return 0; // Fila cheia
    }

    f->fila[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
    return 1;
}

/* Remove a peça da frente da fila */
int desenfileirar(Fila *f) {
    if (f->quantidade == 0) {
        return 0; // Fila vazia
    }

    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
    return 1;
}

/* Exibe o estado atual da fila */
void exibirFila(Fila *f) {
    if (f->quantidade == 0) {
        printf("[Fila vazia]\n");
        return;
    }

    int i, pos = f->inicio;
    for (i = 0; i < f->quantidade; i++) {
        printf("[%c %d] ", f->fila[pos].nome, f->fila[pos].id);
        pos = (pos + 1) % TAM_FILA;
    }
    printf("\n");
}