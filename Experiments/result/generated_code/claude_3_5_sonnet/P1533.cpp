#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 300005
#define MAX_M 50005

typedef struct {
    int value;
    int index;
} Dog;

int n, m;
Dog dogs[MAX_N];
int sorted_dogs[MAX_N];

int cmp(const void *a, const void *b) {
    return ((Dog*)a)->value - ((Dog*)b)->value;
}

int cmp_int(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

void build_sorted_array() {
    qsort(dogs, n, sizeof(Dog), cmp);
    for (int i = 0; i < n; i++) {
        sorted_dogs[dogs[i].index] = i + 1;
    }
}

int query(int l, int r, int k) {
    int temp[MAX_N];
    int count = 0;
    for (int i = l - 1; i < r; i++) {
        temp[count++] = sorted_dogs[i];
    }
    qsort(temp, count, sizeof(int), cmp_int);
    return dogs[temp[k-1] - 1].value;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &dogs[i].value);
        dogs[i].index = i;
    }
    
    build_sorted_array();
    
    for (int i = 0; i < m; i++) {
        int l, r, k;
        scanf("%d %d %d", &l, &r, &k);
        printf("%d\n", query(l, r, k));
    }
    
    return 0;
}