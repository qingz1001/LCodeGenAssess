#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    long long total_cents = 0;
    for(int i=0;i<n;i++){
        int yuan, jiao, b;
        scanf("%d.%d %d", &yuan, &jiao, &b);
        long long a_cents = yuan * 100 + jiao;
        total_cents += a_cents * b;
    }
    long long discounted = (total_cents * 85) / 100;
    long long paid_tenths = discounted / 10;
    printf("%lld.%lld\n", paid_tenths / 10, paid_tenths %10);
    return 0;
}