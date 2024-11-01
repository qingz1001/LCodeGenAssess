#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int type; // 1 for entering, -1 for leaving
    int y1;
    int y2;
} Event;

int cmp_events(const void* a, const void* b) {
    Event* ea = (Event*)a;
    Event* eb = (Event*)b;
    if (ea->x != eb->x)
        return ea->x - eb->x;
    return eb->type - ea->type;
}

int cmp_int(const void* a, const void* b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

typedef struct {
    int count;
    int length;
    int edge;
} Node;

int ys[10000];
int y_size = 0;

Node tree[40000];
int n_rect;

int build(int node, int l, int r) {
    tree[node].count = 0;
    tree[node].length = 0;
    tree[node].edge = 0;
    if (l + 1 >= r) {
        return 0;
    }
    int mid = (l + r) / 2;
    build(2*node, l, mid);
    build(2*node+1, mid, r);
    return 0;
}

int update_tree(int node, int l, int r, int ul, int ur, int val) {
    if (ur <= l || ul >= r) return 0;
    if (ul <= l && r <= ur) {
        tree[node].count += val;
    } else {
        int mid = (l + r) / 2;
        update_tree(2*node, l, mid, ul, ur, val);
        update_tree(2*node+1, mid, r, ul, ur, val);
    }
    if (tree[node].count > 0) {
        tree[node].length = ys[r] - ys[l];
        tree[node].edge = 2;
    }
    else {
        if (l + 1 >= r) {
            tree[node].length = 0;
            tree[node].edge = 0;
        }
        else {
            tree[node].length = tree[2*node].length + tree[2*node+1].length;
            tree[node].edge = tree[2*node].edge + tree[2*node+1].edge;
        }
    }
    return 0;
}

int main(){
    int N;
    scanf("%d", &N);
    Event events[2*N];
    int y_list[2*N];
    for(int i=0;i<N;i++){
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        events[2*i].x = x1;
        events[2*i].type = 1;
        events[2*i].y1 = y1;
        events[2*i].y2 = y2;
        events[2*i+1].x = x2;
        events[2*i+1].type = -1;
        events[2*i+1].y1 = y1;
        events[2*i+1].y2 = y2;
        y_list[y_size++] = y1;
        y_list[y_size++] = y2;
    }
    qsort(y_list, y_size, sizeof(int), cmp_int);
    int unique = 0;
    ys[unique++] = y_list[0];
    for(int i=1;i<y_size;i++) {
        if(y_list[i] != y_list[i-1]){
            ys[unique++] = y_list[i];
        }
    }
    y_size = unique;
    qsort(events, 2*N, sizeof(Event), cmp_events);
    build(1, 0, y_size-1);
    long long perimeter = 0;
    for(int i=0;i<2*N;i++){
        if(i > 0){
            long long dx = events[i].x - events[i-1].x;
            perimeter += (long long)(tree[1].edge) * dx;
        }
        int ul = 0, ur = y_size-1;
        // Find indices
        int a = events[i].y1;
        int b = events[i].y2;
        int left = 0, right = y_size-1;
        while(left < right){
            int mid = (left + right)/2;
            if(ys[mid] < a) left = mid +1;
            else right = mid;
        }
        ul = left;
        left = 0; right = y_size-1;
        while(left < right){
            int mid = (left + right)/2;
            if(ys[mid] < b) left = mid +1;
            else right = mid;
        }
        ur = left;
        update_tree(1, 0, y_size-1, ul, ur, events[i].type);
    }
    printf("%lld\n", perimeter);
    return 0;
}