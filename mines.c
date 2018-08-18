#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cutils.h"

char **board; // board[row][column]
char **gboard;
int w, h, mines, xc, curx, cury;

int valid(int x, int y) {
    return x>=0 && x<h && y>=0 && y<w && board[x][y]!='B';
}

char at(int x, int y) {
    return valid(x,y) ? board[x][y] : -1;
}

void surround(int x, int y) {
    if (valid(x-1,y-1)) board[x-1][y-1]++;
    if (valid(x-1,y)) board[x-1][y]++;
    if (valid(x-1,y+1)) board[x-1][y+1]++;
    if (valid(x,y-1)) board[x][y-1]++;
    if (valid(x,y+1)) board[x][y+1]++;
    if (valid(x+1,y-1)) board[x+1][y-1]++;
    if (valid(x+1,y)) board[x+1][y]++;
    if (valid(x+1,y+1)) board[x+1][y+1]++;
}

void allocboard(char ***b, char tok) {
    int i,j;
    *b=malloc(h*w*sizeof(char));
    for (i=0; i<h; i++) {
        (*b)[i]=calloc(w,sizeof(char));
        for (j=0; j<w; j++) {
            (*b)[i][j]=tok;
        }
    }
}

void makeboard() {
    int x,y;
    allocboard(&board,(char)0);
    allocboard(&gboard,'#');
    while (mines>0) {
        do {
            x=rand()%w;
            y=rand()%h;
        } while (board[x][y]=='B');
        board[x][y]='B';
        surround(x,y);
        mines--;
    }
}

char repr(char c) {
    return c==0 ? ' ' : (c<10 ? c+'0' : c);
}

void pboard() {
    int i, j;
    
    for (i=0; i<h; i++) {
        gotoxy(1,i);
        for (j=0; j<w; j++) {
            if (i==curx && j==cury) {
                setformat(0,7,0);
            } else {
                setformat(7,0,0);
            }
            printf("%c",repr(gboard[i][j]));
        }
    }
    setformat(0,0,0);
    fflush(stdout);
}

void printboard(char **b) {
    int i,j;
    for (j=0; j<w; j++) {
        printf("-");
    }
    printf("\n");
    for (i=0; i<h; i++) {
        for (j=0; j<w; j++) {
            printf("%c",repr(b[i][j]));
        }
        printf("\n");
    }
    for (j=0; j<w; j++) {
        printf("-");
    }
    printf("\n");
}

void propagate(int x, int y) {
    if (valid(x-1,y-1)) play(x-1,y-1);
    if (valid(x-1,y)) play(x-1,y);
    if (valid(x-1,y+1)) play(x-1,y+1);
    if (valid(x,y-1)) play(x,y-1);
    if (valid(x,y+1)) play(x,y+1);
    if (valid(x+1,y-1)) play(x+1,y-1);
    if (valid(x+1,y)) play(x+1,y);
    if (valid(x+1,y+1)) play(x+1,y+1);
}

int check(int x, int y) {
    return at(x,y)=='F';
}

void expand(int x, int y) {
    int mf=0,z=0;
    if ((z=at(x,y))>0) {
        mf+=check(x-1,y-1);
        mf+=check(x-1,y);
        mf+=check(x-1,y+1);
        mf+=check(x,y-1);
        mf+=check(x,y+1);
        mf+=check(x+1,y-1);
        mf+=check(x+1,y);
        mf+=check(x+1,y+1);
    }
    if (mf==z) {
        if (at(x-1,y-1)=='#') play(x-1,y-1);
        if (at(x-1,y)=='#') play(x-1,y-1);
        if (at(x-1,y+1)=='#') play(x-1,y-1);
        if (at(x,y-1)=='#') play(x-1,y-1);
        if (at(x,y+1)=='#') play(x-1,y-1);
        if (at(x+1,y-1)=='#') play(x-1,y-1);
        if (at(x+1,y)=='#') play(x-1,y-1);
        if (at(x+1,y+1)=='#') play(x-1,y-1);
    }
}

int play(int x, int y) {
    if (gboard[x][y]!='#') {
        if (gboard[x][y]<10) {
            expand(x,y);
        }
    } else {
        gboard[x][y]=board[x][y]; xc++;
        if (gboard[x][y]=='B') return 1;
        if (gboard[x][y]==0) {
        propagate(x,y);
        }
    }
    return 0;
}

int flag(int x, int y) {
    if (gboard[x][y]=='#') {
        gboard[x][y]='F'; xc++;
    } else if (gboard[x][y]=='F') {
        gboard[x][y]='#'; xc--;
    }
}

int mod (int a, int b)
{
   return a%b < 0 ? (a%b)+b : a%b;
}

void game() {
    int dead=0, x,y;
    char c;
    srand(time(NULL));
    w=16;
    h=16;
    mines=40;
    xc=0;
    curx=0;
    cury=0;
    clrscr();
    makeboard();
    while (!dead && xc<w*h) {
        pboard(gboard);
        setformat(0,0,0);
        while (!kbhit());
        c=getch();
        if (c==27) {
            getch(); c=getch();
        }
        switch (c) {
            case 'A':
                // up
                curx=mod(curx-1,h);
                break;
            case 'B':
                // down
                curx=mod(curx+1,h);
                 break;
            case 'C':
                // right
                cury=mod(cury+1,w);
                break;
            case 'D':
                // left
                cury=mod(cury-1,w);
                break;
            case 'F':
            case 'f':
                flag(curx,cury);
                break;
            case 'Q':
            case 'q':
                return;
            case 13:
                dead=play(curx,cury);
                break;
            default:
                printf("\a");
        }
    }
    pboard(gboard);
}
int main(int argc, char *argv[]) {
    game();
    formatreset();
}
