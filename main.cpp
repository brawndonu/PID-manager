#include <iostream>
#include <unistd.h>  // For fork()
#include "pid_manager.h"

int main() {
    PidManager parentManager;
    parentManager.allocate_map();  // Initialize the PID manager for the parent

    pid_t pid = fork();  // Create a child process

    if (pid == 0) {
        // Child process
        PidManager childManager;
        childManager.allocate_map();  // Initialize the PID manager for the child

        int child_pid = childManager.allocate_pid();  // Allocate PID in the child
        std::cout << "Child process allocated PID: " << child_pid << std::endl;

        childManager.release_pid(child_pid);  // Release PID in the child
        std::cout << "Child process release34  d PID: " << child_pid << std::endl;
    } else if (pid > 0) {
        // Parent process
        int parent_pid = parentManager.allocate_pid();  // Allocate PID in the parent
        std::cout << "Parent process allocated PID: " << parent_pid << std::endl;

        parentManager.release_pid(parent_pid);  // Release PID in the parent
        std::cout << "Parent process released PID: " << parent_pid << std::endl;
    } else {
        // Error if fork fails
        std::cerr << "Fork failed" << std::endl;
    }

    return 0;
}
