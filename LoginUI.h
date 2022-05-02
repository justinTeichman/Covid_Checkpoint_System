/**
 * Description: This LoginUI.h file declares the class blueprint of the
 * LoginUI class which is used for creating the login GUI. It also 
 * includes all the necessary libraries and files for this class.
 * @brief The header file for the LoginUI class.
 * @author Justin Weller
 * @date 2021-11-09
*/

// Include Guards
#ifndef LOGINUI_H
#define LOGINUI_H

// Include all the required system and standard libraries
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextBrowser>
#include <QListWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QTextEdit>
#include <string>
#include <iostream>

// This is the blueprint for the LoginUI class
class LoginUI : public QWidget
{
  Q_OBJECT

// Declares all the public members within the class
public:
  static LoginUI* getInstance();
  ~LoginUI();

// Declares all the private members which require QT signals to execute their action
private slots:
  void handleLoginButton();
  void handleBackButton();

// Declares all the private members within the class
private:
  explicit LoginUI(QWidget *parent = nullptr);

  static LoginUI *instance;

  void createMainBox();
  
  QLabel *title;

  QLineEdit *username;
  QLineEdit *password;

  QLabel *usernameLabel;
  QLabel *passwordLabel;
  QLabel *result;

  QPushButton *loginButton;
  QPushButton *backButton;

  QVBoxLayout *windowLayout;
  QGridLayout *mainBoxLayout;

  QWidget *mainBox;
};

// Include the other required classes
#include "CredentialsVerifier.h"
#include "window.h"

#endif // This header has been included