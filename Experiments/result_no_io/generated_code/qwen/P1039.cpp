#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define MAX_PEOPLE 20
#define MAX_STATEMENTS 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int always_lies;
} Person;

typedef struct {
    char speaker[MAX_NAME_LENGTH];
    char statement[MAX_NAME_LENGTH * 2];
} Statement;

Person people[MAX_PEOPLE];
Statement statements[MAX_STATEMENTS];

int find_suspect(int M, int N, int P) {
    int truth_tellers = M - N;
    int suspect_count = 0;
    char suspects[MAX_PEOPLE][MAX_NAME_LENGTH];
    memset(suspects, 0, sizeof(suspects));

    for (int i = 0; i < P; i++) {
        char speaker[MAX_NAME_LENGTH], rest[MAX_NAME_LENGTH * 2];
        sscanf(statements[i].speaker, "%s", speaker);
        sscanf(statements[i].statement, "%*[^:]: %s", rest);

        int found = 0;
        for (int j = 0; j < M; j++) {
            if (strcmp(people[j].name, speaker) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) continue;

        int is_truth_teller = 1;
        for (int j = 0; j < M; j++) {
            if (strcmp(people[j].name, speaker) == 0) {
                is_truth_teller = !people[j].always_lies;
                break;
            }
        }

        if (is_truth_teller) {
            if (strstr(rest, "I am guilty.") != NULL) {
                return -1; // Impossible
            } else if (strstr(rest, "I am not guilty.") != NULL) {
                // Do nothing
            } else if (strstr(rest, " is guilty.") != NULL) {
                strcpy(suspects[suspect_count], strtok(rest, " "));
                suspect_count++;
            } else if (strstr(rest, " is not guilty.") != NULL) {
                // Do nothing
            } else if (strstr(rest, "Today is ") != NULL) {
                // Do nothing
            }
        } else {
            if (strstr(rest, "I am guilty.") != NULL) {
                strcpy(suspects[suspect_count], strtok(rest, " "));
                suspect_count++;
            } else if (strstr(rest, "I am not guilty.") != NULL) {
                // Do nothing
            } else if (strstr(rest, " is guilty.") != NULL) {
                // Do nothing
            } else if (strstr(rest, " is not guilty.") != NULL) {
                strcpy(suspects[suspect_count], strtok(rest, " "));
                suspect_count++;
            } else if (strstr(rest, "Today is ") != NULL) {
                // Do nothing
            }
        }
    }

    if (suspect_count == 0) {
        return -2; // Cannot Determine
    }

    for (int i = 0; i < suspect_count; i++) {
        for (int j = i + 1; j < suspect_count; j++) {
            if (strcmp(suspects[i], suspects[j]) == 0) {
                return -2; // Cannot Determine
            }
        }
    }

    return 0;
}

int main() {
    int M, N, P;
    scanf("%d %d %d", &M, &N, &P);

    for (int i = 0; i < M; i++) {
        scanf("%s", people[i].name);
        people[i].always_lies = 0;
    }

    for (int i = 0; i < N; i++) {
        char liar[MAX_NAME_LENGTH];
        scanf("%s", liar);
        for (int j = 0; j < M; j++) {
            if (strcmp(people[j].name, liar) == 0) {
                people[j].always_lies = 1;
                break;
            }
        }
    }

    for (int i = 0; i < P; i++) {
        scanf("%s : %s", statements[i].speaker, statements[i].statement);
    }

    int result = find_suspect(M, N, P);

    if (result == -1) {
        printf("Impossible\n");
    } else if (result == -2) {
        printf("Cannot Determine\n");
    } else {
        for (int i = 0; i < M; i++) {
            if (strcmp(people[i].name, suspects[0]) == 0) {
                printf("%s\n", people[i].name);
                break;
            }
        }
    }

    return 0;
}