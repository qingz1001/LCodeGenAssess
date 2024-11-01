#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_A 1000001
#define BUFFER_SIZE 1 << 20

typedef struct {
    int l;
    int r;
    int idx;
} Query;

char input_buffer[BUFFER_SIZE];
int input_pos = 0, input_len = 0;

char output_buffer[BUFFER_SIZE];
int output_pos = 0;

int read_char() {
    if (input_pos == input_len) {
        input_len = fread(input_buffer, 1, BUFFER_SIZE, stdin);
        if (input_len == 0) return EOF;
        input_pos = 0;
    }
    return input_buffer[input_pos++];
}

int read_int() {
    int x = 0, c;
    while ((c = read_char()) < '0' || c > '9') {
        if (c == EOF) return x;
    }
    do {
        x = x * 10 + (c - '0');
    } while ((c = read_char()) >= '0' && c <= '9');
    return x;
}

void write_int(int x) {
    if (output_pos + 12 >= BUFFER_SIZE) {
        fwrite(output_buffer, 1, output_pos, stdout);
        output_pos = 0;
    }
    if (x == 0) {
        output_buffer[output_pos++] = '0';
        output_buffer[output_pos++] = '\n';
        return;
    }
    char tmp[12];
    int len = 0;
    while (x > 0) {
        tmp[len++] = '0' + (x % 10);
        x /= 10;
    }
    for (int i = len - 1; i >= 0; i--)
        output_buffer[output_pos++] = tmp[i];
    output_buffer[output_pos++] = '\n';
}

int cmp(const void *a, const void *b) {
    int r1 = ((Query*)a)->r;
    int r2 = ((Query*)b)->r;
    return r1 - r2;
}

int BIT_tree[500005];
int n, m;

void BIT_add(int idx, int val) {
    while (idx <= n) {
        BIT_tree[idx] += val;
        idx += idx & -idx;
    }
}

int BIT_sum(int idx) {
    int res = 0;
    while (idx > 0) {
        res += BIT_tree[idx];
        idx -= idx & -idx;
    }
    return res;
}

int main(){
    n = read_int();
    int *a = (int*)malloc((n + 1) * sizeof(int));
    for(int i=1;i<=n;i++) a[i] = read_int();
    m = read_int();
    Query *queries = (Query*)malloc(m * sizeof(Query));
    for(int i=0;i<m;i++){
        queries[i].l = read_int();
        queries[i].r = read_int();
        queries[i].idx = i;
    }
    qsort(queries, m, sizeof(Query), cmp);
    int *ans = (int*)malloc(m * sizeof(int));
    memset(BIT_tree, 0, sizeof(int)*(n+1));
    memset((int*)malloc(sizeof(int)*MAX_A), 0, sizeof(int)*MAX_A);
    int *last = (int*)calloc(MAX_A, sizeof(int));
    int current_r = 0;
    for(int i=0;i<m;i++){
        while(current_r < queries[i].r){
            current_r++;
            int val = a[current_r];
            if(last[val]){
                BIT_add(last[val], -1);
            }
            BIT_add(current_r, 1);
            last[val] = current_r;
        }
        ans[queries[i].idx] = BIT_sum(queries[i].r) - BIT_sum(queries[i].l - 1);
    }
    for(int i=0;i<m;i++) write_int(ans[i]);
    if(output_pos){
        fwrite(output_buffer, 1, output_pos, stdout);
    }
    free(a);
    free(queries);
    free(ans);
    free(last);
    return 0;
}