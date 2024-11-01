#include <stdio.h>

long long memo[21][21][21];

int main(){
    int a, b, c;
    // Precompute memo table
    for(a=0; a<=20; a++){
        for(b=0; b<=20; b++){
            for(c=0; c<=20; c++){
                if(a ==0 || b ==0 || c ==0){
                    memo[a][b][c] =1;
                }
                else if(a < b && b < c){
                    memo[a][b][c] = memo[a][b][c-1] + memo[a][b-1][c-1] - memo[a][b-1][c];
                }
                else{
                    memo[a][b][c] = memo[a-1][b][c] + memo[a-1][b-1][c] + memo[a-1][b][c-1] - memo[a-1][b-1][c-1];
                }
            }
        }
    }
    while(scanf("%d %d %d", &a, &b, &c) ==3){
        if(a ==-1 && b ==-1 && c ==-1){
            break;
        }
        long long ans;
        if(a <=0 || b <=0 || c <=0){
            ans =1;
        }
        else if(a >20 || b >20 || c >20){
            ans = memo[20][20][20];
        }
        else{
            ans = memo[a][b][c];
        }
        printf("w(%d, %d, %d) = %lld\n", a, b, c, ans);
    }
    return 0;
}