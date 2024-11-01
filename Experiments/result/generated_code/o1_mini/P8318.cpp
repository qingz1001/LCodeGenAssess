#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int type;
    int x;
    int y;
} Operation;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    unsigned long long *a = (unsigned long long*)malloc((n+1)*sizeof(unsigned long long));
    for(int i=1;i<=n;i++) scanf("%llu", &a[i]);
    Operation *ops = (Operation*)malloc(m * sizeof(Operation));
    for(int i=0;i<m;i++) scanf("%d %d %d", &ops[i].type, &ops[i].x, &ops[i].y);
    for(int i=m-1;i>=0;i--){
        if(ops[i].type == 1){
            a[ops[i].x] -= a[ops[i].y];
        }
        else{
            a[ops[i].x] /= a[ops[i].y];
        }
    }
    for(int i=1;i<=n;i++) printf("%llu%c", a[i], i==n? '\n':' ');
    free(a);
    free(ops);
    return 0;
}