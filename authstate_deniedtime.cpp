/**
 * AuthState that appears when the user is vaccinated, but the date of vaccination
 * is less than 14 days previous to the system time. For more information, see
 * AuthState class docs.
 * @brief AuthState for user denied for being vaccinated less than 14 days.
 * @author Austin Hatherell
 */

#include "authstates_header.h"

AuthStateDeniedTime::AuthStateDeniedTime(){ 
	duration = 10;
}

void AuthStateDeniedTime::logEvent(Record *user){
	Logger::instance().deniedDate(user->getId());
}

void AuthStateDeniedTime::updateUI(Record *user){
	ui->setBackgroundColor("#e5877b");
	ui->setHeading("Denied.");
	ui->setPrimaryText("Do not proceed. According to our records, it has not been 14 days since "
	                   "your final dose of the COVID-19 vaccine.");
	ui->setSecondaryText("<p>In order to be considered fully vaccinated, you must have received "
	                     "your final dose at least 14 days ago.</p>"
						 "<p>For more information, please visit the COVID-19 information page: "
						 "<b>www.uwo.ca/coronavirus/</b></p>");
	ui->setUserName(user->getfName() + " " + user->getlName());
	ui->setStatusIcon("resources/denied-circle.png");
}
