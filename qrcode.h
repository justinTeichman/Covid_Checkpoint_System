/**
 * Header for QRCode class. QRCode instances are created when the camera recognizes
 * a QR code, providing a standard datatype for the many other classes that depend on
 * the data read from QR codes.
 * @brief The header file for the qrcode class.
 * @author Liam Garrett
 */

#ifndef QRCODE_H
#define QRCODE_H

#include <ctime>
#include <string>

class QRCode{
	private:
		std::string data;		
		std::time_t creationTime;
	public:
		QRCode();
		QRCode(std::string data);
		std::string getData();
		void setData(std::string data);
		void setCreationTime();
		std::time_t getCreationTime();
};

#endif
