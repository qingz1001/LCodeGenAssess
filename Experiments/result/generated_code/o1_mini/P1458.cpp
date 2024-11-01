#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Fraction;

int gcd(int a, int b){
    while(b){
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int cmp(const void *x, const void *y){
    Fraction *f1 = (Fraction*)x;
    Fraction *f2 = (Fraction*)y;
    int lhs = f1->a * f2->b;
    int rhs = f2->a * f1->b;
    if(lhs < rhs) return -1;
    else if(lhs > rhs) return 1;
    else return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    Fraction fractions[20000];
    int count = 0;
    // Add 0/1
    fractions[count].a = 0;
    fractions[count].b = 1;
    count++;
    // Add fractions
    for(int b=2; b<=n; b++){
        for(int a=1; a<b; a++){
            if(gcd(a, b) == 1){
                fractions[count].a = a;
                fractions[count].b = b;
                count++;
            }
        }
    }
    // Add 1/1
    if(n >=1){
        fractions[count].a = 1;
        fractions[count].b = 1;
        count++;
    }
    // Sort fractions
    qsort(fractions, count, sizeof(Fraction), cmp);
    // Print fractions
    for(int i=0; i<count; i++){
        printf("%d/%d\n", fractions[i].a, fractions[i].b);
    }
    return 0;
}