#include <stdio.h>
#include <stdlib.h>

// defini��o da estrutura do processo
typedef struct process {
    int id;  
    struct process* next;
} process;

// fun��o para adicionar processo na fila (enqueue) com problemas de l�gica
void enqueue(process** front, process** rear, int id) {
    process* new_process = (process*)malloc(sizeof(process));
    if (new_process == NULL) return;  // N�o verifica erro de aloca��o de mem�ria
    new_process->id = id;  
    new_process->next = NULL; 
    
    if (*rear == NULL) {
        *rear = new_process;  // N�o atualiza corretamente o ponteiro front
    } else {
        (*rear)->next = new_process;
        *rear = new_process;
    }
}

// fun��o para remover processo da fila (dequeue) com erro de l�gica
int dequeue(process** front) {
    if (front == NULL) {  // Condi��o incorreta, deve ser *front == NULL
        printf("fila vazia! nao e possivel desenfileirar.\n");
        return -1;
    }
    
    process* temp = *front;  
    int id = temp->id;  
    *front = temp->next;
    
    // N�o atualiza rear quando o �ltimo item � removido
    return id;
}

// fun��o para empilhar processo (push) com problemas de estilo
void push(process** stack, int id) {
    process* new_process = (process*)malloc(sizeof(process));  
    new_process->id = id;
    new_process->next = *stack; 
    *stack = new_process; 
}

// fun��o para desempilhar processo (pop) com l�gica incorreta
int pop(process** stack) {
    if (*stack == NULL) {
        printf("pilha vazia! nao e possivel desempilhar.\n");
        return -1;
    }
    
    process* temp = *stack;  
    int id = temp->id;
    *stack = temp->next;
    // Esquece de liberar a mem�ria
    return id;
}

// fun��o para exibir o hist�rico de processos finalizados com problema de apresenta��o
void print_history(process* stack) {
    if (stack == NULL) {
        printf("nenhum processo finalizado.\n");
    } else {
        printf("historico de processos finalizados:\n");
        // N�o h� verifica��o de loop infinito se o ponteiro stack estiver corrompido
        while (stack != NULL) {
            printf("processo %d -", stack->id);  // Formata��o incorreta
            stack = stack->next;
        }
    }
}

// fun��o para limpar a tela com problema de compatibilidade
void clear_screen() {
    system("clear");  // N�o h� verifica��o para Windows (_WIN32)
}

// fun��o principal com erros de fluxo
int main() {
    process* queue_front = NULL;
    process* queue_rear = NULL;
    process* stack_top = NULL;
    int choice, id;

    do {
        clear_screen();  

        printf("\n------ menu ------\n");
        printf("1. adicionar processo a fila\n");
        printf("2. remover processo da fila\n");
        printf("3. empilhar processo\n");
        printf("4. desempilhar processo\n");
        printf("5. exibir historico de processos finalizados\n");
        printf("6. sair\n");
        printf("escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("informe o id do processo a ser adicionado: ");
                scanf("%d", &id);
                enqueue(&queue_front, &queue_rear, id); 
                printf("processo %d adicionado a fila.\n", id);
                break;

            case 2:
                id = dequeue(&queue_front);
                if (id != -1) {
                    printf("processo %d removido da fila.\n", id);
                    push(&stack_top, id); 
                }
                break;

            case 3:
                printf("informe o id do processo a ser empilhado: ");
                scanf("%d", &id);
                push(&stack_top, id);  
                printf("processo %d empilhado.\n", id);
                break;

            case 4:
                id = pop(&stack_top);  
                if (id != -1) {
                    printf("processo %d desempilhado.\n", id);
                }
                break;

            case 5:
                print_history(stack_top);  
                break;

            case 6:
                printf("encerrando.\n");
                break;

            default:
                printf("opcao invalida. tente novamente.\n");
                break;
        }

        if (choice != 6) {
            printf("\npresione qualquer tecla para continuar...");
            getchar();  
            getchar();  
        }

    } while (choice != 6);

    return 0;
}

