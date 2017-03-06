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
// CONSTANTS DE COLOR
#define CL_BLACK		0
#define CL_RED			1
#define CL_GREEN		2
#define CL_BROWN		3
#define CL_BLUE			4
#define CL_MAGENTA	5
#define CL_CYAN			6
#define CL_WHITE		7

// CONSTANTS DE FORMAT

#define ST_BOLD			1
#define ST_DARKER		2
#define ST_UNDERLINE	4
#define ST_BLINK		8
#define ST_STRIKE		16

// FUNCIONS D'ESBORRAT
extern void clrscr();
extern void clrln();
extern void gotoxy(int x, int y);
extern void gotohome();
extern void cursorup();
extern void cursordown();
extern void cursorright();
extern void cursorleft();
extern void formatreset();
extern void setformat(int textcolor, int textbackground, int format);
extern void drawrect(int x, int y, int w, int h, int color);



#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))

extern void reset_terminal_mode();
extern void set_conio_terminal_mode();
extern int kbhit();
extern int getch();

#elif defined(_WIN32) || defined(__WIN64)
	// Sistema Windows, métode conio (Ecs.)
	#include <conio.h>
#endif


