#include <iostream>
#include <unistd.h>  // For fork()
#include "pid_manager.h"
#include <cstdlib>  // For random number generation
#include <ctime>    // For seeding randomness

int main() {
    // Test calling allocate_pid() before initializing the map
    PidManager testManager;
    int invalid_alloc = testManager.allocate_pid();  // Should fail
    std::cout << "Attempt to allocate PID before initializing the map (should fail): " << invalid_alloc << std::endl;

    // Test releasing a PID before initializing the map
    testManager.release_pid(100);  // Should fail, map not initialized

    // Initialize PID manager for parent
    PidManager parentManager;
    if (parentManager.allocate_map() != 1) {
        std::cerr << "Error initializing PID map for parent.\n";
        return -1;
    }

    // Fork to create a child process
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        PidManager childManager;
        if (childManager.allocate_map() != 1) {
            std::cerr << "Error initializing PID map for child.\n";
            return -1;
        }

        int child_pid = childManager.allocate_pid();
        std::cout << "Child process allocated PID: " << child_pid << std::endl;

        childManager.release_pid(child_pid);
        std::cout << "Child process released PID: " << child_pid << std::endl;

        // Testing edge cases
        childManager.release_pid(101);  // Trying to release a non-allocated PID

    } else if (pid > 0) {
        // Parent process
        int parent_pid = parentManager.allocate_pid();
        std::cout << "Parent process allocated PID: " << parent_pid << std::endl;

        parentManager.release_pid(parent_pid);
        std::cout << "Parent process released PID: " << parent_pid << std::endl;

        // Test PID exhaustion
        for (int i = 0; i < MAX_PID - MIN_PID + 1; i++) {
            parentManager.allocate_pid();  // Allocate all PIDs
        }
        int exhausted_pid = parentManager.allocate_pid();
        if (exhausted_pid == -1) {
            std::cout << "All PIDs exhausted. Cannot allocate more.\n";
        }

        // Loop to allocate and release PIDs multiple times
        for (int i = 0; i < 5; i++) {
            int loop_pid = parentManager.allocate_pid();
            std::cout << "Allocated PID in loop: " << loop_pid << std::endl;
            parentManager.release_pid(loop_pid);
            std::cout << "Released PID in loop: " << loop_pid << std::endl;
        }

        // Seed random number generator
        std::srand(std::time(nullptr));

        // Random allocation and release
        for (int i = 0; i < 5; i++) {
            int rand_pid = MIN_PID + (std::rand() % (MAX_PID - MIN_PID + 1));
            parentManager.allocate_pid();
            std::cout << "Randomly allocated PID: " << rand_pid << std::endl;
            parentManager.release_pid(rand_pid);
            std::cout << "Randomly released PID: " << rand_pid << std::endl;
        }

    } else {
        std::cerr << "Fork failed.\n";
        return -1;
    }

    return 0;
}
