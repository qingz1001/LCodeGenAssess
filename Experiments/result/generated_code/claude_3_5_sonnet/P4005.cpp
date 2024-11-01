#include <stdio.h>
#include <string.h>

#define MAX_N 45
#define MAX_LINES 45

int T, n;
int lines[MAX_N];
int count[MAX_LINES];
int intersections[MAX_LINES][MAX_LINES];

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        memset(count, 0, sizeof(count));
        memset(intersections, 0, sizeof(intersections));
        
        for (int i = 0; i < n; i++) {
            scanf("%d", &lines[i]);
            count[lines[i]]++;
            
            for (int j = 0; j < i; j++) {
                if (lines[j] != lines[i]) {
                    intersections[lines[j]][lines[i]]++;
                    intersections[lines[i]][lines[j]]++;
                }
            }
        }
        
        int extra = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (count[i] > 0 && count[j] > 0) {
                    int needed = 1;
                    if (intersections[i][j] == 1) needed = 0;
                    else if (intersections[i][j] > 2) needed = intersections[i][j] - 2;
                    if (needed > extra) extra = needed;
                }
            }
        }
        
        printf("%d\n", extra);
    }
    return 0;
}