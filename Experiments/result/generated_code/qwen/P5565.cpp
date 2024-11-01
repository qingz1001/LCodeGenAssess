#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 998244353

typedef struct {
    int type;
    union {
        char var;
        int value;
        struct {
            int left, right;
        } children;
    };
} Node;

int evaluate(Node* node, int* values) {
    switch (node->type) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '&':
            return evaluate(node->children.left, values) & evaluate(node->children.right, values);
        case '|':
            return evaluate(node->children.left, values) | evaluate(node->children.right, values);
        case '^':
            return evaluate(node->children.left, values) ^ evaluate(node->children.right, values);
        default:
            return values[node->var - 'a'];
    }
}

void update(Node* node, int pos, char new_val, int* variables) {
    if (node->type == '0' || node->type == '1') {
        return;
    }
    if (node->type >= 'a' && node->type <= 'z') {
        variables[node->type - 'a'] = new_val - '0';
        return;
    }
    update(node->children.left, pos, new_val, variables);
    update(node->children.right, pos, new_val, variables);
}

long long count_ones(int* values, int n) {
    long long count = 0;
    for (int i = 0; i < (1 << n); ++i) {
        int val = 1;
        for (int j = 0; j < n; ++j) {
            if ((i >> j) & 1) {
                val &= values[j];
            }
        }
        count += val;
    }
    return count;
}

int main() {
    int m;
    scanf("%d", &m);
    char expression[400001];
    scanf("%s", expression);

    int n = 0;
    int len = strlen(expression);
    Node* nodes = (Node*)malloc(len * sizeof(Node));
    int variables[26] = {0};

    int index = 0;
    for (int i = 0; i < len; ++i) {
        if (expression[i] == '(') {
            nodes[index].type = '(';
        } else if (expression[i] == ')') {
            nodes[index].type = ')';
        } else if (expression[i] == '&' || expression[i] == '|' || expression[i] == '^') {
            nodes[index].type = expression[i];
        } else if (expression[i] == '0' || expression[i] == '1') {
            nodes[index].type = expression[i];
        } else {
            nodes[index].type = expression[i];
            n++;
        }
        index++;
    }

    for (int i = 0; i < m; ++i) {
        int pos;
        char new_val;
        scanf("%d %c", &pos, &new_val);
        update(&nodes[pos], pos, new_val, variables);
        printf("%lld\n", count_ones(variables, n) % MOD);
    }

    free(nodes);
    return 0;
}