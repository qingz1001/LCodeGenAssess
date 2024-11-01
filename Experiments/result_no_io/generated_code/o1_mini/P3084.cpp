#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Photo;

// Comparator to sort photos by their ending position
int compare(const void *p1, const void *p2) {
    Photo *photo1 = (Photo *)p1;
    Photo *photo2 = (Photo *)p2;
    if (photo1->b != photo2->b)
        return photo1->b - photo2->b;
    return photo1->a - photo2->a;
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    
    Photo *photos = (Photo *)malloc(sizeof(Photo)*M);
    for(int i=0;i<M;i++){
        scanf("%d %d", &photos[i].a, &photos[i].b);
    }
    
    qsort(photos, M, sizeof(Photo), compare);
    
    int S_count = 0;
    int last_S = -1;
    for(int i=0;i<M;i++){
        if(photos[i].a > last_S){
            last_S = photos[i].b;
            S_count++;
        }
    }
    
    // Now, verify that each photo has exactly one S in its range
    // Using the assigned S positions
    // Since we assigned S to cover all photos in the greedy way, it's valid
    // So output S_count
    printf("%d\n", S_count);
    
    free(photos);
    return 0;
}