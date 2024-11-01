#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

typedef struct {
    int left, right;
} Segment;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *values = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &values[i]);
    }
    
    Segment *segments = (Segment *)malloc(m * sizeof(Segment));
    for (int i = 0; i < m; i++) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int u, v, d;
            scanf("%d %d %d", &u, &v, &d);
            segments[i].left = u - 1;
            segments[i].right = v - 1;
        } else if (type == 2) {
            int l, r;
            scanf("%d %d", &l, &r);
            segments[i].left = l - 1;
            segments[i].right = r - 1;
        }
    }
    
    long long result = 0;
    for (int i = 0; i < m; i++) {
        if (segments[i].left <= segments[i].right) {
            int length = segments[i].right - segments[i].left + 1;
            if (length >= 1 && length <= n) {
                for (int j = segments[i].left; j <= segments[i].right; j++) {
                    result += values[j];
                    result %= MOD;
                }
            }
        }
    }
    
    printf("%lld\n", result);
    
    free(values);
    free(segments);
    
    return 0;
}