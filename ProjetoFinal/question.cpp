#include <question.h>

void Question::set_category(QString category){
    m_category = category;
}

QString Question::get_category()const{
    return m_category;
}

QString Question::get_question_title()const{
    return m_question_title;
}

QString Question::get_correct_answer()const{
    return m_correct_answer;
}

QList<QString> Question::get_incorrect_answers()const{
    return m_incorrect_answers;
}

void Question::set_question_data(QString category, QString correct_answer, QString difficulty, QList<QString> incorrect_answers, QString question_title){
    m_category = category;
    m_correct_answer = correct_answer;
    m_difficulty = difficulty;
    m_incorrect_answers = incorrect_answers;
    m_question_title = question_title;
}
