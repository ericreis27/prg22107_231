#ifndef QUESTION_H
#define QUESTION_H
#include <QList>
#include <QString>

class Question{
public:
    Question(){}

    void set_category(QString category);
    void set_question_data(QString category, QString correct_answer, QString difficulty, QList<QString> incorrect_answers, QString question_title);
    QString get_category()const;
    QString get_correct_answer()const;
    QList<QString> get_incorrect_answers()const;
    QString get_question_title()const;

private:
    QString m_category;
    QString m_correct_answer;
    QList<QString> m_incorrect_answers;
    QString m_difficulty;
    QString m_question_title;

};

#endif // QUESTION_H
