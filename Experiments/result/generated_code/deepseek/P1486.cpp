#include <stdio.h>
#include <stdlib.h>

#define MAX_N 300005

typedef struct Node {
    int salary;
    struct Node *left, *right;
    int height;
    int size;
} Node;

Node *newNode(int salary) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->salary = salary;
    node->left = node->right = NULL;
    node->height = 1;
    node->size = 1;
    return node;
}

int height(Node *N) {
    if (N == NULL) return 0;
    return N->height;
}

int size(Node *N) {
    if (N == NULL) return 0;
    return N->size;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    y->size = size(y->left) + size(y->right) + 1;
    x->size = size(x->left) + size(x->right) + 1;

    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    x->size = size(x->left) + size(x->right) + 1;
    y->size = size(y->left) + size(y->right) + 1;

    return y;
}

int getBalance(Node *N) {
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}

Node *insert(Node *node, int salary) {
    if (node == NULL) return newNode(salary);

    if (salary < node->salary)
        node->left = insert(node->left, salary);
    else if (salary > node->salary)
        node->right = insert(node->right, salary);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    node->size = 1 + size(node->left) + size(node->right);

    int balance = getBalance(node);

    if (balance > 1 && salary < node->left->salary)
        return rightRotate(node);

    if (balance < -1 && salary > node->right->salary)
        return leftRotate(node);

    if (balance > 1 && salary > node->left->salary) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && salary < node->right->salary) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node *minValueNode(Node *node) {
    Node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

Node *deleteNode(Node *root, int salary) {
    if (root == NULL) return root;

    if (salary < root->salary)
        root->left = deleteNode(root->left, salary);
    else if (salary > root->salary)
        root->right = deleteNode(root->right, salary);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            Node *temp = minValueNode(root->right);
            root->salary = temp->salary;
            root->right = deleteNode(root->right, temp->salary);
        }
    }

    if (root == NULL) return root;

    root->height = 1 + max(height(root->left), height(root->right));
    root->size = 1 + size(root->left) + size(root->right);

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int getKthLargest(Node *root, int k) {
    if (root == NULL) return -1;

    int rightSize = size(root->right);

    if (rightSize + 1 == k)
        return root->salary;
    else if (rightSize >= k)
        return getKthLargest(root->right, k);
    else
        return getKthLargest(root->left, k - rightSize - 1);
}

void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->salary);
        inorder(root->right);
    }
}

int main() {
    int n, minSalary, k, salary, totalLeaves = 0;
    char command;
    Node *root = NULL;

    scanf("%d %d", &n, &minSalary);

    int globalAdjust = 0;

    for (int i = 0; i < n; i++) {
        scanf(" %c %d", &command, &k);

        if (command == 'I') {
            if (k >= minSalary) {
                root = insert(root, k - globalAdjust);
            }
        } else if (command == 'A') {
            globalAdjust += k;
        } else if (command == 'S') {
            globalAdjust -= k;
            Node *temp = root;
            while (temp != NULL) {
                if (temp->salary + globalAdjust < minSalary) {
                    totalLeaves++;
                    root = deleteNode(root, temp->salary);
                    temp = root;
                } else {
                    temp = temp->left;
                }
            }
        } else if (command == 'F') {
            if (k > size(root)) {
                printf("-1\n");
            } else {
                printf("%d\n", getKthLargest(root, k) + globalAdjust);
            }
        }
    }

    printf("%d\n", totalLeaves);

    return 0;
}