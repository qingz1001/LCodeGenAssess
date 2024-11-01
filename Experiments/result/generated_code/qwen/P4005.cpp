#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        int lines[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", &lines[i]);
        }
        
        int min_stations = n;
        for (int i = 0; i < n; i++) {
            if (i > 0 && lines[i] == lines[i - 1]) {
                continue;
            }
            int count = 1;
            for (int j = i + 1; j < n; j++) {
                if (lines[j] == lines[i]) {
                    count++;
                }
            }
            if (count >= 3) {
                min_stations -= 2;
                break;
            } else if (count == 2) {
                min_stations--;
            }
        }
        
        printf("%d\n", min_stations);
    }
    return 0;
}