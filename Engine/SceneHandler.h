#ifndef SCENEHANDLER_H
#define SCENEHANDLER_H

#include <memory>
#include <stack>

#include "INonCopyable.h"
#include "IScene.h"

#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Drawable.hpp"

class SceneHandler : public IScene
{
    public:

    SceneHandler(IScene* scene);
    ~SceneHandler();

    void init() override;
    void handleEvents(const sf::Event& event) override;
    void update(const sf::Time& deltatime) override;
    void draw(Renderer render) const override;

    bool closeRequest() override;

    private:

    std::stack<IScene*> scenes;

};

#endif