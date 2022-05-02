/**
* @brief Visual authentication state in AuthUI.
* This abstract class provides an interface between AuthUI and various
* visual states associated with feedback provided to the user. Each AuthState
* overrides methods that define what changes should be made to the user interface
* how long the state should remain on screen, plus any logging associated with the
* event that brought about the state.
* @author Austin Hatherell
*
*/

#include "authui.h"
#include "authstate.h"

/**
 * Retrives an instance of AuthUI for derived classes to use in their updateUI()
 * implementations, and sets a default sleep value. This method should be overriden
 * in derived classes that want to be displayed for shorter or longer than the default.
 * @brief Default constructor.
*/
AuthState::AuthState(){
	ui = AuthUI::getInstance();
	duration = 7;
}

/**
 * This method should not be overridden. It calls all of the other behaviours
 * in this class in the appropriate sequence to do UI update, a minimum display time,
 * and logging. It takes a user arg, which is used by updateUI().
 * @brief Universal implementation for when the state is activated.
 * @param user    The user whose information should be displayed on screen.
*/
void AuthState::activate(Record *user){
	resetUI(); // Blank all of the labels so ones not set in updateUI() aren't visible
	updateUI(user);
	logEvent(user);

	// Before blocking, make sure all of the pending Qt events for this
	// thread have been processed. This ensures that the UI changes made
	// in updateUI() are painted first.
	QApplication::instance()->processEvents();

	sleepDuration();
}

/**
 * Resets the state of AuthUI in such a way that the concrete implementations of
 * updateUI() only need to call whichever setters from AuthUI of elements they
 * want to be visible. Everything else remains blank. This ensures that UI state
 * from previous AuthState's updateUI() calls never carry over to the next state.
 * @brief Reset the UI to allow for updateUI().
 */
void AuthState::resetUI(){
	ui->setBackgroundColor("#ffffff");
	ui->setHeading("");
	ui->setPrimaryText("");
	ui->setSecondaryText("");
	ui->setUserName("");
	ui->setUserStudentNumber("");
	ui->setStatusIcon("");
}

/*
 * This, combined with the setting of variable duration in the constructor,
 * will block the calling thread when an AuthState is activated, guranteeing
 * that it's UI state will remain visible for some minimum number of seconds
 * before AuthUI changes states again.
 * @brief Block for the class's minimum display time.
 */
void AuthState::sleepDuration(){
	sleep(duration);
}

/**
 * @brief Empty destructor.
 */
AuthState::~AuthState(){
	// Nothing on heap to clean up
}
