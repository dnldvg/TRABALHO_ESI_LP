# TRABALHO_ESI_LP

# Guia do Usuário // leiame

## “CATÁLOGO DE FILMES”
Sistema de Cadastro e Busca de Filmes

### Daniel R. Dovigo, Filipe Leão Santos e Júlia Marques

## a.	Descrição Geral
Este programa é uma aplicação simples para gerenciar informações sobre films, Ele permite cadastrar novos filmes, buscar por critérios específicos (ID, título, director/a, ano de lançamento), remover filmes existentes e listar todos os filmes cadastrados. As informações dos filmes são armazenadas em um arquivo de texto e podem ser acessadas a qualquer momento.
## b.	Requisitos
1. Sistema operacional compatível (Windows ou Linux).
2. Compilador C com suporte à biblioteca padrão (`stdio.h`, `string.h`, etc.).
3. Arquivo `filmes.txt` para armazenar os registros (o programa cria automaticamente se não existir).
4. Configuração de idioma em português para exibir mensagens corretamente.
## c.	Como Executar
1. Compile o programa com seu compilador (ex.: GCC).

 	 `gcc -o gerenciador_filmes main.c filmes.c`

2. Execute o programa:

    `./gerenciador_filmes`
   
## d.	Menu Principal
Ao iniciar o programa, o seguinte menu será exibido:

```
========================
      MENU DE OPCOES     
========================
1. Cadastrar um novo filme
2. Remover um filme
3. Exibir todos os filmes
4. Procurar um filme
5. Sair
========================
Escolha uma operacao:
```

## e.	Funcionalidades

### 1. Cadastrar um Novo Filme
1. Digite `1` no menu principal para acessar o cadastro.
2. Insira os dados solicitados:
   - Título do Filme: Ex.: *O Poderoso Chefão*.
   - Diretor/a: Ex.: *Francis Ford Coppola*.
   - Ano de Lançamento: Ex.: *1972*.
   - ID do Filme (4 dígitos): Ex.: *0001*.
3. Se a ID já existir, o programa exibirá uma mensagem de erro:
   “Erro: ID já existe no Sistema.”
4. Caso contrário, o filme será cadastrado com sucesso e a seguinte mensagem será exibida:
   “Filme cadastrado com sucesso!”
5. O programa retornará para o menu de opções.
   
### 2. Remover um Filme
1. Digite `2` no menu principal.
2. Insira a ID do filme que deseja remover (4 dígitos).
   Ex.: Para remover *O Poderoso Chefão*, digite: `0001`.
3. O programa confirmará se o filme foi removido e a seguinte mensagem será exibida:
   “Filme removido com sucesso.”
4. Se a ID não for encontrada, será exibida a mensagem:
   “ID não encontrada.”
5. O programa retornará para o menu de opções.
### 3. Exibir Todos os Filmes
1. Digite `3` no menu principal.
2. O programa exibirá todos os filmes cadastrados no seguinte formato:
   ID: 0001; Título: O Poderoso Chefão; Diretor/a: Francis Ford Coppola; Ano de lançamento: 1972
3. O programa retornará para o menu de opções.

### 4. Procurar um Filme
1. Digite `4` no menu principal.
2. Escolha um critério de busca:
   1 - ID
   2 - Título
   3 - Diretor/a
   4 - Ano de lançamento
3. Insira o termo de busca:
   - ID: Ex.: `0002`.
   - Título: Ex.: `Matrix`.
   - Diretor/a: Ex.: `Francis`.
   - Ano de Lançamento: Ex.: `1999`.
4. O programa exibirá os filmes que correspondem ao critério, ou:
   Nenhum filme encontrado com o termo '...'.
5. O programa retornará para o menu de opções.

### 5. Sair
1. Digite `5` no menu principal para encerrar o programa.
   
## f.	Formato do Arquivo `filmes.txt`
O arquivo que armazena os filmes segue o formato:
ID: 0001; Título: O Poderoso Chefão; Diretor/a: Francis Ford Coppola; Ano de lançamento: 1972
## g.	Mensagens de Erro Comuns
1. **Erro ao abrir o arquivo**: Certifique-se de que o programa tem permissão para acessar o arquivo `filmes.txt`.
2. **Erro: ID já existe no sistema**: A ID inserida já está cadastrada.
3. **Nenhum filme encontrado**: O termo de busca não corresponde a nenhum filme no arquivo.
## h.	Dicas
1. Para uma melhor experiência, mantenha o arquivo `filmes.txt` em UTF-8 e sem linhas em branco ou inconsistências no formato.
2. Use IDs únicas para cada filme.
