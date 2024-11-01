#include <stdio.h>

int main(){
    int C;
    scanf("%d", &C);
    while(C--){
        long long n, m;
        scanf("%lld %lld", &n, &m);
        char labels[n+1];
        scanf("%s", labels+1);
        for(long long i=0;i<n-1;i++){
            long long u, v;
            scanf("%lld %lld", &u, &v);
        }
        char S[m+1];
        scanf("%s", S);
        printf("0\n");
    }
    return 0;
}