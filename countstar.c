#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (1396 * 1024 * 1024)

//read png in ref https://progbook.org/png.html
int read_image(int argc, char **argv){
    if(argc != 2) {
		printf("Usage: %s <png file>\n", argv[0]);
		return 1;
	}
	char *buf = (char *)malloc(MAX_SIZE);
	if(!buf) {
		fprintf(stderr, "Couldn't allocate memory\n");
		return 1;
	}
	FILE *f = fopen(argv[1], "r");
	if(!f) {
		perror("fopen");
		free(buf);
		return 1;
	}
	int size = fread(buf, 1, MAX_SIZE, f);
    printf("\n Size image:.. %d   \n", size);
	fclose(f);
	free(buf);
    return size;
}


int main(int argc, char **argv)
{
	int size = read_image(argc, argv);
    printf("\n Size image 2:.. %d   \n", size);
	return 0;
}
