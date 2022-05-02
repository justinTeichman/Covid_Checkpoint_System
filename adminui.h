/**
 * Description: This adminui.h file declares the class blueprint of the
 * AdminUI class which is used for creating the Admin GUI. It also 
 * includes all the necessary libraries and files for this class.
 * @brief The header file for the AdminUI class.
 * @author Justin Teichman, Justin Weller
 * @date 2021-11-09
*/

// Include Guards
#ifndef ADMINUI_H
#define ADMINUI_H

// Include all the required system and standard libraries
#include <QAction>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QTextBrowser>
#include <QMenuBar>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <QDateTimeEdit>
#include <QChartView>
#include <QtCharts>
#include <QList>
#include <QtGlobal>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>
#include <math.h>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string.hpp>

// This is the blueprint for the AdminUI class
class AdminUI : public QWidget{

    // Declares all the public members within the class
    public:
        static AdminUI *getInstance();

        ~AdminUI();
        std::string cleanFormat(std::string);
        void updateLogList();

    // Declares all the private members which require QT signals to execute their action
    private slots:
        void addRec();
        void deleteSpecRec();
        void clearLineEdit();
        void searchRec();
        void fillEditor(QListWidgetItem *);
        void editRec();
        void cleanWindow();
        void toMain();
        void toAuth();
        bool valiDate(std::string date);
        void computeAnalysis();

        std::vector<std::string> tokenize(std::string const &str);
        void attendanceAnalysis(std::string);
        void admissionAnalysis(std::string);
        void timeAnalysis(std::string);


    // Declares all the private members within the class
    private:
        AdminUI(QWidget *parent = nullptr);

        static AdminUI *instance;

        bool isrecordSelected; 
        void createMenu();
        void createCommandWindow();
        void createVaxWindow();
        void createAnalysis();
        void createLogWindow();
        void displayLog();
        
        
	    QPushButton *toMainButton;
	    QPushButton *toAuthButton;

        QMenuBar *menuBar; 
        QGroupBox *horizontalGroupBox;
        QGroupBox *gridGroupBox;
        QGroupBox *formGroupBox;
        QGroupBox *loginConfigBox;
        QListWidget *smallEditor;
        QChartView  *analysisWindow;
        

        QLabel *id_label;
        QLabel *fName_label;
        QLabel *lName_label;
        QLabel *twoDose_label;
        QLabel *attr5_label;
        QLabel *attr6_label;
        QLabel *attr7_label;
        QLabel *attr8_label;
        QLabel *result_label;

        QLineEdit *id_line;
        QLineEdit *fName_line;
        QLineEdit *lName_line;
        QLineEdit *twoDose_line;

        QPushButton *add;
        QPushButton *del;
        QPushButton *search;
        QPushButton *edit;
        QPushButton *clearRec;
        QPushButton *clearWindow;
        QPushButton *clear;
        QPushButton *execute;
        QPushButton *generateLogSummary;

        QComboBox *logSessions;
        QComboBox *logSelectA;
        QComboBox *analysis;

        QTextBrowser *logOutput;

        QListWidgetItem *recordSelected;

        QMenu *fileMenu;
	QAction *homeAction;
	QAction *authAction;
        
};

// Include the other required classes
#include "record.h"
#include "database.h"
#include <window.h>

#endif // This header has been included
