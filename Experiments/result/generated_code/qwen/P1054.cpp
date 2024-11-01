#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 55

typedef struct Node {
    char op;
    int val;
    struct Node *left, *right;
} Node;

Node* create_node(char op, int val, Node* left, Node* right) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->op = op;
    node->val = val;
    node->left = left;
    node->right = right;
    return node;
}

int evaluate(Node* root) {
    if (root == NULL) return 0;
    if (root->op == '\0') return root->val;
    switch (root->op) {
        case '+': return evaluate(root->left) + evaluate(root->right);
        case '-': return evaluate(root->left) - evaluate(root->right);
        case '*': return evaluate(root->left) * evaluate(root->right);
        case '^': return pow(evaluate(root->left), evaluate(root->right));
    }
    return 0;
}

Node* parse_expression(const char* expr, int* pos) {
    if (expr[*pos] == '(') (*pos)++;
    if (isdigit(expr[*pos])) {
        int val = 0;
        while (isdigit(expr[*pos])) {
            val = val * 10 + (expr[*pos] - '0');
            (*pos)++;
        }
        return create_node('\0', val, NULL, NULL);
    } else {
        char op = expr[*pos];
        (*pos)++;
        Node* left = parse_expression(expr, pos);
        Node* right = parse_expression(expr, pos);
        if (expr[*pos] == ')') (*pos)++;
        return create_node(op, 0, left, right);
    }
}

void free_tree(Node* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main() {
    char expr[MAX_LEN], opt[MAX_LEN][MAX_LEN];
    int n, pos = 0;
    scanf("%s", expr);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", opt[i]);
    }

    Node* root = parse_expression(expr, &pos);

    printf("A");
    for (int i = 1; i < n; i++) {
        pos = 0;
        Node* opt_root = parse_expression(opt[i], &pos);
        if (evaluate(root) == evaluate(opt_root)) {
            printf("%c", 'A' + i);
        }
        free_tree(opt_root);
    }
    printf("\n");

    free_tree(root);
    return 0;
}