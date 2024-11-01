#include <stdio.h>
#include <limits.h>

int main() {
    int n, S, T;
    scanf("%d %d %d", &n, &S, &T);
    
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    double max_avg = INT_MIN;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            if (j - i + 1 >= S && j - i + 1 <= T) {
                sum += a[j];
                double avg = (double)sum / (j - i + 1);
                if (avg > max_avg) {
                    max_avg = avg;
                }
            }
        }
    }
    
    printf("%.3f\n", max_avg);
    return 0;
}