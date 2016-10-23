#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define BUFFSIZE 512
int main (int argc, char* argv[]) {
    if (argc !=2) {
        fprintf(stderr, "Usage: ./recover card.raw \n");
       return 1;
         }
    FILE* cardFile;
    if ((cardFile = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Couldn't open file %s\n", argv[1]);
        return 2;
        }
    FILE* imgFile=NULL;
    uint8_t buffer[BUFFSIZE];
    char title[8];
    int count=0;
    while (fread(buffer,sizeof(buffer), 1, cardFile)) {
    if (buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && (buffer[3]==0xe0 || buffer[3]==0xe1)) {
          if (count<10) {
          sprintf(title,"00%d.jpg",count);
            }
        else {
            sprintf(title,"0%d.jpg",count);
        }
        imgFile = fopen(title, "w");
        count++;
        }
    if (imgFile != NULL)
    fwrite(buffer,sizeof(buffer), 1, imgFile);
    
    }
    if (imgFile != NULL)
    fclose(imgFile);
    
    fclose(cardFile);
 }