#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100005
#define PI 3.14159265358979323846

typedef long long ll;
typedef double db;

int n, k, r, L;
int p[MAX_N];
int ans[MAX_N];

db calc(int i, int j) {
    db d = (p[j] - p[i] + L) % L;
    if (d > L / 2) d = L - d;
    if (d >= 2 * r) return 2 * PI * r * r;
    db theta = 2 * acos(d / (2.0 * r));
    return 2 * PI * r * r - r * r * (theta - sin(theta));
}

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    scanf("%d%d%d%d", &n, &k, &r, &L);
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    db max_area = 0;
    for (int start = 0; start < n; start++) {
        db area = 0;
        int cnt = 0;
        int tmp[MAX_N];
        for (int i = 0; i < n && cnt < k; i++) {
            int cur = (start + i) % n;
            db new_area = calc(start, cur);
            if (new_area > area) {
                area = new_area;
                tmp[cnt++] = cur + 1;
            }
        }
        if (area > max_area) {
            max_area = area;
            for (int i = 0; i < k; i++) {
                ans[i] = tmp[i];
            }
        }
    }

    qsort(ans, k, sizeof(int), cmp);
    for (int i = 0; i < k; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");

    return 0;
}