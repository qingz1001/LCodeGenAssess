#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int l;
    int w;
} Stick;

int compare(const void *a, const void *b){
    Stick *s1 = (Stick *)a;
    Stick *s2 = (Stick *)b;
    if(s2->w != s1->w){
        return s2->w - s1->w;
    }
    return s2->l - s1->l;
}

int main(){
    int n;
    scanf("%d", &n);
    Stick sticks[n];
    for(int i=0;i<n;i++){
        scanf("%d %d", &sticks[i].l, &sticks[i].w);
    }
    qsort(sticks, n, sizeof(Stick), compare);
    int prep = 1;
    int current_l = sticks[0].l;
    int current_w = sticks[0].w;
    for(int i=1;i<n;i++){
        if(current_l >= sticks[i].l && current_w >= sticks[i].w){
            // No prep needed
        }
        else{
            prep++;
            current_l = sticks[i].l;
            current_w = sticks[i].w;
        }
    }
    printf("%d\n", prep);
    return 0;
}