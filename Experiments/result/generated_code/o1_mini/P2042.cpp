#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    int val;
    int priority;
    struct Node* left;
    struct Node* right;
    int size;
    long long sum;
    long long max_sum;
    long long prefix;
    long long suffix;
    int rev;
    int assign;
    int assign_val;
} Node;

Node* new_node(int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = val;
    node->priority = rand();
    node->left = node->right = NULL;
    node->size = 1;
    node->sum = val;
    node->max_sum = val;
    node->prefix = val;
    node->suffix = val;
    node->rev = 0;
    node->assign = 0;
    node->assign_val = 0;
    return node;
}

int get_size(Node* root) {
    return root ? root->size : 0;
}

long long get_sum(Node* root) {
    return root ? root->sum : 0;
}

long long get_max_sum(Node* root) {
    return root ? root->max_sum : -2147483647;
}

long long get_prefix(Node* root) {
    return root ? root->prefix : -2147483647;
}

long long get_suffix(Node* root) {
    return root ? root->suffix : -2147483647;
}

void update(Node* root) {
    if (!root) return;
    root->size = 1 + get_size(root->left) + get_size(root->right);
    root->sum = root->val + get_sum(root->left) + get_sum(root->right);
    root->prefix = root->suffix = root->max_sum = root->val;
    if (root->left) {
        root->prefix = get_prefix(root->left);
        if (get_prefix(root->left) < get_sum(root->left) + root->val)
            root->prefix = get_sum(root->left) + root->val;
        if (get_sum(root->left) + root->val + get_prefix(root->right) > root->prefix)
            root->prefix = get_sum(root->left) + root->val + get_prefix(root->right);
    }
    if (root->right) {
        root->suffix = get_suffix(root->right);
        if (get_suffix(root->right) < get_sum(root->right) + root->val)
            root->suffix = get_sum(root->right) + root->val;
        if (get_sum(root->right) + root->val + get_suffix(root->left) > root->suffix)
            root->suffix = get_sum(root->right) + root->val + get_suffix(root->left);
    }
    root->max_sum = root->val;
    if (root->left && root->left->max_sum > root->max_sum)
        root->max_sum = root->left->max_sum;
    if (root->right && root->right->max_sum > root->max_sum)
        root->max_sum = root->right->max_sum;
    if (root->left && root->right) {
        long long temp = get_suffix(root->left) + root->val + get_prefix(root->right);
        if (temp > root->max_sum)
            root->max_sum = temp;
    }
    else if (root->left) {
        long long temp = get_suffix(root->left) + root->val;
        if (temp > root->max_sum)
            root->max_sum = temp;
    }
    else if (root->right) {
        long long temp = root->val + get_prefix(root->right);
        if (temp > root->max_sum)
            root->max_sum = temp;
    }
}

void push_down(Node* root) {
    if (!root) return;
    if (root->assign) {
        if (root->left) {
            root->left->assign = 1;
            root->left->assign_val = root->assign_val;
            root->left->val = root->assign_val;
            root->left->sum = (long long)root->assign_val * root->left->size;
            root->left->prefix = root->left->suffix = root->left->max_sum = (long long)root->assign_val * root->left->size > root->assign_val ? (long long)root->assign_val * root->left->size : root->assign_val;
            root->left->rev = 0;
        }
        if (root->right) {
            root->right->assign = 1;
            root->right->assign_val = root->assign_val;
            root->right->val = root->assign_val;
            root->right->sum = (long long)root->assign_val * root->right->size;
            root->right->prefix = root->right->suffix = root->right->max_sum = (long long)root->assign_val * root->right->size > root->assign_val ? (long long)root->assign_val * root->right->size : root->assign_val;
            root->right->rev = 0;
        }
        root->assign = 0;
    }
    if (root->rev) {
        Node* temp = root->left;
        root->left = root->right;
        root->right = temp;
        if (root->left) root->left->rev ^= 1;
        if (root->right) root->right->rev ^= 1;
        root->rev = 0;
    }
}

void split(Node* root, int pos, Node** left, Node** right) {
    if (!root) {
        *left = *right = NULL;
        return;
    }
    push_down(root);
    if (get_size(root->left) >= pos) {
        split(root->left, pos, left, &(root->left));
        *right = root;
    }
    else {
        split(root->right, pos - get_size(root->left) -1, &(root->right), right);
        *left = root;
    }
    update(root);
}

Node* merge(Node* left, Node* right) {
    if (!left || !right) return left ? left : right;
    if (left->priority > right->priority) {
        push_down(left);
        left->right = merge(left->right, right);
        update(left);
        return left;
    }
    else {
        push_down(right);
        right->left = merge(left, right->left);
        update(right);
        return right;
    }
}

Node* build(int* arr, int l, int r) {
    if (l > r) return NULL;
    int mid = (l + r) / 2;
    Node* root = new_node(arr[mid]);
    root->left = build(arr, l, mid -1);
    root->right = build(arr, mid +1, r);
    update(root);
    return root;
}

int main(){
    srand(time(0));
    int N, M;
    scanf("%d %d", &N, &M);
    int* initial = (int*)malloc(sizeof(int)*N);
    for(int i=0;i<N;i++) scanf("%d", &initial[i]);
    Node* root = build(initial, 0, N-1);
    free(initial);
    char cmd[20];
    for(int i=0;i<M;i++){
        scanf("%s", cmd);
        if(strcmp(cmd, "INSERT")==0){
            int pos, tot;
            scanf("%d %d", &pos, &tot);
            int* vals = (int*)malloc(sizeof(int)*tot);
            for(int j=0;j<tot;j++) scanf("%d", &vals[j]);
            Node* ins = build(vals, 0, tot-1);
            free(vals);
            Node *left, *right;
            split(root, pos, &left, &right);
            root = merge(merge(left, ins), right);
        }
        else if(strcmp(cmd, "DELETE")==0){
            int pos, tot;
            scanf("%d %d", &pos, &tot);
            Node *left, *mid, *right;
            split(root, pos-1, &left, &mid);
            split(mid, tot, &mid, &right);
            // free(mid);
            // In C, freeing all nodes is complex, skip
            root = merge(left, right);
        }
        else if(strcmp(cmd, "MAKE-SAME")==0){
            int pos, tot, c;
            scanf("%d %d %d", &pos, &tot, &c);
            Node *left, *mid, *right;
            split(root, pos-1, &left, &mid);
            split(mid, tot, &mid, &right);
            if(mid){
                mid->assign = 1;
                mid->assign_val = c;
                mid->val = c;
                mid->sum = (long long)c * mid->size;
                mid->prefix = mid->suffix = mid->max_sum = (long long)c * mid->size > c ? (long long)c * mid->size : c;
                mid->rev = 0;
            }
            root = merge(merge(left, mid), right);
        }
        else if(strcmp(cmd, "REVERSE")==0){
            int pos, tot;
            scanf("%d %d", &pos, &tot);
            Node *left, *mid, *right;
            split(root, pos-1, &left, &mid);
            split(mid, tot, &mid, &right);
            if(mid){
                mid->rev ^=1;
            }
            root = merge(merge(left, mid), right);
        }
        else if(strcmp(cmd, "GET-SUM")==0){
            int pos, tot;
            scanf("%d %d", &pos, &tot);
            Node *left, *mid, *right;
            split(root, pos-1, &left, &mid);
            split(mid, tot, &mid, &right);
            long long res = get_sum(mid);
            printf("%lld\n", res);
            root = merge(merge(left, mid), right);
        }
        else if(strcmp(cmd, "MAX-SUM")==0){
            long long res = get_max_sum(root);
            printf("%lld\n", res);
        }
    }
}