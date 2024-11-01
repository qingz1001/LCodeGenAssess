#include <stdio.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    int max_len = 0;
    for (int i = 0; i < n; i++) {
        int length;
        scanf("%d", &length);
        if (length < max_len) continue;
        max_len = length;
    }
    
    if (k == 0) {
        printf("0\n");
        return 0;
    }
    
    int left = 1, right = max_len;
    while (left < right) {
        int mid = (left + right + 1) / 2;
        int total_segments = 0;
        for (int i = 0; i < n; i++) {
            total_segments += max_len / mid;
        }
        if (total_segments >= k) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    
    printf("%d\n", left);
    return 0;
}