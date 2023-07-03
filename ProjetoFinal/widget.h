#ifndef WIDGET_H
#define WIDGET_H

#include "question.h"
#include "player.h"
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QByteArray>
#include <QDebug>
#include <QString>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPalette>
#include <QList>
#include <QPushButton>
#include <QRadioButton>
#include <QColor>
#include <QUrl>
#include <QNetworkRequest>
#include "question_manager.h"

#define LAST_STAGE 18

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void updateCardsAvailable(int card_number);
    void setStageColor(int current_stage, int next_stage);
    void setQuestionLabel();
    void disableCardButtons(bool ok);
    void setButtonsStyle(bool ok);

    void on_confirmButton_clicked();

    void on_card1_button_clicked();

    void on_card2_button_clicked();

    void on_card3_button_clicked();

    void on_card4_button_clicked();

    void on_card5_button_clicked();


private:
    Ui::Widget *ui;
    QNetworkAccessManager *net_manager;
    QNetworkReply * net_reply;
    QByteArray * m_data_buffer;


    int secret_number;
    int current_stage = 0;
    int current_card_try = 0;


    Player player;
    Question temporary_question;
    QuestionManager question_manager;

    QList<int> available_cards;
    QList<QPushButton*> buttons;
    QList<QRadioButton*> alternative_buttons;
    QList<QPushButton*> card_buttons;
    QList<QString> stage_questions;

    QPalette normal_button_palette;
    QPalette player_color_palette;


};
#endif // WIDGET_H
