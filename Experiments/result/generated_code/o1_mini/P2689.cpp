#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 201
#define INF 1000

int main(){
    int x1, y1, x2, y2, T;
    scanf("%d %d", &x1, &y1);
    scanf("%d %d", &x2, &y2);
    scanf("%d", &T);
    char winds[T];
    for(int i=0;i<T;i++) {
        char c;
        scanf(" %c", &c);
        winds[i] = c;
    }
    int offset = 100;
    int dp[2][MAX][MAX];
    for(int i=0;i<2;i++) {
        for(int j=0;j<MAX;j++) {
            for(int k=0;k<MAX;k++) {
                dp[i][j][k] = INF;
            }
        }
    }
    dp[0][x1 + offset][y1 + offset] = 0;
    for(int t=0;t<T;t++){
        int current = t%2;
        int next = (t+1)%2;
        // Initialize next layer
        for(int i=0;i<MAX;i++) {
            for(int j=0; j<MAX; j++) {
                dp[next][i][j] = INF;
            }
        }
        for(int x=0; x<MAX; x++) {
            for(int y=0; y<MAX; y++) {
                if(dp[current][x][y] < INF){
                    // Option 1: stay
                    if(dp[next][x][y] > dp[current][x][y]){
                        dp[next][x][y] = dp[current][x][y];
                    }
                    // Option 2: move
                    int dx=0, dy=0;
                    if(winds[t] == 'E') dx =1;
                    else if(winds[t] == 'W') dx =-1;
                    else if(winds[t] == 'N') dy =1;
                    else if(winds[t] == 'S') dy =-1;
                    int nx = x + dx;
                    int ny = y + dy;
                    if(nx >=0 && nx < MAX && ny >=0 && ny < MAX){
                        if(dp[next][nx][ny] > dp[current][x][y] +1){
                            dp[next][nx][ny] = dp[current][x][y] +1;
                        }
                    }
                }
            }
        }
    }
    int final = dp[T%2][x2 + offset][y2 + offset];
    if(final < INF){
        printf("%d", final);
    }
    else{
        printf("-1");
    }
    return 0;
}