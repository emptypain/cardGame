#include "Card.h"
#include <iostream>
#include <string>

using namespace std;

class Card {
public:
    string name = " ";
    int hp = 0;
    int damage = 0;
    int quality = 0;
    string damageStr = " ";
    string hpStr = " ";
    const long int imageSize;
    const unsigned char* image;

    Card(string name, int hp, int damage, long int imageSize, unsigned char* image) :imageSize(imageSize), image(image)
    {
        this->name = name;
        this->hp = hp;
        this->damage = damage;

        damageStr = to_string(damage);
        hpStr = to_string(hp);

        if (damageStr.size() == 1)
        {
            damageStr.append(" ");
        }

        if (hpStr.size() == 1)
        {
            hpStr.append(" ");
        }
    }
};