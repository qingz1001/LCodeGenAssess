#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_TS 16

int n;
long long c;
char must_on_bits[MAX_N];
char must_off_bits[MAX_N];

struct Transformation {
    char bits[MAX_N + 1]; // +1 for null terminator
};

// Global buttons masks
char button_masks[4][MAX_N];

// Function to initialize button masks
void initialize_buttons() {
    // Button 1: All '1's
    for(int i = 0; i < n; i++) {
        button_masks[0][i] = '1';
    }

    // Button 2: Odd-numbered lights (1-based: 1,3,5,... => 0,2,4,...)
    for(int i = 0; i < n; i++) {
        button_masks[1][i] = (i % 2 == 0) ? '1' : '0';
    }

    // Button 3: Even-numbered lights (1-based: 2,4,6,... => 1,3,5,...)
    for(int i = 0; i < n; i++) {
        button_masks[2][i] = (i % 2 == 1) ? '1' : '0';
    }

    // Button 4: 3k+1 lights (1,4,7,... => 0,3,6,...)
    for(int i = 0; i < n; i++) {
        button_masks[3][i] = (i % 3 == 0) ? '1' : '0';
    }
}

// Function to count number of set bits in s
int count_bits(int s) {
    int count = 0;
    for(int i = 0; i < 4; i++) {
        if (s & (1 << i)) count++;
    }
    return count;
}

// Function to check if two transformations are equal
int equal_ts(struct Transformation *a, struct Transformation *b) {
    return strcmp(a->bits, b->bits) == 0;
}

// Global n for comparator
int global_n;

// Comparator for qsort
int compare_ts(const void *a, const void *b) {
    struct Transformation *ta = (struct Transformation *)a;
    struct Transformation *tb = (struct Transformation *)b;
    for(int i = 0; i < global_n; i++) {
        if(ta->bits[i] < tb->bits[i]) return -1;
        if(ta->bits[i] > tb->bits[i]) return 1;
    }
    return 0;
}

int main(){
    // Read n
    if(scanf("%d", &n)!=1){
        return 0;
    }

    // Read c
    if(scanf("%lld", &c)!=1){
        return 0;
    }

    // Initialize must_on and must_off
    memset(must_on_bits, 0, sizeof(must_on_bits));
    memset(must_off_bits, 0, sizeof(must_off_bits));

    // Read 'ON' list
    int x;
    while(scanf("%d", &x)==1 && x != -1){
        if(x >=1 && x <=n){
            must_on_bits[x-1] = 1;
        }
    }

    // Read 'OFF' list
    while(scanf("%d", &x)==1 && x != -1){
        if(x >=1 && x <=n){
            must_off_bits[x-1] = 1;
        }
    }

    // Initialize button masks
    initialize_buttons();

    // List of possible transformations
    struct Transformation ts_list[MAX_TS];
    int ts_count = 0;

    // Enumerate all subsets of buttons
    for(int s = 0; s < (1<<4); s++){
        int m = count_bits(s);
        if(m > c) continue;
        if((c - m) %2 !=0) continue;

        // Create transformation starting with all '1's
        struct Transformation current;
        for(int i = 0; i < n; i++) {
            current.bits[i] = '1';
        }
        current.bits[n] = '\0';

        // Apply buttons in subset s
        for(int b = 0; b < 4; b++) {
            if(s & (1 << b)){
                for(int i = 0; i < n; i++) {
                    if(button_masks[b][i] == '1'){
                        current.bits[i] = (current.bits[i] == '1') ? '0' : '1';
                    }
                }
            }
        }

        // Check against 'ON' and 'OFF' lists
        int valid = 1;
        for(int i = 0; i < n; i++) {
            if(must_on_bits[i] && current.bits[i] != '1'){
                valid = 0;
                break;
            }
            if(must_off_bits[i] && current.bits[i] != '0'){
                valid = 0;
                break;
            }
        }
        if(!valid) continue;

        // Check for duplicates
        int duplicate = 0;
        for(int t = 0; t < ts_count; t++) {
            if(equal_ts(&ts_list[t], &current)){
                duplicate = 1;
                break;
            }
        }
        if(!duplicate){
            ts_list[ts_count++] = current;
            if(ts_count >= MAX_TS){
                break;
            }
        }
    }

    if(ts_count ==0){
        printf("IMPOSSIBLE\n");
        return 0;
    }

    // Sort the transformations
    global_n = n;
    qsort(ts_list, ts_count, sizeof(struct Transformation), compare_ts);

    // Print the sorted transformations
    for(int t =0; t < ts_count; t++){
        for(int i =0; i < n; i++){
            putchar(ts_list[t].bits[i]);
        }
        putchar('\n');
    }

    return 0;
}