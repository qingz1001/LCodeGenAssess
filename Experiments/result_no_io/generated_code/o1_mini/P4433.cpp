#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct Node {
    struct Node *left, *right;
    ll sum;
    int has_lazy;
    ll A, B, L;
    int time;
} Node;

int current_time = 0;

// Floor sum implementation
ll floor_sum_func(ll a, ll b, ll m, ll n) {
    ll res = 0;
    while (n > 0) {
        if (a == 0) {
            res += (b / m) * n;
            break;
        }
        if (a >= m || b >= m) {
            res += (a / m) * n * (n - 1) / 2;
            res += (b / m) * n;
            a %= m;
            b %= m;
        }
        ll y = a * n + b;
        if (y < m)
            break;
        ll n_new = y / m;
        ll b_new = y % m;
        res += n_new;
        a = m;
        b = b_new;
        n = n_new;
    }
    return res;
}

// Function to compute the sum for a range with assignment
ll compute_sum(ll s, ll e, ll A, ll B, ll L_prime) {
    ll cnt = e - s + 1;
    ll sum_x = (s + e) * cnt / 2;
    ll term1 = A * sum_x;
    ll floor_s = floor_sum_func(A, 0, B, e + 1) - floor_sum_func(A, 0, B, s);
    ll sum_mod = term1 - B * floor_s;
    ll adjust = (A * (L_prime - 1)) % B;
    sum_mod = sum_mod - adjust * cnt;
    // Handle negative modulo
    sum_mod %= B;
    if (sum_mod < 0) sum_mod += B;
    return sum_mod;
}

// Create a new node
Node* new_node() {
    Node* node = (Node*)malloc(sizeof(Node));
    node->left = node->right = NULL;
    node->sum = 0;
    node->has_lazy = 0;
    node->A = node->B = node->L = 0;
    node->time = -1;
    return node;
}

// Push down the lazy updates
void push_down(Node* node, ll s, ll e) {
    if (node->has_lazy) {
        ll mid = s + (e - s) / 2;
        if (!node->left) node->left = new_node();
        if (!node->right) node->right = new_node();
        // Assign to left child
        node->left->has_lazy = 1;
        node->left->A = node->A;
        node->left->B = node->B;
        node->left->L = node->L;
        node->left->time = node->time;
        node->left->sum = compute_sum(s, mid, node->A, node->B, node->L + (s - node->L));
        // Assign to right child
        node->right->has_lazy = 1;
        node->right->A = node->A;
        node->right->B = node->B;
        node->right->L = node->L + (mid + 1 - s);
        node->right->time = node->time;
        node->right->sum = compute_sum(mid + 1, e, node->A, node->B, node->L + (mid + 1 - s));
        // Clear current node's lazy
        node->has_lazy = 0;
    }
}

// Update function
void update(Node* node, ll s, ll e, ll l, ll r, ll A, ll B, ll L_prime, int time_stamp) {
    if (r < s || e < l)
        return;
    if (l <= s && e <= r) {
        node->has_lazy = 1;
        node->A = A;
        node->B = B;
        node->L = L_prime + (s - l);
        node->time = time_stamp;
        node->sum = compute_sum(s, e, A, B, node->L);
        return;
    }
    push_down(node, s, e);
    ll mid = s + (e - s) / 2;
    if (node->left == NULL) node->left = new_node();
    if (node->right == NULL) node->right = new_node();
    update(node->left, s, mid, l, r, A, B, L_prime, time_stamp);
    update(node->right, mid + 1, e, l, r, A, B, L_prime, time_stamp);
    node->sum = node->left->sum + node->right->sum;
}

// Query function
ll query(Node* node, ll s, ll e, ll l, ll r) {
    if (node == NULL || r < s || e < l)
        return 0;
    if (l <= s && e <= r) {
        return node->sum;
    }
    push_down(node, s, e);
    ll mid = s + (e - s) / 2;
    return query(node->left, s, mid, l, r) + query(node->right, mid + 1, e, l, r);
}

int main(){
    ll n, q;
    scanf("%lld %lld", &n, &q);
    Node* root = new_node();
    while(q--){
        int type;
        scanf("%d", &type);
        if(type == 1){
            ll L, R, A, B;
            scanf("%lld %lld %lld %lld", &L, &R, &A, &B);
            current_time++;
            update(root, 1, n, L, R, A, B, L, current_time);
        }
        else{
            ll L, R;
            scanf("%lld %lld", &L, &R);
            ll res = query(root, 1, n, L, R);
            printf("%lld\n", res);
        }
    }
    return 0;
}