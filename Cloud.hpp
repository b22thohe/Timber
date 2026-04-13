//
// Created by thell on 4/13/2026.
//

#ifndef TIMBER_CLOUD_HPP
#define TIMBER_CLOUD_HPP

#include <SFML/Graphics.hpp>

class Cloud
{
private:
    sf::Sprite m_Sprite;
    float m_Speed;
    bool m_Active;
    int m_ID;

public:
    Cloud(sf::Texture& texture, int id);
    void update(float dt, int screenWidth);
    void reset();
    sf::Sprite& getSprite();
};


#endif //TIMBER_CLOUD_HPP
