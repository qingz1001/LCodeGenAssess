#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned long long ull;

#define MAXN 100005
#define SIZE 2000003

typedef struct {
    ull key;
    int used;
} HashEntry;

HashEntry table[SIZE];
ull person_hash[MAXN];
int person_room_arr[MAXN];
ull room_hash_arr[MAXN];
int room_count_arr[MAXN];

int find_or_insert(ull key){
    ull pos = key % SIZE;
    while(table[pos].used){
        if(table[pos].key == key){
            return 1;
        }
        pos = (pos + 1) % SIZE;
    }
    table[pos].key = key;
    table[pos].used = 1;
    return 0;
}

int main(){
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    
    // Initialize person_hash with pseudo-random values
    ull seed = 88172645463325252ULL;
    for(int i=1;i<=n;i++){
        seed = seed * 2862933555777941757ULL + 3037000493ULL;
        person_hash[i] = seed;
    }
    
    // Initialize all persons to room 1
    for(int i=1;i<=n;i++){
        person_room_arr[i] =1;
    }
    room_count_arr[1] =n;
    
    // Initialize room_hash_arr
    room_hash_arr[1] =0;
    for(int i=1;i<=n;i++){
        room_hash_arr[1] += person_hash[i];
    }
    for(int j=2;j<=m;j++){
        room_hash_arr[j] =0;
        room_count_arr[j]=0;
    }
    
    char op[2];
    int a, b;
    while(q--){
        scanf("%s", op);
        if(op[0] == 'C'){
            scanf("%d %d", &a, &b);
            int old_room = person_room_arr[a];
            if(old_room != b){
                room_hash_arr[old_room] -= person_hash[a];
                room_count_arr[old_room]--;
                room_hash_arr[b] += person_hash[a];
                room_count_arr[b]++;
                person_room_arr[a] = b;
            }
        }
        else if(op[0] == 'W'){
            scanf("%d %d", &a, &b);
            ull total =0;
            for(int room =a; room <=b; room++){
                if(room_hash_arr[room] ==0) continue;
                if(!find_or_insert(room_hash_arr[room])){
                    total += room_count_arr[room];
                }
            }
            printf("%llu\n", total);
        }
    }
    return 0;
}