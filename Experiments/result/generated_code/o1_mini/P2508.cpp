#include <stdio.h>
#include <math.h>

typedef long long ll;

int main(){
    ll r;
    scanf("%lld", &r);
    if(r <0){
        printf("0");
        return 0;
    }
    if(r ==0){
        printf("1");
        return 0;
    }
    ll original_r = r;
    ll count =1;
    // Remove factors of 2
    while(r %2 ==0){
        r /=2;
    }
    ll limit = sqrt((double)r) +1;
    for(ll i=3;i<=limit && r>1;i+=2){
        if(r %i ==0){
            ll exp =0;
            while(r %i ==0){
                exp++;
                r /=i;
            }
            if(i%4 ==3 && (exp %2)!=0){
                printf("0");
                return 0;
            }
            if(i%4 ==1){
                count *= (exp +1);
            }
            limit = sqrt((double)r) +1;
        }
    }
    if(r >1){
        if(r%4 ==3){
            printf("0");
            return 0;
        }
        if(r%4 ==1){
            count *=2;
        }
    }
    printf("%lld", 4*count);
    return 0;
}