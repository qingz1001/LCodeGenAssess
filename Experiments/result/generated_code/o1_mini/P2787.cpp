#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char val;
    int priority;
    int size;
    int cnt[26];
    int assign; // -1 means no assign, otherwise 0-25
    struct Node *left, *right;
} Node;

// Function to create a new node
Node* create_node(char c) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->val = c;
    node->priority = rand();
    node->assign = -1;
    node->left = node->right = NULL;
    memset(node->cnt, 0, sizeof(node->cnt));
    node->cnt[c - 'a'] = 1;
    node->size = 1;
    return node;
}

// Update function to recalculate size and counts
void update(Node *node) {
    if (node == NULL) return;
    node->size = 1;
    memset(node->cnt, 0, sizeof(node->cnt));
    node->cnt[node->val - 'a'] += 1;
    if (node->left) {
        node->size += node->left->size;
        for(int i=0;i<26;i++) node->cnt[i] += node->left->cnt[i];
    }
    if (node->right) {
        node->size += node->right->size;
        for(int i=0;i<26;i++) node->cnt[i] += node->right->cnt[i];
    }
}

// Push down the assign flag
void push_down(Node *node) {
    if (node == NULL || node->assign == -1) return;
    if (node->left) {
        node->left->assign = node->assign;
        memset(node->left->cnt, 0, sizeof(node->left->cnt));
        node->left->cnt[node->assign] = node->left->size;
    }
    if (node->right) {
        node->right->assign = node->assign;
        memset(node->right->cnt, 0, sizeof(node->right->cnt));
        node->right->cnt[node->assign] = node->right->size;
    }
    node->val = 'a' + node->assign;
    node->assign = -1;
}

// Split the treap into left and right with left containing first k nodes
void split_treap(Node *root, int k, Node **left, Node **right) {
    if (root == NULL) {
        *left = *right = NULL;
        return;
    }
    push_down(root);
    int left_size = root->left ? root->left->size : 0;
    if (k <= left_size) {
        split_treap(root->left, k, left, &(root->left));
        update(root);
        *right = root;
    }
    else {
        split_treap(root->right, k - left_size -1, &(root->right), right);
        update(root);
        *left = root;
    }
}

// Merge two treaps
Node* merge_treap(Node *left, Node *right) {
    if (left == NULL) return right;
    if (right == NULL) return left;
    if (left->priority > right->priority) {
        push_down(left);
        left->right = merge_treap(left->right, right);
        update(left);
        return left;
    }
    else {
        push_down(right);
        right->left = merge_treap(left, right->left);
        update(right);
        return right;
    }
}

// Build a sorted treap from counts
Node* rebuild_sort_treap(int cnt[26]) {
    Node *sorted = NULL;
    for(int i=0;i<26;i++) {
        for(int j=0;j<cnt[i];j++) {
            Node *new_node = create_node('a' + i);
            sorted = merge_treap(sorted, new_node);
        }
    }
    return sorted;
}

int main(){
    srand(123456789);
    int n, m;
    scanf("%d %d", &n, &m);
    char *s = (char*)malloc((n+1)*sizeof(char));
    scanf("%s", s);
    // Convert to lowercase
    for(int i=0;i<n;i++) {
        if('A' <= s[i] && s[i] <= 'Z') s[i] = s[i] - 'A' + 'a';
    }
    // Build the initial treap
    Node *root = NULL;
    for(int i=0;i<n;i++) {
        Node *new_node = create_node(s[i]);
        root = merge_treap(root, new_node);
    }
    free(s);
    for(int i=0;i<m;i++) {
        int op;
        scanf("%d", &op);
        if(op == 1){
            int x, y;
            char k;
            scanf("%d %d %c", &x, &y, &k);
            if('A' <= k && k <= 'Z') k = k - 'A' + 'a';
            else k = tolower(k);
            Node *left, *middle, *right;
            split_treap(root, x-1, &left, &middle);
            split_treap(middle, y - (x-1), &middle, &right);
            int res = (middle != NULL) ? middle->cnt[k - 'a'] : 0;
            printf("%d\n", res);
            root = merge_treap(left, merge_treap(middle, right));
        }
        else if(op == 2){
            int x, y;
            char k;
            scanf("%d %d %c", &x, &y, &k);
            if('A' <= k && k <= 'Z') k = k - 'A' + 'a';
            else k = tolower(k);
            Node *left, *middle, *right;
            split_treap(root, x-1, &left, &middle);
            split_treap(middle, y - (x-1), &middle, &right);
            if(middle != NULL){
                middle->assign = k - 'a';
                memset(middle->cnt, 0, sizeof(middle->cnt));
                middle->cnt[k - 'a'] = middle->size;
            }
            root = merge_treap(left, merge_treap(middle, right));
        }
        else if(op == 3){
            int x, y;
            scanf("%d %d", &x, &y);
            Node *left, *middle, *right;
            split_treap(root, x-1, &left, &middle);
            split_treap(middle, y - (x-1), &middle, &right);
            int cnt[26];
            memset(cnt, 0, sizeof(cnt));
            if(middle != NULL){
                for(int j=0; j<26; j++) cnt[j] = middle->cnt[j];
                // Rebuild the middle treap sorted
                Node *sorted = rebuild_sort_treap(cnt);
                middle = sorted;
            }
            root = merge_treap(left, merge_treap(middle, right));
        }
    }
    // Clean up memory (optional)
    return 0;
}