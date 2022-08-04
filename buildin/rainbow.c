#include <buildin/rainbow.h>

uint32_t __libc_true_hsv(int angle) {
	uint64_t red, green, blue, alpha;

	const uint8_t hsv_lights[61] = {
		0, 4, 8, 13, 17, 21, 25, 30, 34, 38, 42, 47, 51, 55, 59, 64, 68, 72, 76,
		81, 85, 89, 93, 98, 102, 106, 110, 115, 119, 123, 127, 132, 136, 140, 144,
		149, 153, 157, 161, 166, 170, 174, 178, 183, 187, 191, 195, 200, 204, 208,
		212, 217, 221, 225, 229, 234, 238, 242, 246, 251, 255
	};

	if (angle < 60) {
		red = 255;
		green = hsv_lights[angle];
		blue = 0;
	} else if (angle < 120) {
		red = hsv_lights[120 - angle];
		green = 255;
		blue = 0;
	} else if (angle < 180) {
		red = 0;
		green = 255;
		blue = hsv_lights[angle - 120];
	} else if (angle < 240) {
		red = 0;
		green = hsv_lights[240 - angle];
		blue = 255;
	} else if (angle<300) {
		red = hsv_lights[angle - 240];
		green = 0;
		blue = 255;
	} else {
		red = 255;
		green = 0;
		blue = hsv_lights[360 - angle];
	} 

	alpha = 255;

	return alpha | (red << 8) | (green << 16) | (blue << 24);
}

uint32_t __libc_rainbow(int i) {
	return __builtin_bswap32(__libc_true_hsv(i % 360));
}
