#include <iostream>
#include <ncurses.h>
#include <ctime>
#include <random>
#include <vector>
#include <map>
#include <set>

using namespace std;

void winExit() {
endwin();
}

class Bacteria {
public:
    Bacteria(WINDOW * win, int y, int x, char c);
    void mv();
    void display();
    void placeWaste();
private:
    int yCur, xCur, yMax, xMax;
    char character;
    WINDOW * curwin;

};



Bacteria::Bacteria(WINDOW * win, int y, int x, char c) {
    curwin = win;
    yCur = y;
    xCur = x;
    getmaxyx(curwin, yMax, xMax);
    character = c;
}

void Bacteria::mv() {
    mvwaddch(curwin, yCur, xCur, ' ');
    int deltaY, deltaX;
    deltaX = rand() % 3 - 1;
    deltaY = rand() % 3 - 1;
    if (yCur + deltaY > yMax - 2)
        yCur = yMax - 2;
    if (yCur + deltaY < 2)
        yCur = 2;
    if (xCur + deltaX > xMax - 2)
        xCur = xMax - 2;
    if (xCur + deltaX < 2)
        xCur = 2;
    else
        yCur += deltaY;
        xCur += deltaX;

}

void Bacteria::display() {
    mvwaddch(curwin, yCur, xCur, character);
}

void Bacteria::placeWaste() {
    mvwaddch(curwin, yCur, xCur, character);
}

int main()
{
    initscr();
    curs_set(0);


    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);


    WINDOW * menuWin = newwin(6, 20, yMax/2 - 3, xMax/2 - 10);
    box(menuWin, 0, 0);
    refresh();
    wrefresh(menuWin);
    string phrase = "Choose world size:";
    mvwprintw(menuWin, 1, 1, phrase.c_str());
    keypad(menuWin, true);
    string choices[3] = {"Small", "Medium", "Big"};
    int choice;
    int highlight = 0;

    while (1) {
        for(int i = 0; i < 3; i++) {
            if(i == highlight)
                wattron(menuWin, A_REVERSE);
            mvwprintw(menuWin, i + 2, 1, choices[i].c_str());
            wattroff(menuWin, A_REVERSE);
        }
        choice = wgetch(menuWin);

        switch(choice) {
            case KEY_UP:
                highlight--;
                if (highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == 3)
                    highlight = 2;
                break;
            default:
                break;
        }
        if(choice == 10)
            break;
    }

    int maxAmount = (highlight + 2) * 2;
    WINDOW * numWin = newwin(4, 40, yMax/2 - 2, xMax/2 - 20);
    box(numWin, 0, 0);
    mvwprintw(numWin, 1, 1, "Enter amount of speices, max is %d", maxAmount);


    wclear(menuWin);
    wrefresh(menuWin);
    wrefresh(numWin);
    wgetch(numWin);





/*
    map<int, pair<int, int>> valueRanges = {
        {0, {1, xMax}},
        {1, {1, yMax}}
    };
    int amount = wgetch(win);
    srand(time(NULL));

    time_t start = time(NULL);
    time_t now = time(NULL);

    WINDOW * inputWin = newwin(1, 50, 13, 100);
    box(inputWin, 0, 0);
    wrefresh(inputWin);
    int amount = wgetch(inputWin);
    vector<Bacteria> speices(amount);
    for (int i = 0; i < amount; i++) {

    }

    WINDOW* win = newwin(25, 50, 13, 100);
    refresh();

    box(win, 0, 0);
    wrefresh(win);



    Bacteria a(win, 1, 1, '?');
    a.display();
    wrefresh(win);
    while ((now - start) < 20) {
    a.mv();
    a.display();
    wrefresh(win);
    napms(1000);
    now = time(NULL);
    }
    getch();*/
    winExit();
    return 0;
}
