#include "uart.h"
#include "framebf.h"
#include "game.h"
#include "game_data.h"
#include "display_img.h"
void drawcheese(int x, int y)
{
    for (int h = 0; h < cheese_height; h++)
    {
        for (int w = 0; w < cheese_width; w++)
        {
            drawPixelARGB32(x + w, y + h, cheese[h * cheese_width + w]);
        }
    }
}
void removecheese(int x, int y)
{
    for (int h = 0; h < cheese_height; h++)
    {
        for (int w = 0; w < cheese_width; w++)
        {
            drawPixelARGB32(x + w, y + h, 0x00);
        }
    }
}
void removecheese1(int x, int y, int mouseX, int mouseY)
{
    for (int h = 0; h < cheese_height; h++)
    {
        for (int w = 0; w < cheese_width; w++)
        {
            // Check if the current pixel is not within the mouse area
            if (x + w < mouseX || x + w >= mouseX + 40 || y + h < mouseY || y + h >= mouseY + 40)
            {
                drawPixelARGB32(x + w, y + h, 0x00); // Set the pixel to the background color (0x00 in your code).
            }
        }
    }
}

void drawtrap(int x, int y)
{
    for (int h = 0; h < trap_height; h++)
    {
        for (int w = 0; w < trap_width; w++)
        {
            drawPixelARGB32(x + w, y + h, trap[h * trap_width + w]);
        }
    }
}
void removetrap(int x, int y)
{
    for (int h = 0; h < trap_height; h++)
    {
        for (int w = 0; w < trap_width; w++)
        {
            drawPixelARGB32(x + w, y + h, 0x00);
        }
    }
}

int comp_str(char sr1[], char sr2[]) // function comparing 2 strings if they are the same
{
    int flag_compare = 0; // flag indicating if 2 strings are the same
    int i = 0;            // variables looping through string

    while (sr1[i] != '\0' || sr2[i] != '\0') // looping each characters of two strings and compare them
    {
        if (sr1[i] != sr2[i])
        {
            flag_compare = 1;
            break;
        }

        if (sr1[i] == '\0' && sr2[i] != '\0')
        {
            flag_compare = 1;
            break;
        }
        i++; // move to next character
    }
    if (flag_compare == 0)
        return 1;
    else
        return 0;
}

int comp_str_short(char sr1[], char sr2[]) // function comparing 2 strings if they are the same
{
    int flag_compare = 0; // flag indicating if 2 strings are the same
    int i = 0;            // variables looping through string

    while (sr1[i] != '\0' && sr2[i] != '\0') // looping each characters of two strings and compare them
    {
        if (sr1[i] != sr2[i])
        {
            flag_compare = 1;
            break;
        }
        i++; // move to next character
    }
    if (flag_compare == 0)
        return 1;
    else
        return 0;
}

void paste_str(char sr1[], const char sr2[]) // function copying string and put data into another string
{
    int i = 0;
    while (sr2[i] != '\0')
    {
        sr1[i] = sr2[i];
        i++;
    }
    sr1[i] = '\0';
}

void print_welcome_game() // function displaying welcome message game
{
    // execute the font _ welcome message to game
    drawString1(0, 5, "WELCOME TO GAME MOUSE EATING CHEESE!!\n", 0x0a, 3);
    int count = 0;
    for (int x = 400; x < 800; x++)
    {
        for (int y = 50; y < 330; y++)
        {
            drawPixelARGB32(x, y, epd_bitmap_title[count]);
            count += 1;
        }
    }
    drawString1((1024 / 2) - 300, 280, "\rHOW TO PLAY:\n", 0x0b, 2);
    drawString1((1024 / 2) - 300, 350, "\rUse key \"a\" to move left, or \"d\" to move right.\n", 0x0b, 2);
    drawString1((1024 / 2) - 300, 400, "\rUse key \"w\" to go up, or \"s\" to go down.\n", 0x0b, 2);
    drawString1((1024 / 2) - 300, 450, "\rRules: Eat four peices of cheese, and go out door.\n", 0x0b, 2);
    drawString1((1024 / 2) - 300, 500, "\rDon't let cats catch your mouse\n", 0x0b, 2);
    drawString1((1024 / 2) - 300, 550, "\rThere are two traps in two unknown cheeses, try to avoid it!!\n", 0x0b, 2);
    drawString1((1024 / 2) - 300, 630, "\rPress enter to start !!!\n", 0x0d, 2);

    count = 0;
    for (int x = 400; x < 700; x++)
    {
        for (int y = 670; y < 770; y++)
        {
            drawPixelARGB32(x, y, epd_bitmap_enter[count]);
            count += 1;
        }
    }
}

void print_count_game() // function displaying welcome count down to start playing game
{
    // clear screen first
    int count = 0;
    for (int x = 0; x < 1024; x++)
    {
        for (int y = 0; y < 768; y++)
        {
            drawPixelARGB32(x, y, 0x00);
        }
    }

    // show number 3
    count = 0;
    for (int x = 1024 / 2 - 100; x < 712; x++)
    {
        for (int y = 200; y < 500; y++)
        {
            drawPixelARGB32(x, y, epd_bitmap_number_3[count]);
            count += 1;
        }
    }
    wait_msec(1000000);
    // show number 2
    count = 0;
    for (int x = 1024 / 2 - 100; x < 712; x++)
    {
        for (int y = 200; y < 500; y++)
        {
            drawPixelARGB32(x, y, epd_bitmap_number_2[count]);
            count += 1;
        }
    }
    wait_msec(1000000);
    // show number 1
    count = 0;
    for (int x = 1024 / 2 - 100; x < 712; x++)
    {
        for (int y = 200; y < 500; y++)
        {
            drawPixelARGB32(x, y, epd_bitmap_number_1[count]);
            count += 1;
        }
    }
    wait_msec(1000000);
    // show start game
    count = 0;
    for (int x = 1024 / 2 - 100; x < 712; x++)
    {
        for (int y = 200; y < 500; y++)
        {
            drawPixelARGB32(x, y, epd_bitmap_start_game[count]);
            count += 1;
        }
    }
}

void print_Win_mess() // print winning messsge
{
    int count = 0;

    // clear screen first
    for (int i = 0; i < 1024; i++)
    {
        for (int j = 0; j < 768; j++)
        {
            drawPixelARGB32(i, j, 0x00);
        }
    }

    // draw Congratulation picture
    for (int i = 262; i < 762; i++)
    {
        for (int j = 0; j < 450; j++)
        {
            drawPixelARGB32(i, j, epd_bitmap_congrats[count]);
            count++;
        }
    }

    // draw Mouse eating cheese
    count = 0;
    for (int i = 362; i < 662; i++)
    {
        for (int j = 468; j < 768; j++)
        {
            drawPixelARGB32(i, j, epd_bitmap_mouse_eating_cheese[count]);
            count++;
        }
    }
}

void drawMap1() // draw the map
{
    int count = 0;
    for (int x = 0; x < 1024; x++)
    {
        for (int y = 0; y < 768; y++)
        {
            drawPixelARGB32(x, y, epd_bitmap_map1_mouse[count]);
            count += 1;
        }
    }

    drawString1(5, 10, "Score: ", 0x0f, 1); // draw the Score
}
void drawMap2(int x, int y) // draw the map
{
    const unsigned int map_width = 1024;
    const unsigned int map_height = 768;
    for (int h = 0; h < map_height; h++)
    {
        for (int w = 0; w < map_width; w++)
        {
            drawPixelARGB32(x + w, y + h, epd_bitmap_map2[h * map_width + w]);
        }
    }

    drawString1(5, 10, "Score: ", 0x0f, 1); // draw the Score
}

void drawCatleft(int x, int y) // draw the character Cat moving left
{
    int count = 0;
    for (int x_c = x; x_c < x + 110; x_c++)
    {
        for (int y_c = y; y_c < y + 110; y_c++)
        {
            drawPixelARGB32(x_c, y_c, epd_bitmap_catleft[count]);
            count++;
        }
    }
}

void drawCatright(int x, int y) // draw the character Cat moving right
{
    int count = 0;
    for (int x_c = x; x_c < x + 110; x_c++)
    {
        for (int y_c = y; y_c < y + 110; y_c++)
        {
            drawPixelARGB32(x_c, y_c, epd_bitmap_catright[count]);
            count++;
        }
    }
}

void drawCatup(int x, int y) // draw the character Cat moving up
{
    int count = 0;
    for (int x_c = x; x_c < x + 110; x_c++)
    {
        for (int y_c = y; y_c < y + 110; y_c++)
        {
            drawPixelARGB32(x_c, y_c, epd_bitmap_catup[count]);
            count++;
        }
    }
}

void drawCatdown(int x, int y) // draw the character Cat moving down
{
    int count = 0;
    for (int x_c = x; x_c < x + 110; x_c++)
    {
        for (int y_c = y; y_c < y + 110; y_c++)
        {
            drawPixelARGB32(x_c, y_c, epd_bitmap_catdown[count]);
            count++;
        }
    }
}

void drawCat3left(int x, int y) // draw the 2-leg cat moving left
{
    int count = 0;
    for (int x_c = x; x_c < x + 60; x_c++)
    {
        for (int y_c = y; y_c < y + 60; y_c++)
        {
            drawPixelARGB32(x_c, y_c, epd_bitmap_cat2_left[count]);
            count++;
        }
    }
}

void drawCat3right(int x, int y) // draw the 2-leg cat moving right
{
    int count = 0;
    for (int x_c = x; x_c < x + 60; x_c++)
    {
        for (int y_c = y; y_c < y + 60; y_c++)
        {
            drawPixelARGB32(x_c, y_c, epd_bitmap_cat2_right[count]);
            count++;
        }
    }
}

void drawMouseup(int x, int y) // draw the character Mouse moving up
{
    int count = 0;
    for (int x_c = x; x_c < x + 40; x_c++)
    {
        for (int y_c = y; y_c < y + 40; y_c++)
        {
            drawPixelARGB32(x_c, y_c, epd_bitmap_mouseup[count]);
            count++;
        }
    }
}

void drawMousedown(int x, int y) // draw the character Mouse moving down
{
    int count = 0;
    for (int x_c = x; x_c < x + 40; x_c++)
    {
        for (int y_c = y; y_c < y + 40; y_c++)
        {
            drawPixelARGB32(x_c, y_c, epd_bitmap_mousedown[count]);
            count++;
        }
    }
}

void drawMouseleft(int x, int y) // draw the character Mouse moving left
{
    int count = 0;
    for (int x_c = x; x_c < x + 40; x_c++)
    {
        for (int y_c = y; y_c < y + 40; y_c++)
        {
            drawPixelARGB32(x_c, y_c, epd_bitmap_mouseleft[count]);
            count++;
        }
    }
}

void drawMouseright(int x, int y) // draw the character Mouse moving right
{
    int count = 0;
    for (int x_c = x; x_c < x + 40; x_c++)
    {
        for (int y_c = y; y_c < y + 40; y_c++)
        {
            drawPixelARGB32(x_c, y_c, epd_bitmap_mouseright[count]);
            count++;
        }
    }
}

void removeMouse(int x, int y) // remove Mouse on screen
{
    drawRectARGB32(x, y, x + 40, y + 40, 0x00, 1);
}

void removeCat(int x, int y) // remove Cat on screen
{
    drawRectARGB32(x, y, x + 110, y + 110, 0x00, 1);
}

void removeCat3(int x, int y) // remove Cat 3 on screen
{
    drawRectARGB32(x, y, x + 60, y + 60, 0x00, 1);
}

void moveMouse(int ox, int oy, int nx, int ny, char c)
{
    removeMouse(ox, oy); // first clear mouse on screen
    if (c == 'a')
        drawMouseleft(nx, ny);
    else if (c == 'd')
        drawMouseright(nx, ny);
    else if (c == 'w')
        drawMouseup(nx, ny);
    else if (c == 's')
        drawMousedown(nx, ny);
}

void moveCat(int ox, int oy, int nx, int ny, char c)
{
    removeCat(ox, oy); // first clear cat on screen
    if (c == 'a')
        drawCatleft(nx, ny);
    else if (c == 'd')
        drawCatright(nx, ny);
    else if (c == 'w')
        drawCatup(nx, ny);
    else if (c == 's')
        drawCatdown(nx, ny);
}

void moveCat3(int ox, int oy, int nx, int ny, char c)
{
    removeCat3(ox, oy); // first clear cat 3 on screen
    if (c == 'a')
        drawCat3left(nx, ny);
    else if (c == 'd')
        drawCat3right(nx, ny);
}

void drawgate(int x, int y) // draw the gate in map
{
    int count = 0;
    for (int x_c = x; x_c < x + 71; x_c++)
    {
        for (int y_c = y; y_c < y + 65; y_c++)
        {
            drawPixelARGB32(x_c, y_c, epd_bitmap_gate[count]);
            count++;
        }
    }
}

int identCollision(int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22)
{
    // Check if the two retangles defined by (x11, y11, x12, y12) and (x21, y21, x22, y22) overlap.
    if (x11 < x22 && x12 > x21 && y11 < y22 && y12 > y21)
    {
        // The two rectangles overlap, indicating a collision.
        return 1;
    }

    // The rectangles do not overlap, indicating no collision.
    return 0;
}

void start_game() // restarting game
{
    // clear screen
    clearscreen(1920, 1080);

    print_welcome_game();
    char c = uart_getc();
    while (c != '\n')
    {
        c = uart_getc();
    }
    if (c == '\n')
        print_count_game();

    // draw the map1
    drawMap1();
    drawCatleft(260, 190);      // draw cat 1
    drawCatleft(830, 190);      // draw cat 2
    drawMouseup(1024 / 2, 700); // draw mouse
    drawgate(950, 30);
}

int playGame1() // playing game1
{
    // define initial coordinate of mouse
    int xms = 1024 / 2;
    int yms = 700;

    // define initial coordinate of cat 1
    int xcat1 = 260;
    int ycat1 = 190;

    // define initial coordinate of cat 2
    int xcat2 = 830;
    int ycat2 = 190;

    char c = uart_getc(); // input the first key from user
    // use to chnange the direction of two cats
    int flag_cat1 = 0;
    int flag_cat2 = 0;

    // use in when mouse hitting walls
    int flag_a = 0;
    int flag_s = 0;
    int flag_w = 0;
    int flag_d = 0;

    // use in mouse eating cheese
    int flag_c1 = 0;
    int flag_c2 = 0;
    int flag_c3 = 0;
    int flag_c4 = 0;

    // use in mouse trap
    int flag_trap1 = 0;
    int flag_trap2 = 0;

    // use in when user is winner
    int flag_win = 0;

    char pc = 'w'; // char to input the previous key of direction

    int score = 0;
    char sc = score + '0';
    int velo = 10;
    int count = 0;
    while (1)
    {
        // execute the path of cat 1
        if (flag_cat1 == 0)
        {
            int velo = 11;
            moveCat(xcat1, ycat1, xcat1 - velo, ycat1, 'a');
            xcat1 -= velo;
            wait_msec(50000);
            if (xcat1 <= 40)
                flag_cat1 = 1;
        }
        else if (flag_cat1 == 1)
        {
            int velo = 11;
            moveCat(xcat1, ycat1, xcat1, ycat1 + velo, 's');
            ycat1 += velo;
            wait_msec(50000);
            if (ycat1 > 400)
                flag_cat1 = 2;
        }
        else if (flag_cat1 == 2)
        {
            int velo = 11;
            moveCat(xcat1, ycat1, xcat1 + velo, ycat1, 'd');
            xcat1 += velo;
            wait_msec(50000);
            if (xcat1 >= 240)
                flag_cat1 = 3;
        }
        else if (flag_cat1 == 3)
        {
            int velo = 11;
            moveCat(xcat1, ycat1, xcat1, ycat1 - velo, 'w');
            ycat1 -= velo;
            wait_msec(50000);
            if (ycat1 <= 190)
                flag_cat1 = 0;
        }

        // execute the path of cat 2
        if (flag_cat2 == 0)
        {
            int velo = 11;
            moveCat(xcat2, ycat2, xcat2 - velo, ycat2, 'a');
            xcat2 -= velo;
            wait_msec(50000);
            if (xcat2 <= 680)
                flag_cat2 = 1;
        }
        else if (flag_cat2 == 1)
        {
            int velo = 11;
            moveCat(xcat2, ycat2, xcat2, ycat2 + velo, 's');
            ycat2 += velo;
            wait_msec(50000);
            if (ycat2 > 400)
                flag_cat2 = 2;
        }
        else if (flag_cat2 == 2)
        {
            int velo = 11;
            moveCat(xcat2, ycat2, xcat2 + velo, ycat2, 'd');
            xcat2 += velo;
            wait_msec(50000);
            if (xcat2 >= 900)
                flag_cat2 = 3;
        }
        else if (flag_cat2 == 3)
        {
            int velo = 11;
            moveCat(xcat2, ycat2, xcat2, ycat2 - velo, 'w');
            ycat2 -= velo;
            wait_msec(50000);
            if (ycat2 <= 190)
                flag_cat2 = 0;
        }

        // use trap mouse
        if ((count % 160) >= 0 && (count & 160) < 80)
        {
            removetrap(830, 690);
            if (flag_c2 == 0)
                drawcheese(830, 690);
            flag_trap1 = 1;
            removecheese(45, 690);
            drawtrap(45, 690);
            flag_trap2 = 0;
        }
        else if ((count % 160) >= 80 && (count & 160) <= 159)
        {
            removecheese(830, 690);
            drawtrap(830, 690);
            removetrap(45, 690);
            if (flag_c1 == 0)
                drawcheese(45, 690);
            flag_trap2 = 1;
            flag_trap1 = 0;
        }

        // control mouse movement
        if (c == 'a' && flag_a == 0)
        {
            if (count == 0)
            {

                int velo = 10; // shift to 10 pixel
                moveMouse(xms, yms, xms - velo, yms, 'a');
                xms -= velo;
            }
            else
            {
                if (pc == c)
                {

                    int velo = 10; // shift to 10 pixel
                    moveMouse(xms, yms, xms - velo, yms, 'a');
                    xms -= velo;
                }
                else if (pc != c)
                {

                    int velo = 0; // not shifting
                    moveMouse(xms, yms, xms - velo, yms, 'a');
                    xms -= velo;
                    if (flag_w == 1)
                        flag_w = 0;
                    if (flag_s == 1)
                        flag_s = 0;
                    if (flag_d == 1)
                        flag_d = 0;
                }
            }
        }
        else if (c == 'd' && flag_d == 0)
        {
            if (count == 0)
            {

                int velo = 10; // shift to 10 pixel
                moveMouse(xms, yms, xms + velo, yms, 'd');
                xms += velo;
            }
            else
            {
                if (pc == c)
                {

                    int velo = 10; // shift to 10 pixel
                    moveMouse(xms, yms, xms + velo, yms, 'd');
                    xms += velo;
                }
                else if (pc != c)
                {

                    int velo = 0; // not shifting
                    moveMouse(xms, yms, xms + velo, yms, 'd');
                    xms += velo;
                    if (flag_w == 1)
                        flag_w = 0;
                    if (flag_s == 1)
                        flag_s = 0;
                    if (flag_a == 1)
                        flag_a = 0;
                }
            }
        }
        else if (c == 'w' && flag_w == 0)
        {
            if (count == 0)
            {

                int velo = 10; // shift to 10 pixel
                moveMouse(xms, yms, xms, yms - velo, 'w');
                yms -= velo;
            }
            else
            {
                if (pc == c)
                {

                    int velo = 10; // shift to 10 pixel
                    moveMouse(xms, yms, xms, yms - velo, 'w');
                    yms -= velo;
                }
                else
                {

                    int velo = 0;
                    moveMouse(xms, yms, xms, yms - velo, 'w');
                    yms -= velo;
                    if (flag_d == 1)
                        flag_d = 0;
                    if (flag_s == 1)
                        flag_s = 0;
                    if (flag_a == 1)
                        flag_a = 0;
                }
            }
        }
        else if (c == 's' && flag_s == 0)
        {
            if (count == 0)
            {

                int velo = 10; // shift to 10 pixel
                moveMouse(xms, yms, xms, yms + velo, 's');
                yms += velo;
            }
            else
            {
                if (pc == c)
                {

                    int velo = 10; // shift to 10 pixel
                    moveMouse(xms, yms, xms, yms + velo, 's');
                    yms += velo;
                }
                else
                {

                    int velo = 0;
                    moveMouse(xms, yms, xms, yms + velo, 's');
                    yms += velo;
                    if (flag_d == 1)
                        flag_d = 0;
                    if (flag_s == 1)
                        flag_s = 0;
                    if (flag_a == 1)
                        flag_a = 0;
                }
            }
        }

        // check the collision b/w mouse and walls
        if (identCollision(xms, yms, xms + 40, yms + 40, 160, 540, 285, 790)     // bottom left object
            || identCollision(xms, yms, xms + 40, yms + 40, 680, 570, 805, 790)  // bottom right object
            || identCollision(xms, yms, xms + 40, yms + 40, 360, 302, 680, 480)  // middle object
            || identCollision(xms, yms, xms + 40, yms + 40, 210, 88, 435, 175)  // top left object
            || identCollision(xms, yms, xms + 40, yms + 40, 790, 90, 1055, 200) // top right object
            || identCollision(xms, yms, xms + 40, yms + 40, 0, 0, 15, 768)       // right boudary
            || identCollision(xms, yms, xms + 40, yms + 40, 0, 0, 1024, 15)      // top boudary
            || identCollision(xms, yms, xms + 50, yms + 40, 0, 770, 1024, 768)   // bottom boundary
            || identCollision(xms, yms, xms + 40, yms + 40, 1010, 0, 1024, 768)  // left boundary
            || identCollision(xms, yms, xms + 40, yms + 40, 0, 0, 600, 50))       // score area

        {
            uart_puts("hit walls\n");
            if (c == 'a')
            {
                moveMouse(xms, yms, xms + velo, yms, 'a');
                xms += velo;
                flag_a = 1;
            }
            else if (c == 'd')
            {
                moveMouse(xms, yms, xms - velo, yms, 'd');
                xms -= velo;
                flag_d = 1;
            }
            else if (c == 'w')
            {
                moveMouse(xms, yms, xms, yms + velo, 'w');
                yms += velo;
                flag_w = 1;
            }
            else if (c == 's')
            {
                moveMouse(xms, yms, xms, yms - velo, 's');
                yms -= velo;
                flag_s = 1;
            }
        }
        // check the coliision b/w mouse and 2 cats
        if (identCollision(xms, yms, xms + 40, yms + 40, xcat1, ycat1, xcat1 + 100, ycat1 + 100) || identCollision(xms, yms, xms + 40, yms + 40, xcat2, ycat2, xcat2 + 100, ycat2 + 100))
        {
            wait_msec(2000);
            clearscreen(1024, 768);
            drawString((1024 / 2) - 400, 768 / 2, "CATS CATCH YOU!!", 0x0c);
            drawString((1024 / 2) - 250, 768 / 2 + 50, "GAME OVER!!", 0x0c);
            break;
        }

        if (c == 'a' || c == 's' || c == 'w' || c == 'd')
            pc = c;
        c = getUart();

        // check mouse eating cheese
        if (identCollision(xms, yms, xms + 40, yms + 40, 55, 710, 95, 730)) // left bottom cheese
        {
            removecheese1(45, 690, xms, yms);
            if (flag_trap1 == 0 && flag_c1 == 0)
            {
                uart_puts("eating cheese !\n");
                score++;
                sc = score + '0';
                drawChar1(sc, 50, 10, 0x0f, 1);
                flag_c1 = 1;
            }
            else if (flag_trap1 == 1)
            {
                clearscreen(1024, 768);
                drawString((1024 / 2) - 400, 768 / 2, "MOUSE IS STRUCK!!", 0x0a);
                drawString((1024 / 2) - 250, 768 / 2 + 50, "GAME OVER!!", 0x0c);
                break;
            }
        }

        if (identCollision(xms, yms, xms + 40, yms + 40, 850, 710, 880, 730)) // right bottom cheese
        {
            removecheese1(830, 690, xms, yms);
            if (flag_trap2 == 0 && flag_c2 == 0)
            {
                score++;
                sc = score + '0';
                drawChar1(sc, 50, 10, 0x0f, 1);
                flag_c2 = 1;
            }
            else if (flag_trap2 == 1)
            {
                clearscreen(1024, 768);
                drawString((1024 / 2) - 400, 768 / 2, "MOUSE IS STRUCK!!", 0x0a);
                drawString((1024 / 2) - 250, 768 / 2 + 50, "GAME OVER!!", 0x0c);
                break;
            }
        }

        if (identCollision(xms, yms, xms + 40, yms + 40, 150, 345, 195, 395)) // middle left cheese
        {
            removecheese1(150, 345, xms, yms);
            if (flag_c3 == 0)
            {
                score++;
                sc = score + '0';
                drawChar1(sc, 50, 10, 0x0f, 1);
                flag_c3 = 1;
            }
        }

        if (identCollision(xms, yms, xms + 40, yms + 40, 845, 365, 880, 390)) // middle right cheese
        {
            removecheese1(845, 345, xms, yms);
            if (flag_c4 == 0)
            {
                score++;
                sc = score + '0';
                drawChar1(sc, 50, 10, 0x0f, 1);
                flag_c4 = 1;
            }
        }
        count++;

        // mouse reaching to gate
        if (identCollision(xms, yms, xms + 40, yms + 40, 950, 40, 1024, 95))
        {
            if (score == 4)
            {
                drawString((1024 / 2) - 120, 768 / 2 + 40, "YOU WIN!!", 0x0f);
                flag_win = 1;
            }
            else if (score < 4)
            {
                drawString1((1024 / 2) - 430, 200, "HAVE TO COLLECT ALL CHEESES!!", 0x0f, 3);
                // draw gate again
                drawRectARGB32(930, 5, 1024, 100, 0x00, 1); // remove original gate
                drawgate(950, 40);
                wait_msec(100000);
                drawRectARGB32(0, 200, 1024, 235, 0x00, 1);
            }
        }
        if (flag_win == 1)
            break;
    }
    return flag_win;
}

int playGame2() // playing game2
{
    // draw the map2
    drawMap2(0, 0);

    drawRectARGB32(5, 400, 141, 768, 0x00, 1); // remove original gate

    // define initial coordinate of mouse
    int xms = 1024 / 2;
    int yms = 700;

    // define initial coordinate of cat 1 (middle left)
    int xcat1 = 180;
    int ycat1 = 260;

    // define initial coordinate of cat 2 (middle right)
    int xcat2 = 900;
    int ycat2 = 370;

    // define initial coordinate of cat 3 (top corner)
    int xcat3 = 740;
    int ycat3 = 20;

    drawCatleft(xcat1, ycat1);  // draw cat 1 (middle left)
    drawCatleft(xcat2, ycat2);  // draw cat 2 (middle right)
    drawCat3left(xcat3, ycat3); // draw 2-leg Cat (top corner)
    drawgate(5, 660); // draw gate

    drawMouseup(xms, yms); // draw mouse

    char c = uart_getc(); // input the first key from user
    // use to chnange the direction of two cats
    int flag_cat1 = 0;
    int flag_cat2 = 0;
    int flag_cat3 = 0;

    // use in when mouse hitting walls
    int flag_a = 0;
    int flag_s = 0;
    int flag_w = 0;
    int flag_d = 0;

    // use in mouse eating cheese
    int flag_c1 = 0;
    int flag_c2 = 0;
    int flag_c3 = 0;
    int flag_c4 = 0;

    // use in mouse trap
    int flag_trap1 = 0;
    int flag_trap2 = 0;

    // use in when user is winner
    int flag_win = 0;

    char pc = 'w'; // char to input the previous key of direction

    int score = 0;
    char sc = score + '0';
    int velo = 10;
    int count = 0;
    while (1)
    {
        // execute the path of cat 1
        if (flag_cat1 == 0)
        {
            int velo = 10;
            moveCat(xcat1, ycat1, xcat1 - velo, ycat1, 'a');
            xcat1 -= velo;
            wait_msec(50000);
            if (xcat1 <= 30)
                flag_cat1 = 1;
        }
        else if (flag_cat1 == 1)
        {
            int velo = 10;
            moveCat(xcat1, ycat1, xcat1, ycat1 + velo, 's');
            ycat1 += velo;
            wait_msec(50000);
            if (ycat1 > 450)
                flag_cat1 = 2;
        }
        else if (flag_cat1 == 2)
        {
            int velo = 10;
            moveCat(xcat1, ycat1, xcat1 + velo, ycat1, 'd');
            xcat1 += velo;
            wait_msec(50000);
            if (xcat1 >= 180)
                flag_cat1 = 3;
        }
        else if (flag_cat1 == 3)
        {
            int velo = 10;
            moveCat(xcat1, ycat1, xcat1, ycat1 - velo, 'w');
            ycat1 -= velo;
            wait_msec(50000);
            if (ycat1 <= 260)
                flag_cat1 = 0;
        }

        // execute the path of cat 2
        if (flag_cat2 == 0)
        {
            int velo = 10;
            moveCat(xcat2, ycat2, xcat2 - velo, ycat2, 'a');
            xcat2 -= velo;
            wait_msec(50000);
            if (xcat2 <= 580)
                flag_cat2 = 1;
        }
        else if (flag_cat2 == 1)
        {
            int velo = 10;
            moveCat(xcat2, ycat2, xcat2, ycat2 - velo, 'w');
            ycat2 -= velo;
            wait_msec(50000);
            if (ycat2 < 110)
                flag_cat2 = 2;
        }
        else if (flag_cat2 == 2)
        {
            int velo = 10;
            moveCat(xcat2, ycat2, xcat2, ycat2 + velo, 's');
            ycat2 += velo;
            wait_msec(50000);
            if (ycat2 >= 370)
                flag_cat2 = 3;
        }
        else if (flag_cat2 == 3)
        {
            int velo = 10;
            moveCat(xcat2, ycat2, xcat2 + velo, ycat2, 'd');
            xcat2 += velo;
            wait_msec(50000);
            if (xcat2 >= 895)
                flag_cat2 = 0;
        }

        // execute the path of cat 3
        if (flag_cat3 == 0)
        {
            int velo = 10;
            moveCat3(xcat3, ycat3, xcat3 - velo, ycat3, 'a');
            xcat3 -= velo;
            wait_msec(50000);
            if (xcat3 <= 100)
                flag_cat3 = 1;
        }
        else if (flag_cat3 == 1)
        {
            int velo = 10;
            moveCat3(xcat3, ycat3, xcat3 + velo, ycat3, 'd');
            xcat3 += velo;
            wait_msec(50000);
            if (xcat3 > 740)
                flag_cat3 = 0;
        }

        // use trap mouse
        if ((count % 160) >= 0 && (count & 160) < 80)
        {
            removetrap(810, 580); // remove bottom right trap
            if (flag_c2 == 0)
                drawcheese(810, 580); // draw bottom right cheese
            flag_trap1 = 1;
            removecheese(310, 210); // remove middle cheese
            drawtrap(310, 210);     // set middle trap
            flag_trap2 = 0;
        }
        else if ((count % 160) >= 80 && (count & 160) <= 159)
        {
            removecheese(810, 580); // remove bottom right trap
            drawtrap(810, 580);     // draw bottom right cheese
            removetrap(310, 210);   // clear middle trap
            if (flag_c1 == 0)
                drawcheese(310, 210); // draw middle cheese
            flag_trap2 = 1;
            flag_trap1 = 0;
        }

        // control mouse movement
        if (c == 'a' && flag_a == 0)
        {
            if (count == 0)
            {

                int velo = 10; // shift to 10 pixel
                moveMouse(xms, yms, xms - velo, yms, 'a');
                xms -= velo;
            }
            else
            {
                if (pc == c)
                {

                    int velo = 10; // shift to 10 pixel
                    moveMouse(xms, yms, xms - velo, yms, 'a');
                    xms -= velo;
                }
                else if (pc != c)
                {

                    int velo = 0; // not shifting
                    moveMouse(xms, yms, xms - velo, yms, 'a');
                    xms -= velo;
                    if (flag_w == 1)
                        flag_w = 0;
                    if (flag_s == 1)
                        flag_s = 0;
                    if (flag_d == 1)
                        flag_d = 0;
                }
            }
        }
        else if (c == 'd' && flag_d == 0)
        {
            if (count == 0)
            {

                int velo = 10; // shift to 10 pixel
                moveMouse(xms, yms, xms + velo, yms, 'd');
                xms += velo;
            }
            else
            {
                if (pc == c)
                {

                    int velo = 10; // shift to 10 pixel
                    moveMouse(xms, yms, xms + velo, yms, 'd');
                    xms += velo;
                }
                else if (pc != c)
                {

                    int velo = 0; // not shifting
                    moveMouse(xms, yms, xms + velo, yms, 'd');
                    xms += velo;
                    if (flag_w == 1)
                        flag_w = 0;
                    if (flag_s == 1)
                        flag_s = 0;
                    if (flag_a == 1)
                        flag_a = 0;
                }
            }
        }
        else if (c == 'w' && flag_w == 0)
        {
            if (count == 0)
            {

                int velo = 10; // shift to 10 pixel
                moveMouse(xms, yms, xms, yms - velo, 'w');
                yms -= velo;
            }
            else
            {
                if (pc == c)
                {

                    int velo = 10; // shift to 10 pixel
                    moveMouse(xms, yms, xms, yms - velo, 'w');
                    yms -= velo;
                }
                else
                {

                    int velo = 0;
                    moveMouse(xms, yms, xms, yms - velo, 'w');
                    yms -= velo;
                    if (flag_d == 1)
                        flag_d = 0;
                    if (flag_s == 1)
                        flag_s = 0;
                    if (flag_a == 1)
                        flag_a = 0;
                }
            }
        }
        else if (c == 's' && flag_s == 0)
        {
            if (count == 0)
            {

                int velo = 10; // shift to 10 pixel
                moveMouse(xms, yms, xms, yms + velo, 's');
                yms += velo;
            }
            else
            {
                if (pc == c)
                {

                    int velo = 10; // shift to 10 pixel
                    moveMouse(xms, yms, xms, yms + velo, 's');
                    yms += velo;
                }
                else
                {

                    int velo = 0;
                    moveMouse(xms, yms, xms, yms + velo, 's');
                    yms += velo;
                    if (flag_d == 1)
                        flag_d = 0;
                    if (flag_s == 1)
                        flag_s = 0;
                    if (flag_a == 1)
                        flag_a = 0;
                }
            }
        }

        // check the collision b/w mouse and walls
        if (identCollision(xms, yms, xms + 40, yms + 40, 165, 570, 287, 770)    // bottom left object
            || identCollision(xms, yms, xms + 40, yms + 40, 740, 510, 935, 578) // bottom right object1
            || identCollision(xms, yms, xms + 40, yms + 40, 740, 570, 802, 770) // bottom right object2
            || identCollision(xms, yms, xms + 40, yms + 40, 290, 300, 495, 460) // middle object
            || identCollision(xms, yms, xms + 40, yms + 40, 170, 103, 540, 208) // top left object
            || identCollision(xms, yms, xms + 40, yms + 40, 740, 80, 1030, 355) // top right object
            || identCollision(xms, yms, xms + 40, yms + 40, 0, 0, 25, 768)      // right boudary
            || identCollision(xms, yms, xms + 40, yms + 40, 0, 0, 1024, 25)     // top boudary
            || identCollision(xms, yms, xms + 40, yms + 40, 0, 770, 1024, 768)  // bottom boundary
            || identCollision(xms, yms, xms + 40, yms + 40, 1010, 0, 1024, 768) // left boundary
            || identCollision(xms, yms, xms + 40, yms + 40, 0, 0, 50, 50))      // score area

        {
            uart_puts("hit walls\n");
            if (c == 'a')
            {
                moveMouse(xms, yms, xms + velo, yms, 'a');
                xms += velo;
                flag_a = 1;
            }
            else if (c == 'd')
            {
                moveMouse(xms, yms, xms - velo, yms, 'd');
                xms -= velo;
                flag_d = 1;
            }
            else if (c == 'w')
            {
                moveMouse(xms, yms, xms, yms + velo, 'w');
                yms += velo;
                flag_w = 1;
            }
            else if (c == 's')
            {
                moveMouse(xms, yms, xms, yms - velo, 's');
                yms -= velo;
                flag_s = 1;
            }
        }

        // check the coliision b/w mouse and 3 cats
        if (identCollision(xms, yms, xms + 40, yms + 50, xcat1, ycat1, xcat1 + 90, ycat1 + 90)
         || identCollision(xms, yms, xms + 40, yms + 50, xcat2, ycat2, xcat2 + 90, ycat2 + 90)
          || identCollision(xms, yms, xms + 40, yms + 40, xcat3, ycat3, xcat3 + 50, ycat3 + 50))
        {
             wait_msec(2000);
             clearscreen(1024, 768);
             drawString((1024 / 2) - 400, 768 / 2, "CATS CATCH YOU!!", 0x0c);
             drawString((1024 / 2) - 250, 768 / 2 + 50, "GAME OVER!!", 0x0c);
             break;
        }

        if (c == 'a' || c == 's' || c == 'w' || c == 'd')
            pc = c;
        c = getUart();

        // check mouse eating cheese
        if (identCollision(xms, yms, xms + 40, yms + 40, 290, 200, 350, 260)) // middle cheese
        {
            removecheese1(290, 200, xms, yms);
            if (flag_trap1 == 0 && flag_c1 == 0)
            {
                uart_puts("eating cheese !\n");
                score++;
                sc = score + '0';
                drawChar1(sc, 50, 10, 0x0f, 1);
                flag_c1 = 1;
            }
            else if (flag_trap1 == 1)
            {
                clearscreen(1024, 768);
                drawString((1024 / 2) - 400, 768 / 2, "MOUSE IS STRUCK!!", 0x0a);
                drawString((1024 / 2) - 250, 768 / 2 + 50, "GAME OVER!!", 0x0c);
                break;
            }
        }

        if (identCollision(xms, yms, xms + 40, yms + 40, 830, 590, 860, 630)) // bottom right cheese
        {
            removecheese1(810, 570, xms, yms);
            if (flag_trap2 == 0 && flag_c2 == 0)
            {
                score++;
                sc = score + '0';
                drawChar1(sc, 50, 10, 0x0f, 1);
                flag_c2 = 1;
            }
            else if (flag_trap2 == 1)
            {
                clearscreen(1024, 768);
                drawString((1024 / 2) - 400, 768 / 2, "MOUSE IS STRUCK!!", 0x0a);
                drawString((1024 / 2) - 250, 768 / 2 + 50, "GAME OVER!!", 0x0c);
                break;
            }
        }

        if (identCollision(xms, yms, xms + 40, yms + 40, 65, 125, 91, 155)) // top left cheese
        {
            removecheese1(50, 110, xms, yms);
            if (flag_c3 == 0)
            {
                score++;
                sc = score + '0';
                drawChar1(sc, 50, 10, 0x0f, 1);
                flag_c3 = 1;
            }
        }

        if (identCollision(xms, yms, xms + 40, yms + 40, 940, 28, 975, 65)) // top right cheese
        {
            removecheese1(910, 5, xms, yms);
            if (flag_c4 == 0)
            {
                score++;
                sc = score + '0';
                drawChar1(sc, 50, 10, 0x0f, 1);
                flag_c4 = 1;
            }
        }
        count++;

        // mouse reaching to gate
        if (identCollision(xms, yms, xms + 40, yms + 40, 40, 680, 70, 730))
        {
            if (score == 4)
            {
                drawString((1024 / 2) - 120, 768 / 2 + 40, "YOU WIN!!", 0x0f);
                flag_win = 1;
            }
            else if (score < 4)
            {
                drawString1((1024 / 2) - 430, 200, "HAVE TO COLLECT ALL CHEESES!!", 0x0f, 2);
                // draw gate again
                drawRectARGB32(5, 400, 141, 768, 0x00, 1); // remove original gate
                drawgate(5, 660);
                wait_msec(100000);
                drawRectARGB32(0, 200, 700, 235, 0x00, 1);
            }
        }
        if (flag_win == 1)
        {
            print_Win_mess();
            break;
        }
    }
    return flag_win;
}
