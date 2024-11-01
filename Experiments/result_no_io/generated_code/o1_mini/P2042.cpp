#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct Node {
    int val;
    int size;
    ll sum;
    ll max_sum;
    ll pre_sum;
    ll suf_sum;
    int rev;
    int same;
    int same_val;
    struct Node *left, *right;
} Node;

Node* new_node(int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = val;
    node->size = 1;
    node->sum = val;
    node->max_sum = val;
    node->pre_sum = val;
    node->suf_sum = val;
    node->rev = 0;
    node->same = 0;
    node->same_val = 0;
    node->left = node->right = NULL;
    return node;
}

int get_size(Node* root) {
    return root ? root->size : 0;
}

ll get_sum(Node* root) {
    return root ? root->sum : 0;
}

ll get_max_sum(Node* root) {
    return root ? root->max_sum : -1000000000000LL;
}

ll get_pre_sum(Node* root) {
    return root ? root->pre_sum : -1000000000000LL;
}

ll get_suf_sum(Node* root) {
    return root ? root->suf_sum : -1000000000000LL;
}

void update(Node* root) {
    if (!root) return;
    root->size = 1 + get_size(root->left) + get_size(root->right);
    root->sum = root->val + get_sum(root->left) + get_sum(root->right);

    root->pre_sum = get_pre_sum(root->left);
    if (get_size(root->left) == 0) root->pre_sum = root->val;
    else if (get_pre_sum(root->left) == get_sum(root->left)) root->pre_sum = get_sum(root->left) + root->val;
    else root->pre_sum = get_pre_sum(root->left);

    if (get_size(root->right) == 0) {
        if (get_size(root->left) == 0) root->suf_sum = root->val;
        else root->suf_sum = root->val + get_suf_sum(root->left);
    }
    else if (get_suf_sum(root->right) == get_sum(root->right)) {
        root->suf_sum = get_sum(root->right) + root->val;
    }
    else root->suf_sum = get_suf_sum(root->right);

    root->max_sum = root->val;
    if (root->left) {
        if (root->left->max_sum > root->max_sum) root->max_sum = root->left->max_sum;
        if (root->left->suf_sum + root->val > root->max_sum) root->max_sum = root->left->suf_sum + root->val;
    }
    if (root->right) {
        if (root->right->max_sum > root->max_sum) root->max_sum = root->right->max_sum;
        if (root->val + root->right->pre_sum > root->max_sum) root->max_sum = root->val + root->right->pre_sum;
    }
    if (root->left && root->right) {
        if (root->left->suf_sum + root->val + root->right->pre_sum > root->max_sum)
            root->max_sum = root->left->suf_sum + root->val + root->right->pre_sum;
    }
}

void push_down(Node* root) {
    if (!root) return;
    if (root->same) {
        if (root->left) {
            root->left->same = 1;
            root->left->same_val = root->same_val;
            root->left->val = root->same_val;
            root->left->sum = (ll)root->same_val * root->left->size;
            root->left->max_sum = root->same_val > 0 ? root->left->sum : root->same_val;
            root->left->pre_sum = root->left->max_sum;
            root->left->suf_sum = root->left->max_sum;
            root->left->rev = 0;
        }
        if (root->right) {
            root->right->same = 1;
            root->right->same_val = root->same_val;
            root->right->val = root->same_val;
            root->right->sum = (ll)root->same_val * root->right->size;
            root->right->max_sum = root->same_val > 0 ? root->right->sum : root->same_val;
            root->right->pre_sum = root->right->max_sum;
            root->right->suf_sum = root->right->max_sum;
            root->right->rev = 0;
        }
        root->same = 0;
    }
    if (root->rev) {
        if (root->left) {
            root->left->rev ^= 1;
            Node* tmp = root->left->left;
            root->left->left = root->left->right;
            root->left->right = tmp;
        }
        if (root->right) {
            root->right->rev ^= 1;
            Node* tmp = root->right->left;
            root->right->left = root->right->right;
            root->right->right = tmp;
        }
        root->rev = 0;
    }
}

Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;
    // For simplicity, use size as priority
    if (rand() % (left->size + right->size) < left->size) {
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

void split(Node* root, int k, Node** left, Node** right) {
    if (!root) {
        *left = *right = NULL;
        return;
    }
    push_down(root);
    if (get_size(root->left) >= k) {
        split(root->left, k, left, &(root->left));
        update(root);
        *right = root;
    }
    else {
        split(root->right, k - get_size(root->left) -1, &(root->right), right);
        update(root);
        *left = root;
    }
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    Node* root = NULL;
    for(int i=0;i<N;i++){
        int x;
        scanf("%d", &x);
        root = merge(root, new_node(x));
    }
    char cmd[20];
    for(int i=0;i<M;i++){
        scanf("%s", cmd);
        if(strcmp(cmd, "INSERT")==0){
            int pos, tot;
            scanf("%d %d", &pos, &tot);
            Node* left, *right;
            split(root, pos, &left, &right);
            Node* mid = NULL;
            for(int j=0; j<tot; j++){
                int c;
                scanf("%d", &c);
                mid = merge(mid, new_node(c));
            }
            root = merge(merge(left, mid), right);
        }
        else if(strcmp(cmd, "DELETE")==0){
            int pos, tot;
            scanf("%d %d", &pos, &tot);
            Node* left, *mid, *right;
            split(root, pos-1, &left, &right);
            split(right, tot, &mid, &right);
            // free(mid);
            root = merge(left, right);
        }
        else if(strcmp(cmd, "MAKE-SAME")==0){
            int pos, tot, c;
            scanf("%d %d %d", &pos, &tot, &c);
            Node* left, *mid, *right;
            split(root, pos-1, &left, &right);
            split(right, tot, &mid, &right);
            if(mid){
                mid->same = 1;
                mid->same_val = c;
                mid->val = c;
                mid->sum = (ll)c * mid->size;
                mid->max_sum = c > 0 ? mid->sum : c;
                mid->pre_sum = mid->max_sum;
                mid->suf_sum = mid->max_sum;
                mid->rev = 0;
            }
            root = merge(merge(left, mid), right);
        }
        else if(strcmp(cmd, "REVERSE")==0){
            int pos, tot;
            scanf("%d %d", &pos, &tot);
            Node* left, *mid, *right;
            split(root, pos-1, &left, &right);
            split(right, tot, &mid, &right);
            if(mid){
                mid->rev ^=1;
                Node* tmp = mid->left;
                mid->left = mid->right;
                mid->right = tmp;
            }
            root = merge(merge(left, mid), right);
        }
        else if(strcmp(cmd, "GET-SUM")==0){
            int pos, tot;
            scanf("%d %d", &pos, &tot);
            Node* left, *mid, *right;
            split(root, pos-1, &left, &right);
            split(right, tot, &mid, &right);
            ll s = get_sum(mid);
            printf("%lld\n", s);
            root = merge(merge(left, mid), right);
        }
        else if(strcmp(cmd, "MAX-SUM")==0){
            printf("%lld\n", get_max_sum(root));
        }
    }
}