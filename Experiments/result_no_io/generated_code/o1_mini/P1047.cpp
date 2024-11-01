#include <stdio.h>

int main(){
    int l, m;
    scanf("%d %d", &l, &m);
    int removed[10001] = {0};
    for(int i=0;i<m;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        for(int j=u; j<=v; j++) {
            removed[j] = 1;
        }
    }
    int total = l + 1;
    int count = 0;
    for(int i=0; i<=l; i++) {
        if(!removed[i]) count++;
    }
    printf("%d\n", count);
    return 0;
}