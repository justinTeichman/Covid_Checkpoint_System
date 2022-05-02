# COVID–19 Checkpoint

COMPSCI 3307A Project, group 50

Members: Austin Hatherell, Justin Teichman, Justin Weller, Liam Garrett, Nicolas Jacobs

Our project uses a Raspberry Pi kit and webcam to scan a QR code unique to each user. This QR code acts as the users “vaccination status passport” and, upon scanning, it queries a database to determine if the person should be admitted entrance into a room based on their vaccination status and room capacity. The Pi is connected to a monitor that provides visual feedback and allows access to a simple frontend for administrators to manage the system.


## Deployment

### Minimum dependencies

- Qt 5 + libqt5charts-dev (Extra package)
    - to install QtChart package -> `sudo apt install libqt5charts5-dev`
- Boost Version 1.71.0
    - to install boost -> `sudo apt-get install boost`

### Compiling with the camera module

Note that we provide keybindings for simulating the action of the camera for testing purposes,
so you can use the application's full functionality without needing to compile or configure
the camera system (see "Scanner" under Usage section).

However, if you plan on connecting a real camera to scan QR codes, the following
dependencies are additionally required:

- Python 3
- Python Development Headers for C++ (usually comes with Python)
- OpenCV (module for Python)

Then, open the file *config.h* and uncomment the following line:

```c++
#define USING_CAMERA
```

Now you're ready to compile with the camera module. See the next section.

### Compilation

Run `qmake && make` inside the cloned repository.

To launch, run `./Application`.


## Usage

Upon successfully launching the program, you will be greeted by the Main UI.

Selecting the "Begin Authentication Session" button will switch the window state to the Authentication UI.
This is where you will scan your vaccination passport QR code and receive visual
feedback on if it is valid or not. Upon entering this state, the vaccine authentication session has begun and 
a new log is created to keep track of all events in this state. These logs can be viewed in the "Logs" directory 
or through the Admin state as specified below once the session has ended (once you've left the session or closed
the program). The logs are in the format "LOG_yyyy-mm-dd_hh-mm-ss.txt" to specify the date and time of log creation.

Selecting the "Admin Tools" button will switch the window state to the Login UI.
This is where you can enter valid credentials to gain access to the Administrator
UI. The entered credentials are compared to credentials in the file
"CredentialsDatabase.txt" in an alternating Username/Password format. Each of the
credentials is Username: "Student first name capitalized" and Password: 
"Student last name capitalized". E.g. Username: "Justin", Password: "Weller".

This Administrator UI that you gained access to is where you can manage the system.
To navigate back to the other states, you can select the drop down menu in the
top-left (Named "Covid-19 Checkpoint System") and select a UI to switch to. The
current functionality we have implemented so far is specified in the "Admin Tools"
section below.

### Scanner

To exit the scanner and return to the main menu, press `[ESC]`.

This part of the UI doesn't require a mouse and keyboard -- feedback flashes
temporarily on the screen when the camera recognizes a QR code, and after several
seconds the UI returns to its waiting state. However, for testing purposes, we
provide keyboard input to demonstrate the scanner's functionality without using
a camera.

| Key     | Action                                                                           |
----------|-----------------------------------------------------------------------------------
| `1`     | Scan the QR code of Alice Abernathy, a full-vaccinated student.                  |
| `2`     | Scan the QR code of Bob Blackburn, a student vaccinated fewer than 14 days.      |
| `3`     | Scan the QR code which encodes the string "Hello world!"                         |
| `4`     | Fill the room with dummy users until it reaches capacity.                        |
| `5`     | Empty the room.                                                                  |

Using just the above keys, you should be able to reproduce the situations that would bring
about all of the possible states of the scanner, as enumerated below. Make sure to press `5`
between test cases in order to reset the state. The scanner only reads input while it's in
its yellow 'Please scan your QR code' state, so you must wait for that screen to reappear
before you enter the next key in the sequence.

| Input sequence | Result                                                                    |
-----------------|----------------------------------------------------------------------------
| `1`            | Successful entrance authentication.                                       |
| `1`, `1`       | Successful exit authentication.                                           |
| `2`            | Denied for not being vaccinated 14 days or longer.                        |
| `3`            | Denied for invalid or unregistered QR code.                               |
| `4`, `1`       | Denied because the room is already full.                                  |

### Admin Tools

#### Add Records

1. input user id (String)
2. input first name
3. input last name
4. input date of form (YYYY.MM.DD)
5. Click the add button and check the result label for feedback

#### Delete Records

##### Option 1
1. input user id (String)
2. input first name
3. input last name
4. input date of form (YYYY.MM.DD)
5. Click the delete button and check the result label for feedback

##### Option 2
1. select a record after issuing a query
2. after selecting the record click the delete button


#### Clear Button 

clear vax record attributes input by the user

#### Clear Window

clears the search window of a query

#### Edit Button

1. query a record using the search function
2. once the parameter fields populate, input your changes for a parameter
3. select edit and look at the result label for feedback

#### Search Button 

1. Populate 0 or more parameters in the Vax Records box
2. Check the result label and box to view the query

#### Log Visualization

1. Select a log that you would like to view
2. Click execute and view the log in the window

#### Data Visualization and Computations

1. Select an analysis that you would like to view
2. Select a log that you would like to see analysis on
3. Click Execute and view the graph in the window
