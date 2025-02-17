#include <stdio.h>
#include <stdlib.h>

void sortProcesses(int n, int *arrival, int *burst, int *process)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arrival[j] > arrival[j + 1])
            {
                int temp = arrival[j];
                arrival[j] = arrival[j + 1];
                arrival[j + 1] = temp;

                temp = burst[j];
                burst[j] = burst[j + 1];
                burst[j + 1] = temp;

                temp = process[j];
                process[j] = process[j + 1];
                process[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int *arrival = (int *)malloc(n * sizeof(int));
    int *burst = (int *)malloc(n * sizeof(int));
    int *completion = (int *)malloc(n * sizeof(int));
    int *turnaround = (int *)malloc(n * sizeof(int));
    int *waiting = (int *)malloc(n * sizeof(int));
    int *response = (int *)malloc(n * sizeof(int));
    int *process = (int *)malloc(n * sizeof(int));

    if (!arrival || !burst || !completion || !turnaround ||
        !waiting || !response || !process)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter arrival and burst times for each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process P%d Arrival Time: ", i + 1);
        scanf("%d", &arrival[i]);
        printf("Process P%d Burst Time: ", i + 1);
        scanf("%d", &burst[i]);
        process[i] = i + 1;
    }

    // Sort processes by arrival time
    sortProcesses(n, arrival, burst, process);

    int currentTime = 0;
    float totalTurnaround = 0, totalWaiting = 0, totalResponse = 0;

    for (int i = 0; i < n; i++)
    {
        if (currentTime < arrival[i])
        {
            currentTime = arrival[i]; // Handle CPU idle time
        }

        response[i] = currentTime - arrival[i];
        completion[i] = currentTime + burst[i];
        currentTime = completion[i];

        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];

        totalTurnaround += turnaround[i];
        totalWaiting += waiting[i];
        totalResponse += response[i];
    }

    // Display the scheduling table
    printf("\n---------------------------------------------------------------\n");
    printf("Process | Arrival | Burst | Completion | Turnaround | Waiting | Response\n");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%-7d| %-7d| %-5d | %-10d | %-10d | %-7d | %-8d\n",
               process[i], arrival[i], burst[i], completion[i],
               turnaround[i], waiting[i], response[i]);
    }

    printf("---------------------------------------------------------------\n");
    printf("Average Turnaround Time: %.2f\n", totalTurnaround / n);
    printf("Average Waiting Time: %.2f\n", totalWaiting / n);
    printf("Average Response Time: %.2f\n", totalResponse / n);

    // Free allocated memory
    free(arrival);
    free(burst);
    free(completion);
    free(turnaround);
    free(waiting);
    free(response);
    free(process);

    return 0;
}
