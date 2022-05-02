/**
 * AuthState that appears when the QR code does not exist in database. For
 * more information, see AuthState class docs.
 * @brief AuthState for unrecognized QR code.
 * @author Austin Hatherell
 */

#include "authstates_header.h"

AuthStateDeniedInvalid::AuthStateDeniedInvalid(){ 
	duration = 10;
}

void AuthStateDeniedInvalid::logEvent(Record *user){
	Logger::instance().deniedQRCode();
}

void AuthStateDeniedInvalid::updateUI(Record *user){
	ui->setBackgroundColor("#e5877b"); 
	ui->setHeading("Denied."); 
	ui->setPrimaryText("Do not proceed. According to our records, you have not demonstrated " 
	                   "proof of COVID-19 vaccination or been granted an exemption.");
	ui->setSecondaryText("<p>All members of our community -- including students, employees and "
	                     "visitors -- are required to demonstrate proof of vaccination, except "
						 "under rare exemptions.</p>"
						 "<p>For more information, please visit the COVID-19 information page: "
						 "<b>www.uwo.ca/coronavirus/</b></p>");
	ui->setStatusIcon("resources/denied-circle.png");
}
