#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1000000

typedef struct Node {
    int id;
    double a, b;
    struct Node* parent;
    struct Node* children;
    struct Node* next;
} Node;

Node* createNode(int id, double a, double b) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    newNode->a = a;
    newNode->b = b;
    newNode->parent = NULL;
    newNode->children = NULL;
    newNode->next = NULL;
    return newNode;
}

void addNode(Node** head, Node* newNode) {
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void addChild(Node* parent, Node* child) {
    if (parent->children == NULL) {
        parent->children = child;
    } else {
        Node* temp = parent->children;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = child;
    }
}

void releaseTree(Node* root) {
    if (root == NULL) return;
    Node* temp = root;
    while (temp != NULL) {
        Node* next = temp->next;
        releaseTree(temp->children);
        free(temp);
        temp = next;
    }
}

double calculateR(Node* root) {
    if (root == NULL) return 0;
    double sumA = root->a, sumB = root->b;
    Node* temp = root->children;
    while (temp != NULL) {
        sumA += temp->a;
        sumB += temp->b;
        temp = temp->next;
    }
    return sumA / sumB;
}

Node* findMinRNode(Node* root) {
    if (root == NULL) return NULL;
    Node* minNode = root;
    double minR = calculateR(root);
    Node* temp = root->children;
    while (temp != NULL) {
        double tempR = calculateR(temp);
        if (tempR < minR) {
            minR = tempR;
            minNode = temp;
        }
        temp = temp->next;
    }
    return minNode;
}

void processTree(Node* root) {
    if (root == NULL) return;
    Node* minRNode = findMinRNode(root);
    if (minRNode == NULL) return;
    Node* temp = root->children;
    while (temp != NULL) {
        if (temp != minRNode) {
            minRNode->a += temp->a;
            minRNode->b += temp->b;
        }
        temp = temp->next;
    }
    releaseTree(minRNode->children);
    minRNode->children = NULL;
    processTree(root);
}

long long calculateW(Node* root, int t) {
    if (root == NULL) return 0;
    long long w = (long long)t * (long long)ceil(calculateR(root));
    Node* temp = root->children;
    while (temp != NULL) {
        w += calculateW(temp, t + 1);
        temp = temp->next;
    }
    return w;
}

int main() {
    int n;
    scanf("%d", &n);
    Node* root = createNode(1, 0, 0);
    for (int i = 2; i <= n; i++) {
        int parent_id;
        scanf("%d", &parent_id);
        double a, b;
        scanf("%lf %lf", &a, &b);
        Node* newNode = createNode(i, a, b);
        addNode(&root->children, newNode);
        addChild(root, newNode);
    }
    processTree(root);
    long long w = calculateW(root, 1);
    printf("%lld\n", w);
    releaseTree(root);
    return 0;
}