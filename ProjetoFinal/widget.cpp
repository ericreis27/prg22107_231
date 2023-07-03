#include "widget.h"
#include "ui_widget.h"
#include "player.h"
#include "question.h"
#include <QInputDialog>
#include <QDebug>
#include <QMessageBox>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    buttons ={ui->stage1, ui-> stage2, ui->stage3, ui->stage4, ui->stage5, ui->stage6, ui-> stage7, ui->stage8, ui->stage9, ui->stage10, ui->stage11, ui-> stage12, ui->stage13, ui->stage14, ui->stage15, ui->stage16, ui->stage17};
    alternative_buttons = {ui->optionA, ui->optionB, ui->optionC, ui->optionD};
    card_buttons = {ui->card1_button, ui->card2_button, ui->card3_button, ui->card4_button, ui->card5_button};
    stage_questions = {
        "",
        "Entertainment: Cartoon & Animations",
        "Entertainment: Television",
        "Entertainment: Video Games",
        "Entertainment: Japanese Anime & Manga",
        "Entertainment: Books",
        "Entertainment: Music",
        "Entertainment: Video Games",
        "Entertainment: Television",
        "Entertainment: Cartoon & Animations",
        "Entertainment: Books",
        "Entertainment: Japanese Anime & Manga",
        "Entertainment: Comics",
        "Entertainment: Books",
        "Entertainment: Video Games",
        "Entertainment: Japanese Anime & Manga",
        "Entertainment: Cartoon & Animations",
        "Entertainment: Film",
    };
    //initializing the available cards list
    available_cards << 1 << 2 << 3 << 4 << 5;

    //Getting player name
    QString player_name = QInputDialog::getText(this, "Nome do jogador", "Jogador", QLineEdit::Normal);

    //Getting player color
    QStringList color_items;
    color_items << tr("Verde") << tr("Vermelho") << tr("Amarelo") << tr("Azul");
    QString player_color = QInputDialog::getItem(this, tr("Selecione a cor do player"), tr("Cor"), color_items, 0, false);

    QStringList difficulty_levels;
    difficulty_levels << tr("easy") << tr("medium") << tr("hard");

    QString difficulty = QInputDialog::getItem(this, tr("Selecione a dificuldade"), tr("Dificuldade"), difficulty_levels, 0, false);

    QColor color;

    if (player_color == "Verde"){
        color = Qt::green;
    } else if (player_color == "Vermelho"){
        color = Qt::red;
    } else if (player_color == "Amarelo"){
        color = Qt::yellow;
    } else if (player_color == "Azul"){
        color = Qt::blue;
    }

    if (!player_name.isEmpty()){
        player.set_player_data(player_name, color);
    }

    question_manager.fetchQuestionsFromApi(difficulty);


    //Initializing the color palettes
    normal_button_palette = buttons[0]->palette();
    player_color_palette.setColor(QPalette::Button, player.get_player_color());

    //Initializing labels
    ui->player1_name->setText(player.get_player_name());

    ui->player1_color_label->setText(player_color);

    ui->questionCategoryLabel->setText("");

}

Widget::~Widget()
{
    delete ui;
    delete m_data_buffer;
}

void Widget::on_confirmButton_clicked()
{
    int question_index = current_stage+current_card_try;

    if (question_index < LAST_STAGE){
        temporary_question = question_manager.questions_map[stage_questions[question_index]].first();
    }else{
        temporary_question = question_manager.questions_map[stage_questions[LAST_STAGE-1]].first();
    }

    QString correct_answer = temporary_question.get_correct_answer();
    QString incorrect_answer_text = "A resposta correta era: " + correct_answer;
    if (alternative_buttons[secret_number]->isChecked()){
        QMessageBox::information(this, "Parabéns", "Certa Respostaaaaaa!!!");
        qDebug() << buttons.size();
        if((question_index) < LAST_STAGE){
            setStageColor(current_stage, current_stage + current_card_try);
            current_stage += current_card_try;
        }else{
            QMessageBox::information(this, "YAY","PARABÉNSSSSS, VOCÊ VENCEU!!");
            QApplication::exit();
        }
    }else{
        QMessageBox::information(this, "Resposta Errada :(", incorrect_answer_text);
    }

    //Removing question from the list so it cannot be repeated
    if (question_index < LAST_STAGE){
        question_manager.questions_map[stage_questions[question_index]].removeFirst();
    }else{
        question_manager.questions_map[stage_questions[LAST_STAGE - 1]].removeFirst();
    }

    setButtonsStyle(false);
    ui->questionTitleEdit->clear();
    ui->questionCategoryLabel->clear();
}

void Widget::on_card1_button_clicked()
{
    current_card_try = 1;

    setButtonsStyle(true);
    setQuestionLabel();
    updateCardsAvailable(current_card_try);
}

void Widget::on_card2_button_clicked()
{
    current_card_try = 2;

    setButtonsStyle(true);
    setQuestionLabel();
    updateCardsAvailable(current_card_try);
}

void Widget::on_card3_button_clicked()
{
    current_card_try = 3;

    setButtonsStyle(true);
    setQuestionLabel();
    updateCardsAvailable(current_card_try);
}

void Widget::on_card4_button_clicked()
{
    current_card_try = 4;

    setButtonsStyle(true);
    setQuestionLabel();
    updateCardsAvailable(current_card_try);
}

void Widget::on_card5_button_clicked()
{
    current_card_try = 5;

    setButtonsStyle(true);
    setQuestionLabel();
    updateCardsAvailable(current_card_try);
}

void Widget::updateCardsAvailable(int card_number){
    if (available_cards.removeOne(card_number)){
        qDebug() << QString::number(card_number) << " removido com sucesso";
        card_buttons[card_number-1]->setDisabled(true);
    }else{
        QMessageBox::information(this, "Operação invalida", "Essa carta já foi utilizada, selecione uma carta disponível");
    }

    if (available_cards.isEmpty()){
        available_cards << 1 << 2 << 3 << 4 << 5;

        for(int i=0; i < card_buttons.size(); i++){
            card_buttons[i]->setDisabled(false);
        }
    }
}

void Widget::setStageColor(int current_stage, int next_stage){
    if(current_stage == 0){
        current_stage = 1;
    }

    buttons[current_stage-1]->setAutoFillBackground(true);
    buttons[current_stage-1]->setPalette(normal_button_palette);
    buttons[current_stage-1]->update();

    buttons[next_stage-1]->setAutoFillBackground(true);
    buttons[next_stage-1]->setPalette(player_color_palette);
    buttons[next_stage-1]->update();

}

void Widget::setQuestionLabel(){
    std::srand(std::time(nullptr));
    secret_number = std::rand() % 4;


    qDebug() <<"Secret Number generated: " << QString::number(secret_number);

    int question_index = current_stage+current_card_try;

    Question question;
    if (question_index < LAST_STAGE){
        question = question_manager.questions_map[stage_questions[question_index]].first();
    }else{
        question = question_manager.questions_map[stage_questions[LAST_STAGE-1]].first();
    }

    qDebug() <<"Resposta certa é: " << question.get_correct_answer();

    QList<QString> incorrect_answers = question.get_incorrect_answers();

    ui->questionTitleEdit->setText(question.get_question_title());
    ui->questionCategoryLabel->setText(question.get_category());

    QList<int> alternatives_index_list;
    alternatives_index_list << 0 << 1 << 2 << 3;

    alternatives_index_list.removeAt(secret_number);

    alternative_buttons[secret_number]->setText(question.get_correct_answer());
    for(int i =0; i < incorrect_answers.size(); i++){
        alternative_buttons[alternatives_index_list[i]]->setText(incorrect_answers[i]);
    }

}

void Widget::disableCardButtons(bool ok){
    for(int i = 0; i < card_buttons.size(); i++){
        card_buttons[i]->setDisabled(ok);
    }
}
void Widget::setButtonsStyle(bool ok){
    if(ok){
        for(int i = 0; i < card_buttons.size(); i++){
            card_buttons[i]->hide();
        }
    }else{
        for (int i=0; i<card_buttons.size();i++){
            card_buttons[i]->show();
        }
        for (int i=0; i < alternative_buttons.size(); i++){
            alternative_buttons[i]->setText("");
            alternative_buttons[i]->setChecked(false);
        }
    }
}
