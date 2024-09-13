#include "pid_manager.h"
#include <iostream>

// Constructor
PidManager::PidManager() {
    is_initialized = false;
    for (int i = 0; i < MAX_PID - MIN_PID + 1; i++) {
        pid_map[i] = 0;  // All PIDs are available initially
    }
}

// Function to initialize the PID map
int PidManager::allocate_map() {
    is_initialized = true;  // Mark the map as initialized
    return 1;  // Success
}

// Function to allocate a PID
int PidManager::allocate_pid() {
    if (!is_initialized) {
        std::cerr << "Error: PID map is not initialized.\n";
        return -1;
    }
    for (int i = 0; i < MAX_PID - MIN_PID + 1; i++) {
        if (pid_map[i] == 0) {  // PID is available
            pid_map[i] = 1;  // Mark PID as in use
            return i + MIN_PID;  // Return the actual PID value
        }
    }
    return -1;  // No available PIDs
}

// Function to release a PID
void PidManager::release_pid(int pid) {
    if (!is_initialized) {
        std::cerr << "Error: PID map is not initialized.\n";
        return;
    }
    if (pid < MIN_PID || pid > MAX_PID) {
        std::cerr << "Error: Invalid PID.\n";
        return;
    }
    if (pid_map[pid - MIN_PID] == 0) {
        std::cerr << "Error: PID " << pid << " was not allocated.\n";
    } else {
        pid_map[pid - MIN_PID] = 0;  // Mark PID as available
    }
}
