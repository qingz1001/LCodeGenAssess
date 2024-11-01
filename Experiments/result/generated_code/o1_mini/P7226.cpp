#include <stdio.h>

typedef long long ll;

int main(){
    int n;
    scanf("%d", &n);
    ll X = 0;
    for(int i = 0; i < n; i++){
        int qi;
        scanf("%d", &qi);
        int p = qi % 10;
        int num = qi / 10;
        ll term = 1;
        for(int j = 0; j < p; j++) term *= num;
        X += term;
    }
    printf("%lld\n", X);
    return 0;
}