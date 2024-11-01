#include <stdio.h>

unsigned char lamp[2000001];

int main(){
    int n;
    scanf("%d", &n);
    double a_i;
    int t_i;
    for(int i=0; i<n; i++){
        scanf("%lf %d", &a_i, &t_i);
        for(int k=1; k<=t_i; k++){
            long long idx = (long long)(k * a_i);
            lamp[idx] ^= 1;
        }
    }
    for(long long idx=1; idx<=2000000; idx++){
        if(lamp[idx]){
            printf("%lld\n", idx);
            break;
        }
    }
    return 0;
}