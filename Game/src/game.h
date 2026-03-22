// ----------------------------------- game.h -------------------------------------


int comp_str(char sr1[], char sr2[]); // function comparing 2 strings if they are the same
int comp_str_short(char sr1[], char sr2[]); // function comparing 2 strings if they are the same
void paste_str(char sr1[], const char sr2[]); // function copying string and put data into another string
void print_welcome_game(); // function displaying welcome message game
void print_count_game(); // function displaying welcome count down to start playing game
void print_Win_mess(); // print winning messsge
void drawMap1(); // draw the map1
void drawMap2(int x, int y); // draw the map2
void drawCatleft(int x, int y); // draw the character Cat moving left
void drawCatright(int x, int y); // draw the character Cat moving right
void drawCatup(int x, int y); // draw the character Cat moving up
void drawCatdown(int x, int y); // draw the character Cat moving down

void drawCat3left(int x, int y); // draw the 2-leg cat moving left
void drawCat3right(int x, int y); // draw the 2-leg cat moving right

void drawMouseup(int x, int y); // draw the character Mouse moving up
void drawMousedown(int x, int y); // draw the character Mouse moving down
void drawMouseleft(int x, int y); // draw the character Mouse moving left
void drawMouseright(int x, int y); // draw the character Mouse moving right
void removeMouse(int x, int y); // remove Mouse on screen
void removeCat(int x, int y); // remove Cat on screen
void removeCat3(int x, int y); // remove Cat 3 on screen
void moveMouse(int ox, int oy, int nx, int ny, char c);
void moveCat(int ox, int oy, int nx, int ny, char c);
void moveCat3(int ox, int oy, int nx, int ny, char c);
void drawgate(int x, int y); // draw the gate
int identCollision(int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22); // object 1 is for non-moved object, 2 is for non-stop object
void start_game();  // restarting game
int playGame1(); // playing game 1
int playGame2(); // playing game 2
void drawcheese(int x, int y); //draw cheese
void drawtrap(int x, int y); // draw trap
void removecheese(int x, int y); // remove cheese
void removetrap(int x, int y); // remove trap
void removecheese1(int x, int y, int mouseX, int mouseY); // remove cheese when mouse eating
