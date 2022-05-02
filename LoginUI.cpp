/** 
 * This LoginUI.cpp file implements the LoginUI class 
 * to create a QT Graphical User Interface for the login menu. 
 * @brief The Login GUI state in the system.
 * @author Justin Weller
 * @date 2021-11-09
 */

// Include the LoginUI header file
#include "LoginUI.h"

// Points to the singleton instance of this class
LoginUI *LoginUI::instance = nullptr;

/**
 * This is the Singleton "Constructor". To access this class, this static
 * method must be called to return an instance of this class. Because of the Singleton 
 * design pattern, only one instance of this class can ever exist.
 * @brief The Singleton accessor.
 * @return The singleton instance of this class called "instance"
 */
LoginUI *LoginUI::getInstance()
{
    if(instance == nullptr)
    {
        instance = new LoginUI();
    }
    return instance;
}
/**
 * This is the constructor of the LoginUI class, used to
 * initialize all the main GUI elements and layouts for the login UI.
 * @brief The constructor of LoginUI.
 * @param parent The pointer to the parent of the GUI elements (if initialized).
*/
LoginUI::LoginUI(QWidget *parent)
  : QWidget(parent)
{
    windowLayout = new QVBoxLayout(this);

    createMainBox(); // Creates the main GUI login box on the screen
    
    // Add the box to the main layout and centre it
    windowLayout->addWidget(mainBox);
    windowLayout->setAlignment(Qt::AlignCenter); 

    // Configure this UI's layout
    // setStyleSheet("background-color: #ffcf88;"); // Not working, currently used in window.cpp instead
    setLayout(windowLayout);
}

/**
 * This is the destructor of the LoginUI class. Since QT automatically destroys
 * the GUI pointers when this class loses scope, the destructor can remain empty.
 * @brief The destructor of LoginUI.
*/
LoginUI::~LoginUI()
{

}

/**
 * This function creates and sets the functionality of the main box's
 * GUI elements on the login UI.
 * @brief Creates the main login box on the GUI.
 */
void LoginUI::createMainBox()
{
    mainBox = new QWidget(this);

    mainBoxLayout = new QGridLayout(this);

    // Configurations for the box title
    title = new QLabel("SIGN IN", this);
    title->setStyleSheet("font: 22pt; font-weight: bold;");
    mainBoxLayout->addWidget(title, 0, 0, 1, -1, Qt::AlignCenter);

    // Configurations for the username label
    usernameLabel = new QLabel("Username:", this);
    usernameLabel->setStyleSheet("font: 10pt;");
    mainBoxLayout->addWidget(usernameLabel, 1, 0);

    // Configurations for the username text field
    username = new QLineEdit(this);
    username->setStyleSheet("font: 10pt; background-color: #fce9cc");
    mainBoxLayout->addWidget(username, 1, 1);

    // Configurations for the password label
    passwordLabel = new QLabel("Password:", this);
    passwordLabel->setStyleSheet("font: 10pt;");
    mainBoxLayout->addWidget(passwordLabel, 2, 0);  

    // Configurations for the password text field
    password = new QLineEdit(this);
    password->setStyleSheet("font: 10pt; background-color: #fce9cc");
    password->setEchoMode(QLineEdit::Password);
    mainBoxLayout->addWidget(password, 2, 1);

    // Configurations for the result label (message saying if credentials were valid or not)
    result = new QLabel("Please Enter Your Credentials");
    result->setStyleSheet("font: 10pt; ");
    mainBoxLayout->addWidget(result, 3, 0, 1, -1);

    // Whenever enter is pressed, the handleButton function is called (the command is executed)
    connect(username, &QLineEdit::returnPressed, this, &LoginUI::handleLoginButton);
    connect(password, &QLineEdit::returnPressed, this, &LoginUI::handleLoginButton);

    // Configurations for the login button
    loginButton = new QPushButton("Login", this);
    loginButton->setStyleSheet("font: 10pt; background-color: #ffcf88;");
    mainBoxLayout->addWidget(loginButton, 4, 0, 1, -1);
    // Whenever the button is pressed, the handleButton function is called (the command is executed)
    connect(loginButton, &QPushButton::released, this, &LoginUI::handleLoginButton);
    
    // Configurations for the back button
    backButton = new QPushButton("Return", this);
    backButton->setStyleSheet("font: 10pt; background-color: #ffcf88;");
    mainBoxLayout->addWidget(backButton, 5, 0, 1, -1);
    // Whenever the button is pressed, the handleButton function is called (the command is executed)
    connect(backButton, &QPushButton::released, this, &LoginUI::handleBackButton);

    // General configurations for the main box
    mainBox->setLayout(mainBoxLayout);
    mainBox->setStyleSheet("background-color: #ffcf88;");
    mainBox->setMaximumSize(550, 325);
    mainBox->setMinimumSize(550, 325);
}

/**
 * This function sends a request to credentials verifier to
 * validate the credentials. If the credentials are valid, the AdminUI is switched to,
 * else, a message is displayed and the user can try again.
 * @brief Verifies the entered credentials and switches states accordingly.
*/
void LoginUI::handleLoginButton()
{
    CredentialsVerifier checker;
    
    // If the credentials are valid
    if(checker.verifyCred((username->text()).toStdString(), (password->text()).toStdString()))
    {
        result->setText("Please Enter Your Credentials"); // Reset the result label
        username->clear(); // Clear the username and password fields
        password->clear();

	    Window &switchWindow = Window::getInstance();
	    switchWindow.setState("admin"); // Switch to admin UI
    }
    else // If the credentials are invalid
    {
        result->setText("Invalid Credentials Entered");
    }
}

/**
 * This function switches the current window back to the Main UI.
 * @brief Switches the window state to Main UI.
*/
void LoginUI::handleBackButton()
{
    // Set state to main menu
    Window &switchWindow = Window::getInstance();
    switchWindow.setState("main"); // Switch to Main UI
}
