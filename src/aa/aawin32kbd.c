#include "config.h"
#include "aalib.h"
#include "aaint.h"
#include <conio.h>

static int win32_init(struct aa_context *context, int mode)
{
    return 1;
}
static void win32_uninit(aa_context * c)
{
}
static int win32_getchar(aa_context * c1, int wait)
{
	int c;
	if(wait){
		c = getch();
	}else{
		c = (kbhit() ? getch() : (AA_NONE));
	}
	if(c == AA_NONE) return c;
	if(c == AA_UNKNOWN) return c;
	if(c == '\n') return AA_NONE;
	return c;
}


__AA_CONST struct aa_kbddriver kbd_win32_d =
{
	"win32", "Win32 keyboard driver 1.0",
	0,
	win32_init,
	win32_uninit,
	win32_getchar,
};
