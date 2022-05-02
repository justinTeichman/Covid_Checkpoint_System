/**
 * AuthState that appears when the room is full and user cannot enter as a result. For
 * more information, see AuthState class docs.
 * @brief AuthState for when room is full, user denied.
 * @author Austin Hatherell
 */

#include "authstates_header.h"

AuthStateDeniedFull::AuthStateDeniedFull(){ 
	duration = 10;
}

void AuthStateDeniedFull::logEvent(Record *user){
	Logger::instance().deniedFull(user->getId());
}

void AuthStateDeniedFull::updateUI(Record *user){
	ui->setBackgroundColor("#e5877b");
	ui->setHeading("Denied.");
	ui->setPrimaryText("Do not proceed. This room has met its allowed capacity and cannot "
	                   "accomodate any more visitors.");
	ui->setStatusIcon("resources/denied-circle.png");
}
