#include "framebf.h"
#include "video.h"
#include "uart.h"

// Function to display video
void displayVideo(int x, int y) {
    // Print message to prompt the user how to use
    uart_puts("Video is playing ...\n");
    uart_puts("Press s to stop ");
    char key;
    // Keep displaying the video until the user press s
    while (1) 
    {
        // Check if the user pressed 's' to stop
        key = uart_getchar();
        if (key == 's') {
            break;
        }
        // // loop through all the frame image video
        for (int i = 0; i < 15; i++) {
            // display each frame image
            display_frame(video[i], x, y, video_width,video_height + y);
            wait_msec(150000);// delay between each frame
        }
    }
    // Print message to announce the user
    uart_puts("\nStopping video ...");
}