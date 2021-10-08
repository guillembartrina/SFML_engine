#include "Engine/SceneHandler.h"

SceneHandler::SceneHandler(IScene* scene)
{
    scenes.push(scene);
}

SceneHandler::~SceneHandler()
{
    while(not scenes.empty())
    {
        delete scenes.top();
        scenes.pop();
        if(not scenes.empty()) scenes.top()->resume();
    }
}

void SceneHandler::init()
{
    scenes.top()->init();
}

void SceneHandler::handleEvents(const sf::Event& event)
{
    if(not scenes.empty()) scenes.top()->handleEvents(event);
}

void SceneHandler::update(const sf::Time& deltatime)
{
    if(not scenes.empty())
    {
        IScene* scene;
        bool replace;
        while(scenes.top()->changeRequest(scene, replace))
        {
            if(replace)
            {
                delete scenes.top();
                scenes.pop();
            }
            else scenes.top()->pause();
            scenes.push(scene);
            scenes.top()->init();
        }
        while(not scenes.empty() and scenes.top()->closeRequest())
        {
            scenes.pop();
            if(not scenes.empty()) scenes.top()->resume();
        }
        if(not scenes.empty()) scenes.top()->update(deltatime);
    }    
}

void SceneHandler::draw(Renderer render) const
{
    if(not scenes.empty()) scenes.top()->draw(render);
}

bool SceneHandler::closeRequest()
{
    return scenes.empty();
}