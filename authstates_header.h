/**
* These concrete classes implement an interface between AuthUI and various
* visual states associated with feedback provided to the user. Each AuthState
* overrides methods that define what changes should be made to the user interface
* how long the state should remain on screen, plus any logging associated with the
* event that brought about the state.
* @brief Header for visual authentication state implementations in AuthUI.
* @author Austin Hatherell
*/

#ifndef AUTHSTATES_HEADER
#define AUTHSTATES_HEADER

#include "authstate.h"

class AuthStateWaiting : public AuthState{
	public:
		AuthStateWaiting();

	private:
		void logEvent(Record *user=nullptr);
		void updateUI(Record *user=nullptr);
};


class AuthStateSuccess : public AuthState{
	public:
		AuthStateSuccess();

	private:
		void logEvent(Record *user=nullptr);
		void updateUI(Record *user=nullptr);
};


class AuthStateDeniedInvalid : public AuthState{
	public:
		AuthStateDeniedInvalid();

	private:
		void logEvent(Record *user=nullptr);
		void updateUI(Record *user=nullptr);
};


class AuthStateDeniedTime : public AuthState{
	public:
		AuthStateDeniedTime();

	private:
		void logEvent(Record *user=nullptr);
		void updateUI(Record *user=nullptr);
};


class AuthStateDeniedFull : public AuthState{
	public:
		AuthStateDeniedFull();

	private:
		void logEvent(Record *user=nullptr);
		void updateUI(Record *user=nullptr);
};


class AuthStateExit : public AuthState{
	public:
		AuthStateExit();

	private:
		void logEvent(Record *user=nullptr);
		void updateUI(Record *user=nullptr);
};

#endif
