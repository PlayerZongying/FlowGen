#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#pragma once
#include "glad/glad.h"

enum MipmapFilter {
    NEAREST = GL_NEAREST,
    LINEAR = GL_LINEAR,
    NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
    LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
    NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
    LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
};

class Texture
{
public:
    MipmapFilter textureMipMapMinFilter = NEAREST_MIPMAP_NEAREST;
    MipmapFilter textureMipMapMagFilter = NEAREST;

    Texture(const char* aPath);

    int Width;
    int Height;

    unsigned int TextureObject;

    void MipMapFilterReset(MipmapFilter aMipMapMinFilter, MipmapFilter aMipMapMagFilter);
};


#endif
