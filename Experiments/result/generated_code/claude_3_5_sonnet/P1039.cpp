#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PEOPLE 20
#define MAX_STATEMENTS 100
#define MAX_NAME_LENGTH 20
#define MAX_STATEMENT_LENGTH 250

char names[MAX_PEOPLE][MAX_NAME_LENGTH];
char statements[MAX_STATEMENTS][MAX_STATEMENT_LENGTH];
char speakers[MAX_STATEMENTS][MAX_NAME_LENGTH];
int M, N, P;

bool is_consistent(bool truth_values[]) {
    int liars = 0;
    for (int i = 0; i < M; i++) {
        if (!truth_values[i]) liars++;
    }
    return liars == N;
}

bool check_statement(int i, bool truth_values[]) {
    char* statement = statements[i];
    int speaker_idx = -1;
    for (int j = 0; j < M; j++) {
        if (strcmp(speakers[i], names[j]) == 0) {
            speaker_idx = j;
            break;
        }
    }

    if (strstr(statement, "I am guilty")) {
        return truth_values[speaker_idx] == truth_values[speaker_idx];
    } else if (strstr(statement, "I am not guilty")) {
        return truth_values[speaker_idx] != truth_values[speaker_idx];
    } else if (strstr(statement, "is guilty")) {
        char* name = strtok(statement, " ");
        name = strtok(NULL, " ");
        for (int j = 0; j < M; j++) {
            if (strcmp(name, names[j]) == 0) {
                return truth_values[speaker_idx] == truth_values[j];
            }
        }
    } else if (strstr(statement, "is not guilty")) {
        char* name = strtok(statement, " ");
        name = strtok(NULL, " ");
        for (int j = 0; j < M; j++) {
            if (strcmp(name, names[j]) == 0) {
                return truth_values[speaker_idx] != truth_values[j];
            }
        }
    }
    return true;
}

bool is_valid_configuration(bool truth_values[]) {
    if (!is_consistent(truth_values)) return false;
    for (int i = 0; i < P; i++) {
        if (!check_statement(i, truth_values)) {
            return false;
        }
    }
    return true;
}

void solve() {
    bool truth_values[MAX_PEOPLE] = {0};
    int guilty_count = 0;
    int guilty_person = -1;

    for (int i = 0; i < (1 << M); i++) {
        for (int j = 0; j < M; j++) {
            truth_values[j] = (i & (1 << j)) != 0;
        }
        if (is_valid_configuration(truth_values)) {
            for (int j = 0; j < M; j++) {
                if (truth_values[j]) {
                    guilty_count++;
                    guilty_person = j;
                    if (guilty_count > 1) break;
                }
            }
            if (guilty_count > 1) break;
        }
    }

    if (guilty_count == 0) {
        printf("Impossible\n");
    } else if (guilty_count > 1) {
        printf("Cannot Determine\n");
    } else {
        printf("%s\n", names[guilty_person]);
    }
}

int main() {
    scanf("%d %d %d", &M, &N, &P);
    for (int i = 0; i < M; i++) {
        scanf("%s", names[i]);
    }
    for (int i = 0; i < P; i++) {
        scanf("%s %[^\n]", speakers[i], statements[i]);
    }
    solve();
    return 0;
}