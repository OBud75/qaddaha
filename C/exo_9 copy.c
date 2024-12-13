#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

typedef struct Node
{
    int x;
    int y;
    struct Node *next;
} Node;

void gotoxy(int x, int y)
{
    move(y, x);
}

void textcolor(int color)
{
    attron(COLOR_PAIR(color));
}

void display_score(int score)
{
    gotoxy(0, 26);
    textcolor(3);
    printw("Score: %d", score);
    refresh();
}

void draw_border(int width, int height)
{
    textcolor(3);
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

Node *create_node(int x, int y)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node)
    {
        printf("Memory allocation error\n");
        exit(1);
    }
    new_node->x = x;
    new_node->y = y;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, int x, int y)
{
    Node *new_node = create_node(x, y);
    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        Node *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void free_list(Node *head)
{
    Node *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void initialize_game(int *apple_x, int *apple_y, int TX, int TY, Node **player)
{
    srand(time(NULL));
    append_node(player, rand() % (TX - 2), rand() % (TY - 2));
    *apple_x = rand() % (TX - 2);
    *apple_y = rand() % (TY - 2);
}

void draw_initial_elements(Node *player, int apple_x, int apple_y)
{
    textcolor(1);
    gotoxy(player->x, player->y);
    addch(ACS_CKBOARD);

    textcolor(2);
    gotoxy(apple_x, apple_y);
    addch(ACS_CKBOARD);
    refresh();
}

void update_player_position(Node *player, int direction, int TX, int TY)
{
    int new_x, new_y;
    switch (direction)
    {
    case KEY_UP:
        new_x = player->x;
        new_y = player->y - 1;
        break;
    case KEY_RIGHT:
        new_x = player->x + 1;
        new_y = player->y;
        break;
    case KEY_DOWN:
        new_x = player->x;
        new_y = player->y + 1;
        break;
    case KEY_LEFT:
        new_x = player->x - 1;
        new_y = player->y;
        break;
    }

    if (new_x < 1)
        new_x = TX - 1;
    if (new_x > TX - 1)
        new_x = 1;
    if (new_y < 1)
        new_y = TY - 1;
    if (new_y > TY - 1)
        new_y = 1;

    player->x = new_x;
    player->y = new_y;
}

void move_body(Node *player, int prev_x, int prev_y)
{
    Node *temp = player;
    while (temp->next != NULL)
    {
        temp = temp->next;
        int temp_x = temp->x, temp_y = temp->y;
        temp->x = prev_x;
        temp->y = prev_y;
        prev_x = temp_x;
        prev_y = temp_y;
    }
}

void draw_player(Node *player)
{
    Node *temp = player;
    while (temp != NULL)
    {
        gotoxy(temp->x, temp->y);
        textcolor(1);
        addch(ACS_CKBOARD);
        temp = temp->next;
    }
}

void erase_player(Node *player)
{
    Node *temp = player;
    while (temp != NULL)
    {
        gotoxy(temp->x, temp->y);
        addch(' ');
        temp = temp->next;
    }
}

int main()
{
    int fin = 0, res, apple_x, apple_y, score = 0;
    const int TX = 50, TY = 25;
    Node *player = NULL;
    int direction = KEY_DOWN;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_WHITE, COLOR_BLACK);
    }

    initialize_game(&apple_x, &apple_y, TX, TY, &player);
    draw_border(TX, TY);
    draw_initial_elements(player, apple_x, apple_y);
    display_score(score);

    while (!fin)
    {
        res = getch();

        if (res != ERR)
        {
            switch (res)
            {
            case KEY_UP:
                if (direction != KEY_DOWN) 
                    direction = res;
                break;
            case KEY_RIGHT:
                if (direction != KEY_LEFT) 
                    direction = res;
                break;
            case KEY_DOWN:
                if (direction != KEY_UP) 
                    direction = res;
                break;
            case KEY_LEFT:
                if (direction != KEY_RIGHT) 
                    direction = res;
                break;
            case 'q':
                fin = 1;
                break;
            default:
                fin = 1;
                break;
            }
        }

        erase_player(player);

        int prev_x = player->x, prev_y = player->y;
        update_player_position(player, direction, TX, TY);
        move_body(player, prev_x, prev_y);

        if (player->x == apple_x && player->y == apple_y)
        {
            score++;
            append_node(&player, prev_x, prev_y);
            apple_x = rand() % (TX - 2) + 1;
            apple_y = rand() % (TY - 2) + 1;
            gotoxy(apple_x, apple_y);
            textcolor(2);
            addch(ACS_CKBOARD);
        }

        draw_player(player);
        display_score(score);
        refresh();
        napms(50);
    }

    endwin();
    printf("Score: %d\n", score);
    free_list(player);
    return 0;
}
