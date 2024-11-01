#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1005
#define MAX_LEN 10005

typedef struct {
    int left;
    int right;
} Minister;

Minister ministers[MAX_N];
char product[MAX_N][MAX_LEN];

int cmp(const void *a, const void *b) {
    Minister *m1 = (Minister *)a;
    Minister *m2 = (Minister *)b;
    return m2->left * m1->right - m1->left * m2->right;
}

void multiply(char *res, int num) {
    int carry = 0;
    for (int i = 0; i < MAX_LEN; i++) {
        int digit = (res[i] - '0') * num + carry;
        res[i] = digit % 10 + '0';
        carry = digit / 10;
    }
}

void divide(char *res, int num) {
    int remainder = 0;
    for (int i = MAX_LEN - 1; i >= 0; i--) {
        int digit = remainder * 10 + (res[i] - '0');
        res[i] = digit / num + '0';
        remainder = digit % num;
    }
}

int main() {
    int n, king_left, king_right;
    scanf("%d", &n);
    scanf("%d %d", &king_left, &king_right);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &ministers[i].left, &ministers[i].right);
    }

    qsort(ministers, n, sizeof(Minister), cmp);

    memset(product, '0', sizeof(product));
    product[0][0] = '1';

    multiply(product[0], king_left);
    int max_reward = 0;

    for (int i = 0; i < n; i++) {
        char temp[MAX_LEN];
        memcpy(temp, product[i], sizeof(temp));
        divide(temp, ministers[i].right);

        int reward = 0;
        for (int j = MAX_LEN - 1; j >= 0; j--) {
            if (temp[j] != '0') {
                reward = temp[j] - '0';
                break;
            }
        }

        if (reward > max_reward) {
            max_reward = reward;
        }

        if (i < n - 1) {
            memcpy(product[i + 1], product[i], sizeof(product[i]));
            multiply(product[i + 1], ministers[i].left);
        }
    }

    printf("%d\n", max_reward);

    return 0;
}