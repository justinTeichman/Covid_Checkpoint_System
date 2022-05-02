/**
 * AuthState that appears when the camera is waiting to recognize a QR code. For
 * more information, see AuthState class docs.
 * @brief AuthState for idling, waiting for QR code.
 * @author Austin Hatherell
 */

#include "authstates_header.h"

AuthStateWaiting::AuthStateWaiting(){ 
	// This is the default state, so there's no need for minimum time before returning to default
	duration = 0;
}

void AuthStateWaiting::logEvent(Record *user){
	// Nothing to log
}

void AuthStateWaiting::updateUI(Record *user){
	ui->setBackgroundColor("#ffcf88");
	ui->setHeading("Please scan your QR code.");
	ui->setPrimaryText("Hold the printed or digital copy of your QR code in front "
	                   "of the camera. Try to keep the image steady. If you require "
					   "assistance, please alert the attendant.");
	ui->setStatusIcon("resources/spinner.gif");
}
