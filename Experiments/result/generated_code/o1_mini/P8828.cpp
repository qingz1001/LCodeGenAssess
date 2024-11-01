#include <stdio.h>
#include <math.h>

int main(){
    int c;
    scanf("%d", &c);
    int a, b;
    for(a=1; a<=c / sqrt(2.0); a++){
        long long b_sq = (long long)c * c - (long long)a * a;
        double b_d = sqrt((double)b_sq);
        if (fabs(b_d - round(b_d)) < 1e-6){
            b = (int)(round(b_d));
            printf("%d %d", a, b);
            return 0;
        }
    }
    return 0;
}