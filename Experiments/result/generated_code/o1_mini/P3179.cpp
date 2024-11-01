#include <stdio.h>

int main(){
    long long n;
    int k;
    scanf("%lld", &n);
    scanf("%d", &k);
    while(k--){
        int w;
        scanf("%d", &w);
        long long xor_sum = 0;
        for(int i=0;i<w;i++){
            long long x;
            scanf("%lld", &x);
            if(x !=0){
                xor_sum ^= (n / x);
            }
        }
        if(xor_sum !=0){
            printf("Yes\n");
        }
        else{
            printf("No\n");
        }
    }
    return 0;
}