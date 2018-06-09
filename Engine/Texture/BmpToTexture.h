#ifndef BMPTOTEXTURE_H_
#define BMPTOTEXTURE_H_

/* Image type - contains height, width, and data */
struct Image {
	unsigned long sizeX;
	unsigned long sizeY;
	char *data;
};
typedef struct Image Image;
#include<string>
void LoadBmpTexture(char * filename, GLuint *texture);


#endif /* BMPTOTEXTURE_H_ */
