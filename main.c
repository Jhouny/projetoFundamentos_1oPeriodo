/*============================================================================*/
/* CSF13 - 2021-2 - TRABALHO 1                                                */
/*----------------------------------------------------------------------------*/
/* Bogdan T. Nassu - btnassu@utfpr.edu.br                                     */
/* Leyza E. B. Dorini - leyza@utfpr.edu.br                                    */
/*============================================================================*/
/** Teste automático para as funções pedidas para o 1o trabalho da disciplina
 * Fundamentos de Programação 1, 2o semestre de 2021, prof. Bogdan T. Nassu e
 * Leyza E. B. Dorini, Universidade Tecnológica Federal do Paraná. */
/*============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>

#include "trabalho1.h"

/*============================================================================*/
/* Selecione aqui quais funções devem ser testadas. */

#define TESTA_FOURCC 1
#define TESTA_RETANGULOS 1
#define TESTA_RAIZ 1

/*----------------------------------------------------------------------------*/
/* Configuração dos testes. Para as funções fourcc e calculaInterseccao,
   coloque o nome de um dos arquivos txt. Para a funçao raizAproximada, você
   não deve precisar de modificações. */

#define ARQUIVO_FOURCC "teste_fourcc.txt" /* Arquivo contendo dados para teste. */

#define ARQUIVO_RETANGULOS "teste_retangulos.txt" /* Arquivo contendo dados para teste. */

#define RSEED 561 /* Semente usada para gerar números aleatórios. O valor será mudado para a correção real. */
#define N_TESTES_RAIZ 10000//00 /* Número de testes para a raiz aproximada. */
#define MAX_X_RAIZ 10000.0 //1000000.0
#define MIN_ERRO_RAIZ 0.0000001
#define MAX_ERRO_RAIZ 0.01

/*============================================================================*/

void testaFourCC ()
{
    int n_testes, i;
    char c1, c2, c3, c4;
    unsigned int resposta, resposta_esperada;
    FILE* in_file;

    /* Abre o arquivo contendo os dados. */
    in_file = fopen (ARQUIVO_FOURCC, "r");
    if (!in_file)
        printf ("Nao foi possivel abrir o arquivo %s!\n", ARQUIVO_FOURCC);

    /* Para cada teste... */
    fscanf (in_file, "%d\n", &n_testes);
    for (i = 0; i < n_testes; i++)
    {
        /* Lê os 4 caracteres e a resposta esperada. */
        fscanf (in_file, "%c %c %c %c %u\n", &c1, &c2, &c3, &c4, &resposta_esperada);

        resposta = fourcc (c1,c2,c3,c4);

        if (resposta != resposta_esperada)
            printf ("Erro no teste %d. %c%c%c%c - Esperava 0x%X, retornou 0x%X.\n", i, c1, c2, c3, c4, resposta_esperada, resposta);
    }

    printf ("fourcc: %d testes executados.\n", n_testes);
    fclose (in_file);
}

/*----------------------------------------------------------------------------*/

void testaRetangulos ()
{
    int n_testes, n_retangulos;
    int i_teste, i_retangulo;
    int resposta, resposta_esperada;
    FILE* in_file;

    /* Abre o arquivo contendo os dados. */
    in_file = fopen (ARQUIVO_RETANGULOS, "r");
    if (!in_file)
        printf ("Nao foi possivel abrir o arquivo %s!\n", ARQUIVO_RETANGULOS);

    /* Para cada teste... */
    fscanf (in_file, "%d\n", &n_testes);
    for (i_teste = 0; i_teste < n_testes; i_teste++)
    {
        /* Para cada retangulo... */
        fscanf (in_file, "%d\n", &n_retangulos);
        criaVetorRetangulos (n_retangulos);
        for (i_retangulo = 0; i_retangulo < n_retangulos; i_retangulo++)
        {
            /* Lê e adiciona. */
            int tlx, tly, brx, bry;
            fscanf (in_file, "%d %d %d %d\n", &tlx, &tly, &brx, &bry);
            adicionaRetangulo (i_retangulo, tlx, tly, brx, bry);
        }

        /* Pronto, agora podemos testar. */
        fscanf (in_file, "%d", &resposta_esperada);
        resposta = calculaInterseccao (n_retangulos);

        if (resposta != resposta_esperada)
        {
            printf ("Erro no teste %d.\nEsperava %d, calculou %d.\nRetangulos:\n", i_teste, resposta_esperada, resposta);
            mostraRetangulos (n_retangulos);
        }

        destroiVetorRetangulos ();
    }

    printf ("calculaInterseccao: %d testes executados.\n", n_testes);
    fclose (in_file);
}

/*----------------------------------------------------------------------------*/

void testaRaiz ()
{
    int i;
    double x, erro_minimo, resultado;

    srand (RSEED);

    /* Para cada teste... */
    for (i = 0; i < N_TESTES_RAIZ; i++)
    {
        /* Sorteia novos valores para x e para o erro mínimo. */
        x = DBL_MIN + ((double) rand () / (double) RAND_MAX) * MAX_X_RAIZ;
        erro_minimo = MIN_ERRO_RAIZ + ((double) rand () / (double) RAND_MAX) * MAX_ERRO_RAIZ;

        resultado = raizAproximada (x, erro_minimo);

        if (!isfinite (resultado))
            printf ("Erro no teste %d. Para x=%lf e erro minimo=%lf, obteve um resultado que nao eh um numero!\n\n", i, x, erro_minimo);
        else if (fabs (resultado*resultado - x) > erro_minimo)
            printf ("Erro no teste %d. Para x=%lf e erro minimo=%lf, obteve %lf, cujo quadrado eh %lf (muito longe de x).\n\n", i, x, erro_minimo, resultado, resultado*resultado);
    }

    printf ("raizAproximada: %d testes executados.\n", N_TESTES_RAIZ);
}

/*----------------------------------------------------------------------------*/

int main()
{
    if (TESTA_FOURCC)
        testaFourCC ();
    if (TESTA_RETANGULOS)
        testaRetangulos ();
    if (TESTA_RAIZ)
        testaRaiz ();

    return 0;
}

/*============================================================================*/
