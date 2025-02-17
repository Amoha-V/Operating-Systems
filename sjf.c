#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int *arrivalTime = (int *)malloc(n * sizeof(int));
    int *burstTime = (int *)malloc(n * sizeof(int));
    int *originalBurstTime = (int *)malloc(n * sizeof(int)); // Store original burst time
    int *completionTime = (int *)malloc(n * sizeof(int));
    int *turnaroundTime = (int *)malloc(n * sizeof(int));
    int *waitingTime = (int *)malloc(n * sizeof(int));
    int *responseTime = (int *)malloc(n * sizeof(int));

    if (!arrivalTime || !burstTime || !originalBurstTime || !completionTime ||
        !turnaroundTime || !waitingTime || !responseTime)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Input process details
    for (int i = 0; i < n; i++)
    {
        printf("Process P%d Arrival Time: ", i + 1);
        scanf("%d", &arrivalTime[i]);
        printf("Process P%d Burst Time: ", i + 1);
        scanf("%d", &burstTime[i]);
        originalBurstTime[i] = burstTime[i]; // Save original burst time
    }

    int completed = 0, currentTime = 0;
    float totalTurnaround = 0, totalWaiting = 0, totalResponse = 0;

    while (completed < n)
    {
        int shortest = -1;
        int minBurst = __INT_MAX__; // Initialize with a high value

        for (int i = 0; i < n; i++)
        {
            // Select the shortest job that has arrived and is not completed
            if (burstTime[i] > 0 && arrivalTime[i] <= currentTime)
            {
                if (burstTime[i] < minBurst)
                {
                    minBurst = burstTime[i];
                    shortest = i;
                }
            }
        }

        if (shortest == -1)
        {
            currentTime++; // If no process available, advance time
            continue;
        }

        // Compute completion, turnaround, waiting, and response times
        completionTime[shortest] = currentTime + burstTime[shortest];
        turnaroundTime[shortest] = completionTime[shortest] - arrivalTime[shortest];
        waitingTime[shortest] = turnaroundTime[shortest] - originalBurstTime[shortest];
        responseTime[shortest] = currentTime - arrivalTime[shortest];

        totalTurnaround += turnaroundTime[shortest];
        totalWaiting += waitingTime[shortest];
        totalResponse += responseTime[shortest];

        currentTime = completionTime[shortest];
        burstTime[shortest] = 0; // Mark this process as completed
        completed++;
    }

    // Display the table
    printf("\n---------------------------------------------------------------\n");
    printf("Process | Arrival | Burst | Completion | Turnaround | Waiting | Response\n");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%-7d| %-7d| %-5d | %-10d | %-10d | %-7d | %-8d\n",
               i + 1, arrivalTime[i], originalBurstTime[i], // Display original burst time
               completionTime[i], turnaroundTime[i], waitingTime[i], responseTime[i]);
    }

    printf("---------------------------------------------------------------\n");
    printf("Average Turnaround Time: %.2f\n", totalTurnaround / n);
    printf("Average Waiting Time: %.2f\n", totalWaiting / n);
    printf("Average Response Time: %.2f\n", totalResponse / n);

    // Free allocated memory
    free(arrivalTime);
    free(burstTime);
    free(originalBurstTime);
    free(completionTime);
    free(turnaroundTime);
    free(waitingTime);
    free(responseTime);

    return 0;
}
