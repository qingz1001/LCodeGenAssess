#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int *f = (int*)calloc(n+1, sizeof(int));
    for(int j=1; j<=n; j++){
        for(int k=j; k<=n; k+=j){
            f[k]++;
        }
    }
    long long sum = 0;
    for(int i=1; i<=n; i++) sum += f[i];
    printf("%lld\n", sum);
    free(f);
    return 0;
}