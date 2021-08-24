#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <DirectXCollision.h>
#include <stdio.h>
#include <time.h>
#include <string>
using namespace sf;

struct point
{ int x,y;};


int main()
{
    srand(time(0));
    RenderWindow window(VideoMode(1000, 600), "My Game"); // creates game window
    window.setFramerateLimit(60); // sets window frame rate limit

    Texture t1, t2, t3, t4, t5, t6, t7; // images 
    t1.loadFromFile("images/sky.jpg");
    t2.loadFromFile("images/user.png");
    t3.loadFromFile("images/coin.png");
    t4.loadFromFile("images/rock.png");
    t5.loadFromFile("images/rock.png");
    t6.loadFromFile("images/bhole.png");  
    t7.loadFromFile("images/newback.png");


    Sprite sBackground(t1); // sprites used to manipulate images
    Sprite drag(t2);
    Sprite coin(t3);
    Sprite rock(t4);
    Sprite rock2(t5);
    Sprite bhole(t6);
    Sprite newback(t7);

    Font font;
    font.loadFromFile("images/nums.ttf"); // loads in font

    int x = 10;
   int y = 450;

   int rocksx[200];
   int rocksy[200];
   int rocksa[200];
   int rocksb[200];
   int coinx[200];
   int coiny[200];
   int transx[200];
   int transy[200];
   int rc = 0;

   for (int i = 0; i < 200; i++) // sets random numbers to x and y cordinates of the rocks, coins and black holes
   {
       rocksx[i] = rand() % 1000;
       rocksy[i] = rand() % 600;
       rocksa[i] = rand() % 1000;
       rocksb[i] = rand() % 600;
       coinx[i] = rand() % 1000;
       coiny[i] = rand() % 600;
       transx[i] = rand() % 1000;
       transy[i] = rand() % 600;
       
   }

   bool hell = false;


   int points = 0;

   while (window.isOpen())
   {
       Event e;


       points++;
       std::string ps = "Points: " + std::to_string(points);
       Text text(ps, font, 50);


       while (window.pollEvent(e))
       {
           if (e.type == Event::Closed)
               window.close();
       }

       if (hell == true)
       {
           x += 6;
       }
       else
       {
           x += 3;
       }

       y += 3;


       if (Keyboard::isKeyPressed(Keyboard::Space))
       {
           y -= 10;
       }

       if (y > 500) y = 500;
       else if (y < 10) y = 10;

       if (x > 900)
       {
           x = 10;
           rc++; // get new random numbers for all the 
           coin.setColor(Color::Yellow); // undo transparent coin
       }


       drag.setPosition(x, y);
       coin.setPosition(coinx[rc], coiny[rc]);
       rock.setPosition(rocksx[rc], rocksy[rc]);
       rock2.setPosition(rocksa[rc], rocksb[rc]);
       bhole.setPosition(transx[rc], transy[rc]);

       FloatRect character = drag.getGlobalBounds();
       FloatRect rockie = rock.getGlobalBounds();
       FloatRect rockie2 = rock2.getGlobalBounds();
       FloatRect coinz = coin.getGlobalBounds();
       FloatRect hole = bhole.getGlobalBounds();

       if (rockie.intersects(rockie2) || rockie.intersects(coinz) || rockie.intersects(hole))
       {
           rocksx[rc] = rocksx[rc] - 30;
           rocksy[rc] = rocksy[rc] - 30;
           if (rocksx[rc] > 1000) rocksx[rc] - 30;
           else if (rocksx[rc] < 10) rocksx[rc] + 30;

           if (rocksy[rc] > 550) rocksy[rc] - 30;
           else if (rocksy[rc] < 10) rocksy[rc] + 30;
       }
       else if (coinz.intersects(rockie) || coinz.intersects(rockie2) || coinz.intersects(hole))
       {
           coinx[rc] = coinx[rc] - 30;
           coiny[rc] = coiny[rc] - 30;

           if (coinx[rc] > 1000) coinx[rc] - 30;
           else if (coinx[rc] < 10) coinx[rc] + 30;

           if (coiny[rc] > 550) coiny[rc] - 30;
           else if (coiny[rc] < 10) coiny[rc] + 30;
       }
       else if (hole.intersects(rockie) || hole.intersects(rockie2) || hole.intersects(coinz))
       {
           transx[rc] = transx[rc] - 30;
           transy[rc] = transy[rc] - 30;

           if (transx[rc] > 1000) transx[rc] - 30;
           else if (transx[rc] < 10) transx[rc] + 30;

           if (transy[rc] > 550) transy[rc] - 30;
           else if (transy[rc] < 10) transy[rc] + 30;
       }

       if (character.intersects(rockie) || character.intersects(rockie2))
       {
           window.clear();
           Text texts("GAME OVER", font, 100);
           Text text("You had " + ps, font, 50);
           texts.setPosition(300, 250);
           text.setPosition(300, 400);
           window.draw(texts);
           window.draw(text);
           window.display();
           sleep(seconds(10));
           window.close();
       }
       else if (character.intersects(coinz))
       {
           coin.setColor(Color::Transparent);
           points += 100;
       }

      
                 
       if (rc == 200) rc = 0;
      
       if (character.intersects(hole))
       {
           hell = !hell;
           bhole.setPosition(1100, 800);
           window.draw(bhole);
       }
       
           window.clear();
           if (hell == true)
           {
               window.draw(newback);
           }
           else
           {
               window.draw(sBackground);
           }
           window.draw(drag);
           window.draw(coin);
           window.draw(text);
           window.draw(rock);
           window.draw(rock2);
           window.draw(bhole);
         

        window.display();
    }


    return 0;
}


  