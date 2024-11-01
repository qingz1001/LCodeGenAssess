#include <stdio.h>

int main(){
    int n, r;
    scanf("%d %d", &n, &r);
    if((r == 0 && n == 0)){
        printf("1\n");
        return 0;
    }
    if(r == 0 || r > n){
        printf("0\n");
        return 0;
    }
    int S[11][11] = {0};
    S[0][0] = 1;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= r; j++){
            S[i][j] = S[i-1][j-1] + j * S[i-1][j];
        }
    }
    // Compute r!
    int fact = 1;
    for(int i = 2; i <= r; i++) fact *= i;
    int answer = fact * S[n][r];
    printf("%d\n", answer);
}