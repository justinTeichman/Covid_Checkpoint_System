/**
 * QRCode class. Instances are created when the camera recognizes a QR code,
 * providing a standard datatype for the many other classes that depend on
 * the data read from QR codes.
 * @brief The decoded qrcode and methods required to access it with.
 * @author Liam Garrett
 */

#include "qrcode.h"

/**
 * Constructor
 * This will create a qrcode object when the data attribute is not known.
 * @brief Constructs a qrcode object when no arguments are passed in.
 * */
QRCode::QRCode(){
	this->creationTime = NULL; // set the creation time to null
	this->data = "NULL"; // set the data for the qr code to null
}

/**
 * Constructor
 * Creates a qrcode object when the data attribute is known.
 * @param data The actual qrcode that is encoded in this object.
 * $brief Constructs a qrcode when the code itself is known.
 * */
QRCode::QRCode(std::string data){
	this->creationTime = std::time(nullptr); // set the creation time
	this->data = data; // set the data for the qr code
}

/**
 * Returns the data of the qrcode object.
 * @brief data accessor method.
 * @return The data of the qrcode object.
 * */
std::string QRCode::getData(){
	return data;
}

/**
 * Updates the data attribute of the qrcode object.
 * @brief data mutator method.
 * @param newData The new value of the data field.
 * */
void QRCode::setData(std::string newData){
	data = newData;
}

/**
 * Updates the creation time of the qrcode object.
 * @brief creationTime mutator method.
 * @param data The new creationTime of the qrcode.
 * */
void QRCode::setCreationTime() {
	this->creationTime = std::time(nullptr);
}

/**
 * Returns the creationTime of the qrcode.
 * @brief creationTime mutator method.
 * @return The creationTime of the qrcode object.
 * */
time_t QRCode::getCreationTime(){
	return creationTime;	
}

