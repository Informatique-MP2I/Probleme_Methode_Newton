#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

//const int MAX_DEGREE = 100;
#define MAX_DEGREE 100

typedef struct {
  double coeff[MAX_DEGREE+1];
  int deg;
  char name[3];
} poly_s;

/*struct poly_s {
  double coeff[MAX_DEGREE+1];
  int deg;
  char name[3];
};
typedef struct poly_s poly_s;*/

poly_s *init_polynomial(double *coeff, int nb_coeff, char *name) {

  // verification of the number of coefficients
  assert(nb_coeff<MAX_DEGREE+1);

  // malloc of the structure
  poly_s *poly = (poly_s *)malloc(sizeof(poly_s));
  assert(poly!= NULL);
  
  // real degree of the polynomial
  bool is_poly_null = true;
  int i = nb_coeff - 1;
  while (i>=0 && is_poly_null) {
    if (coeff[i] != 0){
      is_poly_null = false;
      poly->deg = i;
    }
    i--;
  }
  if (is_poly_null)
    poly->deg = -1;
 
  // copy of the coefficients
  if (!is_poly_null)
    for (int i=0; i<=poly->deg; i++){
      poly->coeff[i] = coeff[i];
    }

  // copy of the name
  strcpy(poly->name, name);
  
  return poly;
}

void free_polynomial(poly_s *poly){
  free(poly);
  return;
}

void print_polynomial(poly_s *poly){
  if (poly->deg == -1) {
    printf("%s : Zero polynomial\n", poly->name);
  }
  else {
    printf("%s : ", poly->name);
    int i;
    for (i=0;i<poly->deg;i++){
      printf("%.2f x^%d + ", poly->coeff[i], i);
      
    }
    printf("%.2f x^%d\n", poly->coeff[i], i);
  }
  return;
}

bool is_zero_polynomial(poly_s *poly){
  return (poly->deg == -1);
}

double eval_polynomial(poly_s *poly, double x){
  double eval = 0;
  for (int i=0; i<=poly->deg; i++) {
    eval = eval + poly->coeff[i] * pow(x,i);
  }
  return eval;
}

poly_s *deriv_polynomial(poly_s *poly){
  if (is_zero_polynomial(poly) || poly->deg == 0) {
    double coeff[] = {};
    return init_polynomial(coeff, 0, "pr"); 
  }
  
  double coeff[poly->deg];
  for (int i=0;i<poly->deg;i++){
    coeff[i] = poly->coeff[i+1]*(i+1);
  }
  
  return init_polynomial(coeff, poly->deg, "pr");
}

double newton(poly_s *poly, double x_0, int max_iter){
  poly_s *deriv = deriv_polynomial(poly);
  int iter = 0;
  double approx = x_0;
  double v1;
  double v2;
  while (iter<max_iter) {
    v1 = eval_polynomial(poly, approx);
    v2 = eval_polynomial(deriv, approx);
    if (v2 != 0)
      approx = approx - v1/v2;
    else
      return INFINITY;
    iter ++;
  }
  return approx;
}

/*
int main(int argc, char **argv) {
  if (argc>3){
    int x_0 = atof(argv[1]);
    double coeff[MAX_DEGREE+1];
    for (int i=0;i<=MAX_DEGREE;i++)
      coeff[i]=0;
    for (int i=2;i<argc;i++)
      coeff[i-2]=atof(argv[i]);
    poly_s *poly = init_polynomial(coeff,argc-2,"P");
    print_polynomial(poly);
    printf("Approximation : %f\n", newton(poly, x_0, 100));
    free_polynomial(poly);
  }
  else {
    double x =-3;
    
    printf("\nPolynomial 1\n");
    double coeffP[] = {-2,0,1};
    poly_s *polyP = init_polynomial(coeffP,3,"P");
    print_polynomial(polyP);
    printf("Zero : %d\n",is_zero_polynomial(polyP));
    printf("Eval en %.2f : %.2f\n", x, eval_polynomial(polyP,x));
    print_polynomial(deriv_polynomial(polyP));
    printf("Approximation : %f\n", newton(polyP, 1, 100));
    free_polynomial(polyP);
    
    printf("\nPolynomial 2\n");
    double coeffQ[] = {0,1,3.5,-7.1};
    poly_s *polyQ = init_polynomial(coeffQ,4,"Q");
    print_polynomial(polyQ);
    printf("Zero : %d\n",is_zero_polynomial(polyQ));
    printf("Eval en %.2f : %.2f\n", x, eval_polynomial(polyQ,x));
    print_polynomial(deriv_polynomial(polyQ));
    free_polynomial(polyQ);
    
    printf("\nPolynomial 3\n");
    double coeffZ[] = {};
    poly_s *polyZ = init_polynomial(coeffZ,0,"Z");
    print_polynomial(polyZ);
    printf("Zero : %d\n",is_zero_polynomial(polyZ));
    printf("Eval en %.2f : %.2f\n", x, eval_polynomial(polyZ,x));
    print_polynomial(deriv_polynomial(polyZ));
    free_polynomial(polyZ);
    
    printf("\nPolynomial 4\n");
    double coeffS[] = {2};
    poly_s *polyS = init_polynomial(coeffS,1,"S");
    print_polynomial(polyS);
    printf("Zero : %d\n",is_zero_polynomial(polyS));
    printf("Eval en %.2f : %.2f\n", x, eval_polynomial(polyS,x));
    print_polynomial(deriv_polynomial(polyZ));
    free_polynomial(polyS);
  }
  return 0;
}
*/

/*
int main(int argc, char **argv) {
  double coeffP[] = {-2,0,1};
  poly_s *polyP = init_polynomial(coeffP,3,"P");
  print_polynomial(poly);
  printf("Approximation : %f\n", newton(polyP, 1, 100));
  free_polynomial(polyP);
  return 0;
}
*/


int main(int argc, char **argv) {
  if (argc>3){
    int x_0 = atof(argv[1]);
    double coeff[MAX_DEGREE+1];
    for (int i=0;i<=MAX_DEGREE;i++)
      coeff[i]=0;
    for (int i=2;i<argc;i++)
      coeff[i-2]=atof(argv[i]);
    poly_s *poly = init_polynomial(coeff,argc-2,"P");
    print_polynomial(poly);
    printf("Approximation : %f\n", newton(poly, x_0, 100));
    free_polynomial(poly);
  }
  else{
    printf("Usage : %s x_0 a_0 a_1 a_2 ...\n", argv[0]);
  } 
  return 0;
}
