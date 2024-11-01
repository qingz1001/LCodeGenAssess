#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

typedef struct {
    int a;
    int h;
    long long c;
} Node;

Node nodes[MAXN];
int n;

long long min(long long a, long long b) {
    return a < b ? a : b;
}

long long max(long long a, long long b) {
    return a > b ? a : b;
}

void merge(int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Node L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = nodes[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = nodes[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].a <= R[j].a) {
            nodes[k++] = L[i++];
        } else {
            nodes[k++] = R[j++];
        }
    }

    while (i < n1)
        nodes[k++] = L[i++];

    while (j < n2)
        nodes[k++] = R[j++];
}

void mergeSort(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(left, mid);
        mergeSort(mid + 1, right);

        merge(left, mid, right);
    }
}

long long solve() {
    mergeSort(0, n - 1);

    long long cost = 0;

    for (int i = 0; i < n; i++) {
        if (nodes[i].h > nodes[i].a) {
            cost += nodes[i].c * (nodes[i].h - nodes[i].a);
        }
    }

    return cost;
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d %lld", &nodes[i].a, &nodes[i].h, &nodes[i].c);
    }

    printf("%lld\n", solve());

    return 0;
}