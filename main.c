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
    FILE *arquivo = fopen("tarefas.txt", "a");

    struct task novaTarefa;

    do
    {
        printf("Digite a descrição da tarefa: ");
        fgets(novaTarefa.descricao, sizeof(novaTarefa.descricao), stdin);
        novaTarefa.descricao[strcspn(novaTarefa.descricao, "\n")] = '\0';
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

    fprintf(arquivo, "%s, %d, %d\n", novaTarefa.descricao, novaTarefa.prioridade, novaTarefa.situacao);
    fclose(arquivo);
    printf("Tarefa adicionada com sucesso!\n");
}

void marcarTarefaConcluida()
{
    FILE *abrirArquivo = fopen("tarefas.txt", "r");
    if (abrirArquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de tarefas.\n");
        return;
    }
    FILE *arquivoTemp = fopen("tarefas_temp.txt", "w");

    int id = 1;
    char situacao_temp[2];

    struct task tarefaEditar;

    printf("\ntarefas:\n");
    while (fscanf(abrirArquivo, "%255[^,], %d, %d\n", tarefaEditar.descricao, &tarefaEditar.prioridade, &tarefaEditar.situacao) != EOF)
    {
        printf("ID: %d | Descrição: %s | Prioridade: %d | Situação: %s\n", id, tarefaEditar.descricao, tarefaEditar.prioridade, tarefaEditar.situacao ? "Concluída" : "Pendente");
        id++;
    }

    rewind(abrirArquivo);
    int idEdicao;

    do
    {
        printf("Digite o ID da tarefa que deseja marcar como concluida: ");
        scanf("%d", &idEdicao);
        getchar();
        if (idEdicao < 1 || idEdicao >= id)
        {
            printf("ID inválido. Por favor, digite um ID válido.\n");
        }
    } while (idEdicao < 1 || idEdicao >= id);

    id = 1;

    while (fscanf(abrirArquivo, "%255[^,], %d, %d\n", tarefaEditar.descricao, &tarefaEditar.prioridade, &tarefaEditar.situacao) != EOF)
    {
        if (id == idEdicao)
        {
            do
            {
                printf("Deseja marcar a tarefa como concluída? (y - SIM, n - NÂO): ");
                fgets(situacao_temp, sizeof(situacao_temp), stdin);
                situacao_temp[strcspn(situacao_temp, "\n")] = '\0';
                if (strcmp(situacao_temp, "y") == 0 || strcmp(situacao_temp, "Y") == 0)
                {
                    tarefaEditar.situacao = 1;
                }
                else if (strcmp(situacao_temp, "n") == 0 || strcmp(situacao_temp, "N") == 0)
                {
                    tarefaEditar.situacao = 0;
                }
                else
                {
                    printf("Opção inválida. Por favor, digite 'y' para SIM ou 'n' para NÃO.\n");
                }

            } while (situacao_temp[0] != 'y' && situacao_temp[0] != 'Y' && situacao_temp[0] != 'n' && situacao_temp[0] != 'N');

            fprintf(arquivoTemp, "%s, %d, %d\n", tarefaEditar.descricao, tarefaEditar.prioridade, tarefaEditar.situacao);
        }

        else
        {
            fprintf(arquivoTemp, "%s, %d, %d\n", tarefaEditar.descricao, tarefaEditar.prioridade, tarefaEditar.situacao);
        }
        id++;
    }

    fclose(abrirArquivo);
    fclose(arquivoTemp);
    remove("tarefas.txt");
    rename("tarefas_temp.txt", "tarefas.txt");
}

void apagarTarefa()
{
    FILE *abrirArquivo = fopen("tarefas.txt", "r");
    if (abrirArquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de tarefas.\n");
        return;
    }
    FILE *arquivoTemp = fopen("tarefas_temp.txt", "w");

    int id = 1;
    char situacao_temp[2];

    struct task tarefaEditar;

    printf("\ntarefas:\n");
    while (fscanf(abrirArquivo, "%255[^,], %d, %d\n", tarefaEditar.descricao, &tarefaEditar.prioridade, &tarefaEditar.situacao) != EOF)
    {
        printf("ID: %d | Descrição: %s | Prioridade: %d | Situação: %s\n", id, tarefaEditar.descricao, tarefaEditar.prioridade, tarefaEditar.situacao ? "Concluída" : "Pendente");
        id++;
    }

    rewind(abrirArquivo);
    int idEdicao;

    do
    {
        printf("Digite o ID da tarefa que deseja apagar: ");
        scanf("%d", &idEdicao);
        getchar();
        if (idEdicao < 1 || idEdicao >= id)
        {
            printf("ID inválido. Por favor, digite um ID válido.\n");
        }
    } while (idEdicao < 1 || idEdicao >= id);

    id = 1;

    while (fscanf(abrirArquivo, "%255[^,], %d, %d\n", tarefaEditar.descricao, &tarefaEditar.prioridade, &tarefaEditar.situacao) != EOF)
    {
        if (id == idEdicao)
        {
            continue;
        }

        else
        {
            fprintf(arquivoTemp, "%s, %d, %d\n", tarefaEditar.descricao, tarefaEditar.prioridade, tarefaEditar.situacao);
        }
        id++;
    }

    fclose(abrirArquivo);
    fclose(arquivoTemp);
    remove("tarefas.txt");
    rename("tarefas_temp.txt", "tarefas.txt");
}

void editarTarefa()
{
    FILE *abrirArquivo = fopen("tarefas.txt", "r");
    if (abrirArquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de tarefas.\n");
        return;
    }
    FILE *arquivoTemp = fopen("tarefas_temp.txt", "w");

    int id = 1;
    char situacao_temp[2];

    struct task tarefaEditar;

    printf("\ntarefas:\n");
    while (fscanf(abrirArquivo, "%255[^,], %d, %d\n", tarefaEditar.descricao, &tarefaEditar.prioridade, &tarefaEditar.situacao) != EOF)
    {
        printf("ID: %d | Descrição: %s | Prioridade: %d | Situação: %s\n", id, tarefaEditar.descricao, tarefaEditar.prioridade, tarefaEditar.situacao ? "Concluída" : "Pendente");
        id++;
    }

    rewind(abrirArquivo);
    int idEdicao;

    do
    {
        printf("Digite o ID da tarefa que deseja editar: ");
        scanf("%d", &idEdicao);
        getchar();
        if (idEdicao < 1 || idEdicao >= id)
        {
            printf("ID inválido. Por favor, digite um ID válido.\n");
        }
    } while (idEdicao < 1 || idEdicao >= id);

    id = 1;

    while (fscanf(abrirArquivo, "%255[^,], %d, %d\n", tarefaEditar.descricao, &tarefaEditar.prioridade, &tarefaEditar.situacao) != EOF)
    {
        if (id == idEdicao)
        {
            do
            {
                printf("Digite a descrição da tarefa: ");
                fgets(tarefaEditar.descricao, sizeof(tarefaEditar.descricao), stdin);
                tarefaEditar.descricao[strcspn(tarefaEditar.descricao, "\n")] = '\0';

                if (strlen(tarefaEditar.descricao) == 0)
                {
                    printf("Descrição inválida. Por favor, digite uma descrição para a tarefa.\n");
                }
                if (strlen(tarefaEditar.descricao) > 255)
                {
                    printf("Descrição muito longa. Por favor, digite uma descrição com no máximo 255 caracteres.\n");
                }

            } while (strlen(tarefaEditar.descricao) == 0 || strlen(tarefaEditar.descricao) > 255);

            do
            {
                printf("Digite a prioridade da tarefa (1-5): ");
                scanf("%d", &tarefaEditar.prioridade);
                if (tarefaEditar.prioridade < 1 || tarefaEditar.prioridade > 5)
                {
                    printf("Prioridade inválida. Por favor, digite um valor entre 1 e 5.\n");
                }
                getchar();

            } while (tarefaEditar.prioridade < 1 || tarefaEditar.prioridade > 5);

            do
            {
                printf("Deseja marcar a tarefa como concluída? (y - SIM, n - NÂO): ");
                fgets(situacao_temp, sizeof(situacao_temp), stdin);
                situacao_temp[strcspn(situacao_temp, "\n")] = '\0';
                if (strcmp(situacao_temp, "y") == 0 || strcmp(situacao_temp, "Y") == 0)
                {
                    tarefaEditar.situacao = 1;
                }
                else if (strcmp(situacao_temp, "n") == 0 || strcmp(situacao_temp, "N") == 0)
                {
                    tarefaEditar.situacao = 0;
                }
                else
                {
                    printf("Opção inválida. Por favor, digite 'y' para SIM ou 'n' para NÃO.\n");
                }

            } while (situacao_temp[0] != 'y' && situacao_temp[0] != 'Y' && situacao_temp[0] != 'n' && situacao_temp[0] != 'N');

            fprintf(arquivoTemp, "%s, %d, %d\n", tarefaEditar.descricao, tarefaEditar.prioridade, tarefaEditar.situacao);
        }

        else
        {
            fprintf(arquivoTemp, "%s, %d, %d\n", tarefaEditar.descricao, tarefaEditar.prioridade, tarefaEditar.situacao);
        }
        id++;
    }

    fclose(abrirArquivo);
    fclose(arquivoTemp);
    remove("tarefas.txt");
    rename("tarefas_temp.txt", "tarefas.txt");
}

void listarTarefas()
{
    FILE *abrirArquivo = fopen("tarefas.txt", "r");
    if (abrirArquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de tarefas.\n");
        return;
    }

    int id = 1;
    char descricao[256];
    int prioridade;
    int situacao;

    printf("\nLista de tarefas:\n");
    while (fscanf(abrirArquivo, "%255[^,], %d, %d\n", descricao, &prioridade, &situacao) != EOF)
    {
        printf("ID: %d | Descrição: %s | Prioridade: %d | Situação: %s\n", id, descricao, prioridade, situacao ? "Concluída" : "Pendente");
        id++;
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

    int id = 1;
    char descricao[256];
    int prioridade;
    int situacao;

    printf("\nLista de tarefas pendentes:\n");
    while (fscanf(abrirArquivo, "%255[^,], %d, %d\n", descricao, &prioridade, &situacao) != EOF)
    {
        if (situacao == 0)
        {
            printf("ID: %d | Descrição: %s | Prioridade: %d | Situação: %s\n", id, descricao, prioridade, situacao ? "Concluída" : "Pendente");
        }
        id++;
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

    int id = 1;
    char descricao[256];
    int prioridade;
    int situacao;

    printf("\nLista de tarefas concluídas:\n");
    while (fscanf(abrirArquivo, "%255[^,], %d, %d\n", descricao, &prioridade, &situacao) != EOF)
    {
        if (situacao == 1)
        {
            printf("ID: %d | Descrição: %s | Prioridade: %d | Situação: %s\n", id, descricao, prioridade, situacao ? "Concluída" : "Pendente");
        }
        id++;
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
        printf("2. Marcar tarefas como concluidas\n");
        printf("3. Apagar Tarefas\n");
        printf("4. Editar tarefa\n");
        printf("5. Listar tarefas\n");
        printf("6. Listar tarefas pendentes\n");
        printf("7. Listar tarefas concluídas\n");
        printf("0. Sair\n");

        do
        {
            printf("Digite sua opção: ");
            scanf("%d", &opcao);
            getchar();
            if (opcao < 0 || opcao > 7)
            {
                printf("Opção inválida. Por favor, digite um número entre 0 e 7.\n");
            }
        } while (opcao < 0 || opcao > 7);

        switch (opcao)
        {
        case 1:
            system("clear");
            printf("\nAdicionar tarefa selecionado.\n");
            adicionarTarefa();
            break;

        case 2:
            system("clear");
            printf("\nMarcar tarefas como concluidas selecionado.\n");
            marcarTarefaConcluida();
            break;

        case 3:
            system("clear");
            printf("\nApagar Tarefas selecionado.\n");
            apagarTarefa();
            break;

        case 4:
            system("clear");
            printf("\nEditar tarefa selecionado.\n");
            editarTarefa();
            break;

        case 5:
            system("clear");
            printf("\nListar tarefas selecionado.\n");
            listarTarefas();
            break;

        case 6:
            system("clear");
            printf("\nListar tarefas pendentes selecionado.\n");
            listarTarefasPendentes();
            break;

        case 7:
            system("clear");
            printf("\nListar tarefas concluídas selecionado.\n");
            listarTarefasConcluidas();
            break;

        case 0:
            printf("Saindo do programa. Até logo!\n");
            exit(0);
        }
    }

    return 0;
}