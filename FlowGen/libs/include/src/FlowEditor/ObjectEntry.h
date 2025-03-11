#pragma once
class VirtualObject;


namespace Flow
{
    class ObjectEntry
    {
    public:
        ObjectEntry();
        ObjectEntry(VirtualObject* anObject);
        ~ObjectEntry();
        VirtualObject* GetVirtualObject();

        void Update();

        bool Opened = false;

    private:
        VirtualObject* myObject;

        int selectedMeshIndex = 0;
        int selectedShaderIndex = 0;
        int selectedTextureIndex = 0;

        void UpdateMesh();
        void UpdateShader();
        void UpdateTexture();
        
        
    };
    
}
