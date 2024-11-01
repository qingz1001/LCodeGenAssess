#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    int x = *(int*)a;
    int y = *(int*)b;
    return x - y;
}

int main(){
    int n;
    scanf("%d", &n);
    int cakes[50];
    for(int i=0;i<n;i++) scanf("%d", &cakes[i]);
    int m;
    scanf("%d", &m);
    int mouths[1024];
    for(int i=0;i<m;i++) scanf("%d", &mouths[i]);
    qsort(cakes, n, sizeof(int), compare);
    qsort(mouths, m, sizeof(int), compare);
    int used[1024];
    for(int i=0;i<m;i++) used[i]=0;
    int count=0;
    for(int i=0;i<n;i++){
        int rem = cakes[i];
        for(int j=0;j<m;j++){
            if(!used[j] && mouths[j] <= rem){
                used[j]=1;
                rem -= mouths[j];
                count++;
            }
        }
    }
    printf("%d\n", count);
    return 0;
}