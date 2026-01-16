#ifndef IMAGE_H
#define IMAGE_H

typedef struct s_img
{
    void *img;
    char *addr;
    int bpp;
    int line_len;
    int endian;
    int w;
    int h;
} t_img;

#endif
