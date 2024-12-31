// shell.cpp
#include <stddef.h>
#include <stdint.h>

// Function to write a string to the screen
void write_string(const char* str) {
    char* video_memory = (char*) 0xb8000;
    for (size_t i = 0; str[i] != '\0'; i++) {
        video_memory[i * 2] = str[i];
        video_memory[i * 2 + 1] = 0x07; // Light gray on black
    }
}

// Main function for the shell
extern "C" void shell_main() {
    const char* welcome_message = "Welcome to Diamond OS Shell!";
    write_string(welcome_message);
    
    // Implement further shell functionality here

    while (1); // Keep the shell running
}
