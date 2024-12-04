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

        void Update();

        bool Opened = false;

    private:
        VirtualObject* myObject;
        
    };
    
}
