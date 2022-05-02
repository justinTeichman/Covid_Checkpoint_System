QT      += core widgets gui charts
TARGET   = Application
TEMPLATE = app
SOURCES  += main.cpp window.cpp authui.cpp adminui.cpp mainui.cpp LoginUI.cpp CredentialsVerifier.cpp record.cpp authstate.cpp authstate_waiting.cpp authstate_success.cpp authstate_deniedinvalid.cpp authstate_deniedtime.cpp authstate_deniedfull.cpp authstate_exit.cpp qrcode.cpp logger.cpp database.cpp Camera.cpp
HEADERS  += window.h authui.h adminui.h mainui.h LoginUI.h CredentialsVerifier.h record.h authstate.h authstates_header.h qrcode.h logger.h database.h config.h Camera.h
CONFIG  += debug
