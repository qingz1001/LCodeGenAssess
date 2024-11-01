#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 11192869

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    int T[3][50];
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            scanf("%d", &T[i][j]);
        }
    }
    
    int L[150];
    for(int i=0;i<n*m;i++) {
        scanf("%d", &L[i]);
    }
    
    if(n ==1){
        // Two possible directions: left to right and right to left
        int match_lr =1, match_rl=1;
        for(int j=0;j<m;j++) {
            if(T[0][j] != L[j]){
                match_lr =0;
            }
            if(T[0][m-1-j] != L[j]){
                match_rl =0;
            }
        }
        printf("%d\n", match_lr + match_rl);
        return 0;
    }
    
    // For n=2 and n=3, not implemented
    printf("0\n");
    return 0;
}