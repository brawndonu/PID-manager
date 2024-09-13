#ifndef PID_MANAGER_H
#define PID_MANAGER_H

#define MIN_PID 100
#define MAX_PID 1000

class PidManager {
private:
    int pid_map[MAX_PID - MIN_PID + 1];  // Bitmap to track PIDs
    bool is_initialized;  // Flag to check if the map is initialized

public:
    PidManager();  // Constructor
    int allocate_map();  // Function to initialize the PID manager
    int allocate_pid();  // Function to allocate a PID
    void release_pid(int pid);  // Function to release a PID
};

#endif
