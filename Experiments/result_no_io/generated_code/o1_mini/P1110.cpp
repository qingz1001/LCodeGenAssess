#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Constants
#define MAXN 1000000
#define MAXM 500500
#define MAX_OP_LEN 20

// Treap structure
typedef struct TreapNode {
    int key;
    int priority;
    int left;
    int right;
} TreapNode;

TreapNode treap[2000000];
int treap_cnt = 0;
int treap_root = -1;

// Function to generate random priority
int rand_priority() {
    return rand();
}

// Insert into treap and return new root
int treap_insert(int root, int key) {
    if (root == -1) {
        treap[root = treap_cnt].key = key;
        treap[root].priority = rand_priority();
        treap[root].left = treap[root].right = -1;
        return treap_cnt++;
    }
    if (key < treap[root].key) {
        treap[root].left = treap_insert(treap[root].left, key);
        if (treap[treap[root].left].priority > treap[root].priority) {
            int left = treap[root].left;
            treap[root].left = treap[left].right;
            treap[left].right = root;
            return left;
        }
    }
    else {
        treap[root].right = treap_insert(treap[root].right, key);
        if (treap[treap[root].right].priority > treap[root].priority) {
            int right = treap[root].right;
            treap[root].right = treap[right].left;
            treap[right].left = root;
            return right;
        }
    }
    return root;
}

// Find predecessor and successor
typedef struct Pair {
    int pred;
    int succ;
} Pair;

Pair find_pred_succ(int root, int key) {
    Pair p;
    p.pred = -1;
    p.succ = -1;
    while (root != -1) {
        if (treap[root].key < key) {
            p.pred = treap[root].key;
            root = treap[root].right;
        }
        else {
            p.succ = treap[root].key;
            root = treap[root].left;
        }
    }
    return p;
}

// List structure
typedef struct ListNode {
    int val;
    int first_child;
    int last_child;
    int next;
} ListNode;

ListNode list_nodes[MAXN];
int list_cnt = 0;
int head_node = -1;

// Insert after parent
void list_insert(int parent, int val) {
    list_nodes[list_cnt].val = val;
    list_nodes[list_cnt].first_child = -1;
    list_nodes[list_cnt].last_child = -1;
    list_nodes[list_cnt].next = -1;
    if (list_nodes[parent].last_child == -1) {
        list_nodes[parent].first_child = list_cnt;
        list_nodes[parent].last_child = list_cnt;
    }
    else {
        list_nodes[list_nodes[parent].last_child].next = list_cnt;
        list_nodes[parent].last_child = list_cnt;
    }
    list_cnt++;
}

// Traverse the list and find min_gap
long long current_min_gap = 1000000001;
void update_min_gap(int new_node, int parent) {
    // Find previous and next in the list
    // To simplify, traverse from head and keep track
    // But it's O(n), need a better way
    // Alternative: maintain a doubly linked list
    // Not implemented due to time
    // Instead, skip and recalculate when MIN_GAP is called
}

// Sorted min gap
long long min_sort_gap = 1000000001;

// Main function
int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    // Initialize list
    for(int i=0;i<n;i++){
        int x;
        scanf("%d", &x);
        list_nodes[i].val = x;
        list_nodes[i].first_child = -1;
        list_nodes[i].last_child = -1;
        list_nodes[i].next = -1;
    }
    list_cnt = n;
    head_node = 0;
    // Initialize treap and min_sort_gap
    for(int i=0;i<n;i++){
        Pair p = find_pred_succ(treap_root, list_nodes[i].val);
        if(p.pred != -1){
            long long gap = (long long)(list_nodes[i].val) - p.pred;
            if(gap < min_sort_gap) min_sort_gap = gap;
        }
        if(p.succ != -1){
            long long gap = (long long)(p.succ) - list_nodes[i].val;
            if(gap < min_sort_gap) min_sort_gap = gap;
        }
        treap_root = treap_insert(treap_root, list_nodes[i].val);
    }
    // Read operations
    char op[MAX_OP_LEN];
    for(int i=0;i<m;i++){
        scanf("%s", op);
        if(strcmp(op, "INSERT") == 0){
            int pos, k;
            scanf("%d %d", &pos, &k);
            // Insert after pos-1 (0-based)
            list_insert(pos-1, k);
            // Update min_sort_gap
            Pair p = find_pred_succ(treap_root, k);
            if(p.pred != -1){
                long long gap = (long long)k - p.pred;
                if(gap < min_sort_gap) min_sort_gap = gap;
            }
            if(p.succ != -1){
                long long gap = (long long)p.succ - k;
                if(gap < min_sort_gap) min_sort_gap = gap;
            }
            treap_root = treap_insert(treap_root, k);
        }
        else if(strcmp(op, "MIN_GAP") == 0){
            // Traverse the list and find min_gap
            long long mgap = 1000000001;
            int current = head_node;
            while(current != -1){
                if(list_nodes[current].first_child != -1){
                    int child = list_nodes[current].first_child;
                    while(child != -1){
                        long long gap = abs((long long)list_nodes[current].val - (long long)list_nodes[child].val);
                        if(gap < mgap) mgap = gap;
                        current = child;
                        child = list_nodes[child].next;
                    }
                }
                if(list_nodes[current].next != -1){
                    long long gap = abs((long long)list_nodes[current].val - (long long)list_nodes[list_nodes[current].next].val);
                    if(gap < mgap) mgap = gap;
                }
                current = list_nodes[current].next;
            }
            printf("%lld\n", mgap);
        }
        else if(strcmp(op, "MIN_SORT_GAP") == 0){
            printf("%lld\n", min_sort_gap);
        }
    }
    return 0;
}