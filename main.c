#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*
 * Estrutura que representa uma tarefa.
 * Armazena a descrição da tarefa, sua prioridade numérica e a situação atual
 * (por exemplo, 0 para pendente e 1 para concluída).
 */
struct task
{
    char descricao[256];
    int prioridade;
    int situacao;
};

/*
 * Função para adicionar uma nova tarefa.
 * Abre o arquivo em modo "a" (append) para adicionar o registro ao final do arquivo,
 * mantendo as tarefas que já existem.
 */
void adicionarTarefa()
{
    FILE *arquivo = fopen("tarefas.txt", "a");

    struct task novaTarefa;

    /*
     * Loop para garantir que a descrição fornecida não seja vazia e não exceda o limite.
     * Utiliza fgets para capturar a string inteira, incluindo espaços, e strcspn para
     * remover o caractere de nova linha ('\n') gerado pelo teclado.
     */
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

    /*
     * Loop de validação para a prioridade (1 a 5).
     *Uusa o getchar() para limpa o buffer do teclado.
     */
    do
    {
        printf("Digite a prioridade da tarefa de (1 - mais alta a 5 - mais baixa): ");
        scanf("%d", &novaTarefa.prioridade);
        if (novaTarefa.prioridade < 1 || novaTarefa.prioridade > 5)
        {
            printf("Prioridade inválida. Por favor, digite um valor entre 1 e 5.\n");
        }
        getchar();

    } while (novaTarefa.prioridade < 1 || novaTarefa.prioridade > 5);

    // Por padrão, toda nova tarefa é inicializada como pendente (0).
    novaTarefa.situacao = 0;

    // Grava a tarefa formatada no arquivo, separando os campos por vírgula.
    fprintf(arquivo, "%s, %d, %d\n", novaTarefa.descricao, novaTarefa.prioridade, novaTarefa.situacao);
    fclose(arquivo);
    printf("Tarefa adicionada com sucesso!\n");
}

/*
 * Função para alterar a situação de uma tarefa para concluída.
 * Funciona lendo o arquivo original e recriando as informações em um arquivo temporário.
 * A tarefa desejada é modificada nesse processo.
 */
void marcarTarefaConcluida()
{
    FILE *abrirArquivo = fopen("tarefas.txt", "r");
    if (abrirArquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de tarefas.\n");
        return;
    }
    
    // Arquivo temporário onde os dados atualizados serão escritos.
    FILE *arquivoTemp = fopen("tarefas_temp.txt", "w");

    int id = 1;
    char situacao_temp[2];
    struct task tarefaEditar;

    printf("\ntarefas:\n");
    /*
     * Lê linha a linha verificando o formato predefinido: [descrição], [prioridade], [situação].
     * Exibe o ID (gerado dinamicamente na leitura) para o usuário identificar a tarefa.
     */
    while (fscanf(abrirArquivo, "%255[^,], %d, %d\n", tarefaEditar.descricao, &tarefaEditar.prioridade, &tarefaEditar.situacao) != EOF)
    {
        printf("ID: %d | Descrição: %s | Prioridade: %d | Situação: %s\n", id, tarefaEditar.descricao, tarefaEditar.prioridade, tarefaEditar.situacao ? "Concluída" : "Pendente");
        id++;
    }

    // Retorna o ponteiro de leitura para o ínicio do arquivo original.
    rewind(abrirArquivo);
    int idEdicao;

    /* Solicita o ID da tarefa que deve ser marcada como concluída e o valida */
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

    // Reinicia o contador para a re-leitura do arquivo
    id = 1;

    /*
     * Segunda leitura: escreve todas as tarefas no arquivo temporário.
     * Quando identifica o ID especificado pelo usuário, pede a confirmação e altera o valor e salva.
     */
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

            // Salva a tarefa atualizada
            fprintf(arquivoTemp, "%s, %d, %d\n", tarefaEditar.descricao, tarefaEditar.prioridade, tarefaEditar.situacao);
        }
        else
        {
            // Salva as tarefas inalteradas
            fprintf(arquivoTemp, "%s, %d, %d\n", tarefaEditar.descricao, tarefaEditar.prioridade, tarefaEditar.situacao);
        }
        id++;
    }

    // Fecha ambos os arquivos, deleta o original e renomeia o temporário substituindo o anterior.
    fclose(abrirArquivo);
    fclose(arquivoTemp);
    remove("tarefas.txt");
    rename("tarefas_temp.txt", "tarefas.txt");
}

/*
 * Função responsável por apagar uma tarefa.
 * Funciona de forma parecida com a edição e conclusão: recria os dados em um arquivo temporário,
 * mas, neste caso, a tarefa selecionada não é reescrita, o que a remove de fato.
 */
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
    // Listagem inicial para fins de visualização do ID pelo usuário.
    while (fscanf(abrirArquivo, "%255[^,], %d, %d\n", tarefaEditar.descricao, &tarefaEditar.prioridade, &tarefaEditar.situacao) != EOF)
    {
        printf("ID: %d | Descrição: %s | Prioridade: %d | Situação: %s\n", id, tarefaEditar.descricao, tarefaEditar.prioridade, tarefaEditar.situacao ? "Concluída" : "Pendente");
        id++;
    }

    rewind(abrirArquivo);
    int idEdicao;
    char confirmacao[3];

    // Validação do id (garantindo que não selecionem IDs inexistentes).
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

    // Passo de confirmação antes de uma ação destrutiva.
    do
    {
        printf("Tem certeza que deseja apagar a tarefa com ID %d? (y - SIM, n - NÂO): ", idEdicao);
        fgets(confirmacao, sizeof(confirmacao), stdin);
        confirmacao[strcspn(confirmacao, "\n")] = '\0';
        
        if (strcmp(confirmacao, "y") == 0 || strcmp(confirmacao, "Y") == 0)
        {
            break;
        }
        else if (strcmp(confirmacao, "n") == 0 || strcmp(confirmacao, "N") == 0)
        {
            printf("Operação de apagar tarefa cancelada.\n");
            // Caso seja cancelado, fecham-se os arquivos e o temporário é removido.
            fclose(abrirArquivo);
            fclose(arquivoTemp);
            remove("tarefas_temp.txt");
            return;
        }
        else
        {
            printf("Opção inválida. Por favor, digite 'y' para SIM ou 'n' para NÃO.\n");
        }
    } while ((confirmacao[0] != 'y') && (confirmacao[0] != 'Y') && (confirmacao[0] != 'n') && (confirmacao[0] != 'N'));

    id = 1;

    /* Transfere as informações entre arquivos, com exceção da lida no ID a ser apagado. */
    while (fscanf(abrirArquivo, "%255[^,], %d, %d\n", tarefaEditar.descricao, &tarefaEditar.prioridade, &tarefaEditar.situacao) != EOF)
    {   
        if (id != idEdicao)
        {
            fprintf(arquivoTemp, "%s, %d, %d\n", tarefaEditar.descricao, tarefaEditar.prioridade, tarefaEditar.situacao);
        }
        id++;
    }

    // Finaliza as operações nos arquivos deletando o antigo.
    fclose(abrirArquivo);
    fclose(arquivoTemp);
    remove("tarefas.txt");
    rename("tarefas_temp.txt", "tarefas.txt");
}

/*
 * Função para alterar todos os campos de uma tarefa (descrição, prioridade, situação).
 * Novamente utiliza o padrão de ler o arquivo principal e reescrever no arquivo temporário.
 */
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
    // Listagem para escolha do usuário.
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

    // Repassa os registros ao arquivo temporário
    while (fscanf(abrirArquivo, "%255[^,], %d, %d\n", tarefaEditar.descricao, &tarefaEditar.prioridade, &tarefaEditar.situacao) != EOF)
    {
        if (id == idEdicao)
        {
            // Para o ID escolhido, repete o processo de coleta e validação das informações (como na função criar)
            do
            {
                printf("Digite a nova descrição da tarefa: ");
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
                printf("Digite a nova prioridade da tarefa (1-5): ");
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
            // reescreve as tarefas não-editadas
            fprintf(arquivoTemp, "%s, %d, %d\n", tarefaEditar.descricao, tarefaEditar.prioridade, tarefaEditar.situacao);
        }
        id++;
    }

    fclose(abrirArquivo);
    fclose(arquivoTemp);
    remove("tarefas.txt");
    rename("tarefas_temp.txt", "tarefas.txt");
}

/*
 * Função para ler o arquivo de dados e imprimir todos os registros encontrados no console.
 * Aguarda por um retorno (Enter) para retornar ao menu.
 */
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
    // O modificador %255[^,] diz para ler até 255 caracteres ou até encontrar uma vírgula
    while (fscanf(abrirArquivo, "%255[^,], %d, %d\n", descricao, &prioridade, &situacao) != EOF)
    {
        printf("ID: %d | Descrição: %s | Prioridade: %d | Situação: %s\n", id, descricao, prioridade, situacao ? "Concluída" : "Pendente");
        id++;
    }
    fclose(abrirArquivo);

    printf("Aperte enter para fechar: ");
    scanf("%*c"); // O * descarta a entrada absorvendo apenas o enter para fechar a função..
}

/*
 * Variação da função de listar que imprime apenas tarefas cuja situacao for igual a 0.
 */
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
        // Se a situação for '0', exibe a tarefa
        if (situacao == 0)
        {
            printf("ID: %d | Descrição: %s | Prioridade: %d | Situação: %s\n", id, descricao, prioridade, situacao ? "Concluída" : "Pendente");
        }
        id++; // Incrementa independente de situação para manter os IDs consistentes.
    }
    fclose(abrirArquivo);

    printf("Aperte enter para fechar: ");
    scanf("%*c");
}

/*
 * Variação da função de listar que imprime apenas tarefas cuja situacao for igual a 1.
 */
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
        // Se a situação for '1', exibe
        if (situacao == 1)
        {
            printf("ID: %d | Descrição: %s | Prioridade: %d | Situação: %s\n", id, descricao, prioridade, situacao ? "Concluída" : "Pendente");
        }
        id++; // Incrementa para manter os IDs corretos
    }
    fclose(abrirArquivo);

    printf("Aperte enter para fechar: ");
    scanf("%*c");
}

/*
 * A função principal do programa. Organiza um laço de repetição infinito (while(true)) controlando
 * um menu interativo (switch-case) com as ações descritas acima na interface do console.
 */
int main()
{
    int opcao;

    while (true)
    {
        // system("clear") é usado para limpar a janela do terminal e melhorar a visibilidade.
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

        // Loop de validação de opções até o usuário digitar um número correto.
        do
        {
            printf("Digite sua opção: ");
            scanf("%d", &opcao);
            getchar(); // Absorve o "enter" gerado.
            if (opcao < 0 || opcao > 7)
            {
                printf("Opção inválida. Por favor, digite um número entre 0 e 7.\n");
            }
        } while (opcao < 0 || opcao > 7);

        // Desvia a execução para a funcionalidade correspondente com base no valor de opção informado.
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
            // Interrompe a execução do programa e retorna código 0.
            exit(0);
        }
    }

    return 0;
}
