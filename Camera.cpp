/**
* This class will run the qr code scanner and create a instance of the QRCode class and put the recieved 
* data from the qr code scanner into it for other classes to use.
* @brief Runs the QR code scanner and stores the received data in a QRCode object.
* @author Liam Garrett 
* @date 2021-11-09
*/

#include <iostream>
#include <string>
#include <Python.h>
#include <qrcode.h>

using namespace std;

bool isRunning;
const char* data;
QRCode qr;

/**
 * This function will run the python code for scanning and processing QR codes.
 * @brief Scans and processes QR codes.
*/
void start(){

	PyObject *pModule, *pFunc, *pValue; // 3 PyObjects required for running python file
	Py_Initialize(); // start the python interpreter
	PyRun_SimpleString("import sys");// import the required packages for the python code
	PyRun_SimpleString("import cv2");
	PyRun_SimpleString("import re");
	PyRun_SimpleString("sys.path.append('./home/pi/Desktop/tester')"); // set the working directory on the raspberry pi 
	PyRun_SimpleString("sys.path.append('/home/pi/Desktop/tester')");
	PyRun_SimpleString("sys.path.insert(0,'/home/pi/Desktop/tester')");
	
	pModule = PyImport_ImportModule("qrcode"); // set the name of the python program to be opened
	
	if (pModule) { // if the module imported the proper program
		pFunc = PyObject_GetAttrString(pModule,"func");} // get the function for running the qrcode scanner
	
	if (pFunc) { // if the fuction was imported properly
		pValue = PyObject_CallObject(pFunc, NULL);// execute the function
		isRunning = true; // process is running
	} 
		
    PyObject* repr = PyObject_Repr(pValue); // convert the recieved value into a string 
    PyObject* str = PyUnicode_AsEncodedString(repr, "utf-8", "~E~");
	data = PyBytes_AS_STRING(str); // set the string for the new QR code
    printf("QR code info %s\n", data);
	qr.setData(data);
	qr.setCreationTime();
	Py_Finalize(); // close the python interpreter
	isRunning = false;
}

/**
 * Function for stopping the qrcode scanning.
 * @brief Stops the QR code scanning.
*/
void stop() {

}

/**
 * Function for returning whether or not the scanner is running.
 * @brief Returns if the scanner is running or not.
 * @return A bool which is true if the scanner is running, else false
*/
bool isRunning() { // return if the program is running or not
	return isRunning;
}

/**
 * Function for returning the QRCode instance if it has been created.
 * @brief Returns the QRCode instance if created.
 * @return QRCode qr or returns NULL
*/
QRCode toQRCode() {// return if the value of the QR code

	if ( strcmp(qr.getData(),"NULL") == 0 ) {
		return NULL;
	}
	else {
		return qr;
	}
}
