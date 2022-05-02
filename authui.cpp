/**
 * This (singleton) class contains all of the logic associated with authenticating
 * or rejecting users, and keeps an active AuthState instance in order to provide
 * visual feedback corresponding with its decisionmaking.
 * @brief UI element that provides QR code authentication and feedback.
 * @author Austin Hatherell
 * @date 2021-11-09
 * */

#include "authui.h"

AuthUI *AuthUI::instance = nullptr;

AuthUI* AuthUI::getInstance(){
	if (instance == nullptr)
		instance = new AuthUI();

	return instance;
}

/**
 * This is the constructor for AuthUI, a singleton class, so it is
 * protected and called only in getInstance()
 * @brief Constructor for AuthUI.
 * @param parent     The widget to set as AuthUI's parent widget
 * */
AuthUI::AuthUI(QWidget *parent) : QWidget(parent)
{

	QVBoxLayout *parentLayout = new QVBoxLayout(this); // Top-level layout
	
	heading = new QLabel();
	heading->setAlignment(Qt::AlignCenter);
	parentLayout->addWidget(heading);

	// Create a size policy for the heading
	QSizePolicy headingSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	headingSizePolicy.setVerticalStretch(20);
	heading->setSizePolicy(headingSizePolicy);
	heading->setStyleSheet("font-size: 60px; font-weight: bold;");

	QFrame *sublayoutFrame = new QFrame();
	sublayoutFrame->setStyleSheet("margin-bottom: 20px");
	parentLayout->addWidget(sublayoutFrame);

	QHBoxLayout *sublayout = new QHBoxLayout(sublayoutFrame);

	// Create a size policy for the sublayout
	QSizePolicy sublayoutSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sublayoutSizePolicy.setVerticalStretch(80);
	sublayoutFrame->setSizePolicy(sublayoutSizePolicy);

	// DETAIL SIDE -- the side of the sublayout where the usage information
	// and detailed feedback explanation is displayed
	detailSideFrame = new QFrame();
	sublayout->addWidget(detailSideFrame);

	// Create a size policy for the detail side
	QSizePolicy detailSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	detailSizePolicy.setHorizontalStretch(60);
	detailSizePolicy.setHeightForWidth(true);
	detailSideFrame->setSizePolicy(detailSizePolicy);

	QVBoxLayout *detailSideLayout = new QVBoxLayout(detailSideFrame);
	detailSideLayout->setSpacing(0);
	
	QSpacerItem *spacer1 = new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	detailSideLayout->addItem(spacer1);

	primaryText = new QLabel();
	primaryText->setStyleSheet("font-size: 30px;");
	primaryText->setWordWrap(true);
	detailSideLayout->addWidget(primaryText);

	secondaryText = new QLabel();
	secondaryText->setStyleSheet("font-size: 25px; padding-left: 80px;");
	secondaryText->setWordWrap(true);
	secondaryText->setTextFormat(Qt::RichText);
	detailSideLayout->addWidget(secondaryText);
	
	QSpacerItem *spacer2 = new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	detailSideLayout->addItem(spacer2);

	// Vertical line divider
	QFrame *verticalLine = new QFrame();
	verticalLine->setFrameShape(QFrame::VLine);
	verticalLine->setLineWidth(3);
	sublayout->addWidget(verticalLine);

	// STATUS SIDE -- the side of the sublayout where the non-generic feedback
	// is shown (user's name and student number, the current room capacity, etc.)
	statusSideFrame = new QFrame();
	sublayout->addWidget(statusSideFrame);

	// Create a size policy for the detail side
	QSizePolicy statusSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	statusSizePolicy.setHorizontalStretch(40);
	statusSideFrame->setSizePolicy(statusSizePolicy);

	QVBoxLayout *statusSideLayout = new QVBoxLayout(statusSideFrame);

	QSpacerItem *spacer3 = new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	statusSideLayout->addItem(spacer3);

	userNameLabel = new QLabel();
	userNameLabel->setStyleSheet("font-size: 35px; font-weight: bold;");
	userNameLabel->setAlignment(Qt::AlignCenter);
	statusSideLayout->addWidget(userNameLabel);

	userStudentNumberLabel = new QLabel();
	userStudentNumberLabel->setStyleSheet("font-size: 25px;");
	userStudentNumberLabel->setAlignment(Qt::AlignCenter);
	statusSideLayout->addWidget(userStudentNumberLabel);

	statusIconLabel = new QLabel();
	statusIconLabel->setAlignment(Qt::AlignCenter);
	statusSideLayout->addWidget(statusIconLabel);

	QLabel *occupancyLabelHeading = new QLabel("Room occupancy");
	occupancyLabelHeading->setStyleSheet("font-size: 25px;");
	occupancyLabelHeading->setAlignment(Qt::AlignCenter);
	statusSideLayout->addWidget(occupancyLabelHeading);

	capacity = 150;

	occupancyLabel = new QLabel(QString::fromStdString("0/") + QString::number(capacity));
	occupancyLabel->setStyleSheet("font-size: 40px;");
	occupancyLabel->setAlignment(Qt::AlignCenter);
	statusSideLayout->addWidget(occupancyLabel);

	QSpacerItem *spacer4 = new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	statusSideLayout->addItem(spacer4);

	this->setFocusPolicy(Qt::StrongFocus);

	interruptCamera = false;

	// Because the constructor of AuthStateWaiting tries to use AuthUI::getInstance()
	// to get a reference to the object we're currently constructing, we need to make "instance"
	// point to this object even before this constructor finishes and returns to the first ever
	// getInstance() call. Otherwise we'd have an infinite loop of constructors like so:
		// AuthState::getInstance() -> AuthState::AuthState() ->
		// AuthStateWaiting::AuthStateWaiting() -> AuthState::getInstance() ->
		// AuthState::AuthState() -> ...
	instance = this;

	currentState = nullptr;
	setState(new AuthStateWaiting);
	available = true;
}

/**
 * This method returns the capacity of the room, i.e. how many students may occupy it
 * at the same time.
 * @brief Get the room's current capacity.
 * @return The capacity of the room
 */
int AuthUI::getCapacity(){
	return capacity;
}


/**
 * Change the text of the large, bold heading in the UI to a given string.
 * @brief Set the heading at top of UI.
 * @param string    New heading text.
*/
void AuthUI::setHeading(std::string text){
	QString s = QString::fromStdString(text);
	heading->setText(s);
}


/**
 * This method changes the larger block of text on the left side of the UI,
 * where the primary explanation for why a certain state was triggered is
 * displayed. 
 * @brief Set main detail text in UI.
 * @param text    New primary text
 */
void AuthUI::setPrimaryText(std::string text){
	QString s = QString::fromStdString(text);
	primaryText->setText(s);
}


/**
 * This method changes the smaller block of text on the left side of the UI,
 * where some additional context to support the primary text (see setPrimaryText)
 * can be included.
 * @brief Set secondary detail text in the UI.
 * @param text    New secondary text
 */
void AuthUI::setSecondaryText(std::string text){
	QString s = QString::fromStdString(text);
	secondaryText->setText(s);
}


/**
 * This method changes the background colour of the UI. This colour should be
 * easily identified with whatever type of response was generated. For example,
 * states indicating successful authentication should be green, and states that
 * deny entry should be red.
 * @brief Set background colour in the UI.
 * @param color    New background color (must be CSS color, e.g. "green" or #3dc64f).
*/
void AuthUI::setBackgroundColor(std::string color){
	QString s = QString::fromStdString(color);
	setStyleSheet("background-color: " + s + ";");
	statusSideFrame->setStyleSheet("background-color: " + s + ";");
	detailSideFrame->setStyleSheet("background-color: " + s + "; padding: 20px;");
}


/**
 * This method changes the username in the UI. This should correspond to the
 * first name and last name attributes of the user record (if a user was recognized
 * in the creation of the state); if no user was recognized, there's no need to call
 * this method.
 * @brief Set username in the UI.
 * @param text    New username.
 */
void AuthUI::setUserName(std::string text){
	QString s = QString::fromStdString(text);
	userNameLabel->setText(s);
}


/**
 * This method changes the student number in the UI. This is currently unused
 * because the student record system doesn't have a student number field.
 * @brief Set student number in UI.
 * @param text    New student number (as a string)
 */
void AuthUI::setUserStudentNumber(std::string text){
	QString s = QString::fromStdString(text);
	userStudentNumberLabel->setText(s);
}


/**
 * This method sets an image or GIF as the main status icon in the UI on the
 * right side. It should be a large (at least 200px by 200px) file, as it
 * takes up a decent portion of the UI. Example status icons might be a check mark,
 * big X, or a GIF of a loading animation. See resources/ for examples.
 * @brief Set status icon in the UI.
 * @param location    Relative path from source root to the image or GIF file
*/
void AuthUI::setStatusIcon(std::string location){
	if(location == ""){
		statusIconLabel->setMovie(nullptr);
		QPixmap image;
		statusIconLabel->setPixmap(image);
		return;
	}

	QString qStringLocation = QString::fromStdString(location);

	std::string lastFourChars;
	if(location.size() >= 4)
		lastFourChars = location.substr(location.size() - 4, 4);
	else
		lastFourChars = "";

	// If it's an animated gif, then must be init'd as QMovie, otherwise (e.g. if .jpg or .png) it's a QPixmap
	if(lastFourChars == ".gif" || lastFourChars == ".GIF"){
		QMovie *gif = new QMovie(qStringLocation);
		statusIconLabel->setMovie(gif);
		gif->start();
	}else{
		QPixmap image(qStringLocation);
		statusIconLabel->setPixmap(image.scaled(200, 200, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
	}
}

/**
 * This method sets the current occupancy of the room. It should only be used
 * internally by AuthUI's logic as a part of authenticate() calls. This doesn't
 * update the vector containing the occupants of room (the logical occupancy)
 * but rather the occupancy indicated visually in the UI. It is displayed as a string
 * of the form occupancy/capacity, e.g. "102/150".
 * @brief Set occupancy of the room in the UI.
 * @param occupancy   New occupancy
 */
void AuthUI::setOccupancy(int occupancy){
	occupancyLabel->setText(QString::number(occupancy) + QString::fromStdString("/") + QString::number(capacity));
}

/**
 * This method returns the result of subtracting a date (in YYYY/MM/DD) from
 * the current operating system time, in seconds. It will return negative seconds
 * if the date is in the future.
 * @brief Calculate number of seconds between current system time and some date.
 * @param date    YYYY/MM/DD date string to subtract
 * @return seconds elapsed since date (based on current OS time). If the date is in
           the future, the date is negative.
 */
int AuthUI::secondsToNow(std::string date){
	std::time_t currentTime;
	std::time(&currentTime);

	std::tm givenTime;
	givenTime.tm_sec = 0;
	givenTime.tm_min = 0;
	givenTime.tm_hour = 0;
	givenTime.tm_year = atoi(date.substr(0, 4).c_str()) - 1900;
	givenTime.tm_mon = atoi(date.substr(5, 2).c_str()) - 1;
	givenTime.tm_mday = atoi(date.substr(8, 2).c_str());
	
	int difference = (int) std::difftime(currentTime, std::mktime(&givenTime));
	return difference;
}

/**
 * This method implements the logic that checks whether the user associated
 * with a QR code should be allowed entry to the room (based on vaccination
 * status and current room occupancy with respect to capacity), then activates
 * an AuthState which handles the visual feedback associated with this use case.
 * @brief Authenticate a QR code and display feedback in UI.
 * @param qr    The QR code to check
 */
void AuthUI::authenticate(QRCode qr){
	available = false;
	if(Database::instance().findId(qr.getData())){ // If user was found in database
		Record user = Database::instance().searchById(qr.getData());

		// Check if this user is already an occupant
		bool found = false;
		int indexFound = -1;
		for(int i = 0; i < occupants.size(); i++){
			if(user == occupants.at(i)){
				found = true;
				indexFound = i;
				break;
			}
		}

		if(found){ // If already an occupant, let them exit
			occupants.erase(occupants.begin() + indexFound);
			setOccupancy(occupants.size());
			setState(new AuthStateExit, &user);
		}else if(occupants.size() >= capacity){ // If room full, error
			setState(new AuthStateDeniedFull, &user);
		}else{
			// Check if (1209600 secs = 14 days) has passed since vaccination
			if(secondsToNow(user.getDate()) >= 1209600){
				// If so, allow entry
				occupants.push_back(user);
				setOccupancy(occupants.size());
				setState(new AuthStateSuccess, &user);
			}else{
				// Otherwise, deny
				setState(new AuthStateDeniedTime, &user);
			}
		}
	}else{ // Deny
		setState(new AuthStateDeniedInvalid, nullptr);
	}

	// Revert to waiting state afterwards
	setState(new AuthStateWaiting);
	available = true;
}

/*
 * When AuthUI stops being the main widget in the UI, then there is no need for
 * the camera to keep looking for QR codes. This method provides a way for the
 * camera to ask whether it should interrupt its image-recognition and stop running.
 * @brief Ask AuthUI whether it still needs the camera.
 * @return True if the camera should stop running; false otherwise.
 */
bool AuthUI::shouldInterruptCamera(){
	return interruptCamera;
}

/*
 * When AuthUI is already displaying feedback for a previously-recognized QR code,
 * it isn't available to accept new input and the camera should disregard whatever
 * it sees durring this time. This method indicates whether AuthUI is available.
 * @brief Ask AuthUI whether it's available to handle QR code input.
 * @return True if AuthUI can receive a QR code; false otherwise.
 */
bool AuthUI::isAvailable(){
	return available;	
}

/**
 * This returns the current AuthState of AuthUI, that being whatever state is
 * currently activated and responsible for providing visual feedback to the
 * user in response to whatever event triggered said state chage.
 * @brief Get current AuthState of AuthUI.
 * @return The active AuthState in AuthUI.
 * */
AuthState* AuthUI::getAuthState()
{
	return currentState;
}


/**
 * This sets AuthUI's state to whatever AuthState is passed into the method,
 * then activates that state so that the UI displays the appropriate feedback
 * and blocks for a specified amount of time. Some AuthStates require a user
 * record in order to properly update the UI (e.g. AuthStateSuccess displays
 * the user's name), so this must also be provided in order to change/activate
 * the state. However, since not all AuthStates require this information
 * (and it isn't always available), the user record may also be a null pointer.
 * @brief Set current AuthState of AuthUI.
 * @param newState    The state to change to and activate.
 * @param user    The user whose information to display (default: nullptr).
*/
void AuthUI::setState(AuthState *newState, Record *user){
	delete currentState;
	currentState = newState;
	currentState->activate(user);
}

/**
 * This method tells AuthUI to enter a state where it is allowed to
 * receive and handle inputs from the camera -- it should only be
 * called when AuthUI becomes visible in the window.
 * @brief Wake up AuthUI.
 */
void AuthUI::activate(){
	interruptCamera = true;
	available = true;
}

/**
 * For debugging and testing purposes, there are keybindings that simulate
 * the camera having recognized a QR code without actually needing to use
 * a camera. See the README for more information. This method provides this
 * behaviour whenever key-release input is detected by Qt.
 * @brief Implementation override for key release events.
 * @param event    QKeyEvent containing information about the key-release.
 */
void AuthUI::keyReleaseEvent(QKeyEvent *event){
	switch(event->key()){
		case 49: // "1" key -- simulate valid user
			authenticate(QRCode("1202"));
			break;
		case 50: // "2" key -- simulate user vaxxed < 14 days
			authenticate(QRCode("1203"));
			break;
		case 51: // "3" key -- simulate invalid QR code
			authenticate(QRCode("Hello world!"));
			break;
		case 52: // "4" key -- fill the room
			while(occupants.size() < capacity)
				occupants.push_back(Record());
			setOccupancy(occupants.size());
			break;
		case 53: // "5" key -- empty the room
			occupants.clear();
			setOccupancy(occupants.size());
			break;
		case 16777216: // "ESC" key
			toMain();
			break;
	}
	
	setState(new AuthStateWaiting);
}

/**
 * This method changes the window's main UI element so that
 * it shows the main menu, effectively ending the behaviour of AuthUI.
 * However, this is *not* a destructor -- AuthUI remains in memory
 * even when not visible, although the behaviour defined in this method
 * should prevent it from doing anything interesting until it becomes
 * visible again. This method effectively ends a "session" -- it 
 * empties the room and lets the logger know to use this as a barrier
 * between files.
 * @brief Return to main menu.
 */
void AuthUI::toMain()
{
	interruptCamera = true;
	Window &switchWindow = Window::getInstance();
	switchWindow.setState("main");
	occupants.clear();
	setOccupancy(occupants.size());
	Logger::instance().end();
}

