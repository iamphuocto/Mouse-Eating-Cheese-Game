// ----------------------------------- framebf.c -------------------------------------
#include "mbox.h"
#include "uart.h"
#include "info.h"
#include "framebf.h"
//Use RGBA32 (32 bits for each pixel)
#define COLOR_DEPTH 32

//Pixel Order: BGR in memory order (little endian --> RGB in byte order)
#define PIXEL_ORDER 0

//Screen info
unsigned int width, height, pitch;

/* Frame buffer address
 * (declare as pointer of unsigned char to access each byte) */
unsigned char *fb;


/**
 * Set screen resolution to 1024x768
 */
void framebf_init()
{
    mBuf[0] = 35*4; // Length of message in bytes
    mBuf[1] = MBOX_REQUEST;

    mBuf[2] = MBOX_TAG_SETPHYWH; //Set physical width-height
    mBuf[3] = 8; // Value size in bytes
    mBuf[4] = 0; // REQUEST CODE = 0
    mBuf[5] = 1024; // Value(width)
    mBuf[6] = 576; // Value(height)

    mBuf[7] = MBOX_TAG_SETVIRTWH; //Set virtual width-height
    mBuf[8] = 8;
    mBuf[9] = 0;
    mBuf[10] = 1024;
    mBuf[11] = 768;

    mBuf[12] = MBOX_TAG_SETVIRTOFF; //Set virtual offset
    mBuf[13] = 8;
    mBuf[14] = 0;
    mBuf[15] = 0; // x offset
    mBuf[16] = 0; // y offset

    mBuf[17] = MBOX_TAG_SETDEPTH; //Set color depth
    mBuf[18] = 4;
    mBuf[19] = 0;
    mBuf[20] = COLOR_DEPTH; //Bits per pixel

    mBuf[21] = MBOX_TAG_SETPXLORDR; //Set pixel order
    mBuf[22] = 4;
    mBuf[23] = 0;
    mBuf[24] = PIXEL_ORDER;

    mBuf[25] = MBOX_TAG_GETFB; //Get frame buffer
    mBuf[26] = 8;
    mBuf[27] = 0;
    mBuf[28] = 16; //alignment in 16 bytes
    mBuf[29] = 0;  //will return Frame Buffer size in bytes

    mBuf[30] = MBOX_TAG_GETPITCH; //Get pitch
    mBuf[31] = 4;
    mBuf[32] = 0;
    mBuf[33] = 0; //Will get pitch value here

    mBuf[34] = MBOX_TAG_LAST;

    // Call Mailbox
    if (mbox_call(ADDR(mBuf), MBOX_CH_PROP) //mailbox call is successful ?
    	&& mBuf[20] == COLOR_DEPTH //got correct color depth ?
		&& mBuf[24] == PIXEL_ORDER //got correct pixel order ?
		&& mBuf[28] != 0 //got a valid address for frame buffer ?
		) {

    	/* Convert GPU address to ARM address (clear higher address bits)
    	 * Frame Buffer is located in RAM memory, which VideoCore MMU
    	 * maps it to bus address space starting at 0xC0000000.
    	 * Software accessing RAM directly use physical addresses
    	 * (based at 0x00000000)
    	*/
    	mBuf[28] &= 0x3FFFFFFF;

        // Access frame buffer as 1 byte per each address
        fb = (unsigned char *)((unsigned long)mBuf[28]);

        width = mBuf[5];     	// Actual physical width
        height = mBuf[6];     	// Actual physical height
        pitch = mBuf[33];       // Number of bytes per line
               
    } else {
    	uart_puts("Unable to get a frame buffer with provided setting\n");
    }
}

void framebf_init1()
{
    mBuf[0] = 35 * 4; // Length of message in bytes
    mBuf[1] = MBOX_REQUEST;

    mBuf[2] = MBOX_TAG_SETPHYWH; // Set physical width-height
    mBuf[3] = 8;                 // Value size in bytes
    mBuf[4] = 0;                 // REQUEST CODE = 0
    mBuf[5] = 1024;              // Value(width)
    mBuf[6] = 768;               // Value(height)

    mBuf[7] = MBOX_TAG_SETVIRTWH; // Set virtual width-height
    mBuf[8] = 8;
    mBuf[9] = 0;
    mBuf[10] = 1024;
    mBuf[11] = 768;

    mBuf[12] = MBOX_TAG_SETVIRTOFF; // Set virtual offset
    mBuf[13] = 8;
    mBuf[14] = 0;
    mBuf[15] = 0; // x offset
    mBuf[16] = 0; // y offset

    mBuf[17] = MBOX_TAG_SETDEPTH; // Set color depth
    mBuf[18] = 4;
    mBuf[19] = 0;
    mBuf[20] = COLOR_DEPTH; // Bits per pixel

    mBuf[21] = MBOX_TAG_SETPXLORDR; // Set pixel order
    mBuf[22] = 4;
    mBuf[23] = 0;
    mBuf[24] = PIXEL_ORDER;

    mBuf[25] = MBOX_TAG_GETFB; // Get frame buffer
    mBuf[26] = 8;
    mBuf[27] = 0;
    mBuf[28] = 16; // alignment in 16 bytes
    mBuf[29] = 0;  // will return Frame Buffer size in bytes

    mBuf[30] = MBOX_TAG_GETPITCH; // Get pitch
    mBuf[31] = 4;
    mBuf[32] = 0;
    mBuf[33] = 0; // Will get pitch value here

    mBuf[34] = MBOX_TAG_LAST;

    // Call Mailbox
    if (mbox_call(ADDR(mBuf), MBOX_CH_PROP) // mailbox call is successful ?
        && mBuf[20] == COLOR_DEPTH          // got correct color depth ?
        && mBuf[24] == PIXEL_ORDER          // got correct pixel order ?
        && mBuf[28] != 0                    // got a valid address for frame buffer ?
    )
    {

        /* Convert GPU address to ARM address (clear higher address bits)
         * Frame Buffer is located in RAM memory, which VideoCore MMU
         * maps it to bus address space starting at 0xC0000000.
         * Software accessing RAM directly use physical addresses
         * (based at 0x00000000)
         */
        mBuf[28] &= 0x3FFFFFFF;

        // Access frame buffer as 1 byte per each address
        fb = (unsigned char *)((unsigned long)mBuf[28]);
       

        width = mBuf[5];  // Actual physical width
        height = mBuf[6]; // Actual physical height
        pitch = mBuf[33]; // Number of bytes per line
    }
    else
    {
        uart_puts("Unable to get a frame buffer with provided setting\n");
    }
}

void drawPixel(int x, int y, unsigned char attr)
{
    int offs = (y * pitch) + (x * 4);
    *((unsigned int *)(fb + offs)) = vgapal[attr & 0x0f];
}
void drawChar(unsigned char ch, int x, int y, unsigned char attr) {
    // add the index for the character
    int index ;
    if ((ch >= 'A' && ch <= 'Z')|| (ch >= 'a' && ch <= 'z')) {
        index = (ch >= 'A' && ch <= 'Z') ? ch - 55: ch - 61;
        }else if (ch >= '0' && ch <= '9'){
            index = ch - 48;
        }else if (ch == ' '){
            index = 62;
        }else if (ch == '!'){
            index = 63;
        }else if (ch == '&'){
            index = 64;
        }else if (ch == 39){ // ASCII value of character '
            index = 65;
        }else if (ch == '@'){
            index = 66;
        }else if (ch == ':'){
            index = 67;
        }else if (ch == ','){
            index = 68;
        }else if (ch == '$'){
            index = 69;
        }else if (ch == '.'){
            index = 70;
        }else if (ch == '%'){
            index = 71;
        }else if (ch == '?'){
            index = 72;
        }else if (ch == '"'){
            index = 73;
        }else if (ch == '('){
            index = 74;
        }else if (ch == ')'){
            index = 75;
        }else if (ch == ';'){
            index = 76;
        }
        else {
            return; // Unsupported character, exit without drawing
        }
// Fill the background with black (0x00)
    for (int i = 0; i < FONT_HGHT; i++) {
        for (int j = 0; j < FONT_WDTH; j++) {
            drawPixel(x + j, y + i, 0x00); // Black background
        }
    }
    for (int i = 0; i < FONT_HGHT; i++) {
        for (int j = 0; j < FONT_WDTH; j++) {
            // get the pixel of the character
            unsigned char *glyph =
                (unsigned char *)&epd_bitmap_allArray[index]
                                                     [i * FONT_WDTH + j];
            // if the pixel is black then draw the pixel with the color 
            // otherwise skip it
         if (*glyph == 0) {
                drawPixel(x + j, y + i, attr);
            }
        }
    }
}
void drawString(int x, int y, char *s, unsigned char attr)
{
    while (*s)
    {
        if (*s == '\r') // carriage return 
        {
            x = 0;
        }
        else if (*s == '\n') // newline 
        {
            x = 0;
            y += (FONT_HGHT);
        }
        else
        {
            drawChar(*s, x, y, attr);
            x += (FONT_WDTH);
        }
        s++;
    }
}

void drawPixelARGB32(int x, int y, unsigned int attr)
{
	int offs = (y * pitch) + (COLOR_DEPTH/8 * x);

/*	//Access and assign each byte
    *(fb + offs    ) = (attr >> 0 ) & 0xFF; //BLUE
    *(fb + offs + 1) = (attr >> 8 ) & 0xFF; //GREEN
    *(fb + offs + 2) = (attr >> 16) & 0xFF; //RED
    *(fb + offs + 3) = (attr >> 24) & 0xFF; //ALPHA
*/

	//Access 32-bit together
	*((unsigned int*)(fb + offs)) = attr;
}


void drawRectARGB32(int x1, int y1, int x2, int y2, unsigned int attr, int fill)
{
	for (int y = y1; y <= y2; y++ )
		for (int x = x1; x <= x2; x++) {
			if ((x == x1 || x == x2) || (y == y1 || y == y2))
				drawPixelARGB32(x, y, attr);
			else if (fill)
				drawPixelARGB32(x, y, attr);
		}
}
void drawlineARGB32(int x1,int y1, int x2, int y2, unsigned int attr){
    for (int y = y1; y <= y2; y++ )
    for (int x = x1; x <= x2; x++) {
			if (( y == (y2-y1)/(x2-x1)*(x-x1)+y1))
				drawPixelARGB32(x, y, attr);
              
}
}
// Draw list of frame images in video
void display_frame(unsigned int frame_image[], int x, int y, int width,int height) 
{
    int num = 0;

    while (y < height) {
        for (x = 0; x < width; x++) {
            int offs = (y * pitch) + (x * 4);
            *((unsigned int *)(fb + offs)) = frame_image[num];
            num++;
        }
        y++;
        x = 0;
    }
}
//Function to display character and string
//Reference: https://github.com/isometimes/rpi4-osdev/tree/master/part5-framebuffer/fb.c 
void drawChar1(unsigned char ch, int x, int y, unsigned char attr, int zm)
{
    unsigned char c = (ch < FONT_NUMGLYPHS ? ch : 0);
    unsigned char *gly = (unsigned char *)&ft + c * FONT_BPG;
    for (int i = 1; i <= (FONT_HEIGHT * zm); i++)
    {
        for (int j = 0; j < (FONT_WIDTH * zm); j++)
        {
            unsigned char msk = 1 << (j / zm);
            unsigned char col;
            if (*gly & msk) col = attr & 0x0f;
            else col = (attr & 0xf0) >> 4;

            drawPixel(x + j, y + i, col); // not drawPixelARGB32
        }
        gly += (i % zm) ? 0 : FONT_BPL;
    }
}
void drawString1(int x, int y, char *s, unsigned char attr, int zm)
{
    while (*s)
    {
        if (*s == '\r') // carriage return 
        {
            x = 0;
        }
        else if (*s == '\n') // newline 
        {
            x = 0;
            y += (FONT_HEIGHT * zm);
        }
        else
        {
            drawChar1(*s, x, y, attr, zm);
            x += (FONT_WIDTH * zm);
        }
        s++;
    }
}