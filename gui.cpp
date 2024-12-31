#include <stddef.h>
#include <stdint.h>

// Function to set a pixel at (x, y) with color
void set_pixel(int x, int y, uint8_t color) {
    uint8_t* video_memory = (uint8_t*) 0xA0000; // VGA graphics mode
    video_memory[y * 320 + x] = color;
}

// Function to draw a rectangle
void draw_rectangle(int x, int y, int width, int height, uint8_t color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            set_pixel(x + i, y + j, color);
        }
    }
}

// Function to clear the screen
void clear_screen(uint8_t color) {
    for (int y = 0; y < 200; y++) {
        for (int x = 0; x < 320; x++) {
            set_pixel(x, y, color);
        }
    }
}

// Main function for GUI
extern "C" void gui_main() {
    clear_screen(0x1F); // Clear screen with blue color
    draw_rectangle(50, 50, 100, 50, 0x4F); // Draw a rectangle
    while (1); // Keep the GUI running
}
