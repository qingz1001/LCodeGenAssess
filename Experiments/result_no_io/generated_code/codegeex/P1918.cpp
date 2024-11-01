#include <stdio.h>

int main() {
    int n, Q, m;
    scanf("%d", &n);
    
    int bottles[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &bottles[i]);
    }
    
    scanf("%d", &Q);
    
    for (int i = 0; i < Q; i++) {
        scanf("%d", &m);
        
        int position = 0;
        for (int j = 0; j < n; j++) {
            if (bottles[j] == m) {
                position = j + 1;
                break;
            }
        }
        
        printf("%d\n", position);
    }
    
    return 0;
}