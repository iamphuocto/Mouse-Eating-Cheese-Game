#include "framebf.h"
#include "uart.h"
#include "3bearsover_img.h"
#include "img.h"
#define TOTAL_IMAGES 3
// Global variables to track the current image index 
int Image = 0;
// Function to clear the emulator screen before showing new thing
void clearscreen(int width, int height)
{
  // Clear both width and height of the screen
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      drawPixel(w, h, 0);
    }
  }
}
// Function to display 3 bears image (oversize image)
void display3bearsoverImage(int x, int y)
{
  for (int h = 0; h < bearsover_height; h++)
  {
    for (int w = 0; w < bearsover_width; w++)
    {
      drawPixelARGB32(x + w, y + h, bearsover_img[h * bearsover_width + w]);
    }
  }
}
// Function to offset the screen up and down
void moveScreen(int width, int height, int x, int y)
{
  for (int h = 0; h < height; h++)
  {
    for (int w = 0; w < width; w++)
    {
      drawPixelARGB32(x + w, y + h, 0);
    }
  }
}
// Function to scroll up and down image (oversize image)
void controlImage(int x, int y)
{
  // Prompt the user how to use
  uart_puts("Press w to scroll up: \n");
  uart_puts("Press s to scroll down: \n");
  uart_puts("Press o to exit: \n");

  // Assign value for screen width, height and offset value for each time scroll up or down
  int screen_width = 1200;
  int offset_value = 10;
  display3bearsoverImage(x, y);
    while (1)
  {
    // Declare key variable to get user input
    char key = uart_getc();

    // Handle user input using a switch statement
    switch (key)
    {
      case 'w':
        // Scroll up
        moveScreen(screen_width, offset_value, x, y);
        y += offset_value;
        break;
      case 's':
        // Scroll down
        moveScreen(screen_width, offset_value, x, y);
        y -= offset_value;
        break;
      case 'o':
        // Stop scrolling and exit
        clearscreen(1024, 768);
        uart_puts("\n\nSuccessfully out!\n");
        return;// Skip the rest of the loop and prompt for input again
      default:
        // Invalid input, display a message
        uart_puts("Invalid command. Please try again.\n");
        continue; 
    }
    // display the updated image
    display3bearsoverImage(x, y);
  }
}

// Function to display a single image at the specified coordinates
void displayImage(int x, int y)
{
   const unsigned int width = 1024;
   const unsigned int height = 576;
    // Display the image at the specified coordinates
    switch (Image)
    {
      case 0:
        for (int h = 0; h < height; h++)
        {
          for (int w = 0; w < width; w++)
          {
            drawPixelARGB32(x + w, y + h, img1[h * width + w]);
          }
        }
        break;
      case 1:
        for (int h = 0; h < height; h++)
        {
          for (int w = 0; w < width; w++)
          {
            drawPixelARGB32(x + w, y + h, img2[h * width + w]);
          }
        } 
        break;
      case 2:
        for (int h = 0; h < height; h++)
        {
          for (int w = 0; w < width; w++)
          {
            drawPixelARGB32(x + w, y + h, img3[h * width + w]);
          }
        } 
        break;
      default:
        break;
    }
}

// Function to switch to the next image in the slideshow
void nextImage()
{
    Image = (Image + 1) % TOTAL_IMAGES;
    displayImage(0, 0);
}

// Function to switch to the previous image in the slideshow
void prevImage()
{
    Image = (Image - 1 + TOTAL_IMAGES) % TOTAL_IMAGES;
    displayImage(0, 0);
}

void switchImage()
{
   // Prompt the user how to use
  uart_puts("Press a to switch to previous image: \n");
  uart_puts("Press d to switch to next image: \n");
  uart_puts("Press o to exit: \n");
    // Display the initial image
    displayImage(0,0);

    while (1)
    {
        // Read user input
        char key = uart_getc();

        // Handle user input
        switch (key)
        {
        case 'a':
            prevImage();
            break;
        case 'd':
            nextImage();
            break;
        case 'o':
         // Stop slideshow
            clearscreen(1024, 768);
            uart_puts("\n\nSuccessfully out!\n");
            return;
        default:
            uart_puts("Invalid command. Use 'a' and 'd' to switch images.\n");
            continue;;
        }
    }
}
