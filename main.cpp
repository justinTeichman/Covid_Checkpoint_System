/**
 * The main driver of the program. It's only job is to call other functions and not execute any code directly itself.
 * @brief The main program that calls all other parts of the system.
 * @author Austin Hatherell
 * @date 2021-11-09
 */

#include "window.h"
#include <QApplication>

using namespace std;

/**
 * The main driver of the program.
 * Only calls other functions.
 * @brief Calls other methods to do all the work of the system.
 * @param argc The length of the argument array.
 * @param argv The argument array.
 * @return The return code of the system.
 * */
int main(int argc, char **argv){
	Database::instance();
	QApplication app(argc, argv);
	Window &w = Window::getInstance();
	w.showMaximized(); // application should be fullscreen by default
	return app.exec();
}
