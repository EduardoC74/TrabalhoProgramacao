// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
//Trabalho realizado por:
//Eduardo Correia - 2020139576

#ifndef TPPROG_H_INCLUDED
#define TPPROG_H_INCLUDED

typedef struct jogador Jogador;

struct jogador{
    char nome[50];
    int linhas_colunas;
    int pedras;
};

typedef struct lista
{
    char **jogos;
    int linhasjogos;
    int colunasjogos;
    int jogada;
    int linha;
    int coluna;
    struct lista* prox;
} Lista;

char** Cria_matriz_dinamica(char **v, int l, int c);
char **Aumenta_Linha(char **v, int* l, int c);
char **Aumenta_Coluna(char **v, int l, int *c);
void mostra_tabuleiro(char **jogo, int l, int c);
int caractereValido(char letra);
int coordenadaValida(int l, int c, int linhas, int colunas);
int posicaoValida(char** jogo, int l, int c);
int posicaoVazia(char** jogo, int l, int c);
void escreveJogo(char** jogo, int l, int c);
int ganhouLinhas(char **jogo, int linhas, int colunas);
int ganhouColunas(char **jogo, int linhas, int colunas);
int ganhouDiagonalPrincipal(char **jogo, int linhas);
int ganhouDiagonalSecundaria(char **jogo, int linhas);
int ganhouTudo(char** jogo, int linhas, int colunas);
void mostraGanhou(char **jogo, Jogador jogador[2], int linhas, int colunas, int jogadas, int ganhou);
void mostraGanhouBot(char **jogo, int linhas, int colunas, int jogadas, int ganhou);
char turnoJogador(int jogadas);
void apagaLista(Lista *tabuleiro);
void jogar(char **jogo, int linhas, int colunas, int *jogadas, int *jogou, int *l, int *c);
void jogarBot(char **jogo, int linhas, int colunas, int *jogadas, int *jogou, int *l, int *c);
void adiciona_pedras(char** jogo, Jogador jogador[2], int linhas, int colunas, int *jogadas, int *jogou, int *l, int *c);
void adiciona_pedrasBot(char** jogo, Jogador jogador[2], int linhas, int colunas, int *jogadas, int *jogou, int *l, int *c);
int Aumentar_Linha_Coluna(Jogador jogador[2], int *jogadas, int *jogou);
int Aumentar_Linha_ColunaBot(Jogador jogador[2], int *jogadas, int *jogou);
Lista* guardaDados(Lista* aux, char **jogo, int linhas, int colunas, int l, int c, int opcao);
void mostraJogadasAnteriores(Lista* tabuleiro, Lista* aux,  int n, int jogadas);
void ficheiroTexto(Lista* tabuleiro, Lista* aux, int *turno);
void ficheirobinario(Lista* tabuleiro, Lista* aux);
void libertaJogo(char **jogo, int linhas);
int menu();
void jogoNormal();
void jogoBot();
void manual();

#endif // TPPROG_H_INCLUDED


