#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

int main() {
    int n;
    scanf("%d", &n);
    
    int hints[MAXN][MAXN];
    for (int i = 0; i < n; i++) {
        int j = 0;
        while (1) {
            scanf("%d", &hints[i][j]);
            if (hints[i][j] == 0) break;
            j++;
        }
    }
    
    int min_length = -1;
    
    for (int start = 1; start <= 9; start++) {
        for (int direction = -1; direction <= 1; direction += 2) {
            int length = 0;
            int seen[10] = {0};
            
            for (int i = 0; i < n; i++) {
                int pos = start;
                int found = 0;
                
                while (pos >= 1 && pos <= 9) {
                    if (!seen[hints[i][0]]) {
                        seen[hints[i][0]] = 1;
                        found = 1;
                        break;
                    }
                    pos += direction;
                }
                
                if (!found) break;
                
                for (int j = 1; j < hints[i][0]; j++) {
                    pos += direction;
                    if (pos < 1 || pos > 9) break;
                    if (!seen[hints[i][j]]) {
                        seen[hints[i][j]] = 1;
                        length++;
                    }
                }
                
                if (pos < 1 || pos > 9) break;
            }
            
            if (length > 0) {
                if (min_length == -1 || length < min_length) {
                    min_length = length;
                }
            }
        }
    }
    
    printf("%d\n", min_length);
    
    return 0;
}