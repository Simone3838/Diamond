#include <stddef.h>
#include <stdint.h>

// Function to write a string to the screen
void write_string(const char* str, size_t offset) {
    char* video_memory = (char*) 0xb8000 + offset * 2;
    for (size_t i = 0; str[i] != '\0'; i++) {
        video_memory[i * 2] = str[i];
        video_memory[i * 2 + 1] = 0x07; // Light gray on black
    }
}

// Function to clear the screen
void clear_screen() {
    char* video_memory = (char*) 0xb8000;
    for (size_t i = 0; i < 80 * 25 * 2; i++) {
        video_memory[i] = 0;
    }
}

// Function to process commands
void process_command(const char* command) {
    if (command[0] == '\0') {
        return; // Ignore empty commands
    } else if (command[0] == 'h' && command[1] == 'e' && command[2] == 'l' && command[3] == 'p' && command[4] == '\0') {
        write_string("Available commands: help, exit", 24);
    } else if (command[0] == 'e' && command[1] == 'x' && command[2] == 'i' && command[3] == 't' && command[4] == '\0') {
        write_string("Exiting shell...", 24);
        while (1); // Halt the system
    } else {
        write_string("Unknown command", 24);
    }
}

// Main function for the shell
extern "C" void shell_main() {
    clear_screen();
    const char* welcome_message = "Welcome to Diamond OS Shell!";
    write_string(welcome_message, 0);
    
    // Simple shell loop
    while (1) {
        write_string("shell> ", 80); // Display prompt

        // Here we would normally read user input. For simplicity, we'll assume a command is entered.
        const char* command = "help"; // Hardcoded command for demonstration
        process_command(command);
    }
}
