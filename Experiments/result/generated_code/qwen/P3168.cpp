#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 100005

typedef struct {
    int start;
    int end;
    int priority;
} Task;

Task tasks[MAXM];
int queries[MAXN][4];
int results[MAXN];

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &tasks[i].start, &tasks[i].end, &tasks[i].priority);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &queries[i][0], &queries[i][1], &queries[i][2], &queries[i][3]);
    }

    int pre = 1;

    for (int x = 0; x < n; x++) {
        int xi = queries[x][0];
        int ai = queries[x][1];
        int bi = queries[x][2];
        int ci = queries[x][3];

        int ki = 1 + (ai * pre + bi) % ci;

        int runningTasks[MAXM];
        int count = 0;

        for (int i = 0; i < m; i++) {
            if (xi >= tasks[i].start && xi <= tasks[i].end) {
                runningTasks[count++] = tasks[i].priority;
            }
        }

        mergeSort(runningTasks, 0, count - 1);

        int sum = 0;
        for (int i = 0; i < ki && i < count; i++) {
            sum += runningTasks[i];
        }

        results[x] = sum;
        pre = sum;
    }

    for (int i = 0; i < n; i++) {
        printf("%d\n", results[i]);
    }

    return 0;
}