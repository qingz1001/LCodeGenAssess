#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 50

typedef struct Node {
    char op;
    int val;
    struct Node *left, *right;
} Node;

Node* createNode(char op, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->op = op;
    newNode->val = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int evaluate(Node* node) {
    if (node == NULL)
        return 0;
    if (node->left == NULL && node->right == NULL)
        return node->val;
    int leftVal = evaluate(node->left);
    int rightVal = evaluate(node->right);
    switch (node->op) {
        case '+': return leftVal + rightVal;
        case '-': return leftVal - rightVal;
        case '*': return leftVal * rightVal;
        case '^': return (int)pow(leftVal, rightVal);
    }
    return 0;
}

Node* parseExpression(const char* expr, int* pos) {
    if (expr[*pos] == '(') {
        (*pos)++;
        Node* left = parseExpression(expr, pos);
        (*pos)++;
        Node* right = parseExpression(expr, pos);
        (*pos)++;
        return createNode(expr[*pos], 0, left, right);
    } else {
        int val = 0;
        while (isdigit(expr[*pos])) {
            val = val * 10 + (expr[*pos] - '0');
            (*pos)++;
        }
        return createNode('\0', val);
    }
}

void freeTree(Node* node) {
    if (node != NULL) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

int main() {
    char expression[MAX_LEN];
    scanf("%s", expression);

    int n;
    scanf("%d", &n);

    char options[27][MAX_LEN];
    for (int i = 0; i < n; i++) {
        scanf("%s", options[i]);
    }

    Node* targetTree = parseExpression(expression, 0);

    char result[27] = {0};
    int index = 0;

    for (int i = 0; i < n; i++) {
        Node* optionTree = parseExpression(options[i], 0);
        if (evaluate(targetTree) == evaluate(optionTree)) {
            result[index++] = 'A' + i;
        }
        freeTree(optionTree);
    }

    for (int i = 0; i < index; i++) {
        printf("%c", result[i]);
    }
    printf("\n");

    freeTree(targetTree);

    return 0;
}