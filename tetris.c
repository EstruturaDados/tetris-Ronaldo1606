#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

/* Estrutura da Peça  */

typedef struct {
    char nome; // I, O, T, L
    int id;    // identificador único
} Peca;

/* Fila Circular  */

typedef struct {
    Peca dados[TAM_FILA];
    int inicio;
    int fim;
    int qtd;
} Fila;

/* Pilha  */

typedef struct {
    Peca dados[TAM_PILHA];
    int topo;
} Pilha;

/* Protótipos   */

void inicializarFila(Fila *f);
void inicializarPilha(Pilha *p);
Peca gerarPeca(int id);

Peca dequeue(Fila *f);
void enqueue(Fila *f, Peca p);

void push(Pilha *p, Peca peca);
Peca pop(Pilha *p);

void exibirEstado(Fila *f, Pilha *p);

/* Função principal*/

int main() {
    Fila fila;
    Pilha pilha;
    int opcao;
    int contadorId = 0;

    srand(time(NULL));

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    /* Preenche fila inicial */

    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(contadorId++));
    }

    do {
        exibirEstado(&fila, &pilha);

        printf("\nOpções disponíveis:\n");
        printf("1 - Jogar peça da frente da fila\n");
        printf("2 - Enviar peça da fila para a pilha\n");
        printf("3 - Usar peça da pilha\n");
        printf("4 - Trocar frente da fila com topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com os 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Opção escolhida: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            dequeue(&fila);
            enqueue(&fila, gerarPeca(contadorId++));

        } else if (opcao == 2) {
            if (pilha.topo < TAM_PILHA - 1) {
                push(&pilha, dequeue(&fila));
                enqueue(&fila, gerarPeca(contadorId++));
            } else {
                printf("\nPilha cheia! Operação cancelada.\n");
            }

        } else if (opcao == 3) {
            if (pilha.topo >= 0) {
                pop(&pilha);
                enqueue(&fila, gerarPeca(contadorId++));
            } else {
                printf("\nPilha vazia!\n");
            }

        } else if (opcao == 4) {
            if (pilha.topo >= 0) {
                Peca temp = fila.dados[fila.inicio];
                fila.dados[fila.inicio] = pilha.dados[pilha.topo];
                pilha.dados[pilha.topo] = temp;
                printf("\nTroca simples realizada.\n");
            } else {
                printf("\nPilha vazia! Troca impossível.\n");
            }

        } else if (opcao == 5) {
            if (fila.qtd >= 3 && pilha.topo >= 2) {
                for (int i = 0; i < 3; i++) {
                    int posFila = (fila.inicio + i) % TAM_FILA;
                    Peca temp = fila.dados[posFila];
                    fila.dados[posFila] = pilha.dados[pilha.topo - i];
                    pilha.dados[pilha.topo - i] = temp;
                }
                printf("\nTroca múltipla realizada entre fila e pilha.\n");
            } else {
                printf("\nNão há peças suficientes para troca múltipla.\n");
            }
        }

    } while (opcao != 0);

    printf("\nPrograma encerrado.\n");
    return 0;
}

/* Implementações  */

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
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

void enqueue(Fila *f, Peca p) {
    f->dados[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->qtd++;
}

Peca dequeue(Fila *f) {
    Peca p = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->qtd--;
    return p;
}

void push(Pilha *p, Peca peca) {
    p->dados[++p->topo] = peca;
}

Peca pop(Pilha *p) {
    return p->dados[p->topo--];
}

void exibirEstado(Fila *f, Pilha *p) {
    printf("\n==============================\n");
    printf("Estado atual:\n");

    printf("Fila de peças: ");
    for (int i = 0; i < f->qtd; i++) {
        int pos = (f->inicio + i) % TAM_FILA;
        printf("[%c %d] ", f->dados[pos].nome, f->dados[pos].id);
    }

    printf("\nPilha de reserva (Topo -> Base): ");
    if (p->topo < 0) {
        printf("[vazia]");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->dados[i].nome, p->dados[i].id);
        }
    }
    printf("\n==============================\n");
}