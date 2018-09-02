#include <SFML/Graphics.hpp>
#include "SFMLDebug.h"
#include <iostream>
#include <stdio.h>

long double map(long double value, long double istart, long double istop, long double ostart, long double ostop){
	return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

void calcColor( int n, int & r, int & g, int & b, int maxiterations){
	long double p = map(n, 0, maxiterations, 0.0f, 1.0f);
	if (p < 0.16){
		r = map(p, 0.0f, 0.16f, 0, 32);
		g = map(p, 0.0f, 0.16f, 7, 107);
		b = map(p, 0.0f, 0.16f, 100, 203);
	} else if(p < 0.42){
		r = map(p, 0.16f, 0.42f, 32, 237);
		g = map(p, 0.16f, 0.42f, 107, 255);
		b = map(p, 0.16f, 0.42f, 203, 255);
	} else
	if(p < 0.6425){
		r = map(p, 0.42f, 0.6425, 237, 255);
		g = map(p, 0.42f, 0.6425, 255, 170);
		b = map(p, 0.42f, 0.6425, 255, 0);
	} else
	 if(p < 0.8575  ){
		r = map(p, 0.6425, 0.8575, 255, 0);
		g = map(p, 0.6425, 0.8575, 170, 2);
		b = map(p, 0.6425, 0.8575, 0, 0);
	 } else
	if(p < 0.6425){
		r = map(p, 0.8575, 1.0f, 0, 0);
		g = map(p, 0.8575, 1.0f, 2, 7);
		b = map(p, 0.8575, 1.0f, 0, 100);
	}

}


void mdb(sf::Image & img, long double minscl, long double maxscl, long double offsetX, long double offsetY , int maxiterations){
    int mx = (int)img.getSize().x, my = (int)img.getSize().y;

    for (int i = 0; i < mx; i++){
		for(int j= 0; j < my; j++){
			long double a = map(i, 0, mx, minscl, maxscl) + offsetX;
			long double b = map(j, 0, my, minscl, maxscl) + offsetY;
            long double ca = a;
            long double cb = b;
			int n = 0;
			while (n < maxiterations) {
       			long double aa = a * a - b * b;
		        long double bb = 2 * a * b;
		        a = aa + ca;
		        b = bb + cb;
		        if (a * a + b * b > 16) {
		          break;
		        }
        		n++;
      		}
            if (n == maxiterations)
                n = 0;
            //std::cout<<n<<" ";//<<std::endl;
            int rc = 0, gc = 0, bc = 0;


      		calcColor(n,rc,gc,bc, maxiterations);
			img.setPixel(i, j, sf::Color(rc, gc, bc));
		}
    }

}


int main()
{
    sf::Clock clock;
    const int size = 1000;
    int width = size, height = size;
    sf::RenderWindow window(sf::VideoMode(size, size), "Mandelbrot!");
    SFMLDebug debug(&window);
    sf::Texture t;
    sf::Sprite m;
	sf::Image img;

	img.create(size, size);

    int numiterations = 100;
	//MANDELBROT STUFF;
	long double offsetX = 0.0f, offsetY = 0.0f;
    long double sz = 2.0f;
    long double speed = 0.01f;
    int fps = 0;

    sf::RectangleShape select;
	select.setFillColor(sf::Color::Transparent);
	select.setOutlineColor(sf::Color::White);
	select.setOutlineThickness(2.0f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			else if (event.type == sf::Event::MouseButtonPressed){
				sz/=2.0f;
				numiterations += 140;
				sf::Vector2i mp = sf::Mouse::getPosition(window);
				offsetX += map((long double) mp.x, 0.0f, (long double) width, -sz, sz);
				offsetY += map((long double) mp.y, 0.0f, (long double) height, -sz, sz);

				mdb(img, -sz, sz, offsetX, offsetY, numiterations);
				t.loadFromImage(img);
				m.setTexture(t);
			}
        }
        if(clock.getElapsedTime().asMilliseconds() > 1000){
            debug.print("Fps", std::to_string(fps));
            fps = 0;
            clock.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            offsetY -= speed;
            mdb(img, -sz, sz, offsetX, offsetY,numiterations);
            t.loadFromImage(img);
            m.setTexture(t);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            offsetY += speed;
            mdb(img, -sz, sz, offsetX, offsetY,numiterations);
            t.loadFromImage(img);
            m.setTexture(t);
        }
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            offsetX -= speed;
            mdb(img, -sz, sz, offsetX, offsetY,numiterations);
            t.loadFromImage(img);
            m.setTexture(t);
         }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            offsetX += speed;
            mdb(img, -sz, sz, offsetX, offsetY,numiterations);
            t.loadFromImage(img);
            m.setTexture(t);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
            sz-= speed;

            mdb(img, -sz, sz, offsetX, offsetY,numiterations);
            t.loadFromImage(img);
            m.setTexture(t);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
            sz+= speed;
            mdb(img, -sz, sz, offsetX, offsetY,numiterations);
            t.loadFromImage(img);
            m.setTexture(t);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            std::cin>>numiterations;
        }

        speed = 0.01f * sz;
        select.setPosition( window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        float ssizex = map(sz / 2.0f, 0.0f, sz, 0, width);
        float ssizey = map(sz / 2.0f, 0.0f, sz, 0, height);


		select.setOrigin(ssizex / 2.0f, ssizey / 2.0f);
		select.setSize(sf::Vector2f(ssizex, ssizey));
		char sizestr[200];
		sprintf(sizestr,"%.20Lf", sz);
        debug.print("Speed", std::to_string(speed));
        debug.print("numIt", std::to_string(numiterations));
        debug.print("Size", sizestr);
        debug.print("OffsetX", std::to_string(offsetX));
        debug.print("OffsetY", std::to_string(offsetY));



        window.clear();
        window.draw(m);

        debug.draw();
         window.draw(select);
        window.display();
        fps++;
    }

    return 0;
}
