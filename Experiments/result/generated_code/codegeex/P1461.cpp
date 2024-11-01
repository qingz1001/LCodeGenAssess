#include <stdio.h>
#include <stdlib.h>

int n, b, d;
int count = 0;
int *arr;

int hamming_distance(int x, int y) {
    int dist = 0;
    while (x > 0 || y > 0) {
        if ((x & 1) != (y & 1)) dist++;
        x >>= 1;
        y >>= 1;
    }
    return dist;
}

int is_valid(int x) {
    for (int i = 0; i < count; i++) {
        if (hamming_distance(x, arr[i]) < d) return 0;
    }
    return 1;
}

void generate_codes(int x, int bit) {
    if (bit == b) {
        if (count < n) {
            arr[count++] = x;
        }
        return;
    }
    generate_codes(x, bit + 1);
    if (count < n) {
        x |= (1 << bit);
        generate_codes(x, bit + 1);
    }
}

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d %d %d", &n, &b, &d);
    arr = (int*)malloc(n * sizeof(int));
    generate_codes(0, 0);
    qsort(arr, count, sizeof(int), compare);
    for (int i = 0; i < count; i++) {
        printf("%d ", arr[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    free(arr);
    return 0;
}