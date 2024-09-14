// Brandon Uribe
// @csu.fullerton.edu
// @brawndonu
// Partners: @jperezjr221

#include "pid_manager.h"
#include <iostream>
#include <unistd.h>

int main() {
    // Attempt allocatde before initialization
    PidManager manager;
    
    // Test: Allocate a PID before initializing the map
    int invalid_pid = manager.allocate_pid();
    std::cout << "Attempt to allocate PID before initializing the map (return -1): " << invalid_pid << std::endl;

    // Test: Release PID before initializing the map
    manager.release_pid(100);  //fail

    //Initialize the PID map using allocate_map
    if (manager.allocate_map() == 1) {
        std::cout << "PID map initialized.\n";
    } else {
        std::cerr << "Failed to initialize PID map.\n";
        return -1;
    }

    // Test: Allocate some PIDs
    int pid1 = manager.allocate_pid();
    int pid2 = manager.allocate_pid();
    if (pid1 != -1 && pid2 != -1) {
        std::cout << "Allocated PIDs: " << pid1 << ", " << pid2 << std::endl;
    } else {
        std::cerr << "Failed to allocate PIDs.\n";
    }

    // Test: Release PIDs and check if they can be reallocated
    manager.release_pid(pid1);
    manager.release_pid(pid2);
    std::cout << "Released PIDs: " << pid1 << ", " << pid2 << std::endl;

    int pid3 = manager.allocate_pid();
    std::cout << "Reallocated PID after release: " << pid3 << std::endl;

    // Fork - child process
    pid_t pid = fork();

    if (pid == 0) {
        PidManager childManager;
        if (childManager.allocate_map() != 1) {
            std::cerr << "Child: Failed to initialize PID map.\n";
            return -1;
        }

        int child_pid = childManager.allocate_pid();
        std::cout << "Child process allocated PID: " << child_pid << std::endl;

        childManager.release_pid(child_pid);
        std::cout << "Child process released PID: " << child_pid << std::endl;

    } else if (pid > 0) {
        int parent_pid = manager.allocate_pid();
        std::cout << "Parent process allocated PID: " << parent_pid << std::endl;

        manager.release_pid(parent_pid);
        std::cout << "Parent process released PID: " << parent_pid << std::endl;

        // Test: Using all PIDs
        for (int i = 0; i < MAX_PID - MIN_PID + 1; i++) {
            manager.allocate_pid();
        }
        int exhausted_pid = manager.allocate_pid();
        if (exhausted_pid == -1) {
            std::cout << "All PIDs taken\n";
        }

    } else {
        std::cerr << "Fork failed\n";
        return -1;
    }

    return 0;
}
