#ifndef _TURNIP_ART_H_
#define _TURNIP_ART_H_

#include <iostream>
#include <string>
#include <vector>

class TurnipArt
{
    std::vector<std::string> art;

public:
    TurnipArt();
    friend std::ostream &operator<<(std::ostream &out, TurnipArt *art);
};

std::ostream &operator<<(std::ostream &out, TurnipArt *art);

#endif