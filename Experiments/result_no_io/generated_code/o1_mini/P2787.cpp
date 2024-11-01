#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct Node {
    char val;
    int priority, size;
    int count[26];
    char lazy;
    int sorted;
    struct Node *left, *right;
} Node;

// Update size and count
void update(Node *root) {
    if (!root) return;
    root->size = 1;
    memset(root->count, 0, sizeof(root->count));
    root->count[root->val - 'a'] = 1;
    if (root->left) {
        root->size += root->left->size;
        for(int i=0;i<26;i++) root->count[i] += root->left->count[i];
    }
    if (root->right) {
        root->size += root->right->size;
        for(int i=0;i<26;i++) root->count[i] += root->right->count[i];
    }
}

// Pushdown lazy assignment
void pushdown(Node *root) {
    if (!root || root->lazy == 0) return;
    if (root->left) {
        root->left->lazy = root->lazy;
        memset(root->left->count, 0, sizeof(root->left->count));
        root->left->count[root->lazy - 'a'] = root->left->size;
        root->left->val = root->lazy;
    }
    if (root->right) {
        root->right->lazy = root->lazy;
        memset(root->right->count, 0, sizeof(root->right->count));
        root->right->count[root->lazy - 'a'] = root->right->size;
        root->right->val = root->lazy;
    }
    root->lazy = 0;
}

// Split by key, 1-based indexing
void split_node(Node *root, int key, Node **left, Node **right) {
    if (!root) { *left = *right = NULL; return;}
    pushdown(root);
    int curr = root->left ? root->left->size : 0;
    if (key <= curr) {
        split_node(root->left, key, left, &(root->left));
        *right = root;
    }
    else {
        split_node(root->right, key - curr -1, &(root->right), right);
        *left = root;
    }
    update(root);
}

// Merge two treaps
Node* merge_node(Node *left, Node *right) {
    if (!left || !right) return left ? left : right;
    if (left->priority > right->priority) {
        pushdown(left);
        left->right = merge_node(left->right, right);
        update(left);
        return left;
    }
    else {
        pushdown(right);
        right->left = merge_node(left, right->left);
        update(right);
        return right;
    }
}

// Create new node
Node* new_node(char val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = val;
    node->priority = rand();
    node->size = 1;
    memset(node->count, 0, sizeof(node->count));
    node->count[val - 'a'] = 1;
    node->lazy = 0;
    node->sorted = 0;
    node->left = node->right = NULL;
    return node;
}

// Build treap from sorted counts
Node* build(int cnt[], int *idx) {
    Node* root = NULL;
    for(int i=0;i<26;i++) {
        while(cnt[i]--) {
            root = merge_node(root, new_node('a' + i));
        }
    }
    return root;
}

// In-order traversal to collect counts
void collect_counts(Node *root, int cnt[]) {
    if (!root) return;
    pushdown(root);
    collect_counts(root->left, cnt);
    cnt[root->val - 'a']++;
    collect_counts(root->right, cnt);
}

// Free treap
void free_treap(Node *root) {
    if (!root) return;
    free_treap(root->left);
    free_treap(root->right);
    free(root);
}

int main(){
    srand(time(NULL));
    int n, m;
    scanf("%d %d", &n, &m);
    char s[n+1];
    scanf("%s", s);
    // Build initial treap
    Node* treap = NULL;
    for(int i=0;i<n;i++) {
        char c = tolower(s[i]);
        treap = merge_node(treap, new_node(c));
    }
    for(int i=0;i<m;i++) {
        int type;
        scanf("%d", &type);
        if(type == 1){
            int x, y;
            char k;
            scanf("%d %d %c", &x, &y, &k);
            k = tolower(k);
            Node *left, *mid, *right;
            split_node(treap, y, &treap, &right);
            split_node(treap, x-1, &left, &mid);
            int res = mid ? mid->count[k - 'a'] : 0;
            printf("%d\n", res);
            treap = merge_node(left, merge_node(mid, right));
        }
        else if(type == 2){
            int x, y;
            char k;
            scanf("%d %d %c", &x, &y, &k);
            k = tolower(k);
            Node *left, *mid, *right;
            split_node(treap, y, &treap, &right);
            split_node(treap, x-1, &left, &mid);
            if(mid){
                mid->lazy = k;
                memset(mid->count, 0, sizeof(mid->count));
                mid->count[k - 'a'] = mid->size;
                mid->val = k;
            }
            treap = merge_node(left, merge_node(mid, right));
        }
        else if(type == 3){
            int x, y;
            scanf("%d %d", &x, &y);
            Node *left, *mid, *right;
            split_node(treap, y, &treap, &right);
            split_node(treap, x-1, &left, &mid);
            if(mid){
                int cnt[26];
                memset(cnt, 0, sizeof(cnt));
                collect_counts(mid, cnt);
                free_treap(mid);
                mid = build(cnt, NULL);
            }
            treap = merge_node(left, merge_node(mid, right));
        }
    }
    // Free treap
    free_treap(treap);
    return 0;
}