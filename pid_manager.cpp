#include "pid_manager.h"

// Constructor
PidManager::PidManager() {
    for (int i = 0; i < MAX_PID - MIN_PID + 1; i++) {
        pid_map[i] = 0; // Initialize all PIDs as available
    }
}

// Function to initialize the PID map
int PidManager::allocate_map() {
    return 1; // Success
}

// Function to allocate a PID
int PidManager::allocate_pid() {
    for (int i = 0; i < MAX_PID - MIN_PID + 1; i++) {
        if (pid_map[i] == 0) {  // PID is available
            pid_map[i] = 1;     // Mark PID as in use
            return i + MIN_PID; // Return the actual PID value
        }
    }
    return -1; // No available PIDs
}

// Function to release a PID
void PidManager::release_pid(int pid) {
    if (pid >= MIN_PID && pid <= MAX_PID) {
        pid_map[pid - MIN_PID] = 0; // Mark PID as available
    }
}
