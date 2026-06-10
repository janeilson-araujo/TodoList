#include <stdio.h>

int main()
{
    printf("+--------------------------------------+\n");
    printf("|              TODO LIST               |\n");
    printf("|        Organize suas tarefas         |\n");
    printf("+--------------------------------------+\n");

    int opcao;

    do {
        scanf("%d", &opcao);
    } while (opcao != 0);

    return 0;
}