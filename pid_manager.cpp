#include "pid_manager.h"
#include <iostream>
#include <iostream>

PidManager::PidManager() {
    is_initialized = false;
    is_initialized = false;
    for (int i = 0; i < MAX_PID - MIN_PID + 1; i++) {
        pid_map[i] = 0;  // all pid available at start
    }
}

int PidManager::allocate_map() {
    is_initialized = true;
    return 1;
}

int PidManager::allocate_pid() {
    if (!is_initialized) {
        std::cerr << "PID map is not initialized.\n";
        return -1;
    }
    for (int i = 0; i < MAX_PID - MIN_PID + 1; i++) {
        if (pid_map[i] == 0) {
            pid_map[i] = 1;
            return i + MIN_PID;
        }
    }
    return -1; //indicating that all PIDs are in use
}

void PidManager::release_pid(int pid) {
    if (!is_initialized) {
        std::cerr << "PID map is not initialized.\n";
        return;
    }
    if (pid < MIN_PID || pid > MAX_PID) {
        std::cerr << "Invalid PID.\n";
        return;
    }
    if (pid_map[pid - MIN_PID] == 0) {
        std::cerr << "PID: " << pid << " NOT allocated.\n";
    } else {
        pid_map[pid - MIN_PID] = 0;
    }
}
