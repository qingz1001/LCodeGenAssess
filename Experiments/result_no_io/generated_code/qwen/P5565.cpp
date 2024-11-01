#include <stdio.h>
#include <string.h>

#define MOD 998244353

typedef long long ll;

struct Node {
    int type;
    char ch;
    struct Node *left, *right;
};

int evaluate(struct Node *root) {
    if (root->type == 0) return root->ch - '0';
    if (root->type == 1) return evaluate(root->left);
    if (root->type == 2) return evaluate(root->left) & evaluate(root->right);
    if (root->type == 3) return evaluate(root->left) | evaluate(root->right);
    if (root->type == 4) return evaluate(root->left) ^ evaluate(root->right);
}

void update(struct Node **root, int a, char b) {
    if (*root == NULL) return;
    if (a == 0 && (*root)->type != 0) {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->type = 0;
        newNode->ch = b;
        newNode->left = newNode->right = NULL;
        *root = newNode;
    } else if (a > 0) {
        if ((*root)->type == 0) {
            struct Node *temp = *root;
            *root = (struct Node *)malloc(sizeof(struct Node));
            (*root)->type = temp->type;
            (*root)->ch = temp->ch;
            (*root)->left = (*root)->right = NULL;
            free(temp);
        }
        if ((*root)->type == 1) update(&(*root)->left, a - 1, b);
        else if ((*root)->type == 2) update(&(*root)->left, a - 1, b);
        else if ((*root)->type == 3) update(&(*root)->left, a - 1, b);
        else if ((*root)->type == 4) update(&(*root)->left, a - 1, b);
    }
}

ll count_ways(struct Node *root) {
    if (!root) return 0;
    if (root->type == 0) return root->ch == '1' ? 1 : 0;
    ll left = count_ways(root->left), right = count_ways(root->right);
    if (root->type == 2) return (left * right) % MOD;
    if (root->type == 3) return (left + right - left * right) % MOD;
    if (root->type == 4) return (left + right - left * right) % MOD;
    return 0;
}

int main() {
    int m;
    scanf("%d", &m);
    char expr[400005];
    scanf("%s", expr);

    struct Node *root = NULL;
    for (int i = 0; expr[i]; i++) {
        if (expr[i] == '(') {
            struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
            newNode->type = 1;
            newNode->left = newNode->right = NULL;
            update(&root, i, expr[i]);
        } else if (expr[i] == ')') {
            update(&root, i, expr[i]);
        } else if (expr[i] == '&' || expr[i] == '|' || expr[i] == '^') {
            struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
            newNode->type = expr[i] == '&' ? 2 : (expr[i] == '|' ? 3 : 4);
            newNode->left = newNode->right = NULL;
            update(&root, i, expr[i]);
        } else {
            update(&root, i, expr[i]);
        }
    }

    while (m--) {
        int a;
        char b;
        scanf("%d %c", &a, &b);
        update(&root, a - 1, b);
        printf("%lld\n", count_ways(root));
    }

    return 0;
}