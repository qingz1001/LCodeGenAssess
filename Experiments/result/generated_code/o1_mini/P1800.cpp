#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_M 100
#define MAX_N 100
#define MAX_D 20000

int n, m;
int d1[MAX_N], d2[MAX_N];
int dp_prev[MAX_M+1][MAX_M+1];
int dp_curr[MAX_M+1][MAX_M+1];

int min_int(int a, int b){
    return a < b ? a : b;
}

int feasible(int D){
    memset(dp_prev, 0, sizeof(dp_prev));
    dp_prev[0][0] = 1;
    for(int i=0;i<n;i++){
        memset(dp_curr, 0, sizeof(dp_curr));
        for(int x=0;x<=m;x++){
            for(int y=0;y<=m;y++){
                if(dp_prev[x][y]){
                    int max_x = min_int(m - x, D / d1[i]);
                    for(int xi=0; xi<=max_x; xi++){
                        int remaining = D - xi * d1[i];
                        int yi_max = min_int(remaining / d2[i], m - y);
                        for(int yi=0; yi<=yi_max; yi++){
                            dp_curr[x + xi][y + yi] = 1;
                        }
                    }
                }
            }
        }
        // Swap dp_prev and dp_curr
        for(int x=0;x<=m;x++){
            for(int y=0;y<=m;y++){
                dp_prev[x][y] = dp_curr[x][y];
            }
        }
    }
    return dp_prev[m][m];
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0;i<n;i++){
        scanf("%d %d", &d1[i], &d2[i]);
    }
    int left = 0, right = MAX_D, answer = MAX_D;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(feasible(mid)){
            answer = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    printf("%d\n", answer);
    return 0;
}