#include <stdio.h>

typedef long long ll;

int main(){
    int n;
    scanf("%d", &n);
    if(n == 0){
        printf("1");
        return 0;
    }
    ll res = 1;
    for(int i = 1; i <= n; i++){
        res = res * (2 * n - i + 1) / i;
    }
    res /= (n + 1);
    printf("%lld", res);
}