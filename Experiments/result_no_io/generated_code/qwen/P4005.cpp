#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        int lines[45];
        for (int i = 0; i < n; i++) {
            scanf("%d", &lines[i]);
        }
        
        // Initialize the minimum number of stations to a large value
        int min_stations = n * (n - 1) / 2; // Upper bound
        
        // Iterate over all possible pairs of stations
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (lines[i] == lines[j]) {
                    // If two stations have the same line, they share at least one station
                    min_stations--;
                }
            }
        }
        
        printf("%d\n", min_stations);
    }
    return 0;
}