#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Fraction;

int gcd_func(int a, int b){
    while(b){
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int compare(const void* x, const void* y){
    Fraction fx = *(Fraction*)x;
    Fraction fy = *(Fraction*)y;
    long lhs = (long)fx.a * fy.b;
    long rhs = (long)fy.a * fx.b;
    if(lhs < rhs) return -1;
    else if(lhs > rhs) return 1;
    else return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    Fraction fractions[20000];
    int count =0;
    fractions[count].a =0;
    fractions[count].b =1;
    count++;
    for(int b=1; b<=n; b++){
        for(int a=1; a<b; a++){
            if(gcd_func(a, b) ==1){
                fractions[count].a =a;
                fractions[count].b =b;
                count++;
            }
        }
    }
    fractions[count].a =1;
    fractions[count].b =1;
    count++;
    qsort(fractions, count, sizeof(Fraction), compare);
    for(int i=0; i<count; i++){
        printf("%d/%d\n", fractions[i].a, fractions[i].b);
    }
    return 0;
}