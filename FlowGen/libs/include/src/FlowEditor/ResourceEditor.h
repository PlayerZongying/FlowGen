#pragma once
#include "src/FlowGL/Texture.h"

class ResourceHandler;


enum MipmapFilter : int;

enum class EResource
{
    Texture,
    Shader,
    Mesh,
    COUNT
};


class ResourceEditor
{
public:
    ResourceEditor(ResourceHandler* aHandler);
    ~ResourceEditor();

    void Update();

private:
    ResourceHandler* myResources;
    EResource myCurrentResource;

    MipmapFilter mipMapMinFilter = MipmapFilter::LINEAR_MIPMAP_LINEAR;
    MipmapFilter mipMapMagFilter = MipmapFilter::LINEAR;

    int MipmapFilterToIndex(MipmapFilter filter)
    {
        int index = 0;

        switch (filter)
        {
        case NEAREST:
            index = 0;
            break;
        case LINEAR:
            index = 1;
            break;
        case NEAREST_MIPMAP_NEAREST:
            index = 2;
            break;
        case LINEAR_MIPMAP_NEAREST:
            index = 3;
            break;
        case NEAREST_MIPMAP_LINEAR:
            index = 4;
            break;
        case LINEAR_MIPMAP_LINEAR:
            index = 5;
            break;
        }
        return index;
    }

    MipmapFilter IndexToMipmapFilter(int index)
    {
        MipmapFilter mipMapFilter = LINEAR;
        switch (index)
        {
        case 0:
            mipMapFilter = NEAREST;
            break;
        case 1:
            mipMapFilter = LINEAR;
            break;
        case 2:
            mipMapFilter = NEAREST_MIPMAP_NEAREST;
            break;
        case 3:
            mipMapFilter = LINEAR_MIPMAP_NEAREST;
            break;
        case 4:
            mipMapFilter = NEAREST_MIPMAP_LINEAR;
            break;
        case 5:
            mipMapFilter = LINEAR_MIPMAP_LINEAR;
            break;
        default:
            mipMapFilter = LINEAR;
            break;
        }
        return mipMapFilter;
    }
};
