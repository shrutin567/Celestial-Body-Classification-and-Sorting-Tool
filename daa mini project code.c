#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[100];
    int mass;
    int radius;
} CelestialBody;

void bubbleSort(CelestialBody arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].mass > arr[j + 1].mass) {
                CelestialBody temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void merge(CelestialBody arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    CelestialBody leftArr[n1], rightArr[n2];

    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i].radius <= rightArr[j].radius) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(CelestialBody arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int partition(CelestialBody arr[], int low, int high) {
    CelestialBody pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].radius <= pivot.radius) {
            i++;
            CelestialBody temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    CelestialBody temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(CelestialBody arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void knapsack(CelestialBody arr[], int n, int radiusLimit, int massLimit) {
    int** dp = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)malloc((radiusLimit + 1) * sizeof(int));
        memset(dp[i], 0, (radiusLimit + 1) * sizeof(int));
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= radiusLimit; j++) {
            if (arr[i - 1].radius <= j) {
                dp[i][j] = (arr[i - 1].mass + dp[i - 1][j - arr[i - 1].radius] > dp[i - 1][j])
                               ? (arr[i - 1].mass + dp[i - 1][j - arr[i - 1].radius])
                               : dp[i - 1][j];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    int maxMass = dp[n][radiusLimit];
    int currentRadius = radiusLimit;

    printf("\nSelected celestial bodies:\n");
    for (int i = n; i > 0 && maxMass > 0; i--) {
        if (maxMass != dp[i - 1][currentRadius]) {
            printf("- Name: %s, Mass: %d, Radius: %d\n", arr[i - 1].name, arr[i - 1].mass, arr[i - 1].radius);
            maxMass -= arr[i - 1].mass;
            currentRadius -= arr[i - 1].radius;
        }
    }

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
}
int main() {
    int n;
    printf("Enter the number of celestial bodies: ");
    scanf("%d", &n);

    CelestialBody* celestialBodies = (CelestialBody*)malloc(n * sizeof(CelestialBody));

    printf("Enter the details of celestial bodies:\n");
    for (int i = 0; i < n; i++) {
        printf("Celestial body %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", celestialBodies[i].name);
        printf("Mass: ");
        scanf("%d", &celestialBodies[i].mass);
        printf("Radius: ");
        scanf("%d", &celestialBodies[i].radius);
    }
    int massLimit, radiusLimit;
    printf("Enter the mass limit for classification: ");
    scanf("%d", &massLimit);
    printf("Enter the radius limit for classification: ");
    scanf("%d", &radiusLimit);

    bubbleSort(celestialBodies, n);
    printf("\nSorting celestial bodies based on mass using Bubble Sort:\n");
    for (int i = 0; i < n; i++) {
        printf("- Name: %s, Mass: %d, Radius: %d\n", celestialBodies[i].name, celestialBodies[i].mass,
               celestialBodies[i].radius);
    }

    mergeSort(celestialBodies, 0, n - 1);
    printf("\nSorting celestial bodies based on radius using Merge Sort:\n");
    for (int i = 0; i < n; i++) {
        printf("- Name: %s, Mass: %d, Radius: %d\n", celestialBodies[i].name, celestialBodies[i].mass,
               celestialBodies[i].radius);
    }

    quickSort(celestialBodies, 0, n - 1);
    printf("\nSorting celestial bodies based on radius using Quick Sort:\n");
    for (int i = 0; i < n; i++) {
        printf("- Name: %s, Mass: %d, Radius: %d\n", celestialBodies[i].name, celestialBodies[i].mass,
               celestialBodies[i].radius);
    }
    printf("\nClassifying celestial bodies based on radius and mass constraints:\n");
    knapsack(celestialBodies, n, radiusLimit, massLimit);

    free(celestialBodies);

    return 0;
}
