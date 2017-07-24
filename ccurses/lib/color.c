#include "color.h"

void cc_init_colors() {
	init_pair(_cn_red, COLOR_RED, BACKGROUND);
	init_pair(_cn_blue, COLOR_BLUE, BACKGROUND);
	init_pair(_cn_yellow, COLOR_YELLOW, BACKGROUND);
	init_pair(_cn_white, COLOR_WHITE, BACKGROUND);
	init_pair(_cn_black, COLOR_BLACK, BACKGROUND);
	init_pair(_cn_green, COLOR_GREEN, BACKGROUND);
}
