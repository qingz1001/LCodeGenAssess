#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int type; // 1 for entering, -1 for leaving
    int y1;
    int y2;
} Event;

int cmp(const void *a, const void *b) {
    Event *ea = (Event *)a;
    Event *eb = (Event *)b;
    if (ea->x != eb->x)
        return ea->x - eb->x;
    return eb->type - ea->type; // entering before leaving
}

typedef struct {
    int left, right;
    int count;
    long long length;
} Node;

int sortedYSize;
int sortedY[20000];
Node tree[80000];

void build(int node, int l, int r) {
    tree[node].left = l;
    tree[node].right = r;
    tree[node].count = 0;
    tree[node].length = 0;
    if (l + 1 >= r)
        return;
    int mid = (l + r) / 2;
    build(node*2, l, mid);
    build(node*2+1, mid, r);
}

void update(int node, int l, int r, int val) {
    if (tree[node].left >= r || tree[node].right <= l)
        return;
    if (tree[node].left >= l && tree[node].right <= r) {
        tree[node].count += val;
    }
    else {
        update(node*2, l, r, val);
        update(node*2+1, l, r, val);
    }
    if (tree[node].count > 0) {
        tree[node].length = sortedY[tree[node].right] - sortedY[tree[node].left];
    }
    else {
        if (tree[node].left + 1 >= tree[node].right)
            tree[node].length = 0;
        else
            tree[node].length = tree[node*2].length + tree[node*2+1].length;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    Event events[20000];
    int yList[20000];
    int idx = 0;
    for(int i=0;i<n;i++){
        int x1,y1,x2,y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        if(x1 > x2){
            int tmp = x1; x1 = x2; x2 = tmp;
        }
        if(y1 > y2){
            int tmp = y1; y1 = y2; y2 = tmp;
        }
        events[idx].x = x1;
        events[idx].type = 1;
        events[idx].y1 = y1;
        events[idx].y2 = y2;
        yList[idx] = y1;
        idx++;
        events[idx].x = x2;
        events[idx].type = -1;
        events[idx].y1 = y1;
        events[idx].y2 = y2;
        yList[idx] = y2;
        idx++;
    }
    int m = idx;
    // Sort yList and remove duplicates
    qsort(yList, m, sizeof(int), cmp);
    sortedYSize = 0;
    sortedY[sortedYSize++] = yList[0];
    for(int i=1;i<m;i++) {
        if(yList[i]!=sortedY[sortedYSize-1]){
            sortedY[sortedYSize++] = yList[i];
        }
    }
    // Sort events
    qsort(events, m, sizeof(Event), cmp);
    // Build segment tree
    build(1, 0, sortedYSize-1);
    long long area = 0;
    long long prevX = events[0].x;
    for(int i=0;i<m;i++){
        long long dx = events[i].x - prevX;
        area += dx * tree[1].length;
        int l = 0, r = sortedYSize-1;
        // Binary search for y1 and y2
        while(l < sortedYSize && sortedY[l] < events[i].y1) l++;
        while(r > 0 && sortedY[r] > events[i].y2) r--;
        update(1, l, r, events[i].type);
        prevX = events[i].x;
    }
    printf("%lld\n", area);
}