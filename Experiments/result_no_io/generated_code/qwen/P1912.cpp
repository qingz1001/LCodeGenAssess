#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_L 30
#define MAX_P 10

typedef long long ll;

struct Sentence {
    char text[MAX_L];
    int length;
};

int compare(const void *a, const void *b) {
    return ((struct Sentence *)b)->length - ((struct Sentence *)a)->length;
}

ll calculate_cost(int N, int L, int P, struct Sentence sentences[], int lines[]) {
    ll cost = 0;
    for (int i = 0; i < N; ) {
        int line_length = 0;
        int j = i;
        while (j < N && line_length + sentences[j].length <= L) {
            line_length += sentences[j].length + 1;
            j++;
        }
        if (i == j) {
            // If a single sentence exceeds the line length, it's too difficult to arrange.
            return -1;
        }
        int actual_length = line_length - 1; // Subtract the extra space added at the end
        cost += (ll)abs(actual_length - L) * (ll)pow(abs(actual_length - L), P);
        lines[i] = j;
        i = j;
    }
    return cost;
}

void print_lines(int N, int lines[], struct Sentence sentences[]) {
    int i = 0;
    while (i < N) {
        int j = lines[i];
        for (int k = i; k < j; k++) {
            printf("%s", sentences[k].text);
            if (k < j - 1) {
                printf(" ");
            }
        }
        printf("\n");
        i = j;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N, L, P;
        scanf("%d %d %d", &N, &L, &P);

        struct Sentence sentences[N];
        for (int i = 0; i < N; i++) {
            scanf("%s", sentences[i].text);
            sentences[i].length = strlen(sentences[i].text);
        }

        qsort(sentences, N, sizeof(struct Sentence), compare);

        int lines[N];
        ll min_cost = calculate_cost(N, L, P, sentences, lines);
        if (min_cost >= 0 && min_cost <= 1e18) {
            printf("%lld\n", min_cost);
            print_lines(N, lines, sentences);
        } else {
            printf("Too hard to arrange\n");
        }

        printf("--------------------\n");
    }
    return 0;
}