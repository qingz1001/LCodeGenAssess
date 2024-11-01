#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SENTENCES 100005
#define MAX_LENGTH 300005
#define MAX_P 11

typedef long long ll;

ll dp[MAX_SENTENCES][MAX_LENGTH];
char sentences[MAX_SENTENCES][31];
int sentence_lengths[MAX_SENTENCES];
int sentence_count, standard_length, power;

void initialize() {
    memset(dp, 0x3f, sizeof(dp));
    memset(sentences, 0, sizeof(sentences));
    sentence_count = 0;
}

ll calculate_discrepancy(int length) {
    return (ll)abs(length - standard_length) * (ll)abs(length - standard_length);
}

void solve() {
    int i, j, k;
    ll min_discrepancy = LLONG_MAX;
    int best_partition[MAX_SENTENCES];
    int current_length = 0;

    for (i = 1; i <= sentence_count; i++) {
        for (j = 0; j < standard_length; j++) {
            dp[i][j] = dp[i-1][j] + calculate_discrepancy(j + sentence_lengths[i]);
        }
        for (j = sentence_lengths[i]; j <= standard_length; j++) {
            dp[i][j] = calculate_discrepancy(j);
        }
    }

    for (i = 1; i <= sentence_count; i++) {
        for (j = 0; j < standard_length; j++) {
            if (dp[i][j] < min_discrepancy) {
                min_discrepancy = dp[i][j];
                current_length = j;
            }
        }
    }

    if (min_discrepancy > 1e18) {
        printf("Too hard to arrange\n");
        return;
    }

    printf("%lld\n", min_discrepancy);

    i = sentence_count;
    j = current_length;
    while (i > 0) {
        if (dp[i][j] == dp[i-1][j] + calculate_discrepancy(j + sentence_lengths[i])) {
            i--;
        } else {
            best_partition[i] = j + sentence_lengths[i];
            j -= sentence_lengths[i] + 1;
            i--;
        }
    }

    for (i = 1; i <= sentence_count; i++) {
        printf("%s", sentences[i]);
        if (best_partition[i] == 0) {
            printf("\n");
        } else {
            printf(" ");
        }
    }
    printf("\n");

    for (i = 0; i < 20; i++) {
        printf("-");
    }
    printf("\n");
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();
        scanf("%d%d%d", &sentence_count, &standard_length, &power);
        for (int i = 1; i <= sentence_count; i++) {
            scanf("%s", sentences[i]);
            sentence_lengths[i] = strlen(sentences[i]);
        }
        solve();
    }

    return 0;
}