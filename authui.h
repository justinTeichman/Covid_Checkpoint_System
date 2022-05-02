 /**
 * This (singleton) class contains all of the logic associated with authenticating
 * or rejecting users, and keeps an active AuthState instance in order to provide
 * visual feedback corresponding with its decisionmaking.
 * @brief Header for UI element that provides QR code authentication and feedback.
 * @author Austin Hatherell
 * */

#ifndef AUTHUI_H
#define AUTHUI_H

#include <vector>
#include <iostream>
#include <ctime>
#include <string>

#include <QString>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFrame>
#include <QSizePolicy>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QKeyEvent>
#include <QPixmap>
#include <QMovie>

#include "window.h"
#include "record.h"
#include "authstate.h"
#include "authstates_header.h"
#include "qrcode.h"
#include "logger.h"

class AuthState; // Forward declaration

class AuthUI : public QWidget{
	public:
		int getCapacity();
		void setHeading(std::string text);
		void setPrimaryText(std::string text);
		void setSecondaryText(std::string text);
		void setBackgroundColor(std::string color);
		void setUserName(std::string text);
		void setUserStudentNumber(std::string text);
		void setStatusIcon(std::string location);

		void authenticate(QRCode qr);
		void activate();
		bool shouldInterruptCamera();
		bool isAvailable();

		static AuthUI* getInstance();

	protected:
		AuthUI(QWidget *parent = nullptr);

	private:
		int capacity;
		bool interruptCamera;
		bool available;
		std::vector<Record> occupants;
		AuthState *currentState;

		QLabel *heading;
		QLabel *primaryText;
		QLabel *secondaryText;
		QLabel *occupancyLabel;
		QLabel *userNameLabel, *userStudentNumberLabel;
		QLabel *statusIconLabel;
		QFrame *statusSideFrame;
		QFrame *detailSideFrame;

		AuthState* getAuthState();

		void setState(AuthState *newState, Record *user=nullptr);
		void setOccupancy(int occupancy);
		int secondsToNow(std::string date);
		void keyReleaseEvent(QKeyEvent *event);
		void toMain();
		static AuthUI *instance;
};

#endif
