#include <stdio.h>
#include <string.h>

int main(){
    int n;
    scanf("%d", &n);
    char matrix[n][n+1];
    for(int i=0;i<n;i++) {
        scanf("%s", matrix[i]);
    }
    long long count = 0;
    for(int top=0; top<n; top++) {
        int valid[n];
        for(int i=0; i<n; i++) valid[i]=1;
        for(int bottom=top; bottom<n; bottom++) {
            for(int col=0; col<n; col++) {
                if(matrix[bottom][col] != 'W') valid[col]=0;
            }
            int current = 0;
            for(int col=0; col<n; col++) {
                if(valid[col]){
                    current++;
                    count += current;
                }
                else{
                    current = 0;
                }
            }
        }
    }
    printf("%lld", count);
    return 0;
}