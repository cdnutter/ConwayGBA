#include "Intellisense.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;

// Volatile types
typedef volatile uint8_t    vu8;
typedef volatile uint16_t    vu16;
typedef volatile uint32_t    vu32;
typedef volatile int8_t vs8;
typedef volatile int16_t vs16;
typedef volatile int32_t vs32;

#define REG_DISPCNT *((vu32*)(0x04000000))
#define VIDEOMODE_3 0x0003
#define BG_ENABLE2  0x0400

#define SCREENBUFFER ((vu16*)(0x06000000))
#define SCREEN_W 240
#define SCREEN_H 160

u16 setColour(u8 a_red, u8 a_green, u8 a_blue) {
    return (a_red & 0x1F) | (a_green & 0x1F) << 5 | (a_blue & 0x1F) << 10;
}

void plotPixel(s32 a_x, s32 a_y, u16 a_colour) {
    SCREENBUFFER[a_y * SCREEN_W + a_x] = a_colour;
}

int main() {

	//set GBA rendering context to MODE 3 Bitmap Rendering
    REG_DISPCNT = VIDEOMODE_3 | BG_ENABLE2;

	s32 t = 0;
	while(1){
		s32 x,y;
		for(x = 0; x < SCREEN_W; ++x) {
			for( y = 0; y < SCREEN_H; ++y) {
			    plotPixel(x, y, setColour((x&y)+t*5, (x&y)+t*3, (x&y)+t));
            }
		}
		++t;
	}
	return 0;
}
