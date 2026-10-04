# TodoList em C

Uma aplicação de linha de comando para gerenciar tarefas pessoais em linguagem C. O programa permite adicionar, editar, excluir, listar e marcar tarefas como concluídas, mantendo os dados em um arquivo local para persistência entre execuções.

## Funcionalidades

- Adicionar nova tarefa
- Editar uma tarefa existente
- Excluir uma tarefa
- Marcar tarefa como concluída
- Listar todas as tarefas
- Listar apenas tarefas pendentes
- Listar apenas tarefas concluídas
- Persistência dos dados em arquivo `tarefas.txt`

## Estrutura do projeto

- `main.c`: contém toda a lógica da aplicação e o menu interativo
- `README.md`: documentação do projeto
- `tarefas.txt`: arquivo gerado em execução para armazenar as tarefas

## Como compilar

No terminal, execute:

```bash
gcc main.c -o todo
```

## Como executar

```bash
./todo
```

## Menu do programa

Ao iniciar, o programa exibe um menu com as opções:

1. Adicionar tarefa
2. Marcar tarefas como concluídas
3. Apagar tarefas
4. Editar tarefa
5. Listar tarefas
6. Listar tarefas pendentes
7. Listar tarefas concluídas
0. Sair

## Formato das tarefas salvas

Cada tarefa é salva no arquivo `tarefas.txt` no formato:

```text
descrição, prioridade, situação
```

Exemplo:

```text
Estudar para a prova, 2, 0
Comprar leite, 3, 1
```

Onde:

- `0` = pendente
- `1` = concluída
- `prioridade` varia de 1 a 5, sendo 1 a mais alta e 5 a mais baixa

## Observações

- O programa foi desenvolvido para ambientes Unix/Linux/macOS, já que utiliza `system("clear")` para limpar a tela.
- Em sistemas Windows, pode ser necessário trocar `clear` por `cls`.
- As tarefas são armazenadas em um arquivo local no diretório do projeto.

## Autor

Projeto desenvolvido em C como ferramenta de organização de tarefas e estudo de manipulação de arquivos em linguagem C.
