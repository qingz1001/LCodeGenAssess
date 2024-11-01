#include <stdio.h>

typedef long long ll;

int main(){
    ll k, m, n;
    if(scanf("%lld %lld %lld", &k, &m, &n)!=3){
        return 0;
    }
    ll a, b;
    int index;
    // Maximum m is 30000
    int result[30000];
    int count =0;
    for(index=1; index<=m; index++){
        if(scanf("%lld %lld", &a, &b)!=2){
            break;
        }
        if(n >0){
            if(b >0){
                if(a ==0){
                    if(b >= n){
                        result[count++] = index;
                    }
                }
                else{
                    ll t_min = (n + b -1)/b;
                    ll t_max = k /a;
                    if(t_min <= t_max){
                        result[count++] = index;
                    }
                }
            }
        }
        else{
            if(a >0){
                if(k /a >=1){
                    result[count++] = index;
                }
            }
            else{
                result[count++] = index;
            }
        }
    }
    if(count >0){
        for(int i=0;i<count;i++){
            if(i>0){
                printf(" ");
            }
            printf("%d", result[i]);
        }
        printf("\n");
    }
    else{
        printf("-1\n");
    }
    return 0;
}