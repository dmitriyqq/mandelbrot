#ifndef SFMLDEBUG_H
#define SFMLDEBUG_H

#include <SFML/Graphics.hpp>

#include <map>
#include <string>

class SFMLDebug
{
    public:
        SFMLDebug(sf::RenderWindow * window);
        virtual ~SFMLDebug();
        void draw() const;
        void print(const std::string & msg,const std::string & val);
    private:
        sf::RenderWindow * window;
        sf::Font font;
        std::map <std::string, std::string> info;
};

#endif // SFMLDEBUG_H
