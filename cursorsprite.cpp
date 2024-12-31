#include <stddef.h>
#include <stdint.h>

// Function to set a pixel at (x, y) with color
void set_pixel(int x, int y, uint8_t color) {
    uint8_t* video_memory = (uint8_t*) 0xA0000; // VGA graphics mode
    video_memory[y * 320 + x] = color;
}

// Function to draw a cursor sprite
void draw_cursor(int x, int y, uint8_t color) {
    // Draw a simple crosshair cursor
    for (int i = -2; i <= 2; i++) {
        set_pixel(x + i, y, color);
        set_pixel(x, y + i, color);
    }
}

// Function to clear the cursor sprite
void clear_cursor(int x, int y) {
    for (int i = -2; i <= 2; i++) {
        set_pixel(x + i, y, 0x1F); // Assuming background color is 0x1F
        set_pixel(x, y + i, 0x1F); // Assuming background color is 0x1F
    }
}

// Main function for cursor sprite
extern "C" void cursor_main() {
    int cursor_x = 160;
    int cursor_y = 100;

    draw_cursor(cursor_x, cursor_y, 0x0F); // Draw initial cursor

    while (1) {
        // Here we would normally read mouse input. For simplicity, we'll simulate movement.
        clear_cursor(cursor_x, cursor_y); // Clear the current cursor position
        cursor_x += 1; // Simulate cursor moving right
        cursor_y += 1; // Simulate cursor moving down
        draw_cursor(cursor_x, cursor_y, 0x0F); // Draw cursor at new position
    }
}
