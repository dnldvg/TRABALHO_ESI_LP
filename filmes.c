#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "filmes.h"

// Função para verificar se uma ID já existe no arquivo
int idExiste(const char *caminhoArquivo, int id) {
    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo: %s", caminhoArquivo);
        return 0;
    }

    char linha[256];
    char idStr[5];
    sprintf(idStr, "%04d", id);  // Converte ID para string de 4 dígitos

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strstr(linha, idStr) != NULL) {
            fclose(arquivo);
            return 1;  // ID já existe
        }
    }

    fclose(arquivo);
    return 0;  // ID não encontrada
}

// Função para cadastrar um novo filme
void cadastrar(const char *caminhoArquivo, Cadastro *filme) {
    printf("Digite o título do filme: ");
    fgets(filme->titulo, sizeof(filme->titulo), stdin);
    filme->titulo[strcspn(filme->titulo, "\n")] = '\0';  // Remove o \n extra

    printf("Digite o diretor do filme: ");
    fgets(filme->diretor, sizeof(filme->diretor), stdin);
    filme->diretor[strcspn(filme->diretor, "\n")] = '\0';

    printf("Digite o ano de lançamento (4 dígitos): ");
    scanf("%d", &filme->ano);
    getchar();  // Limpa o buffer de entrada

    printf("Digite a ID do filme no sistema (4 dígitos): ");
    scanf("%d", &filme->id);
    getchar();  // Limpa o buffer de entrada

    // Verifica se a ID já existe no arquivo
    if (idExiste(caminhoArquivo, filme->id)) {
        printf("Erro: ID já existe no sistema.\n");
        return;
    }

    // Abre o arquivo no modo de adição
    FILE *fp = fopen(caminhoArquivo, "a");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escreve os dados no formato esperado no arquivo
    fprintf(fp, "ID: %04d; Título: %s; Diretor/a: %s; Ano de lançamento: %04d\n",
            filme->id, filme->titulo, filme->diretor, filme->ano);
    fclose(fp);

    printf("Filme cadastrado com sucesso!\n");
}

void obterIDRemover(char *idParaRemover) {
    printf("Digite o ID do filme que deseja remover: ");
    fgets(idParaRemover, 5, stdin);
    idParaRemover[strcspn(idParaRemover, "\n")] = '\0';
}

// Função de remoção
void remover(const char *caminhoArquivo, const char *idParaRemover) {
    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
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
        printf("ID não encontrada.\n");
    }
}
// Função para exibir todos os filmes cadastrados
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

// Função para procurar um filme por título, diretor, ano ou ID

// Função para converter string para minúsculas (auxiliar)
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

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
    printf("1 - ID\n2 - Título\n3 - Diretor/a\n4 - Ano de lançamento\n");
    printf("Digite a opção: ");
    scanf("%d", &opcao);
    getchar(); // Limpa o buffer de entrada

    // Solicita o termo de busca
    printf("Digite o termo de busca: ");
    fgets(termo, sizeof(termo), stdin);
    termo[strcspn(termo, "\n")] = '\0'; // Remove o '\n' do final

    char linha[256];
    int encontrado = 0;

    // Processa cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Variáveis para capturar os campos
        char id[10] = "", titulo[100] = "", diretor[100] = "", ano[10] = "";

        // Analisar a linha e separar os campos
        int camposLidos = sscanf(linha, "ID: %9[^;]; Título: %99[^;]; Diretor/a: %99[^;]; Ano de lançamento: %9s",
                                 id, titulo, diretor, ano);

        if (camposLidos == 4) {
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