#include <stdio.h>

int main(){
    int n, v, m, a;
    scanf("%d %d %d %d", &n, &v, &m, &a);
    long long total = 0;
    int current_price = v;
    for(int i=1;i<=n;i++){
        total += current_price;
        if(m >0 && i % m ==0){
            current_price += a;
        }
    }
    printf("%lld\n", total);
    return 0;
}