const char *const banner =
  "cnpf: calculadora em nota��o p�s-fixada\n"
  "==========================================\n"
  "'cnpf' � uma simples calculadora de linha\n"
  "de comando que implementa as opera��es\n"
  "aritm�ticas (+ - * / ^ ! ? ? ? ?) em\n"
  "inteiros na nota��o p�s-fixada (tamb�m\n"
  "(conhecida como 'Reverse Polish Notation).\n"
  "==========================================\n"
  "DIGITE 'q' PARA SAIR | DIGITE 'e' PARA EXEMPLOS"
;

/* SUGEST�O DE NOVOS OPERADORES:
 * ~: Nega��o          (ex: 5 ~     -> -5)
 * #: Raiz quadrada    (ex: 9 #     -> 3)
 * %: M�dulo (resto)   (ex: 10 % 3  -> 1)
 * <: Menor que        (ex: 3 5 <   -> 1)
 * >: Maior que        (ex: 3 5 >   -> 0)
 * =: Igual a          (ex: 7 7 =   -> 1)
 * @: M�dia de dois n. (ex: 10 20 @ -> 15)
 * f: En�simo n. Fibonacci (ex: 7 f -> 13)
 * p: N�mero � primo?  (ex: 4 p     -> 0)
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#include "cnpf.h"

#include "util.c"
#include "calc_stack.c"
#include "calc.c"

int main(int argc, char **argv)
{
  char *expression;
  int expression_length;
  long value;
  int i;

  setlocale(LC_ALL, "Portuguese");

  if (argc == 2 && strcmp(argv[1], "-q") == 0) {
    /* Desativar 'banner' inicial ao passar a op��o "-q". */
  } else if (argc < 2) {
    puts(banner);
  } else {
    fatal_error("Utiliza��o: cnpf [-q]");
  }

  while (true) {
    /* Obtenha a express�o aritm�tica do usu�rio. */
    expression = get_user_line(&expression_length);

    /* Remova espa�os desnecess�rios no *in�cio* da express�o. */
    while (expression[0] == ' ') {
      ++expression;
      --expression_length;
    }

    /* Remova espa�os desnecess�rios no *final* da express�o. */
    for (i = expression_length-1; expression[i] == ' '; --i) {
      expression[i] = '\0';
      --expression_length;
    }

    /* Se usu�rio n�o digitar nada, prossiga para a pr�xima leitura. */
    if (expression_length == 0) {
      continue;
    }
    /* Se usu�rio digitar 'q', finalize o programa (quit). */
    else if (strcmp(expression, "q") == 0) {
      break;
    }
    /* Se usu�rio digitar 'e', exiba exemplos da calculadora. */
    else if (strcmp(expression, "e") == 0) {
      putchar('\n');
      puts("Express�o convencional: 2 + 2");
      puts("Express�o 'cnpf':       2 2 +");
      putchar('\n');
      puts("Express�o convencional: (4 + 6) / 2");
      puts("Express�o 'cnpf':       4 6 + 2 /");
      putchar('\n');
      puts("Express�o convencional: ((4 * 2) - (5 * 2)) / (2 * -1)");
      puts("Express�o 'cnpf':       4 2 * 5 2 * - 2 -1 * /");
      putchar('\n');
      puts("Express�o convencional: 2 ^ 3");
      puts("Express�o 'cnpf':       2 3 ^");
      putchar('\n');
      puts("Note que na nota��o p�s-fixada n�o � usado par�nteses.");
      puts("Obs: neste programa, espa�os entre operandos ou operadores s�o obrigat�rios!\n");
      continue;
    }

    /* Execute a calculadora 'calc': */
    if (calc(expression, &value)) {
      printf("%ld\n", value);
    } else {
      puts("<Erro de sintaxe>");
    }
  }

  return 0;
}