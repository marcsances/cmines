// cutils.h
// basic terminal manipulation functions

/*
Copyright (c) 2016, Marc Sances
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/ 
#include <string.h>
#include <stdio.h>

#define true 1
#define false 0
// FUNCIONS D'ESBORRAT

void clrscr() {
// void clrscr()
// Esborra la pantalla.
printf("\033[2J");
printf("\033[0;0H");
}

void clrln() {
// void clrln()
// Esborra la línia actual.
printf("\033[2K");
}

// FUNCIONS DE CURSOR

void gotoxy(int x, int y) {
// void gotoxy(int x, int y)
// Desplaça el cursor a la posició indicada (X,Y), essent X les columnes i Y les files.
printf("\033[%d;%dH",y+1,x+1);
}

void gotohome() {
// void gotohome()
// Desplaça el cursor a l'origen de pantalla (0,0).
printf("\033[0;0H");
}

void cursorup() {
// void cursorup()
// Desplaça el cursor una línia amunt.
printf("\033[A");
}

void cursordown() {
// void cursordown()
// Desplaça el cursor una línia avall.
printf("\033[B");
}

void cursorright() {
// void cursordown()
// Desplaça el cursor una posició a la dreta.
printf("\033[C");
}

void cursorleft() {
// void cursordown()
// Desplaça el cursor una línia a l'esquerra.
printf("\033[D");
}


// FUNCIONS DE FORMAT

void formatreset() {
// void formatreset()
// Suprimeix tot el format aplicat anteriorment en les futures impressions.
printf("\033[0;0;0m");
}

const char *flags[32] = {"0;","1;","2;","1;2;","4;","1;4;","2;4;","1;2;4","5;","1;5;","2;5;","1;2;5;","4;5;",
"1;4;5;","2;4;5;","1;2;4;5;","9;","1;9;","2;9;","1;2;9;","4;9;","1;4;9;","2;4;9;","1;2;4;9;",
"5;9;","1;5;9;","2;5;9;","1;2;5;9;","4;5;9;","1;4;5;9;","2;4;5;9;","1;2;4;5;9;"};
// this deserves a better, byte manipulation version. might implement it some day.

void setformat(int textcolor, int textbackground, int format) {
// void setformat(int textcolor, int textbackground, int bold, int underline, int blink, int strike)
// Aplica color de text textcolor, color de fons textbackground i formats format.
printf("\033[%s%d;%dm",flags[format],30+textcolor,40+textbackground);
}

// FUNCIONS DE GRÁFICS

void drawrect(int x, int y, int w, int h, int color) {
// drawrect (int x, int y, int w, int h, int color)
// Dibuixa un rectangle amb vèrtex en (x,y) i mida (w,h), de color color.
// Caldrà especificar de nou el format a la fi de la trucada.
int i,j;
for (i=0; i<h; i++) {
gotoxy(x,y+i);
setformat(0,color,0);
	for (j=0; j<w; j++) {
	printf(" ");
	}
}
gotoxy(x,y);
formatreset();
}


// FUNCIÓ DE CAPTURA

#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
// Sistema UNIX, métode POSIX
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

struct termios orig_termios;
int assigned=false;
void reset_terminal_mode()
{
    tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode()
{
    struct termios new_termios;
    /* take two copies - one for now, one for later */
if (assigned) { reset_terminal_mode(); }
tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));
assigned=true;
    /* register cleanup handler, and set the new terminal mode */
    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

int kbhit()
{
// kbhit()
// retorna TRUE si s'ha premut una tecla
set_conio_terminal_mode();
struct timeval tv = { 0L, 0L };
fd_set fds;
FD_ZERO(&fds);
FD_SET(0, &fds);
return select(1, &fds, NULL, NULL, &tv);
reset_terminal_mode();
}

int getch()
{
// getch()
// Emula el getch() de CONIO, que pren un caracter SENSE retorn.
    int r;
    unsigned char c;
	set_conio_terminal_mode();
    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
	reset_terminal_mode();
}

#elif defined(_WIN32) || defined(__WIN64)
	// Sistema Windows, métode conio (Ecs.)
	#include <conio.h>
#endif


