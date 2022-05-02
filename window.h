/**
 *  Main GUI window. It switches between multiple states according to what mode
 *  of operation the application is currently running in -- the "administrate" state
 *  displays an administrator's control panel, while the "authenticate" state displays
 *  feedback related to successful/failed QR code authentication.
 *  "main" is the first thing seen on load up. From here the user can select admin tools
 *  or select the scanner, both options will lead to a different UI.
 * 
 *  @brief Contains a declaration of all variables and methods used in window.cpp
 *  @author Austin Hatherell
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QDir>
#include <string>

#include "config.h"

#ifdef USING_CAMERA

// TODO: this should be a class or namespace, not just a set of global functions.
// When converted, it should be includable via a header file.
#include "Camera.cpp"

#endif

#include "authui.h"
#include "mainui.h"
#include "adminui.h"
#include "LoginUI.h"
#include "logger.h"
#include "database.h"

class AuthUI; // Forward declaration

class Window : public QMainWindow{
	public:
		~Window();
		void setState(std::string newState);
		static Window& getInstance();
		std::string getState();

	private slots: // Event handlers for Qt widgets

	private:
		Window(QWidget *parent = nullptr);

		AuthUI *authUIWidget;
		MainUI *mainUIWidget;
		AdminUI *adminUIWidget;
		LoginUI *loginUIWidget;
		std::string currentState;
};

#endif
