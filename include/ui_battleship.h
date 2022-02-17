/********************************************************************************
** Form generated from reading UI file 'battleship.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BATTLESHIP_H
#define UI_BATTLESHIP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Battleship
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *page_main_menu;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_6;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_title;
    QSpacerItem *verticalSpacer_3;
    QPushButton *button_main_play;
    QPushButton *button_main_settings;
    QPushButton *button_main_htp;
    QPushButton *button_main_quit;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_5;
    QWidget *page_fleet_creator;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *button_setup_exit;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QLabel *label_setup_title;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *grid_setup_board;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *button_setup_rand;
    QPushButton *button_setup_rot;
    QPushButton *button_setup_done;
    QSpacerItem *horizontalSpacer_5;
    QWidget *page_game;
    QHBoxLayout *horizontalLayout_15;
    QVBoxLayout *verticalLayout_13;
    QHBoxLayout *horizontalLayout_14;
    QPushButton *button_game_main;
    QSpacerItem *horizontalSpacer_20;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_18;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_10;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_player_board;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_10;
    QGridLayout *grid_game_player_board;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *verticalSpacer_9;
    QVBoxLayout *verticalLayout_9;
    QSpacerItem *verticalSpacer_14;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_16;
    QGridLayout *grid_game_player_fleet;
    QSpacerItem *horizontalSpacer_17;
    QSpacerItem *verticalSpacer_15;
    QFrame *line;
    QVBoxLayout *verticalLayout_11;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_enemy_board;
    QSpacerItem *verticalSpacer_10;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_12;
    QGridLayout *grid_game_enemy_board;
    QSpacerItem *horizontalSpacer_13;
    QSpacerItem *verticalSpacer_11;
    QVBoxLayout *verticalLayout_8;
    QSpacerItem *verticalSpacer_12;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_15;
    QGridLayout *grid_game_enemy_fleet;
    QSpacerItem *horizontalSpacer_14;
    QSpacerItem *verticalSpacer_13;
    QPlainTextEdit *game_plain_text_edit_log;
    QSpacerItem *horizontalSpacer_19;
    QWidget *page_htp;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_8;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_htp_title;
    QLabel *label_htp_help;
    QPushButton *button_htp_back;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *verticalSpacer_7;
    QWidget *page;
    QVBoxLayout *verticalLayout_15;
    QSpacerItem *verticalSpacer_17;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer_21;
    QVBoxLayout *verticalLayout_14;
    QLabel *label_settings;
    QSpacerItem *verticalSpacer_16;
    QCheckBox *checkbox_settings_mma;
    QCheckBox *checkbox_settings_hard_enemy;
    QSpacerItem *verticalSpacer_19;
    QPushButton *button_settings_back;
    QSpacerItem *horizontalSpacer_22;
    QSpacerItem *verticalSpacer_18;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Battleship)
    {
        if (Battleship->objectName().isEmpty())
            Battleship->setObjectName(QString::fromUtf8("Battleship"));
        Battleship->resize(770, 559);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Battleship->sizePolicy().hasHeightForWidth());
        Battleship->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(Battleship);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy1);
        stackedWidget->setMaximumSize(QSize(782, 562));
        page_main_menu = new QWidget();
        page_main_menu->setObjectName(QString::fromUtf8("page_main_menu"));
        verticalLayout_3 = new QVBoxLayout(page_main_menu);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_3->addItem(verticalSpacer_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_title = new QLabel(page_main_menu);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_title->sizePolicy().hasHeightForWidth());
        label_title->setSizePolicy(sizePolicy2);
        QFont font;
        font.setPointSize(24);
        label_title->setFont(font);
        label_title->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_title, 0, Qt::AlignVCenter);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer_3);

        button_main_play = new QPushButton(page_main_menu);
        button_main_play->setObjectName(QString::fromUtf8("button_main_play"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(button_main_play->sizePolicy().hasHeightForWidth());
        button_main_play->setSizePolicy(sizePolicy3);

        verticalLayout_2->addWidget(button_main_play, 0, Qt::AlignHCenter);

        button_main_settings = new QPushButton(page_main_menu);
        button_main_settings->setObjectName(QString::fromUtf8("button_main_settings"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(button_main_settings->sizePolicy().hasHeightForWidth());
        button_main_settings->setSizePolicy(sizePolicy4);

        verticalLayout_2->addWidget(button_main_settings, 0, Qt::AlignHCenter);

        button_main_htp = new QPushButton(page_main_menu);
        button_main_htp->setObjectName(QString::fromUtf8("button_main_htp"));
        sizePolicy3.setHeightForWidth(button_main_htp->sizePolicy().hasHeightForWidth());
        button_main_htp->setSizePolicy(sizePolicy3);

        verticalLayout_2->addWidget(button_main_htp, 0, Qt::AlignHCenter);

        button_main_quit = new QPushButton(page_main_menu);
        button_main_quit->setObjectName(QString::fromUtf8("button_main_quit"));
        sizePolicy3.setHeightForWidth(button_main_quit->sizePolicy().hasHeightForWidth());
        button_main_quit->setSizePolicy(sizePolicy3);

        verticalLayout_2->addWidget(button_main_quit, 0, Qt::AlignHCenter);


        horizontalLayout_6->addLayout(verticalLayout_2);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);


        verticalLayout_3->addLayout(horizontalLayout_6);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_3->addItem(verticalSpacer_5);

        stackedWidget->addWidget(page_main_menu);
        page_fleet_creator = new QWidget();
        page_fleet_creator->setObjectName(QString::fromUtf8("page_fleet_creator"));
        verticalLayout = new QVBoxLayout(page_fleet_creator);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        button_setup_exit = new QPushButton(page_fleet_creator);
        button_setup_exit->setObjectName(QString::fromUtf8("button_setup_exit"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(button_setup_exit->sizePolicy().hasHeightForWidth());
        button_setup_exit->setSizePolicy(sizePolicy5);

        horizontalLayout_4->addWidget(button_setup_exit);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_setup_title = new QLabel(page_fleet_creator);
        label_setup_title->setObjectName(QString::fromUtf8("label_setup_title"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(label_setup_title->sizePolicy().hasHeightForWidth());
        label_setup_title->setSizePolicy(sizePolicy6);
        QFont font1;
        font1.setPointSize(16);
        label_setup_title->setFont(font1);

        verticalLayout->addWidget(label_setup_title, 0, Qt::AlignHCenter);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        grid_setup_board = new QGridLayout();
        grid_setup_board->setSpacing(0);
        grid_setup_board->setObjectName(QString::fromUtf8("grid_setup_board"));

        horizontalLayout->addLayout(grid_setup_board);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        button_setup_rand = new QPushButton(page_fleet_creator);
        button_setup_rand->setObjectName(QString::fromUtf8("button_setup_rand"));
        sizePolicy5.setHeightForWidth(button_setup_rand->sizePolicy().hasHeightForWidth());
        button_setup_rand->setSizePolicy(sizePolicy5);

        horizontalLayout_3->addWidget(button_setup_rand);

        button_setup_rot = new QPushButton(page_fleet_creator);
        button_setup_rot->setObjectName(QString::fromUtf8("button_setup_rot"));

        horizontalLayout_3->addWidget(button_setup_rot);

        button_setup_done = new QPushButton(page_fleet_creator);
        button_setup_done->setObjectName(QString::fromUtf8("button_setup_done"));

        horizontalLayout_3->addWidget(button_setup_done);


        horizontalLayout_5->addLayout(horizontalLayout_3);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_5);

        stackedWidget->addWidget(page_fleet_creator);
        page_game = new QWidget();
        page_game->setObjectName(QString::fromUtf8("page_game"));
        horizontalLayout_15 = new QHBoxLayout(page_game);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        button_game_main = new QPushButton(page_game);
        button_game_main->setObjectName(QString::fromUtf8("button_game_main"));

        horizontalLayout_14->addWidget(button_game_main);

        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_20);


        verticalLayout_13->addLayout(horizontalLayout_14);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_18);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(0);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_player_board = new QLabel(page_game);
        label_player_board->setObjectName(QString::fromUtf8("label_player_board"));
        label_player_board->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_player_board, 0, Qt::AlignHCenter);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_8);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_10);

        grid_game_player_board = new QGridLayout();
        grid_game_player_board->setSpacing(0);
        grid_game_player_board->setObjectName(QString::fromUtf8("grid_game_player_board"));

        horizontalLayout_8->addLayout(grid_game_player_board);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_11);


        verticalLayout_6->addLayout(horizontalLayout_8);

        verticalSpacer_9 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_6->addItem(verticalSpacer_9);


        verticalLayout_10->addLayout(verticalLayout_6);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalSpacer_14 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_9->addItem(verticalSpacer_14);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_16);

        grid_game_player_fleet = new QGridLayout();
        grid_game_player_fleet->setObjectName(QString::fromUtf8("grid_game_player_fleet"));
        grid_game_player_fleet->setHorizontalSpacing(0);
        grid_game_player_fleet->setVerticalSpacing(6);

        horizontalLayout_11->addLayout(grid_game_player_fleet);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_17);


        verticalLayout_9->addLayout(horizontalLayout_11);

        verticalSpacer_15 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_15);


        verticalLayout_10->addLayout(verticalLayout_9);


        horizontalLayout_12->addLayout(verticalLayout_10);

        line = new QFrame(page_game);
        line->setObjectName(QString::fromUtf8("line"));
        QSizePolicy sizePolicy7(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy7);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_12->addWidget(line);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(0);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_enemy_board = new QLabel(page_game);
        label_enemy_board->setObjectName(QString::fromUtf8("label_enemy_board"));
        label_enemy_board->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(label_enemy_board, 0, Qt::AlignHCenter);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_12);

        grid_game_enemy_board = new QGridLayout();
        grid_game_enemy_board->setSpacing(0);
        grid_game_enemy_board->setObjectName(QString::fromUtf8("grid_game_enemy_board"));

        horizontalLayout_9->addLayout(grid_game_enemy_board);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_13);


        verticalLayout_7->addLayout(horizontalLayout_9);

        verticalSpacer_11 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_7->addItem(verticalSpacer_11);


        verticalLayout_11->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalSpacer_12 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_8->addItem(verticalSpacer_12);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_15);

        grid_game_enemy_fleet = new QGridLayout();
        grid_game_enemy_fleet->setObjectName(QString::fromUtf8("grid_game_enemy_fleet"));
        grid_game_enemy_fleet->setHorizontalSpacing(0);
        grid_game_enemy_fleet->setVerticalSpacing(6);

        horizontalLayout_10->addLayout(grid_game_enemy_fleet);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_14);


        verticalLayout_8->addLayout(horizontalLayout_10);

        verticalSpacer_13 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_13);


        verticalLayout_11->addLayout(verticalLayout_8);


        horizontalLayout_12->addLayout(verticalLayout_11);


        verticalLayout_12->addLayout(horizontalLayout_12);

        game_plain_text_edit_log = new QPlainTextEdit(page_game);
        game_plain_text_edit_log->setObjectName(QString::fromUtf8("game_plain_text_edit_log"));
        game_plain_text_edit_log->setAcceptDrops(false);
        game_plain_text_edit_log->setInputMethodHints(Qt::ImhNone);
        game_plain_text_edit_log->setFrameShape(QFrame::StyledPanel);
        game_plain_text_edit_log->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        game_plain_text_edit_log->setUndoRedoEnabled(false);
        game_plain_text_edit_log->setLineWrapMode(QPlainTextEdit::NoWrap);
        game_plain_text_edit_log->setReadOnly(true);
        game_plain_text_edit_log->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout_12->addWidget(game_plain_text_edit_log);

        verticalLayout_12->setStretch(0, 3);
        verticalLayout_12->setStretch(1, 1);

        horizontalLayout_13->addLayout(verticalLayout_12);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_19);


        verticalLayout_13->addLayout(horizontalLayout_13);


        horizontalLayout_15->addLayout(verticalLayout_13);

        stackedWidget->addWidget(page_game);
        page_htp = new QWidget();
        page_htp->setObjectName(QString::fromUtf8("page_htp"));
        verticalLayout_5 = new QVBoxLayout(page_htp);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_8);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_htp_title = new QLabel(page_htp);
        label_htp_title->setObjectName(QString::fromUtf8("label_htp_title"));
        QSizePolicy sizePolicy8(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(label_htp_title->sizePolicy().hasHeightForWidth());
        label_htp_title->setSizePolicy(sizePolicy8);
        label_htp_title->setFont(font);

        verticalLayout_4->addWidget(label_htp_title, 0, Qt::AlignHCenter);

        label_htp_help = new QLabel(page_htp);
        label_htp_help->setObjectName(QString::fromUtf8("label_htp_help"));
        sizePolicy6.setHeightForWidth(label_htp_help->sizePolicy().hasHeightForWidth());
        label_htp_help->setSizePolicy(sizePolicy6);
        label_htp_help->setWordWrap(true);

        verticalLayout_4->addWidget(label_htp_help);

        button_htp_back = new QPushButton(page_htp);
        button_htp_back->setObjectName(QString::fromUtf8("button_htp_back"));

        verticalLayout_4->addWidget(button_htp_back, 0, Qt::AlignHCenter);


        horizontalLayout_7->addLayout(verticalLayout_4);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_9);


        verticalLayout_5->addLayout(horizontalLayout_7);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_7);

        stackedWidget->addWidget(page_htp);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout_15 = new QVBoxLayout(page);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        verticalSpacer_17 = new QSpacerItem(20, 131, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_15->addItem(verticalSpacer_17);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_21);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        label_settings = new QLabel(page);
        label_settings->setObjectName(QString::fromUtf8("label_settings"));
        sizePolicy2.setHeightForWidth(label_settings->sizePolicy().hasHeightForWidth());
        label_settings->setSizePolicy(sizePolicy2);
        label_settings->setFont(font);
        label_settings->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(label_settings);

        verticalSpacer_16 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_14->addItem(verticalSpacer_16);

        checkbox_settings_mma = new QCheckBox(page);
        checkbox_settings_mma->setObjectName(QString::fromUtf8("checkbox_settings_mma"));
        sizePolicy5.setHeightForWidth(checkbox_settings_mma->sizePolicy().hasHeightForWidth());
        checkbox_settings_mma->setSizePolicy(sizePolicy5);

        verticalLayout_14->addWidget(checkbox_settings_mma, 0, Qt::AlignLeft);

        checkbox_settings_hard_enemy = new QCheckBox(page);
        checkbox_settings_hard_enemy->setObjectName(QString::fromUtf8("checkbox_settings_hard_enemy"));

        verticalLayout_14->addWidget(checkbox_settings_hard_enemy, 0, Qt::AlignLeft);

        verticalSpacer_19 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_14->addItem(verticalSpacer_19);

        button_settings_back = new QPushButton(page);
        button_settings_back->setObjectName(QString::fromUtf8("button_settings_back"));

        verticalLayout_14->addWidget(button_settings_back, 0, Qt::AlignHCenter);


        horizontalLayout_16->addLayout(verticalLayout_14);

        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_22);


        verticalLayout_15->addLayout(horizontalLayout_16);

        verticalSpacer_18 = new QSpacerItem(20, 131, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_15->addItem(verticalSpacer_18);

        stackedWidget->addWidget(page);

        horizontalLayout_2->addWidget(stackedWidget);

        Battleship->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Battleship);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 770, 21));
        Battleship->setMenuBar(menubar);
        statusbar = new QStatusBar(Battleship);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Battleship->setStatusBar(statusbar);

        retranslateUi(Battleship);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Battleship);
    } // setupUi

    void retranslateUi(QMainWindow *Battleship)
    {
        Battleship->setWindowTitle(QCoreApplication::translate("Battleship", "Battleship", nullptr));
        label_title->setText(QCoreApplication::translate("Battleship", "Battleship", nullptr));
        button_main_play->setText(QCoreApplication::translate("Battleship", "Play", nullptr));
        button_main_settings->setText(QCoreApplication::translate("Battleship", "Settings", nullptr));
        button_main_htp->setText(QCoreApplication::translate("Battleship", "Help", nullptr));
        button_main_quit->setText(QCoreApplication::translate("Battleship", "Quit", nullptr));
        button_setup_exit->setText(QCoreApplication::translate("Battleship", "Back", nullptr));
        label_setup_title->setText(QCoreApplication::translate("Battleship", "Set up your fleet", nullptr));
        button_setup_rand->setText(QCoreApplication::translate("Battleship", "Generate random", nullptr));
        button_setup_rot->setText(QCoreApplication::translate("Battleship", "Rotate", nullptr));
        button_setup_done->setText(QCoreApplication::translate("Battleship", "Done", nullptr));
        button_game_main->setText(QCoreApplication::translate("Battleship", "Main Menu", nullptr));
        label_player_board->setText(QCoreApplication::translate("Battleship", "Your board", nullptr));
        label_enemy_board->setText(QCoreApplication::translate("Battleship", "Enemy's board", nullptr));
        label_htp_title->setText(QCoreApplication::translate("Battleship", "How to play", nullptr));
        label_htp_help->setText(QCoreApplication::translate("Battleship", "The goal of the game is to destroy the enemy fleet.\n"
"But first, to fight them you need your own fleet - which you set up on the setup page.\n"
"There you can see your fleet and the three buttons you can use to move your ships. First you select a ship by clicking on it. To move it to a new location, click on any other empty space, and if there is enough space for that ship, it will be moved. The square you click on will contain the leftmost highest ship segment you have moved. To rotate the selected ship, press the \"Rotate\" button. To generate a new random fleet, press the \"Generate random\" button. When you are finished setting up your fleet, hit \"Done\" to start the game.\n"
"The game screen consists of two boards and two sets of fleet displays and a message log where you can see what has happened in the last few moves. To shoot a specific field, left-click on it, to mark or unmark that field, right-click on it. The enemy will move when you press the left mouse button during their turn. The first playe"
                        "r to destroy an opponent's fleet wins. Good luck!", nullptr));
        button_htp_back->setText(QCoreApplication::translate("Battleship", "Back", nullptr));
        label_settings->setText(QCoreApplication::translate("Battleship", "Settings", nullptr));
        checkbox_settings_mma->setText(QCoreApplication::translate("Battleship", "Automatically mark misses around sunken ships", nullptr));
        checkbox_settings_hard_enemy->setText(QCoreApplication::translate("Battleship", "Harder computer enemy", nullptr));
        button_settings_back->setText(QCoreApplication::translate("Battleship", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Battleship: public Ui_Battleship {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BATTLESHIP_H
