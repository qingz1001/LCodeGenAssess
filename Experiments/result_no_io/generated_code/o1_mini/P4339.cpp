#include <stdio.h>

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        long long m, K;
        scanf("%lld %lld", &m, &K);
        if(K == 1){
            printf("1\n");
        }
        else if(m == 1){
            printf("-1\n");
        }
        else{
            printf("%lld\n", K);
        }
    }
    return 0;
}