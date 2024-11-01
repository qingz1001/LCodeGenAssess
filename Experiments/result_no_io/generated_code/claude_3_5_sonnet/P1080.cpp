#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1001
#define MAX_LEN 10000

typedef struct {
    int left;
    int right;
    int index;
} Minister;

Minister ministers[MAX_N];
char product[MAX_N][MAX_LEN];

int compare(const void *a, const void *b) {
    Minister *ma = (Minister *)a;
    Minister *mb = (Minister *)b;
    
    if (ma->left * mb->right > mb->left * ma->right) return -1;
    if (ma->left * mb->right < mb->left * ma->right) return 1;
    return 0;
}

void multiply(char *result, int num) {
    int carry = 0;
    for (int i = 0; i < MAX_LEN; i++) {
        int digit = (result[i] - '0') * num + carry;
        result[i] = digit % 10 + '0';
        carry = digit / 10;
    }
}

void divide(char *result, int num) {
    int remainder = 0;
    for (int i = MAX_LEN - 1; i >= 0; i--) {
        int current = remainder * 10 + (result[i] - '0');
        result[i] = current / num + '0';
        remainder = current % num;
    }
}

int main() {
    int n, king_left, king_right;
    scanf("%d", &n);
    scanf("%d %d", &king_left, &king_right);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &ministers[i].left, &ministers[i].right);
        ministers[i].index = i;
    }

    qsort(ministers, n, sizeof(Minister), compare);

    memset(product[0], '0', MAX_LEN);
    product[0][0] = '1';
    multiply(product[0], king_left);

    int max_reward = 0;
    for (int i = 0; i < n; i++) {
        strcpy(product[i+1], product[i]);
        multiply(product[i+1], ministers[i].left);

        char reward[MAX_LEN];
        strcpy(reward, product[i]);
        divide(reward, ministers[i].right);

        int current_reward = 0;
        for (int j = MAX_LEN - 1; j >= 0; j--) {
            if (reward[j] != '0') {
                current_reward = reward[j] - '0';
                break;
            }
        }

        if (current_reward > max_reward) {
            max_reward = current_reward;
        }
    }

    printf("%d\n", max_reward);
    return 0;
}