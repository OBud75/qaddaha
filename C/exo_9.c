#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

typedef struct {
    int x;
    int y; // Define x and y coordinates
} Coordinate; // Define a Coordinate structure

void gotoxy(int x, int y)
{
    move(y, x); // Move the cursor to position (y, x)
}

void textcolor(int color)
{
    attron(COLOR_PAIR(color)); // Set text color using color pairs
}

void display_score(int score)
{
    gotoxy(1, 1);               // Move cursor to (1, 1)
    textcolor(3);               // Set text color to white
    printw("Score: %d", score); // Display the score
    refresh();
}

void draw_border(int width, int height)
{
    textcolor(3); // Set text color to white
    for (int i = 0; i <= width; i++)
    {
        gotoxy(i, 0);
        addch('#');
        gotoxy(i, height);
        addch('#');
    }
    for (int i = 0; i <= height; i++)
    {
        gotoxy(0, i);
        addch('#');
        gotoxy(width, i);
        addch('#');
    }
    refresh();
}

int main()
{
    int fin = 0, res, apple_x, apple_y, score = 0;
    const int TX = 50, TY = 25;
    Coordinate *player = malloc(sizeof(Coordinate) * (TX * TY));
    int player_length = 1;
    int direction = KEY_DOWN; // Initialize direction to down

    // Initialize ncurses
    initscr();             // Start ncurses
    cbreak();              // Disable line buffering and erase/kill character processing
    noecho();              // Don't echo any keypresses
    keypad(stdscr, TRUE);  // Enable arrow keys
    nodelay(stdscr, TRUE); // Non-blocking input
    curs_set(0);           // Hide the cursor

    // Initialize colors
    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);   // color init for player
        init_pair(2, COLOR_RED, COLOR_BLACK); // color init for apple
        init_pair(3, COLOR_WHITE, COLOR_BLACK); // color init for border and score
    }

    srand(time(NULL)); // Seed for random number generator
    player[0].x = rand() % TX;
    player[0].y = rand() % TY;
    apple_x = rand() % TX-1;
    apple_y = rand() % TY-1;

    draw_border(TX, TY); // Draw the border

    textcolor(1); // Set text color to red
    gotoxy(player[0].x, player[0].y); 
    addch('X');   // Display 'X' at (x, y)

    textcolor(2);
    gotoxy(apple_x, apple_y);
    addch('A');
    refresh();

    display_score(score); // Display initial score

    while (!fin)
    {
        res = getch(); // Get character input

        if (res != ERR)
        { // Check if a key was pressed
            switch (res)
            {
            case KEY_UP:
            case KEY_RIGHT:
            case KEY_DOWN:
            case KEY_LEFT:
                direction = res; // Update direction for each arrow key
                break; 
            case 'q':
                fin = 1;
                break; // Quit if 'q' is pressed
            default:
                fin = 1;
                break;
            }
        }

        // Clear the player's body
        for (int i = 0; i < player_length; i++)
        {
            gotoxy(player[i].x, player[i].y);
            addch(' ');
        }

        // Move the player's body
        for (int i = player_length - 1; i > 0; i--)
        {
            player[i] = player[i - 1];
        }

        // Move the player in the current direction
        switch (direction)
        {
        case KEY_UP:
            player[0].y -= 1;
            break; 
        case KEY_RIGHT:
            player[0].x += 1;
            break; 
        case KEY_DOWN:
            player[0].y += 1;
            break; 
        case KEY_LEFT:
            player[0].x -= 1;
            break; 
        }

        // Wrap around screen boundaries
        if (player[0].x < 1)
            player[0].x = TX - 1;
        if (player[0].x > TX - 1)
            player[0].x = 1;
        if (player[0].y < 1)
            player[0].y = TY - 1;
        if (player[0].y > TY - 1)
            player[0].y = 1;

        // Check if the player catches the apple
        if (player[0].x == apple_x && player[0].y == apple_y)
        {
            score++;
            player[player_length] = player[player_length - 1]; // Initialize new segment at the end ( appears after first move)
            player_length++;
            apple_x = rand() % (TX - 2) + 1;
            apple_y = rand() % (TY - 2) + 1;
            gotoxy(apple_x, apple_y);
            textcolor(2);
            addch('A');
        }

        // Draw the player's body
        for (int i = 0; i < player_length; i++)
        {
            gotoxy(player[i].x, player[i].y);
            textcolor(1);
            addch('X');
        }

        display_score(score); // Update the score display
        refresh();

        // Delay to control the speed of the game
        napms(50);
    }

    endwin();
    printf("Score: %d\n", score); // Print the score
    free(player);
    return 0;
}
