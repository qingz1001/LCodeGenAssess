#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int type; // 1 for entering, -1 for leaving
    int y1;
    int y2;
} Event;

typedef struct {
    int l, r;
    int count;
    int length;
} Node;

int cmp_event(const void *a, const void *b) {
    Event *ea = (Event *)a;
    Event *eb = (Event *)b;
    if (ea->x != eb->x)
        return ea->x - eb->x;
    return ea->type - eb->type;
}

int cmp_int(const void *a, const void *b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    return ia - ib;
}

int y_coords[20000];
int y_num = 0;

Node tree_nodes[80000];
int idx = 1;

void build(int node, int l, int r) {
    tree_nodes[node].l = l;
    tree_nodes[node].r = r;
    tree_nodes[node].count = 0;
    tree_nodes[node].length = 0;
    if (l + 1 >= r) return;
    int mid = (l + r) / 2;
    build(2*node, l, mid);
    build(2*node+1, mid, r);
}

void update_tree(int node, int l, int r, int val) {
    if (tree_nodes[node].l >= r || tree_nodes[node].r <= l)
        return;
    if (tree_nodes[node].l >= l && tree_nodes[node].r <= r) {
        tree_nodes[node].count += val;
    } else {
        update_tree(2*node, l, r, val);
        update_tree(2*node+1, l, r, val);
    }
    if (tree_nodes[node].count > 0) {
        tree_nodes[node].length = y_coords[tree_nodes[node].r] - y_coords[tree_nodes[node].l];
    }
    else {
        if (tree_nodes[node].l +1 >= tree_nodes[node].r)
            tree_nodes[node].length = 0;
        else
            tree_nodes[node].length = tree_nodes[2*node].length + tree_nodes[2*node+1].length;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    Event events[20000];
    int ys[20000];
    int y_count = 0;
    for(int i=0;i<n;i++){
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        if(x1 > x2){
            int tmp = x1; x1 = x2; x2 = tmp;
        }
        if(y1 > y2){
            int tmp = y1; y1 = y2; y2 = tmp;
        }
        events[2*i].x = x1;
        events[2*i].type = 1;
        events[2*i].y1 = y1;
        events[2*i].y2 = y2;
        events[2*i+1].x = x2;
        events[2*i+1].type = -1;
        events[2*i+1].y1 = y1;
        events[2*i+1].y2 = y2;
        ys[y_count++] = y1;
        ys[y_count++] = y2;
    }
    qsort(ys, y_count, sizeof(int), cmp_int);
    y_num = 0;
    y_coords[y_num++] = ys[0];
    for(int i=1;i<y_count;i++){
        if(ys[i] != ys[i-1]){
            y_coords[y_num++] = ys[i];
        }
    }
    for(int i=0;i<2*n;i++){
        // Binary search for y1
        int left=0, right=y_num-1, mid, pos;
        while(left <= right){
            mid = (left + right)/2;
            if(y_coords[mid] == events[i].y1){
                pos = mid;
                break;
            }
            else if(y_coords[mid] < events[i].y1){
                left = mid +1;
            }
            else{
                right = mid -1;
            }
        }
        events[i].y1 = pos;
        // Binary search for y2
        left=0; right=y_num-1;
        while(left <= right){
            mid = (left + right)/2;
            if(y_coords[mid] == events[i].y2){
                pos = mid;
                break;
            }
            else if(y_coords[mid] < events[i].y2){
                left = mid +1;
            }
            else{
                right = mid -1;
            }
        }
        events[i].y2 = pos;
    }
    qsort(events, 2*n, sizeof(Event), cmp_event);
    build(1, 0, y_num-1);
    long long area = 0;
    int last_x = events[0].x;
    update_tree(1, events[0].y1, events[0].y2, events[0].type);
    for(int i=1;i<2*n;i++){
        int delta_x = events[i].x - last_x;
        area += (long long)delta_x * tree_nodes[1].length;
        update_tree(1, events[i].y1, events[i].y2, events[i].type);
        last_x = events[i].x;
    }
    printf("%lld\n", area);
    return 0;
}