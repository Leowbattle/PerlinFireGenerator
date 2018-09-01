#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STB_PERLIN_IMPLEMENTATION
#include "stb_perlin.h"

typedef struct {
	int r;
	int g;
	int b;
} colour;

colour colourForValue(float value) {
	if (value > 0.99) return (colour){255, 255, 255};
	else if (value > 0.8) return (colour){value * 230, value * 230, 0};
	else if (value > 0.7) return (colour){value * 250, value * 120, 0};
	else if (value > 0.5) return (colour){value * 250, value, 0};
	return (colour){value * 100, value * 45, 0};
}

int x = 0;
int y = 0;

const int width = 256;
const int height = 256;
const int depth = 120;

void frame(int i) {
	static colour pixels[width][height];
	static int frameSize = width * height * 3 * sizeof(int);
	memset(pixels, 0, frameSize);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			colour colour = colourForValue(stb_perlin_noise3((float)x / 45, (float)y / 45, (float)i/20, width, height, depth/12) + 0.5);
			pixels[x][y] = colour;
		}
	}

	char frameName[100];
	sprintf(frameName, "%03d.ppm", i);

	FILE* file = fopen(frameName, "w");
	fputs("P3\n", file);
	fprintf(file, "%d %d\n255\n", width, height);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			fprintf(file, "%d %d %d ", pixels[j][i].r, pixels[j][i].g, pixels[j][i].b);
		}
		fputs("\n", file);
	}
	fclose(file);
}

int main() {
	for (int i = 0; i < depth; i++) {
		frame(i);
	}

	return 0;
}
