#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Dynamic memory allocation for arrays
    int *burstTime = (int *)malloc(n * sizeof(int));
    int *arrivalTime = (int *)malloc(n * sizeof(int));
    int *remainingBurst = (int *)malloc(n * sizeof(int));
    int *completionTime = (int *)malloc(n * sizeof(int));
    int *turnaroundTime = (int *)malloc(n * sizeof(int));
    int *waitingTime = (int *)malloc(n * sizeof(int));
    int *responseTime = (int *)malloc(n * sizeof(int));
    int *isCompleted = (int *)malloc(n * sizeof(int));
    int *firstResponse = (int *)malloc(n * sizeof(int));

    // Check for memory allocation failure
    if (burstTime == NULL || arrivalTime == NULL || remainingBurst == NULL ||
        completionTime == NULL || turnaroundTime == NULL || waitingTime == NULL ||
        isCompleted == NULL || responseTime == NULL || firstResponse == NULL)
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
        remainingBurst[i] = burstTime[i];
        isCompleted[i] = 0;
        firstResponse[i] = -1;
    }

    int timeQuantum;
    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    // Round Robin scheduling
    int completed = 0, currentTime = 0;
    while (completed < n)
    {
        int allDone = 1;

        for (int i = 0; i < n; i++)
        {
            if (!isCompleted[i] && arrivalTime[i] <= currentTime)
            {
                allDone = 0;

                // Record first response time
                if (firstResponse[i] == -1)
                {
                    firstResponse[i] = currentTime;
                }

                if (remainingBurst[i] > timeQuantum)
                {
                    currentTime += timeQuantum;
                    remainingBurst[i] -= timeQuantum;
                }
                else
                {
                    currentTime += remainingBurst[i];
                    remainingBurst[i] = 0;
                    isCompleted[i] = 1;
                    completed++;

                    // Calculate times
                    completionTime[i] = currentTime;
                    turnaroundTime[i] = completionTime[i] - arrivalTime[i];
                    waitingTime[i] = turnaroundTime[i] - burstTime[i];
                }
            }
        }

        if (allDone)
        {
            currentTime++;
        }
    }

    // Calculate response times
    for (int i = 0; i < n; i++)
    {
        responseTime[i] = firstResponse[i] - arrivalTime[i];
    }

    // Display results
    printf("\n%-8s %-9s %-7s %-12s %-12s %-9s %-9s\n",
           "Process", "Arrival", "Burst", "Completion", "Turnaround", "Waiting", "Response");

    for (int i = 0; i < n; i++)
    {
        printf("P%-7d %-9d %-7d %-12d %-12d %-9d %-9d\n",
               i + 1, arrivalTime[i], burstTime[i], completionTime[i],
               turnaroundTime[i], waitingTime[i], responseTime[i]);
    }

    // Calculate and display averages
    float avgTurnaround = 0, avgWaiting = 0, avgResponse = 0;
    for (int i = 0; i < n; i++)
    {
        avgTurnaround += turnaroundTime[i];
        avgWaiting += waitingTime[i];
        avgResponse += responseTime[i];
    }

    printf("\nAverage Turnaround Time: %.2f\n", avgTurnaround / n);
    printf("Average Waiting Time: %.2f\n", avgWaiting / n);
    printf("Average Response Time: %.2f\n", avgResponse / n);

    // Free allocated memory
    free(burstTime);
    free(arrivalTime);
    free(remainingBurst);
    free(completionTime);
    free(turnaroundTime);
    free(waitingTime);
    free(responseTime);
    free(isCompleted);
    free(firstResponse);

    return 0;
}