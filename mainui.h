/**
 * The header file of the mainui window state object.
 * This contains definitions of all variables and methods used by the mainui class.
 * @brief The header file of the mainui class.
 * @author Nicolas Jacobs
 * */

#ifndef MAINUI_H
#define MAINUI_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <iostream>

class MainUI : public QWidget{
        public:
		static MainUI *getInstance();
 
                ~MainUI();
        private:
		MainUI(QWidget *parent = nullptr);
		static MainUI *instance;

		void createButtons();
                void toLogin();
		void toAuth();

		QLabel *feedbackLabel;
                QVBoxLayout *layout;
		QGroupBox *buttonBox;
		QPushButton *buttons[2];
		QLabel *label;
};

#include "window.h"

#endif
