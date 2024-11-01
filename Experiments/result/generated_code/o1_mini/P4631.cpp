#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    long long x;
    long long y;
    long long r;
    int idx;
} Circle;

int cmp(const void *a, const void *b) {
    Circle *c1 = (Circle*)a;
    Circle *c2 = (Circle*)b;
    if (c2->r != c1->r)
        return (c2->r > c1->r) - (c2->r < c1->r);
    return c1->idx - c2->idx;
}

int main(){
    int n;
    scanf("%d", &n);
    Circle *circles = (Circle*)malloc(n * sizeof(Circle));
    for(int i=0;i<n;i++){
        scanf("%lld %lld %lld", &circles[i].x, &circles[i].y, &circles[i].r);
        circles[i].idx = i+1;
    }
    qsort(circles, n, sizeof(Circle), cmp);
    int *ans = (int*)malloc((n+1) * sizeof(int));
    for(int i=0;i<n;i++) ans[circles[i].idx] = 0;
    for(int i=0;i<n;i++){
        if(ans[circles[i].idx] != 0) continue;
        ans[circles[i].idx] = circles[i].idx;
        for(int j=i+1;j<n;j++){
            if(ans[circles[j].idx] == 0){
                long long dx = circles[i].x - circles[j].x;
                long long dy = circles[i].y - circles[j].y;
                long long dist_sq = dx*dx + dy*dy;
                long long r_sum = circles[i].r + circles[j].r;
                if(dist_sq <= r_sum * r_sum){
                    ans[circles[j].idx] = circles[i].idx;
                }
            }
        }
    }
    for(int i=1;i<=n;i++) printf("%d%c", ans[i], i==n? '\n':' ');
    free(circles);
    free(ans);
    return 0;
}