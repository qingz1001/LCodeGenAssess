#include <stdio.h>
#include <stdlib.h>

#define MAXN 2001

int min3(int a, int b, int c){
    if(a < b) return a < c ? a : c;
    else return b < c ? b : c;
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int matrix[N][M];
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            char c;
            scanf(" %c", &c);
            matrix[i][j] = c - '0';
        }
    }
    
    // Prepare pattern A and B
    int patternA[N][M];
    int patternB[N][M];
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            if( (i + j) %2 ==0){
                patternA[i][j] = (matrix[i][j] == 0) ? 1 : 0;
                patternB[i][j] = (matrix[i][j] == 1) ? 1 : 0;
            }
            else{
                patternA[i][j] = (matrix[i][j] ==1) ? 1 : 0;
                patternB[i][j] = (matrix[i][j] ==0) ? 1 : 0;
            }
        }
    }
    
    // Compute max square
    int dp[N][M];
    int max_square =0;
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            if(patternA[i][j] || patternB[i][j]){
                if(i ==0 || j==0){
                    dp[i][j] =1;
                }
                else{
                    if( (patternA[i][j] && patternA[i-1][j] && patternA[i][j-1] && patternA[i-1][j-1]) ||
                        (patternB[i][j] && patternB[i-1][j] && patternB[i][j-1] && patternB[i-1][j-1]) ){
                        dp[i][j] = min3(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) +1;
                    }
                    else{
                        dp[i][j] =1;
                    }
                }
                if(dp[i][j] > max_square){
                    max_square = dp[i][j];
                }
            }
            else{
                dp[i][j] =0;
            }
        }
    }
    
    // Compute max rectangle
    // For pattern A and B separately
    int max_rectangle =0;
    for(int p=0;p<2;p++){
        int height[M];
        for(int j=0;j<M;j++) height[j]=0;
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                if(p==0){
                    height[j] = patternA[i][j] ? height[j]+1 : 0;
                }
                else{
                    height[j] = patternB[i][j] ? height[j]+1 : 0;
                }
            }
            // Compute largest rectangle in histogram
            int stack[M];
            int top = -1;
            int j =0;
            while(j < M){
                if(top == -1 || height[j] >= height[stack[top]]){
                    stack[++top] = j++;
                }
                else{
                    int tp = stack[top--];
                    int width = top==-1 ? j : j - stack[top] -1;
                    int area = height[tp] * width;
                    if(area > max_rectangle) max_rectangle = area;
                }
            }
            while(top != -1){
                int tp = stack[top--];
                int width = top==-1 ? j : j - stack[top] -1;
                int area = height[tp] * width;
                if(area > max_rectangle) max_rectangle = area;
            }
        }
    }
    
    printf("%d\n%d\n", max_square * max_square, max_rectangle);
    return 0;
}