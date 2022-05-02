/**
 * AuthState that appears when the user successfully scans to exit the room,
 * after having successfully entered before. For more information, see AuthState
 * class docs.
 * @brief AuthState for when user successfully exits room.
 * @author Austin Hatherell
 */

#include "authstates_header.h"

AuthStateExit::AuthStateExit(){ 
	duration = 7;
}

void AuthStateExit::logEvent(Record *user){
	Logger::instance().exit(user->getId());
}

void AuthStateExit::updateUI(Record *user){
	ui->setBackgroundColor("#83c17c");
	ui->setHeading("Goodbye.");
	ui->setPrimaryText("Please exit. Have a nice day!");
	ui->setUserName(user->getfName() + " " + user->getlName());
	ui->setStatusIcon("resources/accepted-circle.png");
}
