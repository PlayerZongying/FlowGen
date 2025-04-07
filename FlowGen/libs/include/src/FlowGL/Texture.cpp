#include <src/FlowGL/Texture.h>
#include <src/FlowGL/stb_image.h>
#include <glad/glad.h>
#include <iostream>

Texture::Texture(const char* aPath)
{
    int Channels = 0;
    Width = 0;
    Height = 0;

    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(aPath, &Width, &Height, &Channels, 0);

    glGenTextures(1, &TextureObject);
    glBindTexture(GL_TEXTURE_2D, TextureObject);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureMipMapMinFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureMipMapMagFilter);
    
    if (data)
    {
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        // glGenerateMipmap(GL_TEXTURE_2D);
        if (Channels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else if(Channels == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    
    stbi_image_free(data);
}

void Texture::MipMapFilterReset(MipmapFilter aMipMapMinFilter, MipmapFilter aMipMapMagFilter)
{
    glBindTexture(GL_TEXTURE_2D, TextureObject);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, aMipMapMinFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, aMipMapMagFilter);
}
