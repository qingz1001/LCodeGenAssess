#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int max_len = 1;
    int current_len = 1;
    
    for (int i = 1; i < n; i++) {
        if (a[i] == a[i - 1] + 1) {
            current_len++;
            if (current_len > max_len) {
                max_len = current_len;
            }
        } else {
            current_len = 1;
        }
    }
    
    printf("%d\n", max_len);
    
    return 0;
}