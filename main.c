#include <stdio.h>
#include <stdbool.h>

struct task
{
    char descricao[256];
    int prioridade;
    bool situacao;
};

void menu()
{
    printf("\nEscolha uma opção:\n");
    printf("1. Adicionar tarefa\n");
    printf("2. Listar tarefas\n");
    printf("3. Listar tarefas pendentes\n");
    printf("4. Listar tarefas concluídas\n");
    printf("0. Sair\n");
}

void adicionarTarefa()
{
    
}

int main()
{
    printf("+--------------------------------------+\n");
    printf("|              TODO LIST               |\n");
    printf("|        Organize suas tarefas         |\n");
    printf("+--------------------------------------+\n");

    int opcao;

    printf("\nEscolha uma opção:\n");
    printf("1. Adicionar tarefa\n");
    printf("2. Listar tarefas\n");
    printf("3. Listar tarefas pendentes\n");
    printf("4. Listar tarefas concluídas\n");
    printf("0. Sair\n");

    
    while (true){
        scanf("%d", &opcao);
        switch (opcao){
        case 1:
            printf("Adicionar tarefa selecionada.\n");
                adicionarTarefa();
    
        case 2:
            printf("Listar tarefas selecionada.\n");
            // Lógica para listar todas as tarefas
    
        case 3:
            printf("Listar tarefas pendentes selecionada.\n");
            // Lógica para listar tarefas pendentes
            
        case 4:
            printf("Listar tarefas concluídas selecionada.\n");
            // Lógica para listar tarefas concluídas
            
        case 0:
            printf("Saindo do programa. Até logo!\n");
            exit(0);
        default:
            printf("Opção inválida. Por favor, tente novamente.\n");
        }
    }
    return 0;
}