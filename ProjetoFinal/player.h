#ifndef PLAYER_H
#define PLAYER_H
#include <QString>
#include <QColor>

class Player
{
public:
    Player(){
        m_name = "Jogador 1";
        m_color = Qt::blue;
        m_stage = 0;
    }

    void set_player_data(QString name, QColor color);

    QString get_player_name()const;
    QColor get_player_color()const;

private:
    QColor m_color;
    QString m_name;
    int m_stage;
};

#endif // PLAYER_H
