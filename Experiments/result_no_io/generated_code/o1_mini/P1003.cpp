#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a, b, g, k;
} Carpet;

int main(){
    int n;
    if(scanf("%d", &n)!=1){
        return 0;
    }
    Carpet *carpets = (Carpet*)malloc(n * sizeof(Carpet));
    for(int i=0;i<n;i++){
        scanf("%d %d %d %d", &carpets[i].a, &carpets[i].b, &carpets[i].g, &carpets[i].k);
    }
    int x, y;
    scanf("%d %d", &x, &y);
    int res = -1;
    for(int i=n-1;i>=0;i--){
        if(x >= carpets[i].a && x <= carpets[i].a + carpets[i].g &&
           y >= carpets[i].b && y <= carpets[i].b + carpets[i].k){
            res = i +1;
            break;
        }
    }
    printf("%d\n", res);
    free(carpets);
    return 0;
}