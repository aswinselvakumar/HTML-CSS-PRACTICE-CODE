#include <stdio.h>

int main() {
    int n, m; // Number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int max[n][m]; // Maximum resource needs of each process
    int alloc[n][m]; // Resources currently allocated to each process
    int avail[m]; // Available resources

    printf("Enter the maximum resource matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter the available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Calculate the need matrix
    int need[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Safety algorithm to check if the system is in a safe state
    int finish[n];
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int safeSeq[n];
    int count = 0;
    int safe = 1;

    while (count < n) {
        safe = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j])
                        break;
                }
                if (j == m) {
                    for (int k = 0; k < m; k++) {
                        avail[k] += alloc[i][k];
                    }
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    safe = 1;
                }
            }
        }
        if (!safe) {
            break;
        }
    }

    if (count < n) {
        printf("System is in an unsafe state.\n");
    } else {
        printf("System is in a safe state.\n");
        printf("Safe sequence: ");
        for (int i = 0; i < n; i++) {
            printf("%d", safeSeq[i]);
            if (i != n - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
    }

return 0;
}
