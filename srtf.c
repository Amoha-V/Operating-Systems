#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int *arrivalTime = (int *)malloc(n * sizeof(int));
    int *burstTime = (int *)malloc(n * sizeof(int));
    int *remainingTime = (int *)malloc(n * sizeof(int));
    int *completionTime = (int *)malloc(n * sizeof(int));
    int *turnaroundTime = (int *)malloc(n * sizeof(int));
    int *waitingTime = (int *)malloc(n * sizeof(int));
    int *responseTime = (int *)malloc(n * sizeof(int));
    int *isFirstResponse = (int *)malloc(n * sizeof(int)); // Track first execution

    if (!arrivalTime || !burstTime || !remainingTime || !completionTime ||
        !turnaroundTime || !waitingTime || !responseTime || !isFirstResponse)
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
        remainingTime[i] = burstTime[i]; // Initialize remaining time
        isFirstResponse[i] = 1;          // Mark as not yet executed
    }

    int completed = 0, currentTime = 0;
    float totalTurnaround = 0, totalWaiting = 0, totalResponse = 0;

    while (completed < n)
    {
        int shortest = -1;
        int minRemainingTime = __INT_MAX__;

        // Find the process with the shortest remaining time that has arrived
        for (int i = 0; i < n; i++)
        {
            if (remainingTime[i] > 0 && arrivalTime[i] <= currentTime)
            {
                if (remainingTime[i] < minRemainingTime)
                {
                    minRemainingTime = remainingTime[i];
                    shortest = i;
                }
            }
        }

        if (shortest == -1)
        {
            currentTime++; // If no process available, advance time
            continue;
        }

        // If the process is being executed for the first time, calculate response time
        if (isFirstResponse[shortest])
        {
            responseTime[shortest] = currentTime - arrivalTime[shortest];
            isFirstResponse[shortest] = 0;
        }

        // Execute the process for one unit time
        remainingTime[shortest]--;
        currentTime++;

        // If the process is completed, update metrics
        if (remainingTime[shortest] == 0)
        {
            completionTime[shortest] = currentTime;
            turnaroundTime[shortest] = completionTime[shortest] - arrivalTime[shortest];
            waitingTime[shortest] = turnaroundTime[shortest] - burstTime[shortest];

            totalTurnaround += turnaroundTime[shortest];
            totalWaiting += waitingTime[shortest];
            totalResponse += responseTime[shortest];

            completed++;
        }
    }

    // Display the result in tabular format
    printf("\n---------------------------------------------------------------\n");
    printf("Process | Arrival | Burst | Completion | Turnaround | Waiting | Response\n");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%-7d| %-7d| %-5d | %-10d | %-10d | %-7d | %-8d\n",
               i + 1, arrivalTime[i], burstTime[i], completionTime[i],
               turnaroundTime[i], waitingTime[i], responseTime[i]);
    }

    printf("---------------------------------------------------------------\n");
    printf("Average Turnaround Time: %.2f\n", totalTurnaround / n);
    printf("Average Waiting Time: %.2f\n", totalWaiting / n);
    printf("Average Response Time: %.2f\n", totalResponse / n);

    // Free allocated memory
    free(arrivalTime);
    free(burstTime);
    free(remainingTime);
    free(completionTime);
    free(turnaroundTime);
    free(waitingTime);
    free(responseTime);
    free(isFirstResponse);

    return 0;
}
