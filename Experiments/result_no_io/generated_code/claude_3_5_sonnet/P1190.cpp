#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define MAX_M 100

int n, m;
int water[MAX_N];
int taps[MAX_M];

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &water[i]);
    }
    
    for (int i = 0; i < m; i++) {
        taps[i] = water[i];
    }
    
    int current = m;
    int total_time = 0;
    
    while (current < n || m > 0) {
        qsort(taps, m, sizeof(int), compare);
        int min_time = taps[0];
        total_time += min_time;
        
        for (int i = 0; i < m; i++) {
            taps[i] -= min_time;
            if (taps[i] == 0 && current < n) {
                taps[i] = water[current];
                current++;
            }
        }
        
        while (m > 0 && taps[m-1] == 0) {
            m--;
        }
    }
    
    printf("%d\n", total_time);
    
    return 0;
}