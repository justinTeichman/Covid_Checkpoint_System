/**
 * The logger class of the system.
 * This will output information about a session to a log file.
 * A log file is created when a user enters the AuthUI state, and the file is closed when they exit the state.
 * A line of text is added to the log whenever a user does a certain action.
 * Lines are added chronologically. The first line will always be "#starttime" and the final will always be "#endtime".
 * This class is based on code provided by Professor Katchabaw.
 * @brief This class can log information about a session to a log file.
 * @author Nicolas Jacobs
 * */

#include "logger.h"
using namespace std;

//Variable that tells Logger if its been created yet.
const Logger* Logger::_instance = NULL;

/**
 * Singleton constructor
 * Only once instance of the logger can ever exist at once because of its use of the singleton design pattern.
 * This will return a reference to the only logger that exists.
 * @brief Returns a reference to the sole instance of the logger class.
 * @return A pointer to the logger instance.
 * */
const Logger& Logger::instance()
{
	if (_instance == NULL)
	{
		_instance = new Logger();
	}

	return *_instance;
}

/**
 * Constructor
 * Open the file for editing.
 * This will create a logger object, meaning it can now begin logging information.
 * Because of singleton, this can only be called once.
 * @brief Constructs the logger object.
 * */
Logger::Logger()
{

}

/**
 * Destructor
 * Closes the file as the Logger is deleted.
 * @brief Destorys the logger object and closes the file.
 * */
Logger::~Logger()
{
	this->_output.close();
}

/**
 * Admit a user.
 * code: #admit
 * Prints a line to the log file saying that a person has been admitted to the session.
 * @brief Prints "#admit message" to the log file.
 * @param message The id of the user who was admitted into the session.
 * @return The pointer to the logger class.
 * */
const Logger& Logger::admit(const string& message) const
{
	return this->log(admitCode, message);
}

/**
 * Start a session.
 * code: #starttime
 * Prints a line to the log file saying that the session has begin.
 * @brief Prints "#starttime" to the log file.
 * @return The pointer to the logger class.
 * */
const Logger& Logger::start() const
{
	this->_output.open("./Logs/LOG_" + Logger::getTime(true, true, true, true) + ".txt");
        return this->log(startCode, "");
}

/**
 * End a session.
 * code: #endtime
 * Prints a line to the log file saying that the session has ended.
 * Closes the file because there is no reason to add to it anymore.
 * @brief Prints "#endtime" to the log file.
 * @return The pointer to the logger class.
 * */
const Logger& Logger::end() const
{
        this->log(endCode, "");
	this->_output.close();
	return *this;
}

/**
 * Write the current date yyyy-mm-dd.
 * code: #date
 * Prints a line to the log file giving the current date of the session.
 * @brief Prints "#date yyyy-mm-dd" to the log file.
 * @return The pointer to the logger class.
 * */
const Logger& Logger::date() const
{
        string str = Logger::getTime(true, true, true, false);

	return this->log(dateCode, str);
}

/**
 * Write the room size of the session.
 * code: #roomsize
 * Prints a line to the log file saying the room size of the current session.
 * @brief Prints "#roomsize message" to the log file.
 * @param message The id of the user who was denied.
 * @return The pointer to the logger class.
 * */
const Logger& Logger::roomSize(const string& message) const
{
        return this->log(roomSizeCode, message);
}

/**
 * A user has been denied because they were not vaccinated over 2 weeks ago.
 * code: #denieddate
 * Prints a line to the log file saying a person was denied entry because they have not been vaccinated long enough.
 * @brief Prints "#denieddate message" to the log file.
 * @param message The id of the user who was denied.
 * @return The pointer to the logger class.
 * */
const Logger& Logger::deniedDate(const string& message) const
{
        return this->log(deniedDateCode, message);
}

/**
 * A user has been denied because the QR code was not recognized as a user in the database.
 * code: #deniedqrcode
 * Prints a line to the log file saying a person has been denied entry because they did not use a valid qrcode.
 * The system was not able to recognized as a valid qrcode.
 * @brief Prints "#deniedqrcode" to the log file.
 * @return The pointer to the logger class.
 * */
const Logger& Logger::deniedQRCode() const
{
        return this->log(deniedQRCodeCode, "");
}

/**
 * A user has been denied because the room is already at capacity.
 * code: #deniedfull
 * Prints a line to the log file saying that a user has been denied entry because the session is already full.
 * @brief Prints "#deniedfull message" to the log file.
 * @param message The id of a user who tried to enter the full session.
 * @return The pointer to the logger class.
 * */
const Logger& Logger::deniedFull(const string& message) const
{
        return this->log(deniedFullCode, message);
}

/**
 * A user who previously entered the room has exited the room.
 * code: #exit
 * Prints a line to the log file saying that a person has left the session.
 * @brief Prints "#exit message" to the log file.
 * @param message The id of the user leaving a session.
 * @return The pointer to the logger class.
 * */
const Logger& Logger::exit(const string& message) const
{
	return this->log(exitCode, message);
}

/**
 * Write something to the file.
 * Prints a combination of CODE and MESSAGE to the file.
 * @brief Prints a line of text to the log file.
 * @param code The code of what method the user called (#admit, #exit, #starttime, etc.)
 * @param message The message of what needs to be logged.
 * @return A pointer to the logger class.
 * */
const Logger& Logger::log(const string& code, const string& message) const
{
	Logger::logTime();
	this->_output << code << " " << message << endl;

	return *this;
}

/**
 * Log the current time to the log file.
 * Everything logged to the log file will have the time listed first.
 * Example: 20-14-09 #exittime 3415
 * This line means that user 3415 left the session at 8:14:09 PM.
 * @brief Prints the time a command is being logged to the log file.
 * @return A pointer to the logger class.
 * */
const Logger& Logger::logTime() const
{
	string str = Logger::getTime(false, false, false, true);

	//Print the time to the file
	this->_output << str << " ";

	return *this;
}

/**
 * Return the time so it can be used by parts of the logger.
 * The method can be called such that the user has control over which parts of the date get returned.
 * For example, they can ask for the format yyyy-dd, mm-dd_hh-mm-ss, dd_hh-mm-ss, or any other combination.
 * The time scale gets smaller the farther right the line goes.
 * Time (hh-mm-ss) uses the delimiter '-' instead of ":" because Windows does not allow ":" in file names.
 * @brief Returns different combinations of the date and time.
 * @param year Return the year?
 * @param month Return the month?
 * @param day Return the day?
 * @param timeSec Return the time?
 * @return The current date and time of the system.
 * */
string Logger::getTime(bool year, bool month, bool day, bool timeSec) const
{
	//Variables
	time_t now = time(0);
	string str;
	bool dash = false;

	tm *ltm = localtime(&now);

	//Print various components of tm structure.
	if (year)	//yyyy
	{
		str += to_string(1900 + ltm->tm_year);
		dash = true;
	}

	if (month)	//mm
	{
		if (dash)
			str += "-";

		str += to_string(1 + ltm->tm_mon);
		dash = true;
	}

	if (day)	//dd
	{
		if (dash)
			str += "-";

		str += to_string(ltm->tm_mday);
		dash = true;
	}

	if (timeSec)	//hh-mm-ss
	{
		if (dash)
			str += "_";

		if (to_string(ltm->tm_hour).length() == 1)
			str += "0";
		str += to_string(ltm->tm_hour) + "-";
		
		if (to_string(ltm->tm_min).length() == 1)
			str += "0";
		str += to_string(ltm->tm_min) + "-";
	       
		if (to_string(ltm->tm_sec).length() == 1)
			str += "0";
		str += to_string(ltm->tm_sec);
	}

	return str;
}

/**
 * Alternate way of writing to the log file.
 * Overrides the << operator so it will write a message to the log.
 * This method of writing to the log should only be used for debugging purposes.
 * @brief Overrides << so it writes to the log.
 * @param message The message being written into the log.
 * @return A pointer to the logger class.
 * */
const Logger& Logger::operator<<(const string& message) const
{
	return this->log("ALERT ", message);
}
