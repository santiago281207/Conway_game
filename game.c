#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define AC_YELLOW "\x1b[33m"
#define AC_BLUE   "\x1b[34m"
#define AC_RESET  "\x1b[0m"

#define COL 50U
#define LIN 25U

int CheckInput(int table[][COL], int x, int y);
int CheckEmptyGame(int table[][COL]);
int ContaVizinhos(int table[][COL],int y,int x);
void CopyArray(int table[][COL], int copy[][COL]);
void MostrarTabuleiro(int table[][COL]);
void GerarCampo(int table[][COL]);
void GerarCampoRandom(int table[][COL]);
void MenuRegras(void);
void Menu(void);

int CheckInput(int table[][COL], int x, int y);
int main()
{
    int table[LIN][COL] = { 0 };
    int tableCopy[LIN][COL] = { 0 };
    int vizinhos = 0, geracoes_count = 0;
    int x, y;
    int i = 0, j = 0;
    int task = -1, regras_leave = 0;
    int sair = 0;
    
    GerarCampo(table);
    while (task != 5 && task != 0)
    {
        do
        {
            //Sleep(2000);
            system("cls");
            MostrarTabuleiro(table);
            Menu();
            printf("Indique o que quer fazer: ");
            scanf("%d", &task);
            if (task != 0 && task != 1 && task != 2 && task != 3 && task != 4 && task != 5)
            {
                printf("Tarefa invalida!");
            }
        } while (task != 0 && task != 1 && task != 2 && task != 3 && task != 4 && task!= 5);

        switch (task)
        {
            sair = 0;
        case 1: //Celula manual
            while (sair == 0)
            {
                system("cls");
                MostrarTabuleiro(table);
                do
                {
                    printf("Indique onde quer colocar a celula(xy): ");
                    scanf("%d %d", &x, &y);
                    if (CheckInput(table, x, y) == 0)
                    {
                        puts("Invalido: Tente novamente!");
                    }
                } while (CheckInput(table, x, y) == 0);
                x--;
                y--;
                table[y][x] = 1;
                system("cls");
                MostrarTabuleiro(table);

                do
                {
                    printf("Deseja continuar?\n");
                    puts("0 - Sim.");
                    puts("1 - Nao.");
                    scanf("%d", &sair);
                    if (sair != 0 && sair != 1)
                    {
                        puts("Invalido,tente novamente.");
                    }
                } while (sair != 0 && sair != 1);
            }
            break;
        case 2: //Mapa random
            GerarCampoRandom(table);
            break;
        case 3: //Limpar 
            GerarCampo(table);
            break;
        case 4: //Regras
            system("cls");
            do
            {
                MenuRegras();
                scanf("%d", &regras_leave);
                if (regras_leave != 0)
                {
                    puts("Valor invalido.");
                }
            } while (regras_leave != 0);
            break;
        case 0:
            break;
        default:
            break;
        }
    }

    if (task == 5)  //Start game
    {
        CopyArray(table, tableCopy);
        //puts("Tarefa 4");
        while (1)
        {
            Sleep(200);
            system("cls");
            MostrarTabuleiro(table);
            vizinhos = 0;
            for (i = 0;i < LIN;i++)
            {

                for (j = 0;j < COL;j++)
                {
                    vizinhos = ContaVizinhos(table, i, j);
                    if (vizinhos < 2)//Morre
                    {
                        tableCopy[i][j] = 0;
                    }
                    else if (vizinhos == 2 || vizinhos == 3)    //Vive para a proxima geracao
                    {
                        tableCopy[i][j] = 1;
                    }
                    else if (vizinhos > 3)  //Sobrepopulacao
                    {
                        tableCopy[i][j] = 0;
                    }
                    else if (table[i][j] == 0 && vizinhos == 3) //Revive
                    {
                        tableCopy[i][j] = 1;
                    }

                    vizinhos = 0;
                }
            }
            if (CheckEmptyGame(table) == 0)
            {
                geracoes_count++;
            }
            else {
                break;
            }
            CopyArray(tableCopy, table);
        }
    }
    printf("Existiram %d geracoes.\n", geracoes_count);
    return 0;
}

void MostrarTabuleiro(int table[][COL])
{
    int i, j;

    for (i = 0; i < LIN; i++)
    {
        // número da linha no início (3 espaços fixos)
        printf("%s%3d%s ", AC_BLUE, i + 1, AC_RESET);

        for (j = 0; j < COL; j++)
        {
            if (table[i][j] == 1)
                printf("%s%2c%s  ", AC_YELLOW,'O', AC_RESET); // célula viva
            else
                printf("%2c  ",'-'); // célula morta
        }
        printf("\n");
    }

    // numeração das colunas em baixo
    printf("   "); // espaço para alinhar com o número da linha
    for (j = 0; j < COL; j++)
    {
        printf("%s%3d%s ", AC_BLUE, j + 1, AC_RESET);
    }
    printf("\n");
}

void GerarCampo(int table[][COL])
{
    int i = 0, j = 0;

    for (i = 0; i < LIN; i++)
    {
        for (j = 0; j < COL; j++)
        {
            table[i][j] = 0;
        }
    }
}

int CheckInput(int table[][COL],int x, int y)
{
    y--;
    x--;
    int empty = table[y][x];


    return ((x >= 0 && x < COL) && (y >= 0 && y < LIN) && empty == 0);
    
}

void Menu(void)
{
    puts(" === GAME OF LIFE === ");
    puts("1 - Configurar mapa manualmente.");
    puts("2 - Configuracao aleatoria.");
    puts("3 - Limpar tabuleiro.");
    puts("4 - Regras.");
    puts("5 - Comecar jogo.");
    puts("0 - Sair");
}

void GerarCampoRandom(int table[][COL])
{
    int i = 0, j = 0;

    srand(time(NULL));

    for (i = 0; i < LIN; i++)
    {
        for (j = 0; j < COL; j++)
        {
            table[i][j] = (rand() % 100 < 35) ? 1 : 0;
        }
    }
}

int ContaVizinhos(int table[][COL],int y,int x)
{
    int vizinhos = 0;

    if (x == 0) //Primeira coluna
    {
        //Verificar se esta nas extremidades
        if (y == 0) //Canto superior esquerdo
        {
            vizinhos = table[y][x + 1] + table[y + 1][x + 1] + table[y + 1][x]; //Verifica a volta da celula
            return vizinhos;
        }
        else if (y == LIN-1)    //Canto inferior esquerdo
        {
            vizinhos = table[y][x + 1] + table[y - 1][x + 1] + table[y - 1][x]; //Verifica a volta da celula
            return vizinhos;
        }
        else    //Celulas do meio da primeira coluna
        {
            vizinhos = table[y - 1][x] + table[y + 1][x] + table[y][x + 1] + table[y - 1][x + 1] + table[y + 1][x + 1];
        }
    }
    else if (x == COL-1)    //Ultima coluna
    {
        if (y == 0) //Canto superior direito
        {
            vizinhos = table[y][x - 1] + table[y + 1][x - 1] + table[y + 1][x]; //Verifica a volta da celula
            return vizinhos;
        }
        else if (y == LIN-1)    //Cnato inferior direito
        {
            vizinhos = table[y][x - 1] + table[y - 1][x - 1] + table[y - 1][x]; //Verifica a volta da celula
            return vizinhos;
        }
        else    //Celulas do meio da ultima coluna
        {
            vizinhos = table[y - 1][x] + table[y + 1][x] + table[y][x - 1] + table[y - 1][x - 1] + table[y + 1][x - 1];
            return vizinhos;
        }
    }
    else if (y == 0 && x > 0 && x < COL-1)  //Linha de cima sem contar com os cantos
    {
        vizinhos = table[y][x - 1] + table[y + 1][x - 1] + table[y + 1][x] + table[y][x + 1] + table[y + 1][x + 1];
        return vizinhos;
    }
    else if (y == LIN - 1 && x > 0 && x < COL - 1)  //Ultima linha em baixo
    {
        vizinhos = table[y][x - 1] + table[y - 1][x - 1] + table[y - 1][x] + table[y][x + 1] + table[y - 1][x + 1];
    }
    else    //Todos do meio
    {
        vizinhos = table[y][x - 1] + table[y][x + 1] + table[y + 1][x] + table[y - 1][x] + table[y - 1][x - 1] + table[y - 1][x + 1] + table[y + 1][x + 1] + table[y + 1][x - 1];
    }
    return vizinhos;
}

void CopyArray(int origem[][COL], int destino[][COL])
{
    int i = 0, j = 0;

    for (i = 0;i < LIN;i++)
    {
        for (j = 0;j < COL;j++)
        {
            destino[i][j] = origem[i][j];
        }
    }
}

void MenuRegras(void)
{
    puts(" === REGRAS DO JOGO ===");
    puts("Este jogo e' constituido por celulas que simulam pessoas.");
    puts("1 - Qualquer celula que tenha menos de dois vizinhos morre (solidao).");
    puts("2 - Qualquer celula que tenha dois ou tres vizinhos sobrevive para a proxima geracao.");
    puts("3 - Qualquer celula que tenha mais de tres vizinhos morre (sobrepopulacao).");
    puts("4 - Qualquer celula morta que tenha exatamente tres vizinhos revive (reproducao).");
    puts("5 - Se nao existir mais celulas vivas o jogo acaba e diz quantas geracoes de celulas ocorreram.");
    puts("6 - ctrl+c para acabar o programa quando quiser.");
    puts("Digite 0 para sair deste menu: ");
}

int CheckEmptyGame(int table[][COL])
{
    int i = 0, j = 0, sum_cells = 0;

    for (i = 0; i < LIN; i++){

        for (j = 0;j < COL;j++) {
            sum_cells += table[i][j];
        }
    }

    return (sum_cells < 7);
}

