#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll max_val;
    ll lazy;
} Node;

Node tree_nodes[320000];
ll coords[80000];
int coord_size = 0;

int cmp_ll(const void *a, const void *b) {
    ll aa = *(ll*)a;
    ll bb = *(ll*)b;
    if (aa < bb) return -1;
    if (aa > bb) return 1;
    return 0;
}

int lower_bound_ll(ll key) {
    int left = 0, right = coord_size;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (coords[mid] < key) left = mid + 1;
        else right = mid;
    }
    return left;
}

void push_down(int node, int l, int r) {
    if (tree_nodes[node].lazy != 0) {
        int mid = (l + r) / 2;
        int left_child = node * 2;
        int right_child = node * 2 + 1;

        if (tree_nodes[left_child].max_val < tree_nodes[node].lazy) {
            tree_nodes[left_child].max_val = tree_nodes[node].lazy;
            if (tree_nodes[left_child].lazy < tree_nodes[node].lazy)
                tree_nodes[left_child].lazy = tree_nodes[node].lazy;
        }

        if (tree_nodes[right_child].max_val < tree_nodes[node].lazy) {
            tree_nodes[right_child].max_val = tree_nodes[node].lazy;
            if (tree_nodes[right_child].lazy < tree_nodes[node].lazy)
                tree_nodes[right_child].lazy = tree_nodes[node].lazy;
        }

        tree_nodes[node].lazy = 0;
    }
}

void update_range(int node, int l, int r, int ul, int ur, ll H) {
    if (ur <= l || r <= ul) return;
    if (ul <= l && r <= ur) {
        if (tree_nodes[node].max_val < H) {
            tree_nodes[node].max_val = H;
            if (tree_nodes[node].lazy < H)
                tree_nodes[node].lazy = H;
        }
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    update_range(node*2, l, mid, ul, ur, H);
    update_range(node*2+1, mid, r, ul, ur, H);
    if (tree_nodes[node*2].max_val > tree_nodes[node*2+1].max_val)
        tree_nodes[node].max_val = tree_nodes[node*2].max_val;
    else
        tree_nodes[node].max_val = tree_nodes[node*2+1].max_val;
}

ll total = 0;

void calculate_sum(int node, int l, int r) {
    if (l + 1 == r) {
        total += tree_nodes[node].max_val * (coords[r] - coords[l]);
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    calculate_sum(node*2, l, mid);
    calculate_sum(node*2+1, mid, r);
}

int main(){
    int N;
    scanf("%d", &N);
    typedef struct {
        ll a, b, h;
    } Building;
    Building buildings[N];
    for(int i=0;i<N;i++){
        scanf("%lld %lld %lld", &buildings[i].a, &buildings[i].b, &buildings[i].h);
        coords[coord_size++] = buildings[i].a;
        coords[coord_size++] = buildings[i].b;
    }
    qsort(coords, coord_size, sizeof(ll), cmp_ll);
    int unique_size = 0;
    for(int i=0;i<coord_size;i++){
        if(i == 0 || coords[i] != coords[i-1]){
            coords[unique_size++] = coords[i];
        }
    }
    coord_size = unique_size;
    for(int i=0;i<N;i++){
        int ul = lower_bound_ll(buildings[i].a);
        int ur = lower_bound_ll(buildings[i].b);
        update_range(1, 0, coord_size, ul, ur, buildings[i].h);
    }
    calculate_sum(1, 0, coord_size);
    printf("%lld\n", total);
    return 0;
}