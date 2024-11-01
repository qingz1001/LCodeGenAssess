#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_K 30000

typedef struct {
    int val;
    int idx;
} Element;

int cmp(const void *a, const void *b) {
    return ((Element *)a)->val - ((Element *)b)->val;
}

void generate_elements(Element *elements, int k) {
    elements[0].val = 1;
    elements[0].idx = 0;
    int count = 1;
    for (int i = 0; i < count && count < k; i++) {
        elements[count].val = 2 * elements[i].val + 1;
        elements[count].idx = count;
        count++;
        if (count >= k) break;
        elements[count].val = 4 * elements[i].val + 5;
        elements[count].idx = count;
        count++;
    }
    qsort(elements, k, sizeof(Element), cmp);
}

void delete_digits(char *num, int m) {
    int len = strlen(num);
    int i = 0, j = 0;
    while (m > 0 && j < len) {
        if (num[j] < num[j + 1]) {
            for (int k = j; k < len - 1; k++) {
                num[k] = num[k + 1];
            }
            m--;
            len--;
            if (j > 0) j--;
        } else {
            j++;
        }
    }
    num[len] = '\0';
}

int main() {
    int k, m;
    scanf("%d %d", &k, &m);

    Element elements[MAX_K];
    generate_elements(elements, k);

    char num[MAX_K * 5];
    num[0] = '\0';
    for (int i = 0; i < k; i++) {
        char temp[10];
        sprintf(temp, "%d", elements[i].val);
        strcat(num, temp);
    }

    printf("%s\n", num);
    delete_digits(num, m);
    printf("%s\n", num);

    return 0;
}