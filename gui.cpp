#include <stddef.h>
#include <stdint.h>

// Screen dimensions
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

// Function to set a pixel at (x, y) with color
void set_pixel(int x, int y, uint8_t color) {
    uint8_t* video_memory = (uint8_t*) 0xA0000; // VGA graphics mode
    video_memory[y * SCREEN_WIDTH + x] = color;
}

// Function to draw a rectangle
void draw_rectangle(int x, int y, int width, int height, uint8_t color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            set_pixel(x + i, y + j, color);
        }
    }
}

// Function to draw an "X" button
void draw_x_button(int x, int y, uint8_t color) {
    // Draw an "X" using two lines
    for (int i = 0; i < 10; i++) {
        set_pixel(x + i, y + i, color);
        set_pixel(x + 9 - i, y + i, color);
    }
}

// Function to clear the screen
void clear_screen(uint8_t color) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            set_pixel(x, y, color);
        }
    }
}

// Function to check if a point is inside a rectangle
int is_point_in_rectangle(int px, int py, int rx, int ry, int rw, int rh) {
    return (px >= rx && px < rx + rw && py >= ry && py < ry + rh);
}

// Main function for GUI
extern "C" void gui_main() {
    clear_screen(0x1F); // Clear screen with blue color

    int rect_x = 50;
    int rect_y = 50;
    int rect_width = 100;
    int rect_height = 50;
    uint8_t rect_color = 0x4F;
    int x_button_x = rect_x + rect_width - 10;
    int x_button_y = rect_y;

    draw_rectangle(rect_x, rect_y, rect_width, rect_height, rect_color); // Draw a rectangle
    draw_x_button(x_button_x, x_button_y, 0x0F); // Draw the "X" button

    while (1) {
        // Here we would normally read mouse input. For simplicity, we'll simulate a click.
        int mouse_x = 60; // Hardcoded mouse position for demonstration
        int mouse_y = 60;

        if (is_point_in_rectangle(mouse_x, mouse_y, x_button_x, x_button_y, 10, 10)) {
            // If the "X" button is clicked, clear the rectangle
            draw_rectangle(rect_x, rect_y, rect_width, rect_height, 0x1F);
        }
    }
}
