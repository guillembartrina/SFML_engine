#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <functional>
#include <thread>

#include "INonCopyable.h"
#include "IScene.h"
#include "SceneHandler.h"

#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Window : private INonCopyable
{
    public:

    class Builder;

    ~Window();

    void join();
    
    private:

    bool isFullscreen;
    sf::Vector2u size;
    
    sf::RenderWindow window;

    IScene* scene;

    std::thread* thread;
    
    sf::Clock clock;

    Window(const Builder& builder);

    void init();
    void loop();

    void handleEvents();
    void update();
    void draw();

};

class Window::Builder
{
    public:

    Builder(IScene* scene);

    Builder& setSize(unsigned int width, unsigned int height);
    Builder& setFullscreen(unsigned int logicalWidth, unsigned int logicalHeight);
    Builder& setTitle(const std::string& title);
    Builder& setStyle(sf::Uint32 style);

    Builder& enableMultiscene();

    Window* build();

    private:

    IScene* scene;

    bool isFullscreen;
    sf::Vector2u size;
    std::string title;
    sf::Uint32 style;

    friend class Window;

};

#endif