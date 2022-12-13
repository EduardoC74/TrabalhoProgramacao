// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
//Trabalho realizado por:
//Eduardo Correia - 2020139576

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#include "tpPROG.h"
#include "utils.h"

//Esta função serve para criar o tabuleiro, que é uma estrutura dinâmica
char** Cria_matriz_dinamica(char **v, int l, int c)
{
    v = malloc(sizeof(char*) * l);

    if(v == NULL)
    {
        printf("Erro na alocacao de memoria");
        return NULL; //se numa função que retorna um ponteiro deve retornar NULL
    }

    for (int i = 0; i < l; i++)
    {
        v[i] = malloc(sizeof(char) * c);
        if(v[i] == NULL)
        {
            printf("Erro na alocacao de memoria");
            return NULL;
        }

        for (int j = 0; j < c; j++)
        {
            v[i][j] = ' ';
        }

    }
    return v;
}

//Função que adiciona uma linha ao fim da estrutura dinâmica
char** Aumenta_Linha(char **v, int* l, int c)
{
    int j;
    (*l)++;

    v = realloc(v, sizeof(char *) * (*l));
    if(v == NULL) {
        printf("Erro na alocacao de memoria");
        return NULL;
    }


    //for(int i = l - 1; i < l; i++)
    //{
       v[(*l) - 1] = NULL;
       v[(*l) - 1] = realloc(v[(*l) - 1], sizeof(char) * c);

  //   v[(*l)-1]= malloc(c * sizeof(char));

        if(v[(*l) - 1] == NULL) {
            printf("Erro na alocacao de memoria");
            return NULL; //se for uma função que devolve um ponteiro deve fazer return NULL
        }

        //v[(*l)-1]=auxc;
    //}


    //Escrita dos caracteres na nova linha
    for (j = 0; j < c; j++)
            v[(*l) - 1][j] = ' ';

  return v;
}

//Função que adiciona uma coluna no fim de cada linha da estrutura dinâmica
char **Aumenta_Coluna(char **v, int l, int *c)
{
    (*c)++;

    for(int i = 0; i < l; i++)
    {
        v[i] = realloc(v[i], sizeof(char) * (*c));

        if(v[i] == NULL)
        {
            printf("Erro na alocacao de memoria");
            return NULL;
        }
    }
    //Atualiza a nova coluna com o caracter
    for (int i = 0; i < l; i++)
        v[i][(*c) - 1] = ' ';

    return v;
}

//Esta função mostra o tabuleiro na consola
void mostra_tabuleiro(char **jogo, int l, int c)
{
    int i,j;

    for(i=0; i<((4*c)+12)/2; i++) //impresao dos x antes do tabuleiro
        printf("x ");
    printf("\n");

    printf("X      C0 "); //9
    for(i=1; i<c; i++)            //impressao das colunas
    {
        printf(" C%d ",i);//4*c
    }
    printf("    X");//+3

    printf("\n");
    printf("X     ");
    for(i=0; i<(4*c)+1; i++)
        printf("-");
    printf("   X");
    printf("\n");

    for(i=0; i<l; i++)
    {
        printf("X ");

        for(j=0; j<c; j++)
        {
            if(j==0)
                printf(" L%d ",i);
            printf("| %c ",jogo[i][j]);
        }

        printf("|");
        printf("   X");

        printf("\n");
        printf("X     ");
        for(int h=0; h<(4*c)+1; h++)
            printf("-");
        printf("   X");
        printf("\n");
    }
    for(i=0; i<((4*c)+12)/2; i++)
        printf("x ");
    printf("\n");
}


//Função que verifica se o caracter numa determinada posição do tabuleiro é ‘G’ ou ‘Y’ ou ‘R’,
// ou seja os caracteres possiveis para a condição de vitória
int caractereValido(char letra)
{
    if(letra=='G' || letra=='Y' || letra=='R')
        return 1;
    else
        return 0;
}

//Função que verifica se a posição que o jogador inseriu pertence ao tabuleiro
int coordenadaValida(int l, int c, int linhas, int colunas)
{
    if(l>=0 && l<linhas)
    {
        if(c>=0 && c<colunas)
            return 1;
    }
    return 0;
}

//Função que verifica se o caracter numa determinada posição do tabuleiro é ‘ ’ ou ‘ G’ ou ‘Y’,
// ou seja que ainda é permitido jogar na mesma
int posicaoValida(char** jogo, int l, int c)
{
    if(jogo[l][c]==' ' || jogo[l][c]=='G' || jogo[l][c]=='Y')
        return 1;
    return 0;
}

//Função que verifica se determinada posição do tabuleiro escolhida pelo jogador está vazia
int posicaoVazia(char** jogo, int l, int c)
{
    if(jogo[l][c]==' ')
        return 1;
    else
        return 0;
}

//Função que escreve o jogo, ou seja que dependendo das corrdenadas do jogador se nessa posição tiver um ‘ ‘
//coloca um ‘G’, se tiver um ‘G’ coloca um ‘Y’ e se tiver um ‘Y’ coloca um ‘R’
void escreveJogo(char** jogo, int l, int c)
{
    if(jogo[l][c]==' ')
        jogo[l][c]='G';
    else if(jogo[l][c]=='G')
        jogo[l][c]='Y';
    else
        jogo[l][c]='R';
}

//Função que verifica se algum jogador venceu por linha
int ganhouLinhas(char **jogo, int linhas, int colunas)
{
    int igual=1;

    for(int i =0; i<linhas; i++)
    {
        for(int j=0; j<colunas-1; j++)
        {
            if(caractereValido(jogo[i][j]) && jogo[i][j]==jogo[i][j+1])
                igual++;
        }
        if(igual==colunas)
            return 1;
        igual=1;
    }
    return 0;
}

//Função que verifica se algum jogador venceu por coluna
int ganhouColunas(char **jogo, int linhas, int colunas)
{
    int igual=1;

    for(int i=0; i<colunas; i++)
    {
        for(int j=0; j<linhas-1; j++)
        {
            if(caractereValido(jogo[j][i]) && jogo[j][i]==jogo[j+1][i])
                igual++;
        }
        if(igual==linhas)
            return 1;
        igual=1;
    }
    return 0;
}

//Função que verifica se algum jogador venceu pela diagonal principal
int ganhouDiagonalPrincipal(char **jogo, int linhas)
{
    int igual=1;

    for(int i=0; i<linhas-1; i++)
    {
        if(caractereValido(jogo[i][i]) && jogo[i][i]==jogo[i+1][i+1])
            igual++;
    }
    if(igual==linhas)
        return 1;
    else
        return 0;
}

//Função que verifica se algum jogador venceu pela diagonal secundária
int ganhouDiagonalSecundaria(char **jogo, int linhas)
{
    int igual=1;

    for(int i=0; i<linhas-1; i++)
    {
        if(caractereValido(jogo[i][linhas-1-i]) && jogo[i][linhas-1-i]==jogo[i+1][linhas-2-i])
            igual++;
    }
    if(igual==linhas)
        return 1;
    else
        return 0;
}

//Função que junta o ganhouLinhas, o ganhouColunas, o ganhouDiagonalPrincipal e o ganhouDiagonalSecundaria numa só
int ganhouTudo(char **jogo, int linhas, int colunas)
{
    int ganhou=0;

    ganhou+=ganhouLinhas(jogo, linhas, colunas);
    ganhou+=ganhouColunas(jogo, linhas, colunas);
    if(linhas==colunas)
    {
        ganhou+=ganhouDiagonalPrincipal(jogo, linhas);
        ganhou+=ganhouDiagonalSecundaria(jogo, linhas);
    }
    return ganhou;
}


//Função que mostra na consola qual o jogador que venceu, quando o jogo é efetuado entre duas pessoas
void mostraGanhou(char **jogo, Jogador jogador[2], int linhas, int colunas, int jogadas, int ganhou)
{
    printf("\n");
    mostra_tabuleiro(jogo, linhas, colunas);

    if(jogadas%2!=0)
        printf("\nParabens, voce venceu jogador A(%s)!\n",jogador[0].nome);
    else
        printf("\nParabens, voce venceu jogador B(%s)!\n",jogador[1].nome);
}

//Função que mostra na consola qual o jogador que venceu, quando o jogo é efetuado entre uma pessoa e um bot
void mostraGanhouBot(char **jogo, int linhas, int colunas, int jogadas, int ganhou)
{
    printf("\n");
    mostra_tabuleiro(jogo, linhas, colunas);

    if(jogadas%2!=0)
        printf("\n  Parabens, venceste!\n");
    else
        printf("\n  Perdeste!\n");
}

//Função que verifica se é a vez do jogador A ou B jogar
char turnoJogador(int jogadas)
{
    if(jogadas%2==0)
        return 'A';
    else
        return 'B';
}

//Função que liberta a lista ligada
void apagaLista(Lista *tabuleiro)
{
    Lista *aux=tabuleiro;

    while(tabuleiro!=NULL)
    {
        aux=tabuleiro;
        tabuleiro=tabuleiro->prox;
        free(aux);
    }
}

//Esta função escreve no tabuleiro uma determinda peça consoante as coordenadas inseridas pelo jogador
// e dependendo do que ja estava nessa posição
void jogar(char **jogo, int linhas, int colunas, int *jogadas, int *jogou, int *l, int *c)
{
    int lin,col;

    do
    {
        printf("\nDigite as coordenadas em que deseja jogar:\n");
        printf("Linha: ");
        scanf("%d",&lin);
        fflush(stdin);
        printf("Coluna: ");
        scanf("%d",&col);
        fflush(stdin);
    }
    while(!(coordenadaValida(lin, col, linhas, colunas) && posicaoValida(jogo, lin, col)));
    escreveJogo(jogo, lin, col);
    (*jogadas)++;
    (*jogou)=1;

    *l=lin;
    *c=col;
}

//Esta função escreve no tabuleiro uma determinda peça consoante as coordenadas inseridas pelo bot e dependendo do que ja estava nessa posição
void jogarBot(char **jogo, int linhas, int colunas, int *jogadas, int *jogou, int *l, int *c)
{
    int lin,col;

    do
    {
        lin=intUniformRnd(0,linhas-1);
        col=intUniformRnd(0, colunas-1);
    }while(!(coordenadaValida(lin, col, linhas, colunas) && posicaoValida(jogo, lin, col)));
    escreveJogo(jogo, lin, col);
    (*jogadas)++;
    (*jogou)=1;

    *l=lin;
    *c=col;

    printf("\n");
    printf(" --> Jogada do BOT <--\n");
    printf("\n");
    mostra_tabuleiro(jogo, linhas, colunas);
}

//Esta função verifica se o jogador que a chamou ainda pode adicionar pedras e caso possa, adicona a na posição escolhida
void adiciona_pedras(char** jogo, Jogador jogador[2], int linhas, int colunas, int *jogadas, int *jogou, int *l, int *c)
{
    int i,lin,col;

    i=((*jogadas)%2);
    if(jogador[i].pedras<1)
    {
        do
        {
            printf("\nDigite as coordenadas em que deseja colocar a pedra:\n");
            printf("Linha: ");
            scanf("%d",&lin);
            fflush(stdin);
            printf("Coluna: ");
            scanf("%d",&col);
            fflush(stdin);
        }
        while(!(coordenadaValida(lin, col, linhas, colunas) && posicaoVazia(jogo, lin, col)));
        jogo[lin][col]='S';
        (jogador[i].pedras)++;
        (*jogadas)++;
        (*jogou)=1;

        *l=lin;
        *c=col;
    }
    else
    {
        printf("\nJa nao pode adicionar mais pedras, jogador %d(%s)!\n",i+1,jogador[i].nome);
        (*jogou)=0;
    }
}

//Esta função verifica se o bot que a chamou ainda pode adicionar pedras e caso possa, adicona a na posição escolhida aleatoriamente por esse bot
void adiciona_pedrasBot(char** jogo, Jogador jogador[2], int linhas, int colunas, int *jogadas, int *jogou, int *l, int *c)
{
    int lin, col;

    if(jogador[1].pedras<1)
    {
        do
        {
            lin=intUniformRnd(0,linhas-1);
            col=intUniformRnd(0, colunas-1);
        }
        while(!(coordenadaValida(lin, col, linhas, colunas) && posicaoVazia(jogo, lin, col)));
        jogo[lin][col]='S';
        (jogador[1].pedras)++;
        (*jogadas)++;
        (*jogou)=1;

        *l=lin;
        *c=col;

        printf("\n");
        printf(" --> Jogada do BOT <--\n");
        printf("\n");
        mostra_tabuleiro(jogo, linhas, colunas);
    }
    else
        (*jogou)=0;
}

//Função que verifica se o jogador que a chamou ainda pode adicionar linhas ou colunas e caso possa, adicona
int Aumentar_Linha_Coluna(Jogador jogador[2], int *jogadas, int *jogou)
{
    int i;

    i=((*jogadas)%2);

    if(jogador[i].linhas_colunas<2)
    {
        (jogador[i].linhas_colunas)++;
        (*jogadas)++;
        (*jogou)=1;
        return 1;
    }
    else
    {
        printf("\nJa nao pode adicionar mais linhas/colunas, jogador %d(%s)!\n",i+1,jogador[i].nome);
        (*jogou)=0;
        return 0;
    }
}

//Função que verifica se o bot que a chamou ainda pode adicionar linhas ou colunas e caso possa, adicona
int Aumentar_Linha_ColunaBot(Jogador jogador[2], int *jogadas, int *jogou)
{
    if(jogador[1].linhas_colunas<2)
    {
        (jogador[1].linhas_colunas)++;
        (*jogadas)++;
        (*jogou)=1;
        printf("\n");
        printf(" --> Jogada do BOT <--\n");
        return 1;
    }
    else
    {
        (*jogou)=0;
        return 0;
    }
}

//Função que guarda na lista ligada os seus respetivos estados referentes ao tabuleiro e as suas linhas
// e colunas e em relação a jogada efetuada pelo jogador ou bot numa certa posicao.
Lista* guardaDados(Lista* aux, char**jogo, int linhas, int colunas, int l, int c, int opcao)
{
    char **tab = malloc(sizeof(char*) * linhas);

    if(tab == NULL)
    {
        printf("Erro na alocacao de memoria");
        return NULL;
    }

    for (int i = 0; i < linhas; i++)
    {
        tab[i] = malloc(sizeof(char) * colunas);
        if(tab[i] == NULL)
        {
            printf("Erro na alocacao de memoria");
            return NULL;
        }

        for (int j = 0; j < colunas; j++)
        {
            tab[i][j] = jogo[i][j];
        }
    }

    aux->prox=malloc(sizeof(Lista));
    aux->jogos=tab;
    aux->linhasjogos=linhas;
    aux->colunasjogos=colunas;
    aux->linha=l;
    aux->coluna=c;
    aux->jogada=opcao;
    aux=aux->prox;
    aux->prox=NULL;
    if(aux==NULL)
        exit(0);

    return aux;
}

//Função que recebe do jogador o numero de jogadas que deseja rever e caso seja possivel,
// mostra os respetivos estados do tabuleiro na consola
void mostraJogadasAnteriores(Lista* tabuleiro, Lista* aux,  int n, int jogadas)
{
    int i;

    aux=tabuleiro;

    if(aux==NULL || jogadas==0)
    {
        printf("\nNenhuma jogada efetuada ate ao momento!\n");
        return;
    }

    if(n>jogadas)
    {
        printf("\nN e maior que as jogadas efetuadas ate ao momento!\n");
        return;
    }

    for(i=0; i< jogadas-n; i++)
    {
        aux=aux->prox;
    }

    for(; aux->prox!=NULL; i++)
    {
        if(jogadas-i>=0)
        {
            if(i==jogadas-n)
            {
                printf("\n  --> Ha %d jogada atras <--\n",n);
                mostra_tabuleiro(aux->jogos, aux->linhasjogos, aux->colunasjogos);
            }
            else
            {
                printf("\n  --> Ha %d jogadas atras <--\n",jogadas-i);
                mostra_tabuleiro(aux->jogos, aux->linhasjogos, aux->colunasjogos);
            }
        }
        aux=aux->prox;
    }
}

//Função que escreve num ficheiro de texto a jogada e a linha e coluna em que esta foi efetuada em cada turno
void ficheiroTexto(Lista* tabuleiro, Lista* aux, int *turno)
{
    char nome[25];
    FILE *f;

    aux=tabuleiro;

    printf("\nQual o nome do ficheiro em que deseja guardar o historico de jogadas?   ");
    scanf("%s",nome);
    strcat(nome,".txt");
    f=fopen(nome,"w");
    if(f==NULL)
    {
        printf("Erro: O arquivo texto.txt nao foi aberto\n");
        exit(0);
    }
    fprintf(f,"----------------------------------------------------------\n");
    while(aux->prox!=NULL)
    {
        if(aux->jogada==2)
            fprintf(f,"Na jogada %d foi adicionada uma pedra na linha %d e coluna %d\n",(*turno),aux->linha,aux->coluna);
        else if(aux->jogada==3)
            fprintf(f,"Na %d jogada foi adicionada uma linha\n",(*turno));
        else if(aux->jogada==4)
            fprintf(f,"Na %d jogada foi adicionada uma coluna\n",(*turno));
        else if(aux->jogada==7)
            fprintf(f,"Na %d jogada o jogo foi fechado\n",(*turno));
        else
            fprintf(f,"Na jogada %d foi jogada uma peca na linha %d e coluna %d\n",(*turno),aux->linha,aux->coluna);

        fprintf(f,"----------------------------------------------------------\n");
        (*turno)++;
        aux=aux->prox;
    }
    fclose(f);
}

//Função que escreve num ficheiro binário os diferentes estados da lista ligada
void ficheirobinario(Lista* tabuleiro, Lista* aux)
{
    int cont;
    FILE *b;

    aux=tabuleiro;

    b=fopen("jogo.bin","wb");
    if(b==NULL)
    {
        printf("Erro: O arquivo jogo.bin nao foi aberto\n");
        exit(0);
    }

    while(aux!=NULL)
    {
        cont++;
        aux=aux->prox;
    }
    /*fwrite(&opjogo,sizeof(int),1,b);*/
    fwrite(&cont, sizeof(int),1,b);
    fwrite(aux,sizeof(Lista),cont,b);

    fclose(b);
}

//Função que le o ficheiro binário criado anteriormente
Lista* lebinario(Lista* tabuleiro, Lista* aux)
{
    int conta;
    FILE *b;

    aux=tabuleiro;

    b=fopen("jogo.bin","rb");

    if(b==NULL)
    {
        printf("Erro no acesso ao ficheiro jogo.bin\n");
        return NULL;
    }

    /*fread(&opjogo,sizeof(int),1,b);*/
    fread(&conta,sizeof(int),1,b);
    aux=malloc(sizeof(Lista)*conta);
    if(aux==NULL)
    {
        fclose(b);
        return aux;
    }

    fread(aux,sizeof(Lista),conta,b);

    /*printf("\nDeseja continuar o jogo anterior?\n");
    printf(" 1 - Sim\n");
    printf(" 2 - Nao\n ");
    scanf("%d", &escolha);
    if(escolha==2)
        return NULL;
    else if(escolha==1 && opjogo==1)
         jogoNormal(aux, 1);
    else if(escolha==1 && opjogo==2)
         jogoBot(aux, 1);*/

    fclose(b);
    return aux;
}

//Função que libertao tabuleiro, ou seja a estrutura dinâmica
void libertaJogo(char **jogo, int linhas)
{
    int i;

    //Como libertar a memória
    for(i=0; i<linhas; i++) //Liberto o array de caracteres correspondente a cada linha
    {
        free(jogo[i]);
    }
    free(jogo);//liberto o array de ponteiros
}

//Esta funcao disponibiliza um menu, a escolher a opcao e retorna essa opcao
int menu()
{
    int opcao;

    printf("\n***********OPCOES************");
    printf("\n1 - Colocar uma peca");
    printf("\n2 - Colocar uma pedra");
    printf("\n3 - Adicionar uma linha");
    printf("\n4 - Adicionar uma coluna");
    printf("\n5 - Verificar o estado do tabuleiro nas N jogadas anteriores");
    printf("\n6 - Gravar o jogo");
    printf("\n7 - Sair");
    printf("\n*****************************\n");
    do
    {
        printf("\nEscolha a opcao: ");
        scanf("%d",&opcao);
        fflush(stdin);
    }
    while(opcao<1 || opcao>7);
    printf("------------------\n");

    return opcao;
}

//Esta é uma das funções principais de jogo, que faz o jogo acontecer entre o jogador A e B conforme as suas jogadas
void jogoNormal()
{
    initRandom();

    Jogador jogador[2]= {{"A",0,0},{"B",0,0}};
    /*FILE *g;*/
    char **jogo=NULL;

    int linhas, colunas, opcao, l, c, i, vez, valor, jogadas=0, ganhou=0, jogou=1, turno=1, n;

    linhas=colunas=intUniformRnd(3,5);

    printf(" INICIO DO JOGO\n\n");
    printf("Jogador A digite o seu nome: ");
    scanf(" %49[^\n]", jogador[0].nome);
    printf("Jogador B digite o seu nome: ");
    scanf(" %49[^\n]", jogador[1].nome);

    jogo = Cria_matriz_dinamica(jogo,linhas,colunas);
    Lista *tabuleiro=malloc(sizeof(Lista));
    if(tabuleiro==NULL)
        exit(0);
    Lista *aux=tabuleiro;

    do
    {
        printf("\n  ---TABULEIRO---\n");
        printf("\n");
        mostra_tabuleiro(jogo, linhas, colunas);
        i=jogadas%2;
        vez=turnoJogador(jogadas);
        printf("\n Turno do jogador %c (%s)",vez,jogador[i].nome);
        opcao=menu(&jogadas, jogador);
        switch(opcao)
        {
        case 1:
            jogar(jogo, linhas, colunas, &jogadas, &jogou, &l, &c);
            ganhou=ganhouTudo(jogo, linhas, colunas);
            break;
        case 2:
            adiciona_pedras(jogo, jogador, linhas, colunas, &jogadas, &jogou, &l, &c);
            break;
        case 3:
            valor=Aumentar_Linha_Coluna(jogador, &jogadas, &jogou);
            if(valor==1)
                jogo=Aumenta_Linha(jogo, &linhas, colunas);
            break;
        case 4:
            valor=Aumentar_Linha_Coluna(jogador, &jogadas, &jogou);
            if(valor==1)
                jogo=Aumenta_Coluna(jogo, linhas, &colunas);
            break;
        case 5:
            printf("Quantas jogadas deseja rever? ");
            scanf("%d",&n);
            mostraJogadasAnteriores(tabuleiro, aux,  n, jogadas);
            break;
        case 6:
            ficheirobinario(tabuleiro, aux);
            break;
        case 7:
            jogou=1;
            break;
        }

        if(jogou!=0)
            aux=guardaDados(aux, jogo, linhas, colunas, l, c, opcao);

        if(ganhou==1)
            mostraGanhou(jogo, jogador, linhas, colunas, jogadas, ganhou);

    }while(opcao>=1 && opcao<6 && ganhou==0);

    ficheiroTexto(tabuleiro, aux, &turno);

    apagaLista(tabuleiro);

    libertaJogo(jogo, linhas);

    printf("\n ~~~~~ ACABOU O JOGO ~~~~~\n");
}

//Esta função faz o jogo acontecer entre o jogador e o bot conforme as suas jogadas
void jogoBot()
{
    initRandom();

    Jogador jogador[2]= {{"A",0,0},{"B",0,0}};

    char **jogo=NULL;
    int linhas, colunas, opcao, l, c, i, n, valor, jogadas=0, ganhou=0, jogou=1, turno=1;

    linhas=colunas=intUniformRnd(3,5);

    printf(" INICIO DO JOGO\n");
    printf("\n ---TABULEIRO---\n");

    jogo = Cria_matriz_dinamica(jogo,linhas,colunas);
    printf("\n");
    mostra_tabuleiro(jogo, linhas, colunas);

    Lista *tabuleiro=malloc(sizeof(Lista));
    if(tabuleiro==NULL)
        exit(0);
    Lista *aux=tabuleiro;

    do
    {
        i=(jogadas%2);
        if(i==0)
        {
            opcao=menu( &jogadas, jogador);
            switch(opcao)
            {
            case 1:
                jogar(jogo, linhas, colunas, &jogadas, &jogou, &l, &c);
                ganhou=ganhouTudo(jogo, linhas, colunas);
                break;
            case 2:
                adiciona_pedras(jogo, jogador, linhas, colunas, &jogadas, &jogou, &l, &c);
                break;
            case 3:
                valor=Aumentar_Linha_Coluna(jogador, &jogadas, &jogou);
                if(valor==1)
                    jogo=Aumenta_Linha(jogo, &linhas, colunas);
                break;
            case 4:
                valor=Aumentar_Linha_Coluna(jogador, &jogadas, &jogou);
                if(valor==1)
                    jogo=Aumenta_Coluna(jogo, linhas, &colunas);
                break;
            case 5:
                printf("Quantas jogadas deseja rever? ");
                scanf("%d",&n);
                mostraJogadasAnteriores(tabuleiro, aux,  n, jogadas);
                break;
            case 6:
                ficheirobinario(tabuleiro, aux);
                break;
            case 7:
                jogou=1;
                break;
            }
            printf("\n  ---TABULEIRO---\n");
            printf("\n");
            mostra_tabuleiro(jogo, linhas, colunas);
        }
        else
        {
            opcao=intUniformRnd(1,4);
            switch(opcao)
            {
            case 1:
                jogarBot(jogo, linhas, colunas, &jogadas, &jogou, &l, &c);
                ganhou=ganhouTudo(jogo, linhas, colunas);
                break;
            case 2:
                adiciona_pedrasBot(jogo, jogador, linhas, colunas, &jogadas, &jogou, &l, &c);
                break;
            case 3:
                valor=Aumentar_Linha_ColunaBot(jogador, &jogadas, &jogou);
                if(valor==1)
                {
                    jogo=Aumenta_Linha(jogo, &linhas, colunas);
                    printf("\n");
                    mostra_tabuleiro(jogo, linhas, colunas);
                }
                break;
            case 4:
                valor=Aumentar_Linha_ColunaBot(jogador, &jogadas, &jogou);
                if(valor==1)
                {
                    jogo=Aumenta_Coluna(jogo, linhas, &colunas);
                    printf("\n");
                    mostra_tabuleiro(jogo, linhas, colunas);
                }
                break;
            }
        }

        if(jogou!=0)
            aux=guardaDados(aux, jogo, linhas, colunas, l, c, opcao);

        if(ganhou==1)
            mostraGanhouBot(jogo, linhas, colunas, jogadas, ganhou);

    }while(opcao>=1 && opcao<6 && ganhou==0);

    ficheiroTexto(tabuleiro, aux, &turno);

    apagaLista(tabuleiro);

    libertaJogo(jogo, linhas);

    printf("\n ~~~~~ ACABOU O JOGO ~~~~~\n");

}

//Esta função mostra na consola um pequeno manual de funcionamento do jogo
void manual()
{
    printf("\n     -----> COMO JOGAR <-----\n");
    printf("- O jogo realiza-se num tabuleiro, inicialmente vazio.\n");
    printf("- Em cada jogada, cada jogador realiza uma das seguintes acoes:\n");
    printf("   - Coloca uma peca verde numa posicao vazio;\n");
    printf("   - Substitui uma peca verde por uma peca amarela;\n");
    printf("   - Substitui uma peca amarela por uma peca vermelha.\n");
    printf("- Cada jogador pode realizar tambem as seguintes jogadas extra:\n");
    printf("   - Adicionar uma linha ao tabuleiro (maximo de 2 linhas e colunas por jogador);\n");
    printf("   - Adicionar uma coluna ao tabuleiro (maximo de 2 linhas e colunas por jogador);\n");
    printf("   - Colocar uma pedra numa posicao vazia (maximo de 1 pedra por jogador).\n");
    printf("- Cada jogador no inicio da sua jogada podera tambem rever o tabuleiro nas ultimas N jogadas,\n  assim como pedir para pausar o jogo e retoma lo mais tarde.\n");
}
