#include <stdio.h>
#include <math.h>

int main() {
    int n, a[7], b[7], t, totalScore = 0, auScore;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &a[i], &b[i]);
        totalScore += b[i];
    }
    
    scanf("%d", &t);
    
    if (totalScore >= t) {
        printf("Already Au.\n");
        return 0;
    }
    
    auScore = t - totalScore;
    
    for (int i = 0; i < n; i++) {
        int remainingPoints = a[i] - b[i];
        int maxPoints = 100 / a[i];
        
        if (remainingPoints * maxPoints >= auScore) {
            printf("%d\n", ceil((double)auScore / maxPoints));
        } else {
            printf("NaN\n");
        }
    }
    
    return 0;
}