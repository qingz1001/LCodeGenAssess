#include <stdio.h>
#include <math.h>

#define MAX_N 55
#define MAX_K 10000
#define MAX_SQUARE 20000

int main(){
    int n;
    scanf("%d", &n);
    
    // Precompute squares
    int is_square[MAX_SQUARE +1];
    for(int i=0;i<=MAX_SQUARE;i++) is_square[i]=0;
    for(int i=1;i*i <= MAX_SQUARE;i++) is_square[i*i] =1;
    
    // Initialize columns
    int columns[MAX_N][MAX_K];
    int col_size[MAX_N];
    for(int i=0;i<n;i++) col_size[i]=0;
    
    int k=1;
    while(k <= MAX_K){
        int placed = 0;
        for(int i=0;i<n;i++){
            if(col_size[i]==0 || is_square[columns[i][col_size[i]-1] + k]){
                columns[i][col_size[i]++] = k;
                placed =1;
                break;
            }
        }
        if(!placed) break;
        k++;
    }
    printf("%d\n", k-1);
    for(int i=0;i<n;i++){
        for(int j=0;j<col_size[i];j++){
            if(j>0) printf(" ");
            printf("%d", columns[i][j]);
        }
        printf("\n");
    }
    return 0;
}