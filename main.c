#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct task
{
    char descricao[256];
    int prioridade;
    int situacao;
};

void adicionarTarefa()
{
    FILE *abrirArquivo = fopen("tarefas.txt", "r");
    if (abrirArquivo == NULL)
    {
        FILE *abrirArquivo = fopen("tarefas.txt", "w");
    };
    fclose(abrirArquivo);

    struct task novaTarefa;

    do
    {
        printf("Digite a descrição da tarefa: ");
        fgets(novaTarefa.descricao, sizeof(novaTarefa.descricao), stdin);
        novaTarefa.descricao[strcspn(novaTarefa.descricao, "\n")] = '\0';
        // tratamento de erros para descrição da tarefa
        if (strlen(novaTarefa.descricao) == 0)
        {
            printf("Descrição inválida. Por favor, digite uma descrição para a tarefa.\n");
        }
        if (strlen(novaTarefa.descricao) > 255)
        {
            printf("Descrição muito longa. Por favor, digite uma descrição com no máximo 255 caracteres.\n");
        }

    } while (strlen(novaTarefa.descricao) == 0 || strlen(novaTarefa.descricao) > 255);

    do
    {
        printf("Digite a prioridade da tarefa (1-5): ");
        scanf("%d", &novaTarefa.prioridade);
        if (novaTarefa.prioridade < 1 || novaTarefa.prioridade > 5)
        {
            printf("Prioridade inválida. Por favor, digite um valor entre 1 e 5.\n");
        }
        getchar();

    } while (novaTarefa.prioridade < 1 || novaTarefa.prioridade > 5);

    novaTarefa.situacao = 0;

    FILE *arquivo = fopen("tarefas.txt", "a");
    fprintf(arquivo, "%s, %d, %d\n", novaTarefa.descricao, novaTarefa.prioridade, novaTarefa.situacao);
    fclose(arquivo);
    printf("Tarefa adicionada com sucesso!\n");
}

void editarTarefas()
{
}

void listarTarefas()
{
    FILE *abrirArquivo = fopen("tarefas.txt", "r");
    if (abrirArquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de tarefas.\n");
        return;
    }

    char descricao[256];
    int prioridade;
    int situacao;

    printf("\nLista de tarefas:\n");
    while (fscanf(abrirArquivo, "%255[^,], %d, %d\n", descricao, &prioridade, &situacao) != EOF)
    {
        printf("Descrição: %s | Prioridade: %d | Situação: %s\n", descricao, prioridade, situacao ? "Concluída" : "Pendente");
    }
    fclose(abrirArquivo);

    printf("Aperte enter para fechar: ");
    scanf("%*c");
}

void listarTarefasPendentes()
{
    FILE *abrirArquivo = fopen("tarefas.txt", "r");
    if (abrirArquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de tarefas.\n");
        return;
    }

    char descricao[256];
    int prioridade;
    int situacao;

    printf("\nLista de tarefas pendentes:\n");
    while (fscanf(abrirArquivo, "%255[^,], %d, %d\n", descricao, &prioridade, &situacao) != EOF)
    {
        if (situacao == 0)
        {
            printf("Descrição: %s | Prioridade: %d | Situação: %s\n", descricao, prioridade, situacao ? "Concluída" : "Pendente");
        }
    }
    fclose(abrirArquivo);

    printf("Aperte enter para fechar: ");
    scanf("%*c");
}

void listarTarefasConcluidas()
{
    FILE *abrirArquivo = fopen("tarefas.txt", "r");
    if (abrirArquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de tarefas.\n");
        return;
    }

    char descricao[256];
    int prioridade;
    int situacao;

    printf("\nLista de tarefas concluídas:\n");
    while (fscanf(abrirArquivo, "%255[^,], %d, %d\n", descricao, &prioridade, &situacao) != EOF)
    {
        if (situacao == 1)
        {
            printf("Descrição: %s | Prioridade: %d | Situação: %s\n", descricao, prioridade, situacao ? "Concluída" : "Pendente");
        }
    }
    fclose(abrirArquivo);

    printf("Aperte enter para fechar: ");
    scanf("%*c");
}

int main()
{

    int opcao;

    while (true)
    {
        system("clear");
        printf("+--------------------------------------+\n");
        printf("|              TODO LIST               |\n");
        printf("|        Organize suas tarefas         |\n");
        printf("+--------------------------------------+\n");

        printf("Escolha uma opção:\n");
        printf("1. Adicionar tarefa\n");
        printf("2. Editar tarefas\n");
        printf("3. Listar tarefas\n");
        printf("4. Listar tarefas pendentes\n");
        printf("5. Listar tarefas concluídas\n");
        printf("0. Sair\n");

        do
        {
            printf("Digite sua opção: ");
            scanf("%d", &opcao);
            getchar();
            if (opcao < 0 || opcao > 5)
            {
                printf("Opção inválida. Por favor, digite um número entre 0 e 5.\n");
            }
        } while (opcao < 0 || opcao > 5);

        switch (opcao)
        {
        case 1:
            system("clear");
            printf("\nAdicionar tarefa selecionado.");
            adicionarTarefa();
            break;

        case 2:
            system("clear");
            printf("\nEditar tarefa selecionado.");
            editarTarefas();
            break;

        case 3:
            system("clear");
            printf("\nListar tarefas selecionado.");
            listarTarefas();
            break;

        case 4:
            system("clear");
            printf("\nListar tarefas pendentes selecionado.");
            listarTarefasPendentes();
            break;

        case 5:
            system("clear");
            printf("\nListar tarefas concluídas selecionado.");
            listarTarefasConcluidas();
            break;

        case 0:
            printf("Saindo do programa. Até logo!\n");
            exit(0);
        }
    }

    return 0;
}