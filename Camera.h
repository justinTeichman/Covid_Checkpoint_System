/**
 * This represents the camera that the system uses to take a picture of the QR code.
 * All methods and variables that the camera uses are defined here.
 * @brief Header file of the camera class.
 * @author Liam Garrett
 * */

#ifndef CAMERA_H
#define CAMERA_H


#include <iostream>
#include <string>
#include <Python.h>
#include "qrcode.h"


class Camera{
	private:
		bool running;
		const char* data;
		QRCode qr;
	public:
		void start();
		void stop();
		bool isRunning();
		QRCode toQRCode();

};

#endif
