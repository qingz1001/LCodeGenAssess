#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

int main() {
    int n;
    scanf("%d", &n);
    
    int ropes[MAXN][2];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &ropes[i][0], &ropes[i][1]);
    }
    
    // Sort the endpoints to ensure they are in order
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (ropes[i][0] > ropes[j][0]) {
                int temp[2] = ropes[i];
                ropes[i] = ropes[j];
                ropes[j] = temp;
            } else if (ropes[i][0] == ropes[j][0] && ropes[i][1] > ropes[j][1]) {
                int temp[2] = ropes[i];
                ropes[i] = ropes[j];
                ropes[j] = temp;
            }
        }
    }
    
    int cuts = 0;
    int last_cut = 0;
    for (int i = 0; i < n; ++i) {
        if (ropes[i][0] > last_cut) {
            cuts++;
            last_cut = ropes[i][1];
        }
    }
    
    printf("%d\n", cuts);
    
    return 0;
}