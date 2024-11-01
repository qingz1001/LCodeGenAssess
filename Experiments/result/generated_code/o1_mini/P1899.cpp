#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int Pi;
    int delta;
} MagicItem;

int cmp(const void *a, const void *b) {
    MagicItem *itemA = (MagicItem *)a;
    MagicItem *itemB = (MagicItem *)b;
    if (itemA->Pi != itemB->Pi)
        return itemA->Pi - itemB->Pi;
    return 0;
}

int main(){
    int N, Pi;
    scanf("%d %d", &N, &Pi);
    // To consume the remaining newline after scanf
    getchar();
    long long S = 0;
    MagicItem magicList[1000];
    int magicCount = 0;
    char line[50];
    for(int i=0; i<N; i++){
        if(fgets(line, sizeof(line), stdin) == NULL){
            break;
        }
        int p1, p2;
        int cnt = sscanf(line, "%d %d", &p1, &p2);
        if(cnt ==1){
            // Normal item
            S += p1;
        }
        else if(cnt ==2){
            // Magic item
            S += p1;
            int delta = p2 - p1 - Pi;
            if(delta >0){
                magicList[magicCount].Pi = Pi;
                magicList[magicCount].delta = delta;
                magicCount++;
            }
        }
    }
    qsort(magicList, magicCount, sizeof(MagicItem), cmp);
    for(int i=0; i<magicCount; i++){
        if(S >= magicList[i].Pi){
            S += magicList[i].delta;
        }
    }
    printf("%lld\n", S);
    return 0;
}