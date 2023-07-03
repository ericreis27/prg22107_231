#include "question_manager.h"


void QuestionManager::fetchQuestionsFromApi(QString difficulty)
{
    API_ENDPOINTS << ANIMATIONS_ENDPOINT << TV_ENDPOINT << GAMES_ENDPOINT << ANIME_MANGA_ENDPOINT << BOOKS_ENDPOINT << MUSIC_ENDPOINT << COMICS_ENDPOINT << MOVIES_ENDPOINT;
    qDebug() << API_ENDPOINTS;

    for (int i=0; i< API_ENDPOINTS.size(); i++){
        QUrl url = setUrlContent(difficulty, API_ENDPOINTS[i]);
        qDebug() << difficulty;

        requests.append(QNetworkRequest());
        requests.back().setUrl(url);

        qDebug() << requests.back().url();

        QNetworkReply* reply;


        data_buffer.append(QByteArray());


        reply = net_manager->get(requests.back());
        net_replies.append(reply);
        qDebug() << reply;
        QObject::connect(reply,&QIODevice::readyRead,this,[=](){QuestionManager::dataReadyToRead(i);});
        QObject::connect(reply,&QNetworkReply::finished,this,[=](){QuestionManager::dataReadFinished(i);});
    }
}


QUrl QuestionManager::setUrlContent(QString difficulty, QUrl url)
{
    QString urlString = url.toString();
    QString oldDifficulty = "difficulty=medium";
    QString newDifficulty = "difficulty=" + difficulty;

    urlString.replace(oldDifficulty, newDifficulty);
    QUrl newAPI_ENDPOINT(urlString);

    return newAPI_ENDPOINT;
}

void QuestionManager::dataReadyToRead(int i)
{
    qDebug() << "Cheguei no ready, i = " << i;
    data_buffer[i].append(net_replies[i]->readAll());
}

void QuestionManager::dataReadFinished(int i)
{
    qDebug() <<"Data ready, i = " << i;
    if(net_replies[i]->error()){
        qDebug() << "Error : " << QString(data_buffer[i]);
    }else{
        qDebug() << "Data fetch finished";

        QJsonDocument doc = QJsonDocument::fromJson(data_buffer[i]);
        QJsonObject obj = doc.object();
        QJsonArray array = obj["results"].toArray();
        if (array.isEmpty()){
            qDebug() << "Erro ao buscar as perguntas na API, abra novamente o programa";
            QApplication::exit();
        }

        for (int i = 0; i < array.size(); i++){
            QJsonObject object = array.at(i).toObject();
            QVariantMap map = object.toVariantMap();
            QString title = map["question"].toString();
            QString category = map["category"].toString();
            QString difficulty = map["difficulty"].toString();
            QString correct_answer = map["correct_answer"].toString();
            QList<QString> incorrect_answers = map["incorrect_answers"].toStringList();

            qDebug() << "titulo antes era:" << title;
            title = cleanQuestionText(title);
            qDebug() << "Categoria é:" << category;
            qDebug() << "Titulo da pergunta eh" << title;
            Question q;
            q.set_question_data(category, correct_answer, difficulty, incorrect_answers, title);

            questions_map[category].append(q);

        }
    }
}

QString QuestionManager::cleanQuestionText(QString question_title){
/*
 * Function necessary to remove unwanted content inside the questions.
 * The symbols <'> and <"> can't be sent on the API so it is necessary to remove them.
*/
    question_title.remove("&quot;");
    question_title.replace("&#039;", "'");

    return question_title;
}
