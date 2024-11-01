#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int main() {
    int n, m, r;
    scanf("%d %d %d", &n, &m, &r);
    
    int detectors[m][2];
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &detectors[i][0], &detectors[i][1]);
    }
    
    bool covered[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            covered[i][j] = false;
        }
    }
    
    for (int k = 0; k < m; k++) {
        int x = detectors[k][0] - 1;
        int y = detectors[k][1] - 1;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (sqrt((i - x) * (i - x) + (j - y) * (j - y)) <= r) {
                    covered[i][j] = true;
                }
            }
        }
    }
    
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (covered[i][j]) {
                count++;
            }
        }
    }
    
    printf("%d\n", count);
    
    return 0;
}