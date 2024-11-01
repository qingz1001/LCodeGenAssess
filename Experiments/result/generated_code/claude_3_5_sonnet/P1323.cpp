#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_K 30000
#define MAX_DIGITS 100000

long long elements[MAX_K];
char number[MAX_DIGITS + 1];
char result[MAX_DIGITS + 1];

int compare(const void *a, const void *b) {
    return (*(long long*)a - *(long long*)b);
}

void generate_elements(int k) {
    elements[0] = 1;
    int count = 1;
    for (int i = 0; count < k; i++) {
        if (2 * elements[i] + 1 <= 1000000000000000000LL) {
            elements[count++] = 2 * elements[i] + 1;
        }
        if (count < k && 4 * elements[i] + 5 <= 1000000000000000000LL) {
            elements[count++] = 4 * elements[i] + 5;
        }
    }
    qsort(elements, k, sizeof(long long), compare);
}

void create_number(int k) {
    int pos = 0;
    for (int i = 0; i < k; i++) {
        pos += sprintf(number + pos, "%lld", elements[i]);
    }
}

void delete_digits(int m) {
    int len = strlen(number);
    int i = 0, j = 0;
    
    for (i = 0; i < len; i++) {
        while (j > 0 && m > 0 && result[j-1] < number[i]) {
            j--;
            m--;
        }
        if (j < len - m) {
            result[j++] = number[i];
        } else {
            m--;
        }
    }
    result[j] = '\0';
}

int main() {
    int k, m;
    scanf("%d %d", &k, &m);

    generate_elements(k);
    create_number(k);
    
    printf("%s\n", number);
    
    delete_digits(m);
    printf("%s\n", result);

    return 0;
}