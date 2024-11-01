#include <stdio.h>
#include <stdlib.h>

#define MAX 30000

int main(){
    int s;
    scanf("%d", &s);
    int *sum = (int*)calloc(MAX+1, sizeof(int));
    for(int i=1;i<=MAX/2;i++){
        for(int j=2*i;j<=MAX;j+=i){
            sum[j] += i;
        }
    }
    for(int a = s; a <= MAX; a++){
        int b = sum[a];
        if(b != a && b >=1 && b <= MAX){
            if(sum[b] == a){
                printf("%d %d\n", a, b);
                free(sum);
                return 0;
            }
        }
    }
    free(sum);
    return 0;
}