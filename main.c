#include <stdio.h>
#include <stdlib.h>
#include "draw.h"

#define MAXLINELENGTH 1024
#define MAXLINECNT 65536


int main(int argc, char **argv) {
	if (argc<2) {
		printf("Kerlek adj meg egy abc fajlt!");
		return(0);
	} else {
		FILE *inputFile;
		inputFile = fopen(argv[1],"r");
		if(!inputFile) {
			printf("Sajnos nem talalom a fajlt, probalkozz egy masikkal!");
			return(0);
		}
		struct abc_struct abc;
		abc.text = malloc(26*sizeof(void*));
		if(abc.text==NULL) {
			fprintf(stderr,"elfogyott a memoria :(");
			return 1;
		}
		fscanf(inputFile,"%d",&abc.height);
		fgetc(inputFile);
		abc.space_size = 0;
		for(int i = 0;i<26;i++) {
			if(abc.height>=MAXLINECNT) {
				fprintf(stderr,"tul sok sorbol allnak a betuk\n");
				return 1;
			}
			char **letter;
			letter = malloc(abc.height*sizeof(void*));
			if(letter==NULL) {
				fprintf(stderr,"elfogyott a memoria :(");
				return 1;
			}
			for(int j = 0;j<abc.height;j++) {
				char line[MAXLINELENGTH];
				char ch;
				int k = 0;
				while((ch=fgetc(inputFile))!='\n') {
					line[k] = ch;
					k++;
					if(k>=MAXLINELENGTH) {
						fprintf(stderr,"error: tul hosszu sor a fileban\n");
						return 1;
					}
				}
				line[k] = 0;
				k++;
				letter[j] = malloc(k*sizeof(char));
				abc.space_size += k;
				if(letter[j]==NULL) {
					fprintf(stderr,"elfogyott a memoria :(");
					return 1;
				}
				for(int l = 0;l<k;l++) {
					letter[j][l] = line[l];
				}
			}
			abc.text[i] = letter;
		}
		abc.space_size /= 26*abc.height;
		int run = 1;
		while(run) {
			char ch;
			char line[MAXLINELENGTH] = "";
			int i = 0;
			while((ch=getchar())!='\n') {
				if(ch==EOF) {
					run = 0;
					break;
				}
				if(i>=MAXLINELENGTH) {
					run = 0;
					fprintf(stderr,"error: tul hosszu sor");
					return 1;
				}
				line[i] = ch;
				i++;
			}
			if(run){draw_str(abc,line);}
		}
		for(int i = 0;i<26;i++) {
			for(int j = 0;j<abc.height;j++) {
				free(abc.text[i][j]);
			}
			free(abc.text[i]);
		}
		free(abc.text);
		return(0);
	}
}