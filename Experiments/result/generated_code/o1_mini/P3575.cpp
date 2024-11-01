#include <stdio.h>
#include <stdint.h>

int main(){
    int n, s;
    scanf("%d %d", &n, &s);
    int64_t l;
    int64_t sum_l = 0;
    int max_l = 0;
    for(int i=0;i<n;i++){
        scanf("%lld", &l);
        sum_l += l;
        if(l > max_l){
            max_l = l;
        }
    }
    int d;
    for(int i=0;i<s;i++){
        scanf("%d", &d);
        if(d < max_l){
            printf("NIE\n");
        }
        else if(sum_l <= d){
            printf("2\n");
        }
        else{
            int64_t res = (sum_l + d -1)/d;
            printf("%lld\n", res);
        }
    }
    return 0;
}