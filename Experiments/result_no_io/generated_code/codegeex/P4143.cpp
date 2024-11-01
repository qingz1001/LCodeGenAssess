#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXQ 100005

char str[MAXN];
int value[MAXN];
int SA[MAXN], RA[MAXN], temp[MAXN], temp2[MAXN], C[MAXN];
int rank[MAXN], height[MAXN];
int st[MAXN][18], lg[MAXN];
int n, m;

void build_SA() {
    int i, j, p;
    for (i = 0; i < m; i++) C[i] = 0;
    for (i = 0; i < n; i++) C[RA[i] = str[i]]++;
    for (i = 1; i < m; i++) C[i] += C[i - 1];
    for (i = n - 1; i >= 0; i--) SA[--C[RA[i]]] = i;
    for (p = j = 1; p < n; j <<= 1, m = p) {
        for (p = 0, i = n - j; i < n; i++) temp[p++] = i;
        for (i = 0; i < n; i++) if (SA[i] >= j) temp[p++] = SA[i] - j;
        for (i = 0; i < n; i++) temp2[i] = RA[temp[i]];
        for (i = 0; i < m; i++) C[i] = 0;
        for (i = 0; i < n; i++) C[temp2[i]]++;
        for (i = 1; i < m; i++) C[i] += C[i - 1];
        for (i = n - 1; i >= 0; i--) SA[--C[temp2[i]]] = temp[i];
        for (i = 0; i < n; i++) temp[i] = RA[i];
        for (p = RA[SA[0]] = 0, i = 1; i < n; i++) {
            if (temp[SA[i]] == temp[SA[i - 1]] && temp[SA[i] + j] == temp[SA[i - 1] + j]) {
                RA[SA[i]] = p;
            } else {
                p++;
                RA[SA[i]] = p;
            }
        }
    }
}

void build_height() {
    int i, j, k = 0;
    for (i = 0; i < n; i++) rank[SA[i]] = i;
    for (i = 0; i < n; height[rank[i++]] = k)
        for (k ? k-- : 0, j = SA[rank[i] - 1]; str[i + k] == str[j + k]; k++);
}

void build_ST() {
    int i, j;
    for (i = 0; i < n; i++) st[i][0] = height[i];
    for (i = 1; (1 << i) <= n; i++)
        for (j = 0; j + (1 << i) <= n; j++)
            st[j][i] = (st[j][i - 1] < st[j + (1 << (i - 1))][i - 1]) ? st[j][i - 1] : st[j + (1 << (i - 1))][i - 1];
}

int RMQ(int l, int r) {
    int k = lg[r - l + 1];
    return (st[l][k] < st[r - (1 << k) + 1][k]) ? st[l][k] : st[r - (1 << k) + 1][k];
}

int main() {
    int i, j, k, ans = 0;
    scanf("%s", str);
    n = strlen(str);
    for (i = 0; i < n; i++) scanf("%d", &value[i]);
    for (i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    m = 300;
    build_SA();
    build_height();
    build_ST();
    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
            k = RMQ(i, j);
            if (k == value[i] + (j - i + 1)) {
                printf("%d %d\n", i + 1, j + 1);
                ans++;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}