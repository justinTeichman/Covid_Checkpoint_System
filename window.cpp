/**
 * The Window class is responsible for displaying something to the user. The user will see whatever the current state of Window is.
 * Window has 4 states, authui, mainui, loginui, and adminui. The default is mainui.
 * mainui -> loginui
 * 	  -> authui
 * loginui -> mainui
 * 	   -> adminui
 * adminui -> mainui
 * 	   -> authui
 * authui -> mainui
 * @brief Window is what is displayed to the user. It can switch between displaying four states: Main, Admin, Auth, and Login.
 * @author Austin Hatherell, Justin Weller, Nicolas Jacobs
 * @date 2021-11-09
 */

#include "window.h"

/** 
 * Singleton "Constructor"
 * When the program needs access to the Window class, this will be called.
 * Because of the Singleton design pattern, only one Window can ever exist.
 * @brief A singleton accessor.
 * @return The same instance of the window class.
 * */
Window& Window::getInstance()
{
	static Window instance;
	return instance;
}

/**
 * Constructor
 * Window utilizes the Singleton design pattern so only one Window can be created.
 * @param *parent The QWidget it inherits from.
 * @brief The constructor of window.
 * */
Window::Window(QWidget *parent) : QMainWindow(parent)
{
	authUIWidget = AuthUI::getInstance();
	mainUIWidget = MainUI::getInstance();
	adminUIWidget = AdminUI::getInstance();
	loginUIWidget = LoginUI::getInstance();
	
	setState("main");
}

/**
 * This will return Window's current state.
 * @brief Returns the current state of window.
 * @return The current state of Window.
 * */
std::string Window::getState()
{
	return currentState;
}


/**
 * Set the current state of Window.
 * It will be updated and display a new state after this is called.
 * @param newState The name of the state Window will switch to.
 * @brief Changes the state of window to the state given.
 * */
void Window::setState(std::string newState)
{
	// Ensure widget is no longer parented to Window so that it's not
	// destroyed when a new one becomes CentralWidget
	authUIWidget->setParent(nullptr);
	mainUIWidget->setParent(nullptr);
	adminUIWidget->setParent(nullptr);
	loginUIWidget->setParent(nullptr);

	//Check for what type of state is being changed to
	if(newState == "auth")
	{
		setCentralWidget(authUIWidget);
		authUIWidget->setFocus();
		authUIWidget->activate();

		// Start the logging session (session end is handled inside AuthUI::toMain())
		Logger::instance().start();
		Logger::instance().date();
		Logger::instance().roomSize(std::to_string(authUIWidget->getCapacity()));

		#ifdef USING_CAMERA

		// Start the camera
		while(!authUIWidget->shouldInterruptCamera())
		{
			// TODO: start() needs to be organized inside an object or namespace
			start();

			// TODO: need some mechanism to interrupt the camera while it's
			// still waiting for a code inside start(), which is blocking

			if(authUIWidget->isAvailable())
			{
				// TODO: toQRCode() needs to be organized inside an object or namespace
				authUIWidget->authenticate(toQRCode());
			}
		}

		#endif
	}
	else if(newState == "admin")
	{
		setCentralWidget(adminUIWidget);

		// When switching to the admin state, the list of logs in the comboBox must be 
		// refreshed in case a new log was created while the program was running
		adminUIWidget->updateLogList(); 
	}		
	else if (newState == "main")
	{
		setCentralWidget(mainUIWidget);
	}
	else if (newState == "login")
	{
		setCentralWidget(loginUIWidget);
		setStyleSheet("background-color: #ffcf88;");
	}

	currentState = newState;	
}

/**
 * Destructor
 * @brief Destroys window and the four states
 * */
Window::~Window(){
	// currentState will be deleted by its parent, but the others are
	// orphans so we need to delete them manually
	if(currentState != "auth") delete authUIWidget;
	if(currentState != "admin") delete adminUIWidget;
	if(currentState != "main") delete mainUIWidget;
	if(currentState != "login") delete loginUIWidget;
}
