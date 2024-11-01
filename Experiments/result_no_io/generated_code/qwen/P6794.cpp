#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

typedef struct Node {
    int height;
    struct Node* left;
    struct Node* right;
} Node;

Node* create_node(int height) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->height = height;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void update_height(Node** root, int pos, int new_height, int version) {
    if (*root == NULL) {
        *root = create_node(new_height);
    } else {
        Node* old_root = *root;
        *root = create_node(old_root->height);
        (*root)->left = old_root->left;
        (*root)->right = old_root->right;
        if (pos == 0) {
            (*root)->height = new_height;
        } else {
            update_height(&((*root)->left), pos - 1, new_height, version);
        }
    }
}

int query_height(Node* root, int pos) {
    if (root == NULL) {
        return 0;
    } else {
        if (pos == 0) {
            return root->height;
        } else {
            return query_height(root->left, pos - 1);
        }
    }
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    int* heights = (int*)malloc((n - 1) * sizeof(int));
    for (int i = 0; i < n - 1; i++) {
        scanf("%d", &heights[i]);
    }

    Node* root = NULL;
    for (int i = 0; i < n - 1; i++) {
        update_height(&root, i, heights[i], 0);
    }

    for (int i = 0; i < q; i++) {
        int type, x, y, z;
        scanf("%d", &type);
        switch (type) {
            case 0:
                scanf("%d %d %d", &x, &y, &z);
                update_height(&root, x, z, i + 1);
                break;
            case 1:
                scanf("%d %d", &x, &y);
                // No action needed as the problem does not require simulating water flow
                break;
            case 2:
                scanf("%d %d %d", &x, &y, &z);
                update_height(&root, x, z, i + 1);
                break;
            case 3:
                scanf("%d %d", &x, &y);
                printf("%d\n", query_height(root, x));
                break;
        }
    }

    free(heights);
    return 0;
}