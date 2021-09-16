#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (1396 * 1024 * 1024)

void validate(int val, const char *msg)
{
    if(!val) {
        fprintf(stderr, "Invalid file: %s\n", msg);
        exit(1);
    }
}

void check_header(const char *buf)
{
    validate((unsigned char)buf[0] == 0x89, "header byte 1");
    validate((unsigned char)buf[1] == 'P',  "header byte 2");

}

int get_big_endian(const char *buf)
{
    return ((unsigned char)buf[0] << 24) |
           ((unsigned char)buf[1] << 16) |
           ((unsigned char)buf[2] << 8)  |
            (unsigned char)buf[3];
}

void header_handler(const char *buf, int len)
{
    validate(len == 13, "header must be 13 bytes");
    printf("Width:              %d\n", get_big_endian(buf));
    printf("Height:             %d\n", get_big_endian(buf + 4));
    printf("Bit depth:          %d\n", (unsigned char)buf[8]);
    
}

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
	int pos = 8;
//	while(1) { /* FIXME: infinite loop */
      char lenbuf[4];
      memcpy(lenbuf, buf + pos, 4);
      int len = get_big_endian(lenbuf);
      char chunkbuf[5];
    /* TODO: fill chunkbuf */
        printf("chunk: %s - len: %d (%d)\n", chunkbuf, len, size - (pos + len + 12));
    /* TODO: increment pos correctly */
	//}
	header_handler(buf, len);	
    printf("\n info:.. %d   \n", size);
	check_header(buf);
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
