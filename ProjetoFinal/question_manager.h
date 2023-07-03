#ifndef QUESTION_MANAGER_H
#define QUESTION_MANAGER_H
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QByteArray>
#include <QString>
#include <QNetworkRequest>
#include <QUrl>
#include <QList>
#include "question.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QIODevice>
#include <QMessageBox>
#include <QApplication>

class QuestionManager:public QObject{
public:
    QuestionManager(){
        net_manager = new QNetworkAccessManager();
    }

    QList<Question> questions;
    QMap<QString, QList<Question>> questions_map;

    QUrl setUrlContent(QString difficulty, QUrl url);
    void fetchQuestionsFromApi(QString difficulty);
    QString cleanQuestionText(QString question_title);

private:
    QNetworkAccessManager *net_manager;

    QList<QUrl> API_ENDPOINTS;
    QList<QNetworkReply*> net_replies;
    QList<QNetworkRequest> requests;
    QList<QByteArray> data_buffer;

    //API ENDPOINTS
    QUrl ANIMATIONS_ENDPOINT = QUrl ("https://opentdb.com/api.php?amount=10&category=32&difficulty=medium&type=multiple");
    QUrl TV_ENDPOINT = QUrl ("https://opentdb.com/api.php?amount=10&category=14&difficulty=medium&type=multiple");
    QUrl GAMES_ENDPOINT = QUrl ("https://opentdb.com/api.php?amount=10&category=15&difficulty=medium&type=multiple");
    QUrl ANIME_MANGA_ENDPOINT = QUrl ("https://opentdb.com/api.php?amount=10&category=31&difficulty=medium&type=multiple");
    QUrl BOOKS_ENDPOINT = QUrl ("https://opentdb.com/api.php?amount=10&category=10&difficulty=medium&type=multiple");
    QUrl MUSIC_ENDPOINT = QUrl ("https://opentdb.com/api.php?amount=10&category=12&difficulty=medium&type=multiple");
    QUrl COMICS_ENDPOINT = QUrl ("https://opentdb.com/api.php?amount=10&category=29&difficulty=medium&type=multiple");
    QUrl MOVIES_ENDPOINT = QUrl ("https://opentdb.com/api.php?amount=10&category=11&difficulty=medium&type=multiple");

private slots:
    void dataReadyToRead(int i);
    void dataReadFinished(int i);

};

#endif // QUESTION_MANAGER_H;
