#pragma once
#include <src/FlowGL/Camera.h>


class CameraEditor
{
public:
    CameraEditor(Flow::Camera* camera);
    ~CameraEditor();

    void Update();

private:
    Flow::Camera* camera;
};
