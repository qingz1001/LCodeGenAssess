#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    int *f = (int*)calloc(n+1, sizeof(int));
    if(!f){
        return 1;
    }
    for(int i=1;i<=n;i++){
        for(int j=i; j<=n; j+=i){
            f[j]++;
        }
    }
    long long sum = 0;
    for(int i=1;i<=n;i++){
        sum += f[i];
    }
    printf("%lld\n", sum);
    free(f);
    return 0;
}