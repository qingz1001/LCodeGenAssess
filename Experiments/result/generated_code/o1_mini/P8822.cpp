#include <stdio.h>

int main(){
    int n, v, m, a;
    scanf("%d %d %d %d", &n, &v, &m, &a);
    long long total = 0;
    if(m == 0){
        total = (long long)n * v;
    }
    else{
        int full = n / m;
        int rem = n % m;
        for(int i=0;i<full;i++){
            total += (long long)m * (v + i * a);
        }
        if(rem >0){
            total += (long long)rem * (v + full * a);
        }
    }
    printf("%lld", total);
    return 0;
}