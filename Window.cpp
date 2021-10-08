#include "Engine/Window.h"

#include "SFML/Window/Window.hpp"
#include "SFML/Window/Context.hpp"
#include "SFML/Window/Event.hpp"

#include <iostream>

Window::Window(const Builder& builder)
{
    isFullscreen = builder.isFullscreen;
    size = builder.size;
    scene = builder.scene;
    window.create(isFullscreen ? sf::VideoMode::getFullscreenModes()[0] : sf::VideoMode(size.x, size.y), builder.title, builder.style);
    window.setActive(false);
    thread = new std::thread(&Window::init, this);
}

Window::~Window()
{
    delete thread;
    delete scene;
}

void Window::join()
{
    thread->join();
}

void Window::init()
{
    window.setActive(true);
    if(isFullscreen)
    {
        float ratio = float(size.x)/float(size.y);
        float fullscreenRatio = float(window.getSize().x)/float(window.getSize().y);
        float ratiosRatio = ratio/fullscreenRatio;
        sf::View view(sf::FloatRect(0.f, 0.f, float(size.x), float(size.y)));
        view.setViewport(sf::FloatRect((1.f-ratiosRatio)/2.f, 0.f, ratiosRatio, 1.f));
        window.setView(view);
    }
    scene->init();
    clock.restart();
    loop();
}

void Window::loop()
{
    while(window.isOpen())
    {
        handleEvents();
        update();
        draw();
        if(scene->closeRequest()) window.close();
    }
}

void Window::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) scene->handleEvents(event);
}

void Window::update()
{
    sf::Time deltatime = clock.restart();
    scene->update(deltatime);
}

void Window::draw()
{
    window.clear(sf::Color::Black);
    scene->draw([&](const sf::Drawable& drawable){ window.draw(drawable); });
    // std::bind(static_cast<void(sf::RenderWindow::*)(const sf::Drawable&, const sf::RenderStates&)>(&sf::RenderWindow::draw), &window, std::placeholders::_1, sf::RenderStates::Default)
    window.display();
}


Window::Builder::Builder(IScene* scene)
{
    isFullscreen = false;
    size = sf::Vector2u(800, 600);
    title = "";
    style = sf::Style::Close;
    this->scene = scene;
}

Window::Builder& Window::Builder::setSize(unsigned int width, unsigned int height)
{
    isFullscreen = false;
    size = sf::Vector2u(width, height);
    return *this;
}

Window::Builder& Window::Builder::setFullscreen(unsigned int logicalWidth, unsigned int logicalHeight)
{
    isFullscreen = true;
    size = sf::Vector2u(logicalWidth, logicalHeight);
    return *this;
}

Window::Builder& Window::Builder::setTitle(const std::string& title)
{
    this->title = title;
    return *this;
}

Window::Builder& Window::Builder::setStyle(sf::Uint32 style)
{
    this->style = style;
    return *this;
}

Window::Builder& Window::Builder::enableMultiscene()
{
    scene = new SceneHandler(scene);
    return *this;
}

Window* Window::Builder::build()
{
    return new Window(*this);
}
