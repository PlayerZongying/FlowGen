#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#pragma once

class Texture
{
public:
    Texture(const char* aPath);

    int Width;
    int Height;

    unsigned int TextureObject;
};


#endif
