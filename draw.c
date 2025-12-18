#include "draw.h"
#include <stdio.h>

void draw_str(struct abc_struct abc, char string[]) {
	for(int i = 0;i<abc.height;i++) {
		int j = 0;
		while(string[j]!=0) {
			if(string[j]==' ') {
				for(int k = 0;k<abc.space_size;k++) {
					printf(" ");
				}
			} else if(string[j]>='a' && string[j]<='z') {
				printf("%s",abc.text[string[j]-'a'][i]);
			}
			j++;
		}
		printf("\n");
	}
}
