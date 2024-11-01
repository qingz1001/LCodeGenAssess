#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int d1[n], d2[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &d1[i], &d2[i]);
    }
    
    int max_days = 0;
    for (int i = 0; i < n; i++) {
        max_days = (max_days < d1[i]) ? d1[i] : max_days;
        max_days = (max_days < d2[i]) ? d2[i] : max_days;
    }
    
    int left = max_days, right = max_days * m;
    while (left < right) {
        int mid = (left + right) / 2;
        int sum1 = 0, sum2 = 0;
        
        for (int i = 0; i < n; i++) {
            sum1 += mid / d1[i];
            sum2 += mid / d2[i];
        }
        
        if (sum1 >= m && sum2 >= m) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    printf("%d\n", left);
    return 0;
}