/** 
 * This adminui.cpp file implements the AdminuUI class 
 * to create a QT Graphical User Interface for the adminstrator. 
 * @brief Creates the GUI for the Admin state in the system.
 * @author Justin Teichman, Justin Weller
 * @date 2021-11-09
 */
#include "adminui.h"

// Points to the singleton instance of this class
AdminUI *AdminUI::instance = nullptr;

/**
 * This is the Singleton "Constructor". To access this class, this static
 * method must be called to return an instance of this class. Because of the Singleton 
 * design pattern, only one instance of this class can ever exist.
 * @brief The Singleton accessor.
 * @return The singleton instance of this class called "instance"
 */
AdminUI *AdminUI::getInstance()
{
    if(instance == nullptr)
    {
        instance = new AdminUI();
    }
    return instance;
}

/**
 * This is the constructor of the AdminUI class, used to initialize all the GUI
 * elements.
 * @brief The constructor of AdminUI.
 * @param parent The pointer to the parent of the GUI elements.
*/
AdminUI::AdminUI(QWidget *parent):QWidget(parent){
    
    // Admin Ui is divided into 4 sections

    createMenu();   // holds the menu bar that allows user to navigate through the windows
    createCommandWindow();  // holds function buttons for records
    createVaxWindow();  // holds record attributes and query interface
    createLogWindow(); // Creates log session selector, generate button, and the log display window
    createAnalysis();   // holds analysis functions
    

    // attaches sub boxes to the main box
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(horizontalGroupBox, 0, 0, 1, -1);
    mainLayout->addWidget(gridGroupBox, 1, 0, 1, -1);
    mainLayout->addWidget(loginConfigBox, 2, 0, 1, 1);
    mainLayout->addWidget(formGroupBox, 2, 1, 1, 1);
    mainLayout->addWidget(logOutput, 3, 0, 1, 1);
    mainLayout->addWidget(analysisWindow, 3, 1, 1, 1);

    setLayout(mainLayout);
    isrecordSelected = false;

    // Customizes the look of this state
    setStyleSheet("* { background-color: #ffcf88; } "
                    "QLineEdit, QListWidget, QTextBrowser, QTextEdit { background-color: #fce9cc; }");

    connect(add, &QPushButton::pressed, this, &AdminUI::addRec);   // signal is created when user pushes add button
    connect(del, &QPushButton::pressed, this, &AdminUI::deleteSpecRec);    // signal is created when user pushes delete button
    connect(clearRec, &QPushButton::pressed, this, &AdminUI::clearLineEdit);
    connect(search, &QPushButton::pressed, this, &AdminUI::searchRec);
    connect(smallEditor, &QListWidget::itemClicked, this, &AdminUI::fillEditor);
    connect(edit, &QPushButton::pressed, this, &AdminUI::editRec);
    connect(clearWindow, &QPushButton::pressed, this, &AdminUI::cleanWindow);
    connect(execute, &QPushButton::pressed, this, &AdminUI::computeAnalysis);

	//Connect file actions
	connect(homeAction, &QAction::triggered, this, &AdminUI::toMain);
	connect(authAction, &QAction::triggered, this, &AdminUI::toAuth);
}

/**
 * Changes the state of the window to the MainUI class.
 * @brief Changes the state to MainUI.
*/
void AdminUI::toMain(){
	Window &switchWindow = Window::getInstance();
	switchWindow.setState("main");
}

/**
 * Changes the state of the window to the AuthUI class.
 * @brief Changes the state to AuthUI.
*/
void AdminUI::toAuth(){
	Window &switchWindow = Window::getInstance();
	switchWindow.setState("auth");
}    

/**
 * Creates the QMenu sub box in GUI and add navigation buttons
 * @brief Creates the QMenu sub box with navigation buttons.
*/
void AdminUI::createMenu(){
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&COVID-19 Checkpoint System"), this); // title
    homeAction = fileMenu->addAction(tr("&Home"));   // home tab -> link to main window
    authAction = fileMenu->addAction(tr("&Begin Authentication Session"));    // scanner tab -> link to scanner window
    menuBar->addMenu(fileMenu);
}

/**
 * Creates a sub box containing all the function buttons for managing the vax database such as
 * search, add, delete, etc. 
 * @brief Creates a sub box containing the vax database managing buttons.
*/
void AdminUI::createCommandWindow()
{
    horizontalGroupBox = new QGroupBox(tr("Functions"));
    QHBoxLayout *layout = new QHBoxLayout;

    add = new QPushButton(tr("Add"));
    layout->addWidget(add);
    
    del = new QPushButton(tr("Delete"));
    layout->addWidget(del);
    
    search = new QPushButton(tr("Search"));
    layout->addWidget(search);
    
    edit = new QPushButton(tr("Edit"));
    layout->addWidget(edit);
    
    clearRec = new QPushButton(tr("Clear"));
    layout->addWidget(clearRec);

    result_label = new QLabel(tr("Result"));
    result_label->setAlignment(Qt::AlignCenter);
    layout->addWidget(result_label);

    horizontalGroupBox->setLayout(layout);
}

/**
 * Creates window holding query result box when interacting with the command buttons
 * and input lines for parameters.
 * @brief Creates a query result box which gets filled when interacting with the command buttons.
*/
void AdminUI::createVaxWindow()
{
    gridGroupBox = new QGroupBox(tr("COVID-19 VAX Records"));
    QGridLayout *layout = new QGridLayout;

    id_label = new QLabel(tr("Client ID"));
    id_line = new QLineEdit;
    layout->addWidget(id_label, 0 + 1, 0);
    layout->addWidget(id_line, 0 + 1, 1);
    
    fName_label = new QLabel(tr("First Name"));
    fName_line = new QLineEdit;
    layout->addWidget(fName_label, 1 + 1, 0);
    layout->addWidget(fName_line, 1 + 1, 1);

    lName_label = new QLabel(tr("Last Name"));
    lName_line = new QLineEdit;
    layout->addWidget(lName_label, 2 + 1, 0);
    layout->addWidget(lName_line, 2 + 1, 1);
    
    twoDose_label = new QLabel(tr("2nd Dose (Date)"));
    twoDose_line = new QLineEdit;
    layout->addWidget(twoDose_label, 3 + 1, 0);
    layout->addWidget(twoDose_line, 3 + 1, 1);

    clearWindow = new QPushButton(tr("Clear Window"));
    layout->addWidget(clearWindow, 4 + 1, 1);
    
    smallEditor = new QListWidget;      // each record will be inserted into  Qwidgetitem. 
    layout->addWidget(smallEditor, 1, 2, 8, 1); // these records will be related to the queries

    layout->setColumnStretch(1, 10);
    layout->setColumnStretch(2, 20);
    gridGroupBox->setLayout(layout);
}

/**
 * Create the Log Visualization section of the AdminUI
 * containing a log session selector, a display log button, and a window
 * to display the log's contents.
 * @brief Creates the log visualization section of the AdminUI.
*/
void AdminUI::createLogWindow()
{
    loginConfigBox = new QGroupBox(tr("Log Visualization"), this);
    QHBoxLayout *logConfigLayout = new QHBoxLayout(this);

    generateLogSummary = new QPushButton("Display Log", this); // Pressed to display the selected log
    // Whenever this button is pressed, the displayLog function is called
    connect(generateLogSummary, &QPushButton::released, this, &AdminUI::displayLog);
    logConfigLayout->addWidget(generateLogSummary);

    logSessions = new QComboBox(this); // Combo box containing the list of logs for past sessions
    logConfigLayout->addWidget(logSessions);
    updateLogList(); // Creates the list and stores it in the combo box

    loginConfigBox->setLayout(logConfigLayout);
    
    logOutput = new QTextBrowser(this); // Used to display the log contents
    logOutput->setReadOnly(true);
}

/**
 * Updates the list of logs for the past sessions and stores it in the combo box
 * @brief Updates the list of logs able to be selected in the combo box.
*/
void AdminUI::updateLogList()
{
    QDir path("Logs"); // Sets the relative file location for the logs
    QStringList logList = path.entryList(QDir::Files); // Stores the names of all the logs in the string list
    logSessions->clear();
    logSessions->addItems(logList); // Adds all the log names to the combo box
}

/**
 * Upon button pressed, this method fills the log results window with the selected log's 
 * contents for visualization.
 * @brief Fills the log results window with the log's contents.
*/
void AdminUI::displayLog()
{
    QFile file("Logs/" + logSessions->currentText()); // Gets the selected log at the appropriate location
    file.open(QFile::ReadOnly | QFile::Text);
    logOutput->setText(file.readAll()); // Fills the display with the log content
    file.close();
}

/**
 * Creates the analysis window containing analysis function buttons used to configure and display the graphs which
 * summarize the selected log info.
 * @brief Creates the analysis window for configuring and displaying graphs for log data.
*/
void AdminUI::createAnalysis(){
    
    formGroupBox = new QGroupBox(tr("Data Visualization and Computations"));
    QHBoxLayout *comp_layout = new QHBoxLayout;

    execute = new QPushButton(tr("Execute"));
    comp_layout->addWidget(execute);

    logSelectA = new QComboBox(); // Combo box containing the list of logs for past sessions
    comp_layout->addWidget(logSelectA);

    QDir path("Logs"); // Sets the relative file location for the logs
    QStringList logList = path.entryList(QDir::Files); // Stores the names of all the logs in the string list
    logSelectA->addItems(logList); // Adds all the log names to the combo box

    QList<QString> stringsList;
    stringsList.append("Attendance");
    stringsList.append("Acception and Rejection");
    stringsList.append("Length of Stay");

    analysis = new QComboBox();
    analysis->addItems(stringsList);
    comp_layout->addWidget(analysis);

    formGroupBox->setLayout(comp_layout);

    analysisWindow = new QChartView();
}

/**
 * upon execution of the analysis button this method check user input and activates the correct method
 * @brief Calls corresponding analysis method
*/
void AdminUI::computeAnalysis(){
    
    std::string log =  (logSelectA->currentText()).toStdString();
    std::string computation = (analysis->currentText()).toStdString();

    // references analysis combo box and selects corresponding analysis

    if(computation == "Attendance"){
        attendanceAnalysis(log);
        
    }else if(computation == "Acception and Rejection"){
        admissionAnalysis(log);

    }else if(computation == "Length of Stay"){
        timeAnalysis(log);

    }
}

/**
 * This method scans the logs file and processes the data for a line graph showing the attendence of 
 * individuals with respect to time. It then carries out the neccesary computations and renders the graph
 * @param log file to process and scan
 * @brief Produces a line graph showing attendance over the session
*/
void AdminUI::attendanceAnalysis(std::string log){
    std::string start;
    std::string end;
    std::vector<std::string> times;
    std::map<std::string,std::string> admissionTimes;
    std::map<std::string,std::string>::iterator it;
    std::vector<std::string> lineWords;
    
    std::ifstream file("Logs/"+log);

    if(file.is_open()){

        //Scans log file and stores information in corresponding vectors and maps
        std::string line;
        while(std::getline(file,line)){

            lineWords = tokenize(line);
            if(lineWords.size() == 2 && lineWords.at(1) == "#starttime"){
                start = lineWords.at(0);
            }else if(lineWords.size() == 2 && lineWords.at(1) == "#endtime"){
                end = lineWords.at(0);
            }else if(lineWords.size() == 3 && lineWords.at(1) == "#admit"){
                times.push_back(lineWords.at(0));
                admissionTimes.insert({lineWords.at(0),lineWords.at(1)});
            }else if(lineWords.size() == 3 && lineWords.at(1) == "#exit"){
                times.push_back(lineWords.at(0));
                admissionTimes.insert({lineWords.at(0),lineWords.at(1)});
            }
        }

        file.close();

        // Converts string dates from log file into QDateTime objects

        QString start_time = QString::fromStdString(start);
        QDateTime session_start = QDateTime::fromString(start_time, "hh:mm:ss");
        QString end_time = QString::fromStdString(end);
        QDateTime session_end = QDateTime::fromString(end_time, "hh:mm:ss");
        
        QLineSeries *lineSeries = new QLineSeries();
        int capacity = 0;
        qreal yvalue = capacity;
        lineSeries->append(session_start.toMSecsSinceEpoch(),yvalue);
        
        QString tempString;
        QDateTime tempTime;

        // Adds a plot to the graph everytime an event occurs (#admit, #exit)

        for(int i = 0; i < (int)times.size(); i++){
            if(admissionTimes.find(times.at(i))->second == "#admit"){
                capacity++;
            }else{
                capacity--;
            }
                yvalue = capacity;
                tempString = QString::fromStdString(times.at(i));
                tempTime = QDateTime::fromString(tempString,"hh:mm:ss");
                lineSeries->append(tempTime.toMSecsSinceEpoch(),yvalue);
        }

        yvalue = capacity;
        lineSeries->append(session_end.toMSecsSinceEpoch(),yvalue);
        

        // Setting up x axis
        QDateTimeAxis *axisX = new QDateTimeAxis();
        axisX->setFormat("hh:mm:ss");
        axisX->setRange(session_start, session_end);

        // Setting up y axis
        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0, 8);
        axisY->setTickCount(1);
        axisY->setLabelFormat("%d");

        // Adding data, axises to the chart
        QChart *chart = new QChart();
        chart->addSeries(lineSeries);
        chart->setAxisX(axisX,lineSeries);
        chart->setAxisY(axisY,lineSeries);
        chart->setTitle("Room Attendance");
        chart->legend()->hide();

        analysisWindow->setChart(chart);
        
    }
    
}

/**
 * This method scans the logs file and processes the data for a pie graph expressing the time a client 
 * spend inside the checkpoint. It then carries out the neccesary computations and renders the graph
 * @param log file to process and scan 
 * @brief Produces a pie chart showing the time spent inside a checkpoint by individuals.
*/
void AdminUI::timeAnalysis(std::string log){

    std::vector<int> durationValues;
    std::vector<std::string> lineWords;
    std::vector<std::vector<std::string>> logRec;
    std::ifstream file("Logs/"+log);
    
    
    if(file.is_open()){

        std::string line;

        // Save the log file in a vector of vectors for processing later
        while(std::getline(file,line)){

            lineWords = tokenize(line);
           
            if(lineWords.size() == 3 && (lineWords.at(1) == "#admit" || lineWords.at(1) == "#exit")){
                logRec.push_back(lineWords);
            }
        }
        file.close();

        // Search for #admit and #exit entries where they have the same ID and add to vector
        std::vector<std::string> temp;
        for(int i = 0; i < (int)logRec.size(); i++){

            temp = logRec.at(i);

            std::vector<std::string> tempSearch;
            for(int j = i + 1; j < (int)logRec.size(); j++){
                tempSearch = logRec.at(j);
                
                if(temp.at(2) == tempSearch.at(2)){
                    QString start_time = QString::fromStdString(temp.at(0));
                    QDateTime session_start = QDateTime::fromString(start_time, "hh:mm:ss");
                    
                    QString end_time = QString::fromStdString(tempSearch.at(0));
                    QDateTime session_end = QDateTime::fromString(end_time, "hh:mm:ss");
                    
                    qint64 secondsDiff = (session_start.msecsTo(session_end))/1000; // calculates time between entry and exit       
                    durationValues.push_back(int(secondsDiff));           
                }
            
            }

        }

        int underMin = 0; // 60 seconds
        int under5Min = 0; // 300 seconds
        int over5Min = 0;

        // Scan entries and exits and update counters

        for (int i = 0; i < (int)durationValues.size(); i++){
            if(durationValues.at(i) < 60){
                underMin++;
            }else if(durationValues.at(i) < 300){
                under5Min++;
            }else{
                over5Min++;
            }
        }

        float underMinPercent,under5MinPercent,over5MinPercent;

        // Process data for pie chart

        if(underMin == 0){
            underMinPercent = 0;
        }else{
            underMinPercent = ((float)underMin/((float)underMin+(float)under5Min+(float)over5Min))*100;
        }

        if(under5Min == 0){
            under5MinPercent = 0;
        }else{
            under5MinPercent = ((float)under5Min/((float)underMin+(float)under5Min+(float)over5Min))*100;
        }
    
        if(over5Min == 0){
            over5MinPercent = 0;
        }else{
            over5MinPercent = ((float)over5Min/((float)underMin+(float)under5Min+(float)over5Min))*100;
        }

        std::string undermin_num(std::to_string(underMinPercent));
        std::string under5_num(std::to_string(under5MinPercent));
        std::string over5_num(std::to_string(over5MinPercent));

        std::string underMinLabel = "Under 1 minute % "+undermin_num;
        std::string under5MinLabel = "Under 5 minutes % "+under5_num;
        std::string over5MinLabel = "Over 5 minutes % "+over5_num;

        // attach data to the series
        QPieSeries *pieSeries = new QPieSeries();
        QPieSlice *slice = pieSeries->append(underMinLabel.c_str(), underMinPercent);
        if(underMinPercent != 0){
            slice->setLabelVisible();
        }
        
        QPieSlice *slice2 = pieSeries->append(under5MinLabel.c_str(), under5MinPercent);
        if(under5MinPercent != 0){
            slice2->setLabelVisible();
        }

        QPieSlice *slice3 = pieSeries->append(over5MinLabel.c_str(), over5MinPercent);
        if(over5MinPercent != 0){
            slice3->setLabelVisible();
        }

        // Visulize the pie chart
        QChart *chart = new QChart();
        chart->addSeries(pieSeries);
        chart->setTitle("Length of Stay");
        chart->legend()->hide();

        analysisWindow->setChart(chart);
        analysisWindow->setRenderHint(QPainter::Antialiasing);


    }

}

/**
 * This method scans the logs file and processes the data for a pie graph expressing the admission of 
 * inviduals past the checkpoint. It then carries out the neccesary computations and renders the graph
 * @param log file to process and scan 
 * @brief Produces a pie chart of admission over a session
*/
void AdminUI::admissionAnalysis(std::string log){
    int accepted = 0;
    int denied = 0;
    int invalid = 0;

    std::vector<std::string> lineWords;


    std::ifstream file("Logs/"+log);
    if(file.is_open()){
        
        // Scan log file and update admission counter variables
        std::string line;
        while(std::getline(file,line)){
            
            lineWords = tokenize(line);

            if(lineWords.size() == 3 && lineWords.at(1) == "#admit"){
                accepted++;
            }else if(lineWords.size() == 3 && lineWords.at(1) == "#denieddate"){
                denied++;
            }else if(lineWords.size() == 2 && lineWords.at(1) == "#deniedqrcode"){
                invalid++;
            }
            lineWords.clear();
        }
        file.close();
        float acceptPercent,deniedPercent, invalidPercent;

        // Process data for the pie chart visualization
        if(accepted == 0){
            acceptPercent = 0;
        }else{
            acceptPercent = ((float)accepted/((float)accepted+(float)denied+(float)invalid))*100;
        }

        if(denied == 0){
            deniedPercent = 0;
        }else{
            deniedPercent = ((float)denied/((float)accepted+(float)denied+(float)invalid))*100;
        }
    
        if(invalid == 0){
            invalidPercent = 0;
        }else{
            invalidPercent = ((float)invalid/((float)accepted+(float)denied+(float)invalid))*100;
        }

        std::string accept_num(std::to_string(acceptPercent));
        std::string denied_num(std::to_string(deniedPercent));
        std::string invalid_num(std::to_string(invalidPercent));

        std::string acceptanceLabel = "Admited % "+accept_num;
        std::string deniedLabel = "Denied % "+denied_num;
        std::string invalidLabel = "Invalid QR Code % "+invalid_num;

        // Attach data to the pie series and set the titles
        QPieSeries *pieSeries = new QPieSeries();
        QPieSlice *slice = pieSeries->append(acceptanceLabel.c_str(), acceptPercent);
        if(acceptPercent != 0){
            slice->setLabelVisible();
        }
        
        QPieSlice *slice2 = pieSeries->append(deniedLabel.c_str(), deniedPercent);
        if(deniedPercent != 0){
            slice2->setLabelVisible();
        }

        QPieSlice *slice3 = pieSeries->append(invalidLabel.c_str(), invalidPercent);
        if(invalidPercent != 0){
            slice3->setLabelVisible();
        }

        QChart *chart = new QChart();
        chart->addSeries(pieSeries);
        chart->setTitle("COVID-19 Checkpoint Admission");
        chart->legend()->hide();

        // Visualize the data
        analysisWindow->setChart(chart);
        analysisWindow->setRenderHint(QPainter::Antialiasing);

    }

}

/**
 * @brief This method scans a line of character and seperates them into words
 * @param str line to process
 * @return vector of words from log.  
*/
std::vector<std::string> AdminUI::tokenize(std::string const &str){
    std::vector<std::string> words;
    char *token = strtok(const_cast<char*>(str.c_str()), " ");  // Seperate by space
    while (token != nullptr){ 
        words.push_back(std::string(token)); 
        token = strtok(nullptr, " "); 
    } 
    return words;
}

/**
 * Takes the user input entered in the record text fields and adds 
 * the new record into the vax database if valid.
 * @brief Adds the new record defined by the user's input into the vax database.
*/
void AdminUI::addRec(){

    if(!id_line->text().isEmpty() && !fName_line->text().isEmpty() && !lName_line->text().isEmpty() && !twoDose_line->text().isEmpty()){

        std::string id = (id_line->text()).toStdString();
        std::string fName = (fName_line->text()).toStdString();
        std::string lName = (lName_line->text()).toStdString();
        std::string date = (twoDose_line->text()).toStdString();
    
        id = cleanFormat(id);
        fName = cleanFormat(fName);
        lName = cleanFormat(lName);
        date = cleanFormat(date);

        Record rec(id,fName, lName, date);

        if(!valiDate(date)){
            result_label->setText(QString::fromStdString("Invalid Date"));
        
        }else if(Database::instance().findId(id)){
            result_label->setText(QString::fromStdString("Id Already Exists"));
        
        }else if(Database::instance().addUser(rec)){
            result_label->setText(QString::fromStdString("Record Added"));
        
        }else{
            result_label->setText(QString::fromStdString("Record already Exists"));
        }

    }else {
        result_label->setText(QString::fromStdString("Empty Fields Cannot Add"));

    }

    smallEditor->clear();
    clearLineEdit();
    isrecordSelected = false;
}

/**
 * Takes the user input entered in the record text fields and removes 
 * the defined record from the vax database if valid.
 * @brief Removes the record defined by the user's input from the vax database.
*/
void AdminUI::deleteSpecRec(){

    if(!id_line->text().isEmpty() && !fName_line->text().isEmpty() && !lName_line->text().isEmpty() && !twoDose_line->text().isEmpty()){
        
        std::string id = (id_line->text()).toStdString();
        std::string fName = (fName_line->text()).toStdString();
        std::string lName = (lName_line->text()).toStdString();
        std::string date = (twoDose_line->text()).toStdString();

        id = cleanFormat(id);
        fName = cleanFormat(fName);
        lName = cleanFormat(lName);
        date = cleanFormat(date);

        Record rec(id,fName, lName, date);

        if(Database::instance().deleteUser(rec)){
            clearLineEdit();
            result_label->setText(QString::fromStdString("Record Deleted"));

        }else{
            clearLineEdit();
            result_label->setText(QString::fromStdString("Record does not exist"));
        }

        }else if(!id_line->text().isEmpty() && fName_line->text().isEmpty() && lName_line->text().isEmpty() && twoDose_line->text().isEmpty()){
            std::string id = (id_line->text()).toStdString();
            id = cleanFormat(id);

            if(Database::instance().deleteUser(id)){
                clearLineEdit();
                result_label->setText(QString::fromStdString("Record Deleted"));
            
            }else{
                clearLineEdit();
                result_label->setText(QString::fromStdString("Record does not exist"));

            }

    }else{
        clearLineEdit();
        result_label->setText(QString::fromStdString("Invalid Input"));
    }

    smallEditor->clear();
    isrecordSelected = false;
}

/**
 * Based on the user's input in the text fields, this method returns a query
 * of all the vax records which match the entered fields and displays it to the results box.
 * @brief Displays a query of records matching the fields defined by the user.
*/
 void AdminUI::searchRec(){

    bool cond = false;
    bool empty = true;
    smallEditor->clear();
    std::vector<Record> results;
    Record result;

    //NO input fields entered
    if(id_line->text().isEmpty() && fName_line->text().isEmpty() && lName_line->text().isEmpty() && twoDose_line->text().isEmpty()){    
        
        results = Database::instance().getAll();
        if(results.size() != 0){
            empty = false;
        }    

    // ID field is entered
    }else if(!id_line->text().isEmpty()){
        cond = true;
        std::string id_num = (id_line->text()).toStdString();
        // Check if exists
        if(Database::instance().findId(id_num)){
            result = Database::instance().searchById(id_num);
            empty = false;
        }

    // First name is entered
    }else if(!fName_line->text().isEmpty() && lName_line->text().isEmpty() && twoDose_line->text().isEmpty()){
        
        std::string name = (fName_line->text()).toStdString();
        // Check if exists
        if(Database::instance().findFirst(name)){
            results = Database::instance().searchByFirst(name);
            empty = false;
        }
       
    // Last name is entered
    }else if(fName_line->text().isEmpty() && !lName_line->text().isEmpty() && twoDose_line->text().isEmpty()){
        
        std::string name = (lName_line->text()).toStdString();
        // Check if exists
        if(Database::instance().findlast(name)){
            results = Database::instance().searchByLast(name);
            empty = false;
        }

    // vax dose date
    }else if(fName_line->text().isEmpty() && lName_line->text().isEmpty() && !twoDose_line->text().isEmpty()){
        
        std::string date = (twoDose_line->text()).toStdString();
        // Check if exists
        if(Database::instance().findDate(date)){
            results = Database::instance().searchByDate(date);
            empty = false;
        }

    // first and last name entered
    }else if(!fName_line->text().isEmpty() && !lName_line->text().isEmpty() && twoDose_line->text().isEmpty()){
        
        std::string first = (fName_line->text()).toStdString();
        std::string last = (lName_line->text().toStdString());
        // Check if exists
        if(Database::instance().findFirstLast(first, last)){
            results = Database::instance().searchByFirstLast(first,last);
            empty = false;
        }

    // last name and dose date entered
    }else if(fName_line->text().isEmpty() && !lName_line->text().isEmpty() && !twoDose_line->text().isEmpty()){
        
        std::string date = (twoDose_line->text()).toStdString();
        std::string last = (lName_line->text().toStdString());
        // Check if exists
        if(Database::instance().findLastDate(last, date)){
            results = Database::instance().searchByLastDate(last,date);
            empty = false;
        }

    // first name and dose date entered
    }else if(!fName_line->text().isEmpty() && lName_line->text().isEmpty() && !twoDose_line->text().isEmpty()){
        
        std::string date = (twoDose_line->text()).toStdString();
        std::string first = (fName_line->text().toStdString());
        // Check if exists
        if(Database::instance().findFirstDate(first, date)){
            results = Database::instance().searchByFirstDate(first,date);
            empty = false;
        }
    
    }else if(!fName_line->text().isEmpty() && !lName_line->text().isEmpty() && !twoDose_line->text().isEmpty()){
        
        std::string date = (twoDose_line->text()).toStdString();
        std::string first = (fName_line->text().toStdString());
        std::string last = (lName_line->text().toStdString());
        // Check if exists
        if(Database::instance().findFirstLastDate(first,last,date)){
            results = Database::instance().searchByFirstLastDate(first,last,date);
            empty = false;
        }
    }

    clearLineEdit();
    isrecordSelected = false;

    if(cond && !empty){
        std::string temp = cleanFormat(result.getId()) + "," + cleanFormat(result.getfName()) + "," + cleanFormat(result.getlName()) + "," + cleanFormat(result.getDate());
        smallEditor->insertItem(0,QString::fromStdString(temp));
        result_label->setText(QString::fromStdString("Search Successful"));
    
    }else if(!cond && !empty){
        std::string temp;
        for(std::vector<int>::size_type i = 0; i < results.size(); i++){
            temp = cleanFormat(results.at(i).getId()) + "," + cleanFormat(results.at(i).getfName()) + "," + cleanFormat(results.at(i).getlName()) + "," + cleanFormat(results.at(i).getDate());
            smallEditor->insertItem(i,QString::fromStdString(temp));
        }
        result_label->setText(QString::fromStdString("Search Successful"));
    
    }else{
        result_label->setText(QString::fromStdString("No rows found"));
    }

}

/**
 * After searching for the record, selecting it, and edditing one of the attributes,
 * this method will modify the record in the database based on what was changed.
 * Takes record from database and edits attributes  
 * @brief Based on user input, this modifies the selected record's attributes.
*/
void AdminUI::editRec(){

    if(fName_line->text().isEmpty() || lName_line->text().isEmpty() || twoDose_line->text().isEmpty()){
        result_label->setText(QString::fromStdString("Invalid: Empty Fields"));

    }else if(!valiDate(twoDose_line->text().toStdString())){    
        result_label->setText(QString::fromStdString("Invalid Date"));
    
    }else if(Database::instance().findId((id_line->text()).toStdString())){
        result_label->setText(QString::fromStdString("ID Already Exists"));

    }else if(!isrecordSelected){
        result_label->setText(QString::fromStdString("Please Select Record to Edit"));
   
    }else{
        
        std::string line = recordSelected->text().toStdString();
        std::vector<std::string> vector = Database::instance().readRecord(line);
        std::string id = vector[0];
        std::string first = vector[1];
        std::string last = vector[2];
        std::string date = vector[3];
        Record oldrec(id,first,last,date);

        std::string new_id = (id_line->text()).toStdString();
        std::string new_first = (fName_line->text()).toStdString();
        std::string new_last = (lName_line->text()).toStdString();
        std::string new_date = (twoDose_line->text()).toStdString();

        new_id = cleanFormat(new_id);
        new_first = cleanFormat(new_first);
        new_last = cleanFormat(new_last);
        new_date = cleanFormat(new_date);

        Record newrec(new_id, new_first, new_last, new_date);

        if(Database::instance().recordEquals(newrec,oldrec)){
            result_label->setText(QString::fromStdString("No Changes Were Made"));
        
        }else{
            Database::instance().editRecord(oldrec,newrec);
            result_label->setText(QString::fromStdString("Edit Successful"));
        }
    }

    isrecordSelected = false;
    clearLineEdit();
    smallEditor->clear();
}

/**
* Once a record is selected from the record query box, this method
* takes the record and fills up the editor with it's attributes. 
* @brief Fills up the editor with the selected record's attributes.
* @param record The selected record to retrieve the attributes from
*/
void AdminUI::fillEditor(QListWidgetItem *record){

    std::string line = record->text().toStdString();
    std::vector<std::string> vector = Database::instance().readRecord(line);
    std::string id = vector[0];
    std::string first = vector[1];
    std::string last = vector[2];
    std::string date = vector[3];

    id_line->setText(QString::fromStdString(id));
    fName_line->setText(QString::fromStdString(first));
    lName_line->setText(QString::fromStdString(last));
    twoDose_line->setText(QString::fromStdString(date));
    recordSelected = record;
    isrecordSelected = true;
}

/**
 * Upon the clear button being pressed, this method clears the editor's input boxes.
 * @brief Clears the editor input boxes.
*/
void AdminUI::clearLineEdit(){

    id_line->setText(QString::fromStdString(""));       // set parameter text to empty after execution 
    fName_line->setText(QString::fromStdString(""));
    lName_line->setText(QString::fromStdString(""));
    twoDose_line->setText(QString::fromStdString(""));
}

/**
 * Upon the clear button being pressed, this method clears the editor's record query box.
 * @brief Clears the record query box.
*/
void AdminUI::cleanWindow(){
    smallEditor->clear();
    result_label->setText(QString::fromStdString(""));
}

/**
 * This method validates that the user's entered date attribute is in the appropriate format.
 * @brief Checks that the user's entered date attribute has a valid format.
 * @param date The string containing the entered date
 * @return true if the format is valid, else return false
*/
bool AdminUI::valiDate(std::string date){
    if(std::regex_match(date, std::regex("^((((19|20)(([02468][048])|([13579][26])).02.29))|((20[0-9][0-9])|(19[0-9][0-9])).((((0[1-9])|(1[0-2])).((0[1-9])|(1[0-9])|(2[0-8])))|((((0[13578])|(1[02])).31)|(((0[1,3-9])|(1[0-2])).(29|30)))))$"))){
        return true;
    }
    return false;
}

/**
 * Takes the string parameter "word" and cleans off the punctuation and whitespace.
 * @brief Cleans the punctuation and whitespace from the given string parameter.
 * @param word The word to be cleaned for proccessing
 * @return The formatted word
*/
std::string AdminUI::cleanFormat(std::string word){ // removes punctuation and white space
    
    boost::algorithm::trim(word);
    boost::algorithm::to_lower(word);

    return word;
}

/**
 * This is the destructor of the AdminUI class. Since QT automatically destroys
 * the GUI pointers when this class loses scope, the destructor can remain empty.
 * @brief The destructor of AdminUI.
*/
AdminUI::~AdminUI(){}
