#include <stdio.h>
#include <stdlib.h>

#define MAXN 300005

typedef struct Node {
    int salary;
    struct Node *left, *right;
    int height;
} Node;

Node *newNode(int salary) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->salary = salary;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

int height(Node *N) {
    if (N == NULL) return 0;
    return N->height;
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

    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

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

int countNodes(Node *root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int getKthLargest(Node *root, int k) {
    int rightCount = countNodes(root->right);
    if (k == rightCount + 1)
        return root->salary;
    else if (k <= rightCount)
        return getKthLargest(root->right, k);
    else
        return getKthLargest(root->left, k - rightCount - 1);
}

int main() {
    int n, minSalary, k, totalExits = 0;
    char command;
    Node *root = NULL;

    scanf("%d %d", &n, &minSalary);

    int globalAdjustment = 0;

    for (int i = 0; i < n; i++) {
        scanf(" %c %d", &command, &k);

        if (command == 'I') {
            if (k >= minSalary) {
                root = insert(root, k - globalAdjustment);
            }
        } else if (command == 'A') {
            globalAdjustment += k;
        } else if (command == 'S') {
            globalAdjustment -= k;
            while (root != NULL && minValueNode(root)->salary + globalAdjustment < minSalary) {
                root = deleteNode(root, minValueNode(root)->salary);
                totalExits++;
            }
        } else if (command == 'F') {
            if (k > countNodes(root))
                printf("-1\n");
            else
                printf("%d\n", getKthLargest(root, k) + globalAdjustment);
        }
    }

    printf("%d\n", totalExits);

    return 0;
}