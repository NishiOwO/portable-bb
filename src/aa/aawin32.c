#include "config.h"
#include <stdio.h>
#include "aalib.h"
#include "aaint.h"
#include <windows.h>

static void cls(void){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hstd = GetStdHandle(STD_OUTPUT_HANDLE);

	if(GetConsoleScreenBufferInfo(hstd, &csbi)){
		SMALL_RECT srect;
		COORD starg;
		CHAR_INFO fill;
		srect.Left = 0;
		srect.Top = 0;
		srect.Right = csbi.dwSize.X;
		srect.Bottom = csbi.dwSize.Y;

		starg.X = 0;
		starg.Y = (SHORT)(0 - csbi.dwSize.Y);

		fill.Char.AsciiChar = ' ';
		fill.Attributes = csbi.wAttributes;

		ScrollConsoleScreenBuffer(hstd, &srect, NULL, starg, &fill);

		csbi.dwCursorPosition.X = 0;
		csbi.dwCursorPosition.Y = 0;

		SetConsoleCursorPosition(hstd, csbi.dwCursorPosition);
	}
}

static int win32_init(__AA_CONST struct aa_hardware_params *p,__AA_CONST  void *none, struct aa_hardware_params *dest, void **n)
{
	__AA_CONST static struct aa_hardware_params def={NULL, AA_NORMAL_MASK | AA_EXTENDED};
	*dest=def;
	cls();
	return 1;
}
static void win32_uninit(aa_context * c)
{
}
static void win32_getsize(aa_context * c, int *width, int *height)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hstd = GetStdHandle(STD_OUTPUT_HANDLE);

	if(GetConsoleScreenBufferInfo(hstd, &csbi)){
		*width = csbi.dwSize.X;
		*height = csbi.dwSize.Y;
	}
}

static HANDLE buffer = NULL;
static CHAR_INFO* cbuffer = NULL;
static void win32_flush(aa_context * c)
{
	int x, y;
	COORD pos;
	COORD size;
	SMALL_RECT srect;
	HANDLE hstd = GetStdHandle(STD_OUTPUT_HANDLE);

	size.X = aa_scrwidth(c);
	size.Y = aa_scrheight(c);

	srect.Left = 0;
	srect.Top = 0;
	srect.Right = aa_scrwidth(c);
	srect.Bottom = aa_scrheight(c);

	if(buffer == NULL){
		buffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		cbuffer = malloc(sizeof(*cbuffer) * aa_scrheight(c) * aa_scrwidth(c));
	}

	pos.X = 0;
	pos.Y = 0;
	SetConsoleCursorPosition(hstd, pos);
	SetConsoleActiveScreenBuffer(hstd);
	for (y = 0; y < aa_scrheight(c); y++) {
		for (x = 0; x < aa_scrwidth(c); x++) {
			int attr[] = {0x0007, 0x0007, 0x000f, 0x000f, 0x0070, 0x0017};
			cbuffer[y * aa_scrwidth(c) + x].Char.AsciiChar = c->textbuffer[x + y * aa_scrwidth(c)];
			cbuffer[y * aa_scrwidth(c) + x].Attributes = attr[c->attrbuffer[x + y * aa_scrwidth(c)]] | 0x4000;
		}
	}
	WriteConsoleOutput(buffer, cbuffer, size, pos, &srect);
	SetConsoleActiveScreenBuffer(buffer);
	WriteConsoleOutput(hstd, cbuffer, size, pos, &srect);
}
static void win32_gotoxy(aa_context * c, int x, int y)
{
}
static void win32_cursor(aa_context * c, int mode)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(consoleHandle, &info);
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
	GetConsoleCursorInfo(buffer, &info);
	info.bVisible = FALSE;
	SetConsoleCursorInfo(buffer, &info);
}
__AA_CONST struct aa_driver win32_d =
{
    "win32", "Win32 driver",
    win32_init,
    win32_uninit,
    win32_getsize,
    NULL,
    NULL,
    win32_gotoxy,
    win32_flush,
    win32_cursor,
};
