#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int left;
    int right;
} Minister;

int compare(const void *a, const void *b) {
    Minister *m1 = (Minister *)a;
    Minister *m2 = (Minister *)b;
    return (m1->left * m1->right) - (m2->left * m2->right);
}

int main() {
    int n;
    scanf("%d", &n);

    Minister king;
    scanf("%d %d", &king.left, &king.right);

    Minister ministers[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &ministers[i].left, &ministers[i].right);
    }

    // Sort ministers based on the product of their left and right hands
    qsort(ministers, n, sizeof(Minister), compare);

    // Calculate the maximum reward
    long long max_reward = 0;
    long long product = king.left;

    for (int i = 0; i < n; i++) {
        long long reward = product / ministers[i].right;
        if (reward > max_reward) {
            max_reward = reward;
        }
        product *= ministers[i].left;
    }

    printf("%lld\n", max_reward);

    return 0;
}