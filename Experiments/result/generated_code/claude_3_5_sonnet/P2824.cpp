#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define BLOCK_SIZE 320

int n, m, q;
int arr[MAXN], sorted[MAXN];
int block[MAXN / BLOCK_SIZE + 5];
int block_size, block_count;

void init() {
    block_size = BLOCK_SIZE;
    block_count = (n - 1) / block_size + 1;
    for (int i = 0; i < n; i++) {
        block[i / block_size] |= 1 << (arr[i] - 1);
    }
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int compare_desc(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

void sort_range(int l, int r, int type) {
    int left_block = l / block_size;
    int right_block = r / block_size;

    if (left_block == right_block) {
        for (int i = l; i <= r; i++) {
            sorted[i - l] = arr[i];
        }
        if (type == 0) {
            qsort(sorted, r - l + 1, sizeof(int), compare);
        } else {
            qsort(sorted, r - l + 1, sizeof(int), compare_desc);
        }
        for (int i = l; i <= r; i++) {
            arr[i] = sorted[i - l];
        }
        block[left_block] = 0;
        for (int i = left_block * block_size; i < (left_block + 1) * block_size && i < n; i++) {
            block[left_block] |= 1 << (arr[i] - 1);
        }
    } else {
        for (int i = left_block + 1; i < right_block; i++) {
            block[i] = (1 << n) - 1;
        }
        for (int i = l; i < (left_block + 1) * block_size; i++) {
            sorted[i - l] = arr[i];
        }
        for (int i = right_block * block_size; i <= r; i++) {
            sorted[i - l] = arr[i];
        }
        int len = r - l + 1 - (right_block - left_block - 1) * block_size;
        if (type == 0) {
            qsort(sorted, len, sizeof(int), compare);
        } else {
            qsort(sorted, len, sizeof(int), compare_desc);
        }
        int idx = 0;
        for (int i = l; i < (left_block + 1) * block_size; i++) {
            arr[i] = sorted[idx++];
        }
        for (int i = right_block * block_size; i <= r; i++) {
            arr[i] = sorted[idx++];
        }
        block[left_block] = 0;
        block[right_block] = 0;
        for (int i = left_block * block_size; i < (left_block + 1) * block_size && i < n; i++) {
            block[left_block] |= 1 << (arr[i] - 1);
        }
        for (int i = right_block * block_size; i < (right_block + 1) * block_size && i < n; i++) {
            block[right_block] |= 1 << (arr[i] - 1);
        }
    }
}

int query(int pos) {
    int b = pos / block_size;
    for (int i = 1; i <= n; i++) {
        if (block[b] & (1 << (i - 1))) {
            for (int j = b * block_size; j < (b + 1) * block_size && j < n; j++) {
                if (arr[j] == i && j == pos) {
                    return i;
                }
            }
        }
    }
    return -1;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    init();

    int op, l, r;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &op, &l, &r);
        sort_range(l - 1, r - 1, op);
    }

    scanf("%d", &q);
    printf("%d\n", query(q - 1));

    return 0;
}