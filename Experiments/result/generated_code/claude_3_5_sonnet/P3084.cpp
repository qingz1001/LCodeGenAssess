#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200001
#define MAX_M 100000

int N, M;
int a[MAX_M], b[MAX_M];
int spot[MAX_N];
int last[MAX_N];

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &a[i], &b[i]);
    }
    
    memset(spot, -1, sizeof(spot));
    memset(last, -1, sizeof(last));
    
    for (int i = 0; i < M; i++) {
        int left = a[i], right = b[i];
        if (spot[left] == 0 || spot[right] == 1) {
            printf("-1\n");
            return 0;
        }
        if (spot[left] == -1 && spot[right] == -1) {
            spot[left] = 1;
            spot[right] = 0;
            last[left] = right;
        } else if (spot[left] == -1) {
            spot[left] = 1;
            last[left] = right;
        } else if (spot[right] == -1) {
            spot[right] = 0;
            if (last[left] != -1 && last[left] < right) {
                printf("-1\n");
                return 0;
            }
            last[left] = right;
        } else {
            if (last[left] != right) {
                printf("-1\n");
                return 0;
            }
        }
    }
    
    int count = 0;
    for (int i = 1; i <= N; i++) {
        if (spot[i] == 1 || spot[i] == -1) {
            count++;
        }
    }
    
    printf("%d\n", count);
    return 0;
}