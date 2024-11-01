#include <stdio.h>
#include <math.h>
#include <float.h>

#define MAX_N 22
#define INF DBL_MAX

typedef struct {
    double x, y1, y2, y3, y4;
} Wall;

Wall walls[MAX_N];
int n;
double dp[MAX_N][4];

double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double min(double a, double b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf %lf %lf %lf %lf", &walls[i].x, &walls[i].y1, &walls[i].y2, &walls[i].y3, &walls[i].y4);
    }
    
    walls[0].x = 0;
    walls[0].y1 = walls[0].y2 = walls[0].y3 = walls[0].y4 = 5;
    walls[n+1].x = 10;
    walls[n+1].y1 = walls[n+1].y2 = walls[n+1].y3 = walls[n+1].y4 = 5;
    
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j < 4; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;
    
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j < 4; j++) {
            double y = (j < 2) ? walls[i].y1 : walls[i].y3;
            y = (j % 2 == 0) ? y : (j < 2 ? walls[i].y2 : walls[i].y4);
            
            for (int k = 0; k < 4; k++) {
                double prev_y = (k < 2) ? walls[i-1].y1 : walls[i-1].y3;
                prev_y = (k % 2 == 0) ? prev_y : (k < 2 ? walls[i-1].y2 : walls[i-1].y4);
                
                dp[i][j] = min(dp[i][j], dp[i-1][k] + dist(walls[i-1].x, prev_y, walls[i].x, y));
            }
        }
    }
    
    printf("%.2f\n", dp[n+1][0]);
    
    return 0;
}