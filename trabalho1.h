/*============================================================================*/
/* CSF13 - 2021-2 - TRABALHO 1                                                */
/*----------------------------------------------------------------------------*/
/* Bogdan T. Nassu - btnassu@utfpr.edu.br                                     */
/* Leyza E. B. Dorini - leyza@utfpr.edu.br                                    */
/*============================================================================*/
/** Funções pedidas e auxiliares para o 1o trabalho da disciplina Fundamentos
 * de Programação 1, 2o semestre de 2021, prof. Bogdan T. Nassu e Leyza E. B.
 * Dorini, Universidade Tecnológica Federal do Paraná. */
/*============================================================================*/

#ifndef __TRABALHO1_H
#define __TRABALHO1_H

/*============================================================================*/
/* Funções do trabalho. */

unsigned int fourcc (char c1, char c2, char c3, char c4);
int calculaInterseccao (int n_retangulos);
double raizAproximada (double x, double erro_minimo);
int codigoValido (unsigned int n, int tamanho);

/*----------------------------------------------------------------------------*/
/* Funções auxiliares que DEVEM ser chamadas pelos alunos. */

int pegaXSE (int pos);
int pegaYSE (int pos);
int pegaXID (int pos);
int pegaYID (int pos);

/*----------------------------------------------------------------------------*/
/* Funções auxiliares que NÃO DEVEM ser chamadas pelos alunos. */

void criaVetorRetangulos (int tamanho);
void destroiVetorRetangulos ();
void adicionaRetangulo (int pos, int tlx, int tly, int brx, int bry);
void mostraRetangulos (int n);

/*============================================================================*/
#endif /* __TRABALHO1_H */

