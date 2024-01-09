#include <stdio.h>

#define MEMORY_SIZE 1000

// Function to initialize memory array
void initializeMemory(int memory[], int size) {
    for (int i = 0; i < size; i++) {
        memory[i] = -1; // -1 represents unallocated memory
    }
}

// Function to display the current state of memory
void displayMemory(int memory[], int size) {
    for (int i = 0; i < size; i++) {
        if (memory[i] == -1) {
            printf(". ");
        } else {
            printf("%d ", memory[i]);
        }
    }
    printf("\n");
}

// Function to allocate memory using First Fit algorithm
int allocateMemoryFirstFit(int memory[], int size, int processSize) {
    int startIndex = -1;
    int count = 0;

    for (int i = 0; i < size; i++) {
        if (memory[i] == -1) {
            if (startIndex == -1) {
                startIndex = i;
            }
            count++;
            if (count == processSize) {
                // Found a contiguous block of required size
                for (int k = startIndex; k < startIndex + processSize; k++) {
                    memory[k] = processSize; // Use processSize to represent the allocated block
                }
                return startIndex; // Return the starting index of the allocated block
            }
        } else {
            startIndex = -1;
            count = 0;
        }
    }
    return -1; // Memory allocation failed
}


// Function to deallocate memory
void deallocateMemory(int memory[], int size, int startIndex, int processSize) {
    for (int i = startIndex; i < startIndex + processSize; i++) {
        memory[i] = -1; // Free the allocated memory
    }
}

int main() {
    int memory[MEMORY_SIZE];
    initializeMemory(memory, MEMORY_SIZE);

    int choice, processSize, startIndex;

    do {
        printf("\n1. Allocate Memory\n");
        printf("2. Deallocate Memory\n");
        printf("3. Display Memory\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the size of the process: ");
                scanf("%d", &processSize);
                startIndex = allocateMemoryFirstFit(memory, MEMORY_SIZE, processSize);
                if (startIndex != -1) {
                    printf("Memory allocated successfully. Starting index: %d\n", startIndex);
                } else {
                    printf("Memory allocation failed. Not enough contiguous space.\n");
                }
                break;

            case 2:
                printf("Enter the starting index of the process to deallocate: ");
                scanf("%d", &startIndex);
                printf("Enter the size of the process to deallocate: ");
                scanf("%d", &processSize);
                deallocateMemory(memory, MEMORY_SIZE, startIndex, processSize);
                printf("Memory deallocated successfully.\n");
                break;

            case 3:
                displayMemory(memory, MEMORY_SIZE);
                break;

            case 4:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 4);

    return 0;
}

