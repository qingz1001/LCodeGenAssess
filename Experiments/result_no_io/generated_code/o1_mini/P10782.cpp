#include <stdio.h>
#include <stdint.h>

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        uint64_t a, c;
        scanf("%llu %llu", &a, &c);
        if(c > a){
            printf("-1\n");
            continue;
        }
        uint64_t n_max = a / c;
        if(n_max ==0){
            printf("-1\n");
            continue;
        }
        uint64_t b = a / n_max;
        if(b == c){
            printf("%llu\n", b);
        }
        else{
            printf("-1\n");
        }
    }
    return 0;
}