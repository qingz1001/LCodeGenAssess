#include <stdio.h>

typedef long long ll;

int main(){
    int n;
    scanf("%d", &n);
    ll C[19];
    C[0] = 1;
    for(int i=1; i<=n; i++){
        C[i] = 0;
        for(int j=0; j<i; j++){
            C[i] += C[j] * C[i-1-j];
        }
    }
    printf("%lld\n", C[n]);
    return 0;
}