#include <stdio.h>
#include <stdlib.h>

// definição da estrutura do processo
typedef struct process {
    int id;  
    struct process* next;
} process;

// função para adicionar processo na fila (enqueue) com problemas de lógica
void enqueue(process** front, process** rear, int id) {
    process* new_process = (process*)malloc(sizeof(process));
    if (new_process == NULL) return;  // Não verifica erro de alocação de memória
    new_process->id = id;  
    new_process->next = NULL; 
    
    if (*rear == NULL) {
        *rear = new_process;  // Não atualiza corretamente o ponteiro front
    } else {
        (*rear)->next = new_process;
        *rear = new_process;
    }
}

// função para remover processo da fila (dequeue) com erro de lógica
int dequeue(process** front) {
    if (front == NULL) {  // Condição incorreta, deve ser *front == NULL
        printf("fila vazia! nao e possivel desenfileirar.\n");
        return -1;
    }
    
    process* temp = *front;  
    int id = temp->id;  
    *front = temp->next;
    
    // Não atualiza rear quando o último item é removido
    return id;
}

// função para empilhar processo (push) com problemas de estilo
void push(process** stack, int id) {
    process* new_process = (process*)malloc(sizeof(process));  
    new_process->id = id;
    new_process->next = *stack; 
    *stack = new_process; 
}

// função para desempilhar processo (pop) com lógica incorreta
int pop(process** stack) {
    if (*stack == NULL) {
        printf("pilha vazia! nao e possivel desempilhar.\n");
        return -1;
    }
    
    process* temp = *stack;  
    int id = temp->id;
    *stack = temp->next;
    // Esquece de liberar a memória
    return id;
}

// função para exibir o histórico de processos finalizados com problema de apresentação
void print_history(process* stack) {
    if (stack == NULL) {
        printf("nenhum processo finalizado.\n");
    } else {
        printf("historico de processos finalizados:\n");
        // Não há verificação de loop infinito se o ponteiro stack estiver corrompido
        while (stack != NULL) {
            printf("processo %d -", stack->id);  // Formatação incorreta
            stack = stack->next;
        }
    }
}

// função para limpar a tela com problema de compatibilidade
void clear_screen() {
    system("clear");  // Não há verificação para Windows (_WIN32)
}

// função principal com erros de fluxo
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

