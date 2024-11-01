#include <stdio.h>
#include <stdbool.h>

#define MAX_N 20000
#define MAX_M 20000

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        int m, n;
        scanf("%d %d", &m, &n);
        
        bool classroom[MAX_M] = {false};
        bool student[MAX_N] = {false};
        
        for (int i = 0; i < m; i++) {
            int k;
            scanf("%d", &k);
            for (int j = 0; j < k; j++) {
                int p;
                scanf("%d", &p);
                student[p - 1] = true;
            }
            classroom[i] = (k > 0);
        }
        
        bool possible = true;
        for (int i = 0; i < m; i++) {
            if (!classroom[i]) {
                possible = false;
                break;
            }
        }
        
        if (possible) {
            for (int i = 0; i < n; i++) {
                if (!student[i]) {
                    possible = false;
                    break;
                }
            }
        }
        
        if (possible) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}