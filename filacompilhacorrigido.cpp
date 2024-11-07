#include <stdio.h>
#include <stdlib.h>

// Defini��o da estrutura do processo
typedef struct process {
    int id;
    struct process* next;
} process;

// Fun��o para adicionar processo na fila (enqueue)
void enqueue(process** front, process** rear, int id) {
    process* new_process = (process*)malloc(sizeof(process));
    if (new_process == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }
    new_process->id = id;
    new_process->next = NULL;

    if (*rear == NULL) {
        *front = *rear = new_process;  // Se a fila estiver vazia, o novo processo � o primeiro e o �ltimo
    } else {
        (*rear)->next = new_process;
        *rear = new_process;
    }
}

// Fun��o para remover processo da fila (dequeue)
int dequeue(process** front, process** rear) {
    if (*front == NULL) {
        printf("Fila vazia! Nao e possivel desenfileirar.\n");
        return -1;
    }

    process* temp = *front;
    int id = temp->id;
    *front = temp->next;

    if (*front == NULL) {  // Se a fila ficou vazia, rear tamb�m deve ser atualizado
        *rear = NULL;
    }

    free(temp);  // Libera a mem�ria do processo removido
    return id;
}

// Fun��o para empilhar processo (push)
void push(process** stack, int id) {
    process* new_process = (process*)malloc(sizeof(process));
    if (new_process == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }
    new_process->id = id;
    new_process->next = *stack;
    *stack = new_process;
}

// Fun��o para desempilhar processo (pop)
int pop(process** stack) {
    if (*stack == NULL) {
        printf("Pilha vazia! Nao e possivel desempilhar.\n");
        return -1;
    }

    process* temp = *stack;
    int id = temp->id;
    *stack = temp->next;

    free(temp);  // Libera a mem�ria do processo removido
    return id;
}

// Fun��o para exibir o hist�rico de processos finalizados
void print_history(process* stack) {
    if (stack == NULL) {
        printf("Nenhum processo finalizado.\n");
        return;
    }

    printf("Historico de processos finalizados:\n");
    while (stack != NULL) {
        printf("Processo %d\n", stack->id);
        stack = stack->next;
    }
}

// Fun��o para limpar a tela
void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Fun��o principal
int main() {
    process* queue_front = NULL;
    process* queue_rear = NULL;
    process* stack_top = NULL;
    int choice, id;

    do {
        clear_screen();

        printf("\n------ Menu ------\n");
        printf("1. Adicionar processo a fila\n");
        printf("2. Remover processo da fila\n");
        printf("3. Empilhar processo\n");
        printf("4. Desempilhar processo\n");
        printf("5. Exibir historico de processos finalizados\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Informe o ID do processo a ser adicionado: ");
                scanf("%d", &id);
                enqueue(&queue_front, &queue_rear, id);
                printf("Processo %d adicionado a fila.\n", id);
                break;

            case 2:
                id = dequeue(&queue_front, &queue_rear);
                if (id != -1) {
                    printf("Processo %d removido da fila.\n", id);
                    push(&stack_top, id);
                }
                break;

            case 3:
                printf("Informe o ID do processo a ser empilhado: ");
                scanf("%d", &id);
                push(&stack_top, id);
                printf("Processo %d empilhado.\n", id);
                break;

            case 4:
                id = pop(&stack_top);
                if (id != -1) {
                    printf("Processo %d desempilhado.\n", id);
                }
                break;

            case 5:
                print_history(stack_top);
                break;

            case 6:
                printf("Encerrando.\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

        if (choice != 6) {
            printf("\nPressione Enter para continuar...");
            getchar();  // Captura o \n deixado pelo scanf
            getchar();  // Aguarda o usu�rio pressionar Enter
        }

    } while (choice != 6);

    return 0;
}

