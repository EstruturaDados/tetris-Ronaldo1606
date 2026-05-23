#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

/*   Estrutura da Peça*/

typedef struct {
    char nome; // Tipo da peça: I, O, T, L
    int id;    // Identificador único
} Peca;

/*   Estrutura da Fila Circular */

typedef struct {
    Peca dados[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

/* Estrutura da Pilha */

typedef struct {
    Peca dados[TAM_PILHA];
    int topo;
} Pilha;

/* Protótipos */

void inicializarFila(Fila *f);
void inicializarPilha(Pilha *p);
Peca gerarPeca(int id);

int enfileirar(Fila *f, Peca p);
Peca desenfileirar(Fila *f);

int empilhar(Pilha *p, Peca peca);
Peca desempilhar(Pilha *p);

void exibirEstado(Fila *f, Pilha *p);

/* Função principal  */

int main() {
    Fila fila;
    Pilha pilha;
    int opcao;
    int contadorId = 0;

    srand(time(NULL));

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    /* Preenche a fila inicial */
    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(&fila, gerarPeca(contadorId++));
    }

    do {
        exibirEstado(&fila, &pilha);

        printf("\nOpções de Ação:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            /* Jogar peça */
            desenfileirar(&fila);
            enfileirar(&fila, gerarPeca(contadorId++));

        } else if (opcao == 2) {
            /* Reservar peça */
            if (pilha.topo < TAM_PILHA - 1) {
                Peca p = desenfileirar(&fila);
                empilhar(&pilha, p);
                enfileirar(&fila, gerarPeca(contadorId++));
            } else {
                printf("\nPilha de reserva cheia!\n");
            }

        } else if (opcao == 3) {
            /* Usar peça reservada */
            if (pilha.topo >= 0) {
                desempilhar(&pilha);
                enfileirar(&fila, gerarPeca(contadorId++));
            } else {
                printf("\nPilha de reserva vazia!\n");
            }

        } else if (opcao != 0) {
            printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    printf("\nJogo encerrado.\n");
    return 0;
}

/* Implementações   */

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

Peca gerarPeca(int id) {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}

int enfileirar(Fila *f, Peca p) {
    if (f->quantidade == TAM_FILA) {
        return 0;
    }
    f->dados[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
    return 1;
}

Peca desenfileirar(Fila *f) {
    Peca removida = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
    return removida;
}

int empilhar(Pilha *p, Peca peca) {
    if (p->topo == TAM_PILHA - 1) {
        return 0;
    }
    p->dados[++p->topo] = peca;
    return 1;
}

Peca desempilhar(Pilha *p) {
    return p->dados[p->topo--];
}

void exibirEstado(Fila *f, Pilha *p) {
    printf("\n=============================\n");
    printf("Estado atual:\n");

    printf("Fila de peças: ");
    int pos = f->inicio;
    for (int i = 0; i < f->quantidade; i++) {
        printf("[%c %d] ", f->dados[pos].nome, f->dados[pos].id);
        pos = (pos + 1) % TAM_FILA;
    }

    printf("\nPilha de reserva (Topo -> Base): ");
    if (p->topo < 0) {
        printf("[vazia]");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->dados[i].nome, p->dados[i].id);
        }
    }
    printf("\n=============================\n");
}