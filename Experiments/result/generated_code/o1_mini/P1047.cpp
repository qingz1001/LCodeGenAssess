#include <stdio.h>

int main(){
    int l, m;
    scanf("%d %d", &l, &m);
    int removed[l+1];
    for(int i=0;i<=l;i++) removed[i]=0;
    for(int i=0;i<m;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        for(int j=u; j<=v; j++) removed[j]=1;
    }
    int remaining=0;
    for(int i=0;i<=l;i++) if(!removed[i]) remaining++;
    printf("%d", remaining);
    return 0;
}