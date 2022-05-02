/** This is the UI that will be displayed when the user first loads into the program.
  * From here the user has the choice to move to "Admin Tools", which will bring up the UI for admin login, or "Scanner", which will being up the UI for authenticating.
  * @brief The initial window state -- allows users to go to LoginUI and AuthUI.
  * @author Nicolas Jacobs
  * @date 2021-11-09
 */

#include "mainui.h"

// Points to the singleton instance of this class
MainUI *MainUI::instance = nullptr;

/**
 * This is the Singleton "Constructor". To access this class, this static
 * method must be called to return an instance of this class. Because of the Singleton
 * design pattern, only one instance of this class can ever exist.
 * This function returns the singleton instance of this class called "instance".
 * @brief Returns a reference to the sole instance of the MainUI class.
 * @return A pointer to the singleton MainUI object.
 */
MainUI *MainUI::getInstance()
{
    if(instance == nullptr)
    {
        instance = new MainUI();
    }
    return instance;
}

/**
 * Constructor
 * The mainui is the first state that is viewable on startup.
 * This can only ever be called once because it is singleton.
 * @brief Constructs a MainUI object.
 * @param *parent The QWidget that MainUI inherits from.
 * */
MainUI::MainUI(QWidget *parent) : QWidget(parent)
{
        layout = new QVBoxLayout(this);

        feedbackLabel = new QLabel();
        feedbackLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(feedbackLabel);

	//Background colour and title
	setStyleSheet("background-color: #ffcf88;");
        feedbackLabel->setText("<h1>Covid-19 Checkpoint</h1>");

	//Two buttons
	createButtons();

	//Link the "Admin Tools" button to the command "toLogin"
	connect(buttons[0], &QPushButton::released, this, &MainUI::toLogin);

	//Link the "Scanner" button to the command "toAuth"
	connect(buttons[1], &QPushButton::released, this, &MainUI::toAuth);

	//Add everything to the screen
	layout->addWidget(buttonBox);

	setLayout(layout);
}

/**
 * Add the "Admin Tools" and "Scanner" buttons to the page.
 * @brief Add the buttons to the window.
 * */
void MainUI::createButtons()
{
	buttonBox = new QGroupBox();
	QHBoxLayout *layout = new QHBoxLayout;
	buttonBox->setStyleSheet("QGroupBox {  border: 0px solid red;}");
	buttons[0] = new QPushButton(tr("Admin Tools"));
	buttons[1] = new QPushButton(tr("Begin Authentication Session"));

	//Set the size of the buttons and add them to the layout
	for (int i = 0; i < 2; i++)
	{
		buttons[i]->setMinimumSize(100, 50);
		layout->addWidget(buttons[i]);
	}
	buttonBox->setLayout(layout);
}

/**
 * The functionality of what happens when "Admin Tools" is pressed.
 * Will change the state to loginui.
 * @brief Changes the state of window to be LoginUI.
 * */
void MainUI::toLogin()
{
	Window &switchWindow = Window::getInstance();
	switchWindow.setState("login");
}

/**
 * The funcionality of what happens when "Scanner" is pressed.
 * Will change the state to authui.
 * @brief Changes the state of window to be AuthUI.
 * */
void MainUI::toAuth()
{
	Window &switchWindow = Window::getInstance();
	switchWindow.setState("auth");
}

/**
 * Destructor
 * Destroys the mainui object.
 * @brief Destorys the mainui object.
 * */
MainUI::~MainUI(){}
