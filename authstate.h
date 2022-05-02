/**
* This abstract class provides an interface between AuthUI and various
* visual states associated with feedback provided to the user. Each AuthState
* overrides methods that define what changes should be made to the user interface
* how long the state should remain on screen, plus any logging associated with the
* event that brought about the state.
* @brief Header for visual authentication state in AuthUI.
* @author Austin Hatherell
*
*/

#ifndef AUTH_STATE_H
#define AUTH_STATE_H

#include <unistd.h>

#include <QApplication>

#include "record.h"
#include "authui.h"
#include "logger.h"

class AuthUI; // Forward declaration

class AuthState {
	public:
		AuthState();
		void activate(Record *user=nullptr); // Calls updateUI(), logEvent(), wait()
		~AuthState();

	protected:
		int duration; // How long, in seconds, to display this screen before resetting
		AuthUI *ui; // Pointer to UI, which has public mutators to change appearance

	private:
		void sleepDuration(); // Ensure the state is displayed for minimum duration
		void resetUI();
		virtual void logEvent(Record *user=nullptr) = 0; // Logging behaviour for event assoc. w/ this state
		virtual void updateUI(Record *user=nullptr) = 0; // Behaviour to alter AuthUI appearance for this state
};

#endif
