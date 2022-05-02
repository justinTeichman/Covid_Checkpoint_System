/**
 * This is the header file for the logger class.
 * All variables and methods used by the logger class are defined here.
 * @brief The header file for the logger class.
 * @author Nicolas Jacobs
 * */
#ifndef LOGGER_H
#define LOGGER_H

#include <cstring>
#include <fstream>
#include <time.h>
#include <ctime>

class Logger
{
	public:
		virtual ~Logger();
		static const Logger& instance();

		const Logger& admit(const std::string& message) const;
		const Logger& start() const;
		const Logger& end() const;
		const Logger& date() const;
		const Logger& roomSize(const std::string& message) const;
		const Logger& deniedDate(const std::string& message) const;
		const Logger& deniedQRCode() const;
		const Logger& deniedFull(const std::string& message) const;
		const Logger& exit(const std::string& message) const;

		const Logger& operator<<(const std::string& message) const;

	protected:
		Logger();

	private:
		//Methods
		const Logger& log(const std::string& code, const std::string& message) const;
		const Logger& logTime() const;	
		Logger(const Logger& other) {};
		Logger& operator=(const Logger& other) {};
		std::string getTime(bool, bool, bool, bool) const;

		//Variables
		mutable std::ofstream _output;
		static const Logger* _instance;

		//Codes
		std::string admitCode = "#admit";
		std::string startCode = "#starttime";
		std::string endCode = "#endtime";
		std::string dateCode = "#date";
		std::string roomSizeCode = "#roomsize";
		std::string deniedDateCode = "#denieddate";
		std::string deniedQRCodeCode = "#deniedqrcode";
		std::string deniedFullCode = "#deniedfull";
		std::string exitCode = "#exit";
};

#endif
