#include <stdio.h>
#include <math.h>
#include <float.h>

#define MAX_CITIES 100
#define MAX_AIRPORTS 4

typedef struct {
    double x, y;
} Point;

typedef struct {
    Point airports[MAX_AIRPORTS];
    double trainCost;
} City;

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double minCost(int S, double t, int A, int B, City cities[]) {
    double dp[MAX_CITIES][MAX_AIRPORTS];
    
    // Initialize dp array
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < MAX_AIRPORTS; j++) {
            dp[i][j] = (i == A - 1) ? 0 : DBL_MAX;
        }
    }
    
    // Dynamic programming
    for (int i = 0; i < S; i++) {
        if (i == A - 1) continue;
        for (int j = 0; j < MAX_AIRPORTS; j++) {
            for (int k = 0; k < MAX_AIRPORTS; k++) {
                double trainCost = cities[i].trainCost * distance(cities[i].airports[j], cities[i].airports[k]);
                for (int m = 0; m < S; m++) {
                    if (m == i) continue;
                    for (int n = 0; n < MAX_AIRPORTS; n++) {
                        double flightCost = t * distance(cities[m].airports[n], cities[i].airports[j]);
                        double totalCost = dp[m][n] + flightCost + trainCost;
                        if (totalCost < dp[i][k]) {
                            dp[i][k] = totalCost;
                        }
                    }
                }
            }
        }
    }
    
    // Find minimum cost to reach city B
    double minCost = DBL_MAX;
    for (int i = 0; i < MAX_AIRPORTS; i++) {
        if (dp[B - 1][i] < minCost) {
            minCost = dp[B - 1][i];
        }
    }
    
    return minCost;
}

int main() {
    int n;
    scanf("%d", &n);
    
    while (n--) {
        int S, A, B;
        double t;
        scanf("%d %lf %d %d", &S, &t, &A, &B);
        
        City cities[MAX_CITIES];
        for (int i = 0; i < S; i++) {
            for (int j = 0; j < 3; j++) {
                scanf("%lf %lf", &cities[i].airports[j].x, &cities[i].airports[j].y);
            }
            scanf("%lf", &cities[i].trainCost);
            
            // Calculate the fourth airport's coordinates
            cities[i].airports[3].x = cities[i].airports[0].x + cities[i].airports[2].x - cities[i].airports[1].x;
            cities[i].airports[3].y = cities[i].airports[0].y + cities[i].airports[2].y - cities[i].airports[1].y;
        }
        
        double result = minCost(S, t, A, B, cities);
        printf("%.1f\n", result);
    }
    
    return 0;
}