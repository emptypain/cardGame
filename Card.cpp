#include "Card.h"
#include <iostream>
#include <string>

using namespace std;

class Card {
public:
    string nameCard = " ";
    int hp = 0;
    int dmg = 0;
    string dmgSTR = " ";
    string hpSTR = " ";
    int qualityCard = 0;
    const long int imageSize;
    const unsigned char* CardPhotoImage;

    Card(string name, int hp, int dmg, long int imgSize, unsigned char* arrImage) :imageSize(imgSize), CardPhotoImage(arrImage)
    {
        nameCard = name;
        this->hp = hp;
        this->dmg = dmg;


        dmgSTR = to_string(dmg);
        hpSTR = to_string(hp);

        if (dmgSTR.size() == 1)
        {
            dmgSTR.append(" ");
        }
        if (hpSTR.size() == 1)
        {
            hpSTR.append(" ");
        }
    }
};