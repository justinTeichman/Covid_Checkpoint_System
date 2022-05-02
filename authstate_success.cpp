/**
 * AuthState that appears when user is allowed entry into room. For
 * more information, see AuthState class docs.
 * @brief AuthState for successful entry.
 * @author Austin Hatherell
 */

#include "authstates_header.h"

AuthStateSuccess::AuthStateSuccess(){ 
	duration = 7;
}

void AuthStateSuccess::logEvent(Record *user){
	Logger::instance().admit(user->getId());
}

void AuthStateSuccess::updateUI(Record *user){
	ui->setBackgroundColor("#83c17c");
	ui->setHeading("Accepted.");
	ui->setPrimaryText("Please proceed. As a reminder:");
	ui->setSecondaryText("<p>All persons on campus must wear a three-layer non-medical "
	                     "mask while indoors.</p>"
						 "<p>Practice physical distancing, and when possible, stay two "
						 "metres apart from others.</p>"
						 "<p>Stay home if you feel ill or after exposure to someone who "
						 "is ill or has tested positive for COVID-19.</p>");
	ui->setUserName(user->getfName() + " " + user->getlName());
	ui->setStatusIcon("resources/accepted-circle.png");
}
