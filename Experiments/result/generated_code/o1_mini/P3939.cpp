#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HASH_SIZE 800003
#define MAX_N 100005
#define MAX_M 100005

typedef struct {
    unsigned int keys[MAX_HASH_SIZE];
    int values[MAX_HASH_SIZE];
    int occupied[MAX_HASH_SIZE];
    int size;
} HashMap;

int get_id(unsigned int color, HashMap* map) {
    int idx = color % MAX_HASH_SIZE;
    while(map->occupied[idx] && map->keys[idx] != color){
        idx = (idx + 1) % MAX_HASH_SIZE;
    }
    if(map->occupied[idx] && map->keys[idx] == color){
        return map->values[idx];
    }
    map->keys[idx] = color;
    map->values[idx] = map->size;
    map->occupied[idx] = 1;
    return map->size++;
} 

typedef struct {
    int type;
    int l;
    int r;
    int c;
    int x;
} Query;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    unsigned int a_raw[MAX_N];
    int a[MAX_N];
    HashMap map;
    map.size = 0;
    memset(map.occupied, 0, sizeof(map.occupied));
    
    for(int i=1;i<=n;i++){
        scanf("%u", &a_raw[i]);
        a[i] = get_id(a_raw[i], &map);
    }
    
    Query* queries = (Query*)malloc(sizeof(Query)*m);
    for(int i=0;i<m;i++){
        int type;
        scanf("%d", &type);
        queries[i].type = type;
        if(type ==1){
            unsigned int tmp;
            scanf("%d %d %u", &queries[i].l, &queries[i].r, &tmp);
            queries[i].c = get_id(tmp, &map);
        }
        else{
            scanf("%d", &queries[i].x);
        }
    }
    
    int k = map.size;
    int* total = (int*)calloc(k, sizeof(int));
    for(int i=1;i<=n;i++) total[a[i]]++;
    
    for(int i=0;i<m;i++){
        if(queries[i].type ==1){
            int l = queries[i].l;
            int r = queries[i].r;
            int c = queries[i].c;
            int len = r - l +1;
            int count =0;
            if(len <=20){
                for(int j=l; j<=r; j++) if(a[j]==c) count++;
            }
            else{
                count = total[c];
                // Count in [1, l-1]
                if(l >1){
                    int limit = (l-1) < (l-1) ? (l-1) : (l-1);
                    for(int j=1; j<l; j++) if(a[j]==c) count--;
                }
                // Count in [r+1, n]
                if(r < n){
                    for(int j=r+1; j<=n; j++) if(a[j]==c) count--;
                }
            }
            printf("%d\n", count);
        }
        else{
            int x = queries[i].x;
            if(x >=1 && x < n){
                if(a[x] != a[x+1]){
                    // Swap
                    a[x] ^= a[x+1];
                    a[x+1] ^= a[x];
                    a[x] ^= a[x+1];
                }
            }
        }
    }
    
    free(queries);
    free(total);
    return 0;
}