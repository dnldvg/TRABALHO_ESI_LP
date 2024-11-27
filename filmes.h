// Sistema de Cadastro de Filmes
//
// Created by Daniel R., Filipe L. e Julia M. on 28/10/2024.

#ifndef FILMES_H
#define FILMES_H

// Struct com os dados dos filmes
typedef struct {
    char titulo[100];  // Título do filme
    char diretor[100];  // Nome do diretor
    int ano;  // Ano de lançamento
    int id;  // ID do filme (4 dígitos)
} Cadastro;

// Cadastrar novo filme e registrar no arquivo
void cadastrar(const char *caminhoArquivo, Cadastro *filme);

// Verificar se existem duplicatas de ID
int idExiste(const char *caminhoArquivo, int id);

// Obter a ID que será removida do arquivo
void obterIDRemover(char *idParaRemover);

// Remover filme baseado na ID fornecida
void remover(const char *nomeArquivo, const char *idRemover);

// Exibir todos os filmes cadastrados (a implementar)
void exibir(const char *nomeArquivo);

//Procurar um filme
void procurar(const char *nomeArquivo);

//Funçao utilizada dentro de procurar
char *strcasestr(const char *haystack, const char *needle);

#endif // FILMES_H
