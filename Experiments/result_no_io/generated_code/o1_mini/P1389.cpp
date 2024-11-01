#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAXN 151

int V[MAXN];
long long A[MAXN];
bool is_deletable[MAXN][MAXN];
int dp_table[MAXN][MAXN];

int main(){
    int N;
    scanf("%d", &N);
    for(int i=1;i<=N;i++) scanf("%d", &V[i]);
    for(int i=1;i<=N;i++) scanf("%lld", &A[i]);
    
    // Precompute is_deletable
    for(int i=1;i<=N;i++){
        for(int j=i;j<=N;j++){
            int len = j - i +1;
            bool valid = true;
            // Condition 1: adjacent diffs ==1
            for(int k=i; k<j; k++){
                if(abs((int)(A[k] - A[k+1])) !=1){
                    valid = false;
                    break;
                }
            }
            if(!valid){
                is_deletable[i][j] = false;
                continue;
            }
            // Condition 2: no inner element is less than both neighbors
            for(int k=i+1; k<j; k++){
                long long mn = A[k-1] < A[k+1] ? A[k-1] : A[k+1];
                if(A[k] < mn){
                    valid = false;
                    break;
                }
            }
            is_deletable[i][j] = valid;
        }
    }
    
    // Initialize dp
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++) dp_table[i][j] = 0;
    }
    
    // Fill dp_table
    for(int length=1; length<=N; length++){
        for(int i=1; i+length-1 <=N; i++){
            int j = i + length -1;
            // If deletable, take V[length]
            if(is_deletable[i][j]){
                if(V[length] > dp_table[i][j]){
                    dp_table[i][j] = V[length];
                }
            }
            // Split the interval
            for(int k=i; k<j; k++){
                int temp = dp_table[i][k] + dp_table[k+1][j];
                if(temp > dp_table[i][j]){
                    dp_table[i][j] = temp;
                }
            }
        }
    }
    
    printf("%d\n", dp_table[1][N]);
    return 0;
}