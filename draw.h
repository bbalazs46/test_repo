#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

struct abc_struct {
	int height;
	char ***text;
	int space_size;
};

void draw_str(struct abc_struct abc, char string[]);

#endif