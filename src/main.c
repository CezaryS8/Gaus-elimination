#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>

int test (char *Ax, char *bx, char *wx);
int matrixCompare(Matrix *x, Matrix *w );

int
main (int argc, char **argv)
{
  int res;
  Matrix *A = readFromFile (argv[1]);
  Matrix *b = readFromFile (argv[2]);
  Matrix *x;

  if (A == NULL)
    return -1;
  if (b == NULL)
    return -2;
  printf ("Wczytane dane macierzy:\n");
  printToScreen (A);
  printf ("\nWektor b:\n");
  printToScreen (b);
  res = eliminate (A, b);
  x = createMatrix (b->r, 1);
  if (x != NULL)
    {
      res = backsubst (x, A, b);
      if(res==1) {
	fprintf(stderr, "%s:Wprowadzono macierz osobliwa( czyli taka, dla ktorej rzad jest mniejszy od rozmiaru wektora x)", argv[0]);
	return EXIT_FAILURE;
      }
      if(res==2) {
	fprintf(stderr, "Błąd! Wprowadzono nieprawidłowe rozmiary macierzy");
	return EXIT_FAILURE;
      }
      printf ("\nMacierz wynikow:\n");
      printToScreen (x);
      freeMatrix (x);
    }
  else
    {
      fprintf (stderr,
	       "Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
    }
  freeMatrix (A);
  freeMatrix (b);
  
  //Testy funkcjonalne
  int t;
  t=test("dane/A1", "dane/b1", "dane/w1");
  if(t==1) printf("Test 1 - poprawne dane 2x2: OK.");
  else if(t==-1) printf("Test 1 - niepoprawne dane!");
  else printf("Test 2 - poprawne dane 2x2: Wystąpił BŁĄD!!!");
  printf("\n");
  t=test("dane/A2", "dane/b2", "dane/w2");
  if(t==1) printf("Test 2 - poprawne dane 5x5: OK.");
  else if(t==-1) printf("Test 2 - niepoprawne dane!");
  else printf("Test 2 - poprawne dane 5x5: Wystąpił BŁĄD!!!");
  printf("\n");
  t=test("dane/A3", "dane/b3", "dane/w3");
  if(t==1) printf("Test 3 - poprawne dane (selekcja elementu diagonalnego): OK.");
  else if(t==-1) printf("Test 3 - niepoprawne dane!(selekcja elementu diagonalnego)");
  else printf("Test 3 - poprawne dane (selekcja elementu diagonalnego): Wystąpił BŁĄD!!!");
  printf("\n");
  t=test("dane/A4", "dane/b4", "dane/w4");
  if(t==1) printf("Test 4 - poprawne dane (macierz osobliwa): OK.");
  else if(t==-1) printf("Test 4 - niepoprawne dane! (macierz osobliwa)");
  else printf("Test 4 - poprawne dane (macierz osobliwa): WYstąpił BŁĄD!!!");
  printf("\n");
  
  t=test("dane/A5", "dane/b5", "dane/w5");
  if(t==1) printf("Test 5 - dane o niewłaściwym formacie: Wystąpił BŁĄD!!!");
  else if(t==-1) printf("Test 5 - dane o niewłaściwym formacie: OK.");
  else printf("Test 5 - dane o niewłaściwym formacie: Wystąpił BŁĄD!!!");
  printf("\n");

  return 0;
}


int
test (char *Ax, char *bx, char *wx)
{
  int res;
  Matrix *A = readFromFile (Ax);
  Matrix *b = readFromFile (bx);
  Matrix *w = readFromFile (wx);
  Matrix *x;

  if (A == NULL || b == NULL )
    return -1;

  res = eliminate (A, b);
  x = createMatrix (b->r, 1);
  if(x != NULL) {
	res = backsubst (x, A, b);
	if(res == 1){
		if(w->r == 0) 
	  		return 1;
		else return 0;
	}	
	if(res == 2) 
		return -1;
   	return matrixCompare(x, w); 
		
  }
  else 
	  return -1;
  
  freeMatrix (x);
  freeMatrix (A);
  freeMatrix (b);
  return 1;
}

int matrixCompare(Matrix *x, Matrix *w ) {
	if(x->r == w->r && x->c == w->c) {
		for(int i=0; i<x->r; i++) {
			for(int j=0; j<x->c; j++) {
				if(x->data[i][j] != w->data[i][j])
					return 0;
			}
		}
		return 1;
	}
	else return -1;
}


