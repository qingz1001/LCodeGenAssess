#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int key;
    int W;
    int priority;
    struct Node* left;
    struct Node* right;
} Node;

int sum_W = 0;
int sum_C = 0;

Node* newNode(int key, int W) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->W = W;
    node->priority = rand();
    node->left = node->right = NULL;
    return node;
}

void split(Node* root, int key, Node** left, Node** right) {
    if (root == NULL) {
        *left = *right = NULL;
    }
    else if (key < root->key) {
        split(root->left, key, left, &(root->left));
        *right = root;
    }
    else {
        split(root->right, key, &(root->right), right);
        *left = root;
    }
}

Node* merge(Node* left, Node* right) {
    if (!left || !right)
        return left ? left : right;
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        return right;
    }
}

Node* insert(Node* root, Node* node) {
    if (root == NULL)
        return node;
    if (node->key == root->key)
        return root;
    if (node->priority > root->priority) {
        split(root, node->key, &(node->left), &(node->right));
        return node;
    }
    else if (node->key < root->key)
        root->left = insert(root->left, node);
    else
        root->right = insert(root->right, node);
    return root;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return NULL;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        Node* temp = merge(root->left, root->right);
        free(root);
        return temp;
    }
    return root;
}

int search(Node* root, int key) {
    while (root != NULL) {
        if (key == root->key)
            return 1;
        else if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return 0;
}

Node* findMin(Node* root) {
    if (root == NULL)
        return NULL;
    while (root->left != NULL)
        root = root->left;
    return root;
}

Node* findMax(Node* root) {
    if (root == NULL)
        return NULL;
    while (root->right != NULL)
        root = root->right;
    return root;
}

int main(){
    srand(time(NULL));
    Node* root = NULL;
    int op;
    while (scanf("%d", &op) == 1 && op != -1){
        if(op == 1){
            int W, C;
            scanf("%d %d", &W, &C);
            if(!search(root, C)){
                Node* node = newNode(C, W);
                root = insert(root, node);
                sum_W += W;
                sum_C += C;
            }
        }
        else if(op == 2){
            if(root != NULL){
                Node* maxNode = findMax(root);
                if(maxNode != NULL){
                    sum_W -= maxNode->W;
                    sum_C -= maxNode->key;
                    root = deleteNode(root, maxNode->key);
                }
            }
        }
        else if(op == 3){
            if(root != NULL){
                Node* minNode = findMin(root);
                if(minNode != NULL){
                    sum_W -= minNode->W;
                    sum_C -= minNode->key;
                    root = deleteNode(root, minNode->key);
                }
            }
        }
    }
    printf("%d %d\n", sum_W, sum_C);
    return 0;
}