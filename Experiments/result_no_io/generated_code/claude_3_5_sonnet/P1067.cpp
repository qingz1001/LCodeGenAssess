#include <stdio.h>
#include <stdlib.h>

void print_term(int coef, int exp) {
    if (coef == 0) return;
    
    if (coef > 0) printf("+");
    if (coef == -1 && exp != 0) printf("-");
    else if (coef != 1 || exp == 0) printf("%d", abs(coef));
    
    if (exp > 1) printf("x^%d", exp);
    else if (exp == 1) printf("x");
}

int main() {
    int n, coef;
    scanf("%d", &n);
    
    int first = 1;
    for (int i = n; i >= 0; i--) {
        scanf("%d", &coef);
        if (coef == 0) continue;
        
        if (first) {
            if (coef < 0) printf("-");
            if (abs(coef) != 1 || i == 0) printf("%d", abs(coef));
            first = 0;
        } else {
            print_term(coef, i);
        }
        
        if (i > 1) printf("x^%d", i);
        else if (i == 1) printf("x");
    }
    
    if (first) printf("0");
    printf("\n");
    
    return 0;
}