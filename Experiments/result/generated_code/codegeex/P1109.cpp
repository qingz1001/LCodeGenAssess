#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int students[50];
    for (int i = 0; i < n; i++) {
        scanf("%d", &students[i]);
    }
    
    int L, R;
    scanf("%d %d", &L, &R);
    
    int total = 0;
    for (int i = 0; i < n; i++) {
        if (students[i] < L) {
            total += L - students[i];
        } else if (students[i] > R) {
            total += students[i] - R;
        }
    }
    
    int min_exchanges = 0;
    for (int i = 0; i < n; i++) {
        if (students[i] > R) {
            min_exchanges += students[i] - R;
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (students[i] < L) {
            min_exchanges += L - students[i];
        }
    }
    
    if (min_exchanges <= total) {
        printf("%d\n", total);
    } else {
        printf("-1\n");
    }
    
    return 0;
}