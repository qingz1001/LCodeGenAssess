#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_Q 300005
#define MAX_NODE 1000005

typedef struct {
    int next[10];
    int fail;
    int output;
    int *occ;
    int occ_size;
    int occ_cap;
} Node;

Node nodes_arr[MAX_NODE];
int node_cnt = 1;

int queue[MAX_NODE];
int head = 0, tail = 0;

int main(){
    int n, q;
    scanf("%d %d", &n, &q);
    char s[MAX_N];
    scanf("%s", s);
    // Read queries and build unique patterns using trie
    int *query_ids = (int*)malloc(q * sizeof(int));
    char **patterns = (char**)malloc(q * sizeof(char*));
    for(int i=0;i<q;i++){
        int l, r;
        scanf("%d %d", &l, &r);
        int len = r - l +1;
        patterns[i] = (char*)malloc((len +1)*sizeof(char));
        strncpy(patterns[i], s + l -1, len);
        patterns[i][len] = '\0';
    }
    // Build trie
    int *pattern_id = (int*)calloc(q, sizeof(int));
    int unique =0;
    // To map patterns to unique ids, use trie
    memset(nodes_arr, 0, sizeof(nodes_arr));
    for(int i=0;i<q;i++){
        int current =0;
        int len = strlen(patterns[i]);
        for(int j=0;j<len;j++){
            int c = patterns[i][j]-'0';
            if(nodes_arr[current].next[c]==0){
                nodes_arr[current].next[c] = node_cnt;
                node_cnt++;
            }
            current = nodes_arr[current].next[c];
        }
        if(nodes_arr[current].output ==0){
            nodes_arr[current].output = unique +1;
            unique++;
        }
        pattern_id[i] = nodes_arr[current].output -1;
    }
    int total_patterns = unique;
    // Initialize occurrence lists
    int **occ_list = (int**)malloc(total_patterns * sizeof(int*));
    int *occ_size = (int*)calloc(total_patterns, sizeof(int));
    int *occ_cap = (int*)calloc(total_patterns, sizeof(int));
    for(int i=0;i<total_patterns;i++){
        occ_cap[i] = 10;
        occ_list[i] = (int*)malloc(occ_cap[i]*sizeof(int));
    }
    // Build fail links
    // Initialize queue
    head=0; tail=0;
    for(int c=0;c<10;c++) {
        if(nodes_arr[0].next[c]){
            nodes_arr[nodes_arr[0].next[c]].fail =0;
            queue[tail++] = nodes_arr[0].next[c];
        }
    }
    while(head < tail){
        int current = queue[head++];
        for(int c=0;c<10;c++){
            if(nodes_arr[current].next[c]){
                int child = nodes_arr[current].next[c];
                int f = nodes_arr[current].fail;
                while(f !=0 && nodes_arr[f].next[c]==0) f = nodes_arr[f].fail;
                if(nodes_arr[f].next[c]) f = nodes_arr[f].next[c];
                nodes_arr[child].fail = f;
                if(nodes_arr[f].output){
                    nodes_arr[child].output = nodes_arr[f].output;
                }
                queue[tail++] = child;
            }
        }
    }
    // Traverse the string
    int state =0;
    for(int i=0;i<n;i++){
        int c = s[i]-'0';
        while(state !=0 && nodes_arr[state].next[c]==0) state = nodes_arr[state].fail;
        if(nodes_arr[state].next[c]) state = nodes_arr[state].next[c];
        if(nodes_arr[state].output){
            int id = nodes_arr[state].output -1;
            if(occ_size[id] == occ_cap[id]){
                occ_cap[id] *=2;
                occ_list[id] = (int*)realloc(occ_list[id], occ_cap[id]*sizeof(int));
            }
            occ_list[id][occ_size[id]++] = i - strlen(patterns[id]) +2;
        }
    }
    // Precompute answers
    long long *answers = (long long*)malloc(q * sizeof(long long));
    for(int i=0;i<q;i++){
        int id = pattern_id[i];
        int plen = strlen(patterns[i]);
        if(occ_size[id]==0){
            answers[i]=0;
            continue;
        }
        // C1_sum
        // a = min_start + len -1
        int min_start = occ_list[id][0];
        int a = min_start + plen -1;
        int b = n -2;
        long long C1=0;
        if(a <= b){
            int l = n -1 - b;
            int r = n -1 - a;
            if(r >= l){
                long long sum = ((long long)r*(r+1))/2 - ((long long)(l-1)*l)/2;
                C1 = sum;
            }
        }
        // C3_sum
        long long C3=0;
        for(int j=0;j<occ_size[id];j++) C3 += (long long)(occ_list[id][j] -2);
        // C2_sum
        long long C2=0;
        for(int j=0;j<occ_size[id];j++) C2 += (long long)(occ_list[id][j]-1) * (n - occ_list[id][j] - plen +1);
        answers[i] = C1 + C3 + C2;
    }
    // Print answers
    for(int i=0;i<q;i++) printf("%lld\n", answers[i]);
    // Free memory
    for(int i=0;i<q;i++) free(patterns[i]);
    free(patterns);
    free(query_ids);
    for(int i=0;i<total_patterns;i++) free(occ_list[i]);
    free(occ_list);
    free(occ_size);
    free(occ_cap);
    free(pattern_id);
    free(answers);
    return 0;
}