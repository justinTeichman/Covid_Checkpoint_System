/**
 * The database header file.
 * This stores the definitions of all objects and methods used by the database class.
 * @brief The header file for the database class.
 * @author Justin Teichman
 * */

#ifndef DATABASE_H
#define DATABASE_H

#include <record.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>


class Database {

    public:
        static Database& instance();
        ~Database();
        bool addUser(Record);
        bool deleteUser(Record);
        bool deleteUser(std::string);
        Record getUser(std::string);
        bool editRecord(Record,Record);
        std::vector<std::string> readRecord(std::string);
        bool recordEquals(Record, Record);
        bool checkDict(Record rec);
        void writeToText();
        std::vector<Record> getAll();
        
        Record searchById(std::string);
        bool findId(std::string);
        
        std::vector<Record> searchByFirst(std::string);
        bool findFirst(std::string);
        
        std::vector<Record> searchByLast(std::string);
        bool findlast(std::string);
        
        std::vector<Record> searchByDate(std::string);
        bool findDate(std::string);
        
        std::vector<Record> searchByFirstLast(std::string, std::string);
        bool findFirstLast(std::string, std::string);
        
        std::vector<Record> searchByFirstDate(std::string, std::string);
        bool findFirstDate(std::string, std::string);
        
        std::vector<Record> searchByLastDate(std::string, std::string);
        bool findLastDate(std::string, std::string);
        
        std::vector<Record> searchByFirstLastDate(std::string, std::string, std::string);
        bool findFirstLastDate(std::string, std::string, std::string);
    
    protected:
        Database();
    
    private:
        std::vector<Record> vaxRec;
        static Database* _instance;
        
};

#endif
