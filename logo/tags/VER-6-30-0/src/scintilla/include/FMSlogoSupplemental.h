#ifndef _WINGDI_H

typedef struct _BLENDFUNCTION
{
    unsigned char BlendOp;
    unsigned char BlendFlags;
    unsigned char SourceConstantAlpha;
    unsigned char AlphaFormat;
}BLENDFUNCTION,*PBLENDFUNCTION;

#endif
