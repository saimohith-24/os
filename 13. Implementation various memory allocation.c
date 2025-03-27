#include <stdio.h>
#define NUM_BLOCKS 5
#define TOTAL_MEMORY 1000
typedef struct {
    int size, isOccupied;
} MemoryBlock;
int allocate(MemoryBlock blocks[], int strategy, int size) {
    int idx = -1;
    if (strategy == 0) { // First-Fit
        for (int i = 0; i < NUM_BLOCKS; i++) {
            if (!blocks[i].isOccupied && blocks[i].size >= size) {
                idx = i;
                break;
            }
        }
    } else if (strategy == 1) { // Best-Fit
        int minWaste = TOTAL_MEMORY + 1;
        for (int i = 0; i < NUM_BLOCKS; i++) {
            if (!blocks[i].isOccupied && blocks[i].size >= size) {
                int waste = blocks[i].size - size;
                if (waste < minWaste) { idx = i; minWaste = waste; }
            }
        }
    } else if (strategy == 2) { // Worst-Fit
        int maxSize = -1;
        for (int i = 0; i < NUM_BLOCKS; i++) {
            if (!blocks[i].isOccupied && blocks[i].size >= size) {
                if (blocks[i].size > maxSize) { idx = i; maxSize = blocks[i].size; }
            }
        }
    }
    if (idx != -1) {
        blocks[idx].isOccupied = 1;
        printf("Allocated %d bytes at block %d\n", size, idx);
    } else {
        printf("No suitable block found\n");
    }
    return idx;
}
int main() {
    MemoryBlock blocks[NUM_BLOCKS] = {{200, 0}, {300, 0}, {400, 0}, {100, 0}, {200, 0}};    
    allocate(blocks, 0, 150); // First-Fit
    allocate(blocks, 1, 120); // Best-Fit
    allocate(blocks, 2, 250); // Worst-Fit    
    return 0;
}
