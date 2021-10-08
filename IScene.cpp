#include "Engine/IScene.h"

IScene::IScene()
{
    change = false;
    close = false;
}

IScene::~IScene()
{
    if(change) delete scene;
}

void IScene::pause() {}

void IScene::resume() {}

bool IScene::changeRequest(IScene*& scene, bool& replace)
{
    if(change)
    {
        scene = this->scene;
        replace = this->replace;
        change = false;
        return true;
    }
    return false;
}

bool IScene::closeRequest()
{
    if(close)
    {
        close = false;
        return true;
    }
    return false;
}

void IScene::changeScene(IScene* scene, bool replace = true)
{
    if(change) delete scene;
    this->scene = scene;
    this->replace = replace;
    change = true;
}

void IScene::closeScene()
{
    close = true;
}