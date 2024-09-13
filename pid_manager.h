#ifndef PID_MANAGER_H
#define PID_MANAGER_H

#define MIN_PID 100
#define MAX_PID 1000

class PidManager {
private:
    int pid_map[MAX_PID - MIN_PID + 1];  // Add 1 to make 901 total
    bool is_initialized;  // Flag to check if the map is initialized

public:
    PidManager();  // Constructor
    int allocate_map();  // Creates and initializes a data structure for representing pids; returns −1 if unsuccessful, 1 if successful
    int allocate_pid();  // Allocates and returns a pid; returns −1 if unable to allocate a pid (all pids are in use)
    void release_pid(int pid);  // Releases a pid
};

#endif
