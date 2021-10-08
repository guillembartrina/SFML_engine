#ifndef ISCENE_H
#define ISCENE_H

#include "INonCopyable.h"
#include "Common.h"

#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Drawable.hpp"

class IScene : private INonCopyable
{
    public:

    IScene();
    virtual ~IScene();

    virtual void init() = 0;
    virtual void handleEvents(const sf::Event& event) = 0;
    virtual void update(const sf::Time& deltatime) = 0;
    virtual void draw(Renderer render) const = 0;
    virtual void pause();
    virtual void resume();

    bool changeRequest(IScene*& scene, bool& replace);
    virtual bool closeRequest();

    protected: 

    void changeScene(IScene* scene, bool replace);
    void closeScene();

    private:

    bool change;
    IScene* scene;
    bool replace;
    bool close;

};



#endif