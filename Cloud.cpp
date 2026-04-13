//
// Created by thell on 4/13/2026.
//

#include "Cloud.hpp"

Cloud::Cloud(sf::Texture& texture, int id) : m_ID(id), m_Active(false), m_Speed(0.0f) {
    m_Sprite.setTexture(texture);
}

void Cloud::update(float dt, int screenWidth)
{
    if (!m_Active)
    {
        m_Speed = (rand() % 200);
        float height = (rand() % (150 * m_ID));
        m_Sprite.setPosition(-200, height);
        m_Active = true;
    } else
    {
        m_Sprite.setPosition(m_Sprite.getPosition().x + (m_Speed * dt),
            m_Sprite.getPosition().y);
        if (m_Sprite.getPosition().x > screenWidth)
        {
            m_Active = false;
        }
    }
}

void Cloud::reset()
{
    m_Active = false;
    m_Sprite.setPosition(-200, m_Sprite.getPosition().y);
}

sf::Sprite& Cloud::getSprite()
{
    return m_Sprite;
}