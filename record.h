/**
 * The header file for record.
 * This will store the initial declarations for each object and method used by record.cpp.
 * @brief The header file for record.cpp.
 * @author Justin Teichman
 * */
#ifndef RECORD_H
#define RECORD_H

#include <string>

class Record {

    public:
        Record(std::string, std::string, std::string, std::string);
        Record();
        std::string getId() const;
        std::string getfName() const;
        std::string getlName() const;
        std::string getDate() const;

        void setId(std::string);
        void setfName(std::string);
        void setlName(std::string);
        void setDate(std::string);

	bool operator==(const Record& other) const;
	bool operator!=(const Record& other) const;

    private:
        std::string vaxId;
        std::string fName;
        std::string lName;
        std::string date;

};
#endif
