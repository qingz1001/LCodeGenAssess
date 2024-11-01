#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 100
#define MAX_N 100
#define MAX_D 20000

int n, m;
int d1[MAX_N], d2[MAX_N];
int dp_prev[101][101];
int dp_curr[101][101];

int min(int a, int b) {
    return a < b ? a : b;
}

int is_possible(int day) {
    memset(dp_prev, 0, sizeof(dp_prev));
    dp_prev[0][0] = 1;
    
    for(int i = 0; i < n; i++) {
        memset(dp_curr, 0, sizeof(dp_curr));
        for(int x = 0; x <= m; x++) {
            for(int y = 0; y <= m; y++) {
                if(dp_prev[x][y]) {
                    // Try all possible assignments for this person
                    for(int a = 0; a <= min(m - x, day / d1[i]); a++) {
                        int remaining = day - a * d1[i];
                        if(remaining < 0) break;
                        int b_max = min(m - y, remaining / d2[i]);
                        for(int b = 0; b <= b_max; b++) {
                            int new_x = x + a;
                            int new_y = y + b;
                            dp_curr[new_x][new_y] = 1;
                        }
                    }
                }
            }
        }
        // Copy dp_curr to dp_prev
        for(int x = 0; x <= m; x++) {
            for(int y = 0; y <= m; y++) {
                dp_prev[x][y] = dp_curr[x][y];
            }
        }
    }
    return dp_prev[m][m];
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &d1[i], &d2[i]);
    }
    int left = 0, right = MAX_D, answer = MAX_D;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(is_possible(mid)){
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