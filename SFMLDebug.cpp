#include "SFMLDebug.h"
#include <iostream>
SFMLDebug::SFMLDebug(sf::RenderWindow * window)
{
    this->window = window;
    font.loadFromFile("default.otf");
}

SFMLDebug::~SFMLDebug()
{
    //dtor
}

void SFMLDebug::draw() const
{
    const float offset = 20.0f;
    const float sz = 20.0f;
    sf::Text text; int i = 1;
    text.setFont(font);
    text.setCharacterSize((unsigned int)sz);
    text.setFillColor(sf::Color::White);
    for( auto &e : info){
        i++;
        text.setPosition(offset, i * sz);
        text.setString(e.first + " : "+ e.second);
        window->draw(text);
    }
}

void SFMLDebug::print(const std::string & msg, const std::string & val)
{
    info[msg] = val;
}
