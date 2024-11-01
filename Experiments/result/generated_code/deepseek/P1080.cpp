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

    Minister ministers[1000];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &ministers[i].left, &ministers[i].right);
    }

    qsort(ministers, n, sizeof(Minister), compare);

    long long product = king.left;
    long long max_reward = 0;

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