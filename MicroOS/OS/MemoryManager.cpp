#include "MemoryManager.h"
#include "ContextSwitching.h"
#include <stdlib.h>


typedef struct MemoryManager {
    int** segments; 
    int count; 
} MemoryManager;

MemoryManager* memoryManager_;

__MICROOS_RESULT MemoryManager_Init()
{
    memoryManager_ = (MemoryManager*)malloc(sizeof(MemoryManager));
    if (memoryManager_ == NULL) {
        return __MICROOS_ERROR; 
    }

    memoryManager_->segments = NULL;
    memoryManager_->count = 0;

    return __MICROOS_SUCCESS;
}

__MICROOS_RESULT MemoryManager_FreeSegment(int segmentIndex)
{
    if (memoryManager_->segments == NULL) {
        return __MICROOS_ERROR; // Return error if segments is not initialized
    }

    if (segmentIndex >= 0 && segmentIndex < memoryManager_->count)
    {
        free(memoryManager_->segments[segmentIndex]);

        int** _tempSegments;
        if (memoryManager_->count > 1)
        {
            for (int i = segmentIndex + 1; i < memoryManager_->count; ++i) {
                memoryManager_->segments[i - 1] = memoryManager_->segments[i];
            }

            _tempSegments = (int**)realloc(memoryManager_->segments, (memoryManager_->count - 1) * sizeof(int*));
        }
        else {
            // If count is already 0 or 1, set _tempSegments to NULL to prevent arithmetic overflow:
            _tempSegments = NULL;
        }

        if (_tempSegments == NULL)
        {
            // In case of realloc failure, assign NULL to prevent memory leak:
            memoryManager_->segments = NULL;
            --memoryManager_->count;

            return __MICROOS_ERROR;
        }

        memoryManager_->segments = _tempSegments;
        --memoryManager_->count;
    }

    return __MICROOS_SUCCESS;
}

int MemoryManager_allocate(int segmentSize) 
{
    int* segment = (int*)malloc(segmentSize * sizeof(int));
    if (segment == NULL) {
        return -1;
    }

    int** newSegments = (int**)realloc(memoryManager_->segments, (memoryManager_->count + 1) * sizeof(int*));
    if (newSegments == NULL) 
    {
        free(segment);
        return -1;
    }
    memoryManager_->segments = newSegments;
    memoryManager_->segments[memoryManager_->count] = segment;

    // Increment the number of segments and return the index of the newly added segment
    return memoryManager_->count++;
}

__MICROOS_RESULT MemoryManager_Is_MemoryFull()
{
    return false;
}

__MICROOS_RESULT MemoryManager_Is_PageFault()
{
    return false;
}

__MICROOS_RESULT MemoryManager_HandlePageFault()
{
    return false;
}


void MemoryManager_Task()
{
    while (ContextSwitchg_SwitchThread())
    {
        if (MemoryManager_Is_MemoryFull()) {

        }

        if (MemoryManager_Is_PageFault()) {
            MemoryManager_HandlePageFault();
        }
    }
}