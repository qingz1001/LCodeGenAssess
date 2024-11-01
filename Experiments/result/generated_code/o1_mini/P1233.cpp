#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int l;
    int w;
} Stick;

// Comparison function for qsort: decreasing l, then decreasing w
int cmp(const void *a, const void *b) {
    Stick *sa = (Stick *)a;
    Stick *sb = (Stick *)b;
    if (sb->l != sa->l)
        return sb->l - sa->l;
    return sb->w - sa->w;
}

int main(){
    int n;
    scanf("%d", &n);
    Stick sticks[n];
    for(int i=0;i<n;i++) {
        scanf("%d %d", &sticks[i].l, &sticks[i].w);
    }
    qsort(sticks, n, sizeof(Stick), cmp);
    int last_w[n];
    int m = 0;
    for(int i=0;i<n;i++){
        int w = sticks[i].w;
        int left = 0, right = m;
        while(left < right){
            int mid = left + (right - left) / 2;
            if(last_w[mid] >= w)
                right = mid;
            else
                left = mid + 1;
        }
        if(left < m){
            last_w[left] = w;
        }
        else{
            last_w[m++] = w;
        }
    }
    printf("%d\n", m);
    return 0;
}