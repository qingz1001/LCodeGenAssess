#include <stdio.h>

typedef long long ll;

int main(){
    int C;
    scanf("%d", &C);
    while(C--){
        ll a, b;
        scanf("%lld %lld", &a, &b);
        if(a < b){
            ll temp = a;
            a = b;
            b = temp;
        }
        int player = 0; // 0 for Stan, 1 for Ollie
        while(1){
            if(b ==0){
                break;
            }
            if(a / b >1){
                player = !player;
                break;
            }
            ll r = a % b;
            a = b;
            b = r;
            player = !player;
        }
        if(player ==0){
            printf("Stan wins\n");
        }
        else{
            printf("Ollie wins\n");
        }
    }
    return 0;
}