#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct treap_node {
    int key;
    int priority;
    int size;
    struct treap_node* left;
    struct treap_node* right;
} treap_node;

// Pool for treap nodes
#define MAX_NODES 200000
treap_node treap_pool[MAX_NODES];
int treap_pool_size = 0;

// Function to create a new node
treap_node* new_node(int key) {
    treap_pool[treap_pool_size].key = key;
    treap_pool[treap_pool_size].priority = rand();
    treap_pool[treap_pool_size].size = 1;
    treap_pool[treap_pool_size].left = NULL;
    treap_pool[treap_pool_size].right = NULL;
    return &treap_pool[treap_pool_size++];
}

// Function to get size of treap
int get_size(treap_node* root) {
    if (root == NULL) return 0;
    return root->size;
}

// Function to update size of treap
void update_size_node(treap_node* root) {
    if (root == NULL) return;
    root->size = 1 + get_size(root->left) + get_size(root->right);
}

// Split treap into left < key and right >= key
treap_node* treap_split(treap_node* root, int key, treap_node** left, treap_node** right) {
    if (!root) {
        *left = NULL;
        *right = NULL;
    }
    else if (root->key < key) {
        treap_split(root->right, key, &(root->right), right);
        *left = root;
    }
    else {
        treap_split(root->left, key, left, &(root->left));
        *right = root;
    }
    update_size_node(root);
    return root;
}

// Merge two treaps
treap_node* treap_merge(treap_node* left, treap_node* right) {
    if (!left) return right;
    if (!right) return left;
    if (left->priority > right->priority) {
        left->right = treap_merge(left->right, right);
        update_size_node(left);
        return left;
    }
    else {
        right->left = treap_merge(left, right->left);
        update_size_node(right);
        return right;
    }
}

// Insert a node into treap
treap_node* treap_insert(treap_node* root, treap_node* node) {
    if (!root) {
        return node;
    }
    if (node->priority > root->priority) {
        treap_split(root, node->key, &(node->left), &(node->right));
        update_size_node(node);
        return node;
    }
    if (node->key < root->key) {
        root->left = treap_insert(root->left, node);
    }
    else {
        root->right = treap_insert(root->right, node);
    }
    update_size_node(root);
    return root;
}

// Erase all keys less than key, return number removed
treap_node* treap_erase_less_than(treap_node* root, int key, int* removed) {
    if (!root) {
        *removed = 0;
        return NULL;
    }
    if (root->key < key) {
        int left_size = get_size(root->left);
        int current_removed = left_size + 1;
        int right_removed = 0;
        treap_node* new_root = treap_erase_less_than(root->right, key, &right_removed);
        *removed = current_removed + right_removed;
        return new_root;
    }
    else {
        int left_removed = 0;
        root->left = treap_erase_less_than(root->left, key, &left_removed);
        *removed += left_removed;
        update_size_node(root);
        return root;
    }
}

// Find k-th smallest key
int treap_kth(treap_node* root, int k, int* result) {
    if (!root) {
        return 0;
    }
    int left_size = get_size(root->left);
    if (k <= left_size) {
        return treap_kth(root->left, k, result);
    }
    else if (k == left_size + 1) {
        *result = root->key;
        return 1;
    }
    else {
        return treap_kth(root->right, k - left_size - 1, result);
    }
}

int main(){
    srand(time(NULL));
    int n;
    long long min_salary;
    if (scanf("%d %lld", &n, &min_salary)!=2){
        return 0;
    }
    treap_node* treap_root = NULL;
    long long global_offset = 0;
    long long leave_count = 0;
    char cmd[2];
    int k;
    for(int i=0;i<n;i++){
        if (scanf("%s %d", cmd, &k)!=2){
            break;
        }
        if (cmd[0]=='I'){
            long long actual_salary = (long long)k;
            if (actual_salary >= min_salary){
                int adjusted_salary = (int)(actual_salary - global_offset);
                treap_node* node = new_node(adjusted_salary);
                treap_root = treap_insert(treap_root, node);
            }
            // else: do not count as leaving
        }
        else if (cmd[0]=='A'){
            global_offset += k;
        }
        else if (cmd[0]=='S'){
            global_offset -= k;
            long long threshold = (long long)(min_salary) - global_offset;
            int th = threshold;
            if (threshold > 2147483647) th = 2147483647;
            else if (threshold < -2147483648LL) th = -2147483648;
            int removed = 0;
            treap_root = treap_erase_less_than(treap_root, th, &removed);
            leave_count += removed;
        }
        else if (cmd[0]=='F'){
            int size = get_size(treap_root);
            if (k > size){
                printf("-1\n");
            }
            else{
                int target = size - k +1;
                int key = 0;
                treap_kth(treap_root, target, &key);
                long long real_salary = (long long)key + global_offset;
                printf("%lld\n", real_salary);
            }
        }
    }
    printf("%lld\n", leave_count);
    return 0;
}