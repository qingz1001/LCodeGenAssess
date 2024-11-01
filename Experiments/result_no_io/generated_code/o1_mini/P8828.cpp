#include <stdio.h>
#include <math.h>

int main(){
    int c;
    scanf("%d", &c);
    for(int a=1; a<=c; a++){
        long long csq = (long long)c * c;
        long long asq = (long long)a * a;
        if(csq < asq) continue;
        long long b_sq = csq - asq;
        double b_d = sqrt((double)b_sq);
        long long b = (long long)(b_d + 1e-9);
        if(b * b == b_sq && a <= b){
            printf("%lld %lld\n", (long long)a, b);
            return 0;
        }
    }
    return 0;
}