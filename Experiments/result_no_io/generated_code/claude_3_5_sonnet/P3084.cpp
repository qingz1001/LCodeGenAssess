#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200001
#define MAX_M 100000

int N, M;
int a[MAX_M], b[MAX_M];
int spotted[MAX_N];
int left_bound[MAX_N], right_bound[MAX_N];

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &a[i], &b[i]);
    }
    
    memset(left_bound, -1, sizeof(left_bound));
    memset(right_bound, -1, sizeof(right_bound));
    
    for (int i = 0; i < M; i++) {
        if (left_bound[a[i]] == -1 || left_bound[a[i]] < b[i]) {
            left_bound[a[i]] = b[i];
        }
        if (right_bound[b[i]] == -1 || right_bound[b[i]] > a[i]) {
            right_bound[b[i]] = a[i];
        }
    }
    
    int count = 0;
    int last_spotted = 0;
    
    for (int i = 1; i <= N; i++) {
        if (left_bound[i] != -1) {
            if (i > last_spotted) {
                count++;
                last_spotted = left_bound[i];
            } else if (left_bound[i] > last_spotted) {
                printf("-1\n");
                return 0;
            }
        }
        if (right_bound[i] != -1) {
            if (i > last_spotted) {
                count++;
                last_spotted = i;
            }
        }
    }
    
    printf("%d\n", count);
    return 0;
}