#include <stdio.h>

typedef long long ll;

int main(){
    int C;
    scanf("%d", &C);
    while(C--){
        ll M, N;
        scanf("%lld %lld", &M, &N);
        ll a = M > N ? M : N;
        ll b = M > N ? N : M;
        int player = 1; // 1 for Stan, 0 for Ollie
        while(1){
            if(b ==0){
                if(player ==1){
                    printf("Ollie wins\n");
                }
                else{
                    printf("Stan wins\n");
                }
                break;
            }
            if(a / b >=2 || a % b ==0){
                if(player ==1){
                    printf("Stan wins\n");
                }
                else{
                    printf("Ollie wins\n");
                }
                break;
            }
            ll temp = a - b;
            a = b;
            b = temp;
            player = 1 - player;
        }
    }
    return 0;
}