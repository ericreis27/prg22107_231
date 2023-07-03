#include <player.h>

void Player::set_player_data(QString name, QColor color){
    m_name = name;
    m_color = color;
}


QString Player::get_player_name()const{
    return m_name;
}

QColor Player::get_player_color()const{
    return m_color;
}

