#include <stdio.h>
#include <locale.h>
#include "filmes.h"

int main(void) {
    // Função principal que fornece uma interface de menu para gerenciar registros de filmes.

    setlocale(LC_ALL, "Portuguese");

    int op = 0;
    char filme;
    const char *nomeArquivo = "c:\\Temp\\filmes.txt";
    char idParaRemover[5];

    do {
        printf("\n========================\n");
        printf("     MENU DE OPCOES     \n");
        printf("========================\n");
        printf("1. Cadastrar um novo filme\n");
        printf("2. Remover um filme\n");
        printf("3. Exibir todos os filmes\n");
        printf("4. Procurar um filme\n");
        printf("5. Sair\n");
        printf("========================\n");
        printf("Escolha uma operacao: ");
        scanf("%d", &op);
        getchar();

        switch(op) {
            // Gerencia a adição de novos registros de filmes.
            case 1:
                //Cadastro filme;
            cadastrar(nomeArquivo, &filme);
            break;
            // Gerencia a remoção de registros de filmes com base no ID.
            case 2:
                obterIDRemover(idParaRemover); // Obtem a ID para remover
            remover(nomeArquivo, idParaRemover); // Remove o filme
            break;
            // Exibe todos os registros de filmes armazenados no sistema.
            case 3:
                exibir(nomeArquivo);
            break;
            // Realiza buscas por filmes com base em critérios especificados pelo usuário.
            case 4:
                procurar(nomeArquivo);
            break;
            // Encerra o programa.
            case 5:
                printf("Saindo\n");
            break;
            default:
                printf("Opcao invalida! Por favor, escolha uma operacao valida.\n");
            break;
        }
    } while (op != 5);

    return 0;
}
