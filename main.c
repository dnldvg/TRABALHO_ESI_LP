#include <stdio.h>
#include <locale.h>
#include "filmes.h"

int main(void) {
    setlocale(LC_ALL, "Portuguese");

    int op = 0;
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
            case 1:
                Cadastro filme;
            cadastrar(nomeArquivo, &filme);
            break;
            case 2:
                obterIDRemover(idParaRemover); // Obtém a ID para remover
            remover(nomeArquivo, idParaRemover); // Remove o filme
            break;
            case 3:
                exibir(nomeArquivo);
            break;
            case 4:
                procurar(nomeArquivo);
            break;
            case 5:
                printf("Saindo\n");
            break;
            default:
                printf("Opcao invalida! Por favor, escolha uma operação valida.\n");
            break;
        }
    } while (op != 5);

    return 0;
}