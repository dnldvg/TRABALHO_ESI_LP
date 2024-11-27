#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "filmes.h"

// Funcao para verificar se uma ID ja existe no arquivo
// Verifica se um ID já existe no arquivo especificado. Retorna 1 se encontrado, caso contrário, 0.
int idExiste(const char *caminhoArquivo, int id) {


    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo: %s", caminhoArquivo);
        return 0;
    }

    char linha[256];
    char idStr[5];
    sprintf(idStr, "%04d", id);  // Converte ID para string de 4 digitos

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strstr(linha, idStr) != NULL) {
            fclose(arquivo);
            return 1;  // ID ja existe
        }
    }

    fclose(arquivo);
    return 0;  // ID nao encontrada
}

// Funcao para cadastrar um novo filme
// Registra um novo filme no sistema, solicitando dados do usuário e gravando no arquivo.
void cadastrar(const char *caminhoArquivo, Cadastro *filme) {


    printf("Digite o titulo do filme: ");
    fgets(filme->titulo, sizeof(filme->titulo), stdin);
    filme->titulo[strcspn(filme->titulo, "\n")] = '\0';  // Remove o \n extra

    printf("Digite o diretor do filme: ");
    fgets(filme->diretor, sizeof(filme->diretor), stdin);
    filme->diretor[strcspn(filme->diretor, "\n")] = '\0';

    printf("Digite o ano de lancamento (4 digitos): ");
    scanf("%d", &filme->ano);
    getchar();  // Limpa o buffer de entrada

    printf("Digite a ID do filme no sistema (4 digitos): ");
    scanf("%d", &filme->id);
    getchar();  // Limpa o buffer de entrada

    // Verifica se a ID ja existe no arquivo
    if (idExiste(caminhoArquivo, filme->id)) {
        printf("Erro: ID ja existe no sistema.\n");
        return;
    }

    // Abre o arquivo no modo de adicao
    FILE *fp = fopen(caminhoArquivo, "a");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escreve os dados no formato esperado no arquivo
    fprintf(fp, "ID: %04d; Titulo: %s; Diretor/a: %s; Ano de lancamento: %04d\n",
            filme->id, filme->titulo, filme->diretor, filme->ano);
    fclose(fp);

    printf("Filme cadastrado com sucesso!\n");
}
//Funcao que armazena o ID que vai ser removido
void obterIDRemover(char *idParaRemover) {
    printf("Digite o ID do filme que deseja remover: ");
    fgets(idParaRemover, 5, stdin);
    idParaRemover[strcspn(idParaRemover, "\n")] = '\0';
}
// Remove um registro de filme do arquivo com base no ID fornecido e obtido pela funcao obterIDRemover
void remover(const char *caminhoArquivo, const char *idParaRemover) {


    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar o arquivo temporario.\n");
        fclose(arquivo);
        return;
    }

    char linha[256];
    int removido = 0;
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strstr(linha, idParaRemover) == NULL) {
            fputs(linha, temp);
        } else {
            removido = 1;
        }
    }
    fclose(arquivo);
    fclose(temp);

    remove(caminhoArquivo);
    rename("temp.txt", caminhoArquivo);

    if (removido) {
        printf("Filme removido com sucesso.\n");
    } else {
        printf("ID nao encontrada.\n");
    }
}
// Funcao para exibir todos os filmes cadastrados
void exibir(const char *caminhoArquivo) {

    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.");
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }

    fclose(arquivo);
}

// Funcao para converter string para minusculas (auxiliar)
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Busca um filme com base em critérios como ID, título, diretor ou ano de lançamento.
void procurar(const char *caminhoArquivo) {
    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    int opcao;
    char termo[100];

    // Menu para selecionar o critério de busca
    printf("Escolha um critério de busca:\n");
    printf("1 - ID\n2 - Titulo\n3 - Diretor/a\n4 - Ano de lancamento\n");
    printf("Digite a opcao: ");
    scanf("%d", &opcao);
    getchar(); // Limpa o buffer de entrada

    // Solicita o termo de busca
    printf("Digite o termo de busca: ");
    fgets(termo, sizeof(termo), stdin);
    termo[strcspn(termo, "\n")] = '\0'; // Remove o '\n' do final

    // Converte o termo para minúsculas, caso seja texto, usando a funçao toLowerCase
    if (opcao == 2 || opcao == 3) {
        toLowerCase(termo);
    }

    char linha[256];
    int encontrado = 0;

    // Processa cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Variáveis para capturar os campos
        char id[10] = "", titulo[100] = "", diretor[100] = "", ano[10] = "";

        // Analisar a linha e separar os campos
        int camposLidos = sscanf(linha, "ID: %9[^;]; Titulo: %99[^;]; Diretor/a: %99[^;]; Ano de lancamento: %9s",
                                 id, titulo, diretor, ano);

        if (camposLidos == 4) {
            // Converte apenas os campos relevantes (titulo e diretor) para minúsculas
            if (opcao == 2) {
                toLowerCase(titulo);
            } else if (opcao == 3) {
                toLowerCase(diretor);
            }

            // Realiza a comparação com base na opção escolhida
            if ((opcao == 1 && strstr(id, termo)) ||
                (opcao == 2 && strstr(titulo, termo)) ||
                (opcao == 3 && strstr(diretor, termo)) ||
                (opcao == 4 && strstr(ano, termo))) {
                printf("%s", linha); // Exibe apenas a linha correspondente
                encontrado = 1;
            }
        }
    }

    // Caso nenhum filme seja encontrado
    if (!encontrado) {
        printf("Nenhum filme encontrado com o termo '%s'.\n", termo);
    }

    fclose(arquivo);
}
