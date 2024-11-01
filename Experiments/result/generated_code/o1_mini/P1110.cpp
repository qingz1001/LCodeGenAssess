#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Treap node structure
typedef struct TreapNode {
    int key;
    int priority;
    int count;
    struct TreapNode* left;
    struct TreapNode* right;
} TreapNode;

// Function to create a new treap node
TreapNode* newNode(int key) {
    TreapNode* node = (TreapNode*)malloc(sizeof(TreapNode));
    node->key = key;
    node->priority = rand();
    node->count = 1;
    node->left = node->right = NULL;
    return node;
}

// Right rotation
TreapNode* rotateRight(TreapNode* y) {
    TreapNode* x = y->left;
    TreapNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    return x;
}

// Left rotation
TreapNode* rotateLeft(TreapNode* x) {
    TreapNode* y = x->right;
    TreapNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    return y;
}

// Insert key into treap
TreapNode* treapInsert(TreapNode* root, int key) {
    if (root == NULL)
        return newNode(key);
    if (key < root->key) {
        root->left = treapInsert(root->left, key);
        if (root->left->priority > root->priority)
            root = rotateRight(root);
    }
    else if (key > root->key) {
        root->right = treapInsert(root->right, key);
        if (root->right->priority > root->priority)
            root = rotateLeft(root);
    }
    else {
        root->count += 1;
    }
    return root;
}

// Delete key from treap
TreapNode* treapDelete(TreapNode* root, int key) {
    if (root == NULL)
        return root;
    if (key < root->key) {
        root->left = treapDelete(root->left, key);
    }
    else if (key > root->key) {
        root->right = treapDelete(root->right, key);
    }
    else {
        if (root->count > 1) {
            root->count -= 1;
        }
        else {
            if (root->left == NULL) {
                TreapNode* temp = root->right;
                free(root);
                root = temp;
            }
            else if (root->right == NULL) {
                TreapNode* temp = root->left;
                free(root);
                root = temp;
            }
            else {
                if (root->left->priority > root->right->priority) {
                    root = rotateRight(root);
                    root->right = treapDelete(root->right, key);
                }
                else {
                    root = rotateLeft(root);
                    root->left = treapDelete(root->left, key);
                }
            }
        }
    }
    return root;
}

// Get minimum key in treap
int treapGetMin(TreapNode* root) {
    if (root == NULL)
        return -1;
    while (root->left != NULL)
        root = root->left;
    return root->key;
}

// Comparison function for qsort
int cmp_func(const void* a, const void* b) {
    int va = *(int*)a;
    int vb = *(int*)b;
    if (va < vb) return -1;
    else if (va > vb) return 1;
    else return 0;
}

// Binary search to find lower bound
int lower_bound_func(int* arr, int left, int right, int target) {
    int l = left, r = right;
    int pos = right + 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m] >= target) {
            pos = m;
            r = m - 1;
        }
        else {
            l = m + 1;
        }
    }
    return pos;
}

// Structure for sequence elements
typedef struct {
    int value;
    int prev;
    int next;
} Element;

#define MAXNODES 1000005
Element seq[MAXNODES];
int last_insert[500005];
int sorted_vals[MAXNODES];
int sorted_count = 0;
int node_count = 0;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++){
        scanf("%d", &seq[i].value);
        seq[i].prev = i-1;
        seq[i].next = i+1;
    }
    seq[1].prev = 0;
    seq[n].next = 0;
    node_count = n;
    for(int i=1;i<=n;i++) last_insert[i] = i;
    // Initialize treap with initial gaps
    TreapNode* treap_root = NULL;
    for(int i=1;i<n;i++){
        int gap = abs(seq[i].value - seq[i+1].value);
        treap_root = treapInsert(treap_root, gap);
    }
    // Initialize sorted_vals
    for(int i=1;i<=n;i++) sorted_vals[i] = seq[i].value;
    sorted_count = n;
    qsort(sorted_vals + 1, n, sizeof(int), cmp_func);
    // Compute initial min_sort_gap
    int min_sort_gap = 1000000000;
    for(int i=1;i<n;i++){
        int gap = sorted_vals[i+1] - sorted_vals[i];
        if(gap < min_sort_gap) min_sort_gap = gap;
    }
    char cmd[15];
    for(int op=0; op<m; op++){
        scanf("%s", cmd);
        if(strcmp(cmd, "INSERT") == 0){
            int i, k;
            scanf("%d %d", &i, &k);
            int pos = last_insert[i];
            node_count++;
            int new_node = node_count;
            seq[new_node].value = k;
            seq[new_node].prev = pos;
            seq[new_node].next = seq[pos].next;
            if(seq[pos].next != 0){
                int next_node = seq[pos].next;
                seq[next_node].prev = new_node;
                // Remove old gap
                int old_gap = abs(seq[pos].value - seq[next_node].value);
                treap_root = treapDelete(treap_root, old_gap);
                // Insert new gaps
                int gap1 = abs(seq[pos].value - k);
                int gap2 = abs(k - seq[next_node].value);
                treap_root = treapInsert(treap_root, gap1);
                treap_root = treapInsert(treap_root, gap2);
            }
            else{
                // Insert new gap
                int gap1 = abs(seq[pos].value - k);
                treap_root = treapInsert(treap_root, gap1);
            }
            seq[pos].next = new_node;
            last_insert[i] = new_node;
            // Insert into sorted_vals
            int insert_pos = lower_bound_func(sorted_vals, 1, sorted_count, k);
            int pred = -1, succ = -1;
            if(insert_pos > 1) pred = sorted_vals[insert_pos-1];
            if(insert_pos <= sorted_count) succ = sorted_vals[insert_pos];
            // Shift to insert
            for(int j=sorted_count+1; j>insert_pos; j--){
                sorted_vals[j] = sorted_vals[j-1];
            }
            sorted_vals[insert_pos] = k;
            sorted_count++;
            // Update min_sort_gap
            if(pred != -1){
                int gap = k - pred;
                if(gap < min_sort_gap) min_sort_gap = gap;
            }
            if(succ != -1){
                int gap = succ - k;
                if(gap < min_sort_gap) min_sort_gap = gap;
            }
        }
        else if(strcmp(cmd, "MIN_GAP") == 0){
            int current_min_gap = treapGetMin(treap_root);
            printf("%d\n", current_min_gap);
        }
        else if(strcmp(cmd, "MIN_SORT_GAP") == 0){
            printf("%d\n", min_sort_gap);
        }
    }
    return 0;
}