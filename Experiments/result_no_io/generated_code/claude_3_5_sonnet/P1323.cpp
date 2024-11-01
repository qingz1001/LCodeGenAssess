#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_K 30000
#define MAX_LEN 100000

long long set[MAX_K];
char num[MAX_LEN], result[MAX_LEN];

int cmp(const void *a, const void *b) {
    return (*(long long*)a - *(long long*)b);
}

void generate_set(int k) {
    set[0] = 1;
    int index = 1;
    for (int i = 0; i < k && index < k; i++) {
        if (2 * set[i] + 1 <= 1000000000000000000LL) {
            set[index++] = 2 * set[i] + 1;
        }
        if (index < k && 4 * set[i] + 5 <= 1000000000000000000LL) {
            set[index++] = 4 * set[i] + 5;
        }
    }
    qsort(set, k, sizeof(long long), cmp);
}

void to_string(int k) {
    int len = 0;
    for (int i = 0; i < k; i++) {
        len += sprintf(num + len, "%lld", set[i]);
    }
}

void delete_digits(int m) {
    int len = strlen(num);
    int top = 0, i = 0;
    
    for (; i < len; i++) {
        while (top > 0 && m > 0 && result[top-1] < num[i]) {
            top--;
            m--;
        }
        if (top < len - m) {
            result[top++] = num[i];
        } else {
            m--;
        }
    }
    result[top] = '\0';
}

int main() {
    int k, m;
    scanf("%d %d", &k, &m);
    
    generate_set(k);
    to_string(k);
    
    printf("%s\n", num);
    
    delete_digits(m);
    printf("%s\n", result);
    
    return 0;
}