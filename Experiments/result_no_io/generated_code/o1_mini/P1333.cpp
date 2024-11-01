#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char s[11];
} Color;

int cmp_color(const void *a, const void *b) {
    return strcmp(((Color*)a)->s, ((Color*)b)->s);
}

int find_set(int *parent, int x) {
    if (parent[x] != x)
        parent[x] = find_set(parent, parent[x]);
    return parent[x];
}

int main(){
    int max_sticks = 250000;
    Color *colors = malloc(max_sticks * 2 * sizeof(Color));
    char a[11], b[11];
    int count =0;
    while(scanf("%s %s", a, b)==2){
        strcpy(colors[count].s, a);
        count++;
        strcpy(colors[count].s, b);
        count++;
        if(count >= max_sticks *2){
            max_sticks *=2;
            colors = realloc(colors, max_sticks * sizeof(Color));
        }
    }
    qsort(colors, count, sizeof(Color), cmp_color);
    int unique = 0;
    for(int i=1;i<count;i++) {
        if(strcmp(colors[i].s, colors[unique].s)!=0){
            unique++;
            colors[unique] = colors[i];
        }
    }
    unique++;
    // Assign IDs
    // Now, to map each color to its ID via binary search
    // Re-process the sticks
    // Rewind input
    rewind(stdin);
    int *deg = calloc(unique, sizeof(int));
    int *parent = malloc(unique * sizeof(int));
    for(int i=0;i<unique;i++) parent[i]=i;
    while(scanf("%s %s", a, b)==2){
        // Binary search
        int left=0, right=unique-1, mid, id1, id2;
        while(left <= right){
            mid = left + (right - left)/2;
            int cmp = strcmp(a, colors[mid].s);
            if(cmp ==0){id1=mid; break;}
            else if(cmp <0){right=mid-1;}
            else{left=mid+1;}
        }
        left=0, right=unique-1;
        while(left <= right){
            mid = left + (right - left)/2;
            int cmp = strcmp(b, colors[mid].s);
            if(cmp ==0){id2=mid; break;}
            else if(cmp <0){right=mid-1;}
            else{left=mid+1;}
        }
        deg[id1]++;
        deg[id2]++;
        int set1 = find_set(parent, id1);
        int set2 = find_set(parent, id2);
        if(set1 != set2){
            parent[set1] = set2;
        }
    }
    // Find number of connected components with degree >0
    int first = -1, odd =0;
    for(int i=0;i<unique;i++){
        if(deg[i]>0){
            if(first == -1){
                first = find_set(parent, i);
            }
            else{
                if(find_set(parent, i) != first){
                    printf("Impossible");
                    free(colors);
                    free(deg);
                    free(parent);
                    return 0;
                }
            }
            if(deg[i]%2 !=0) odd++;
        }
    }
    if(odd ==0 || odd ==2){
        printf("Possible");
    }
    else{
        printf("Impossible");
    }
    free(colors);
    free(deg);
    free(parent);
}