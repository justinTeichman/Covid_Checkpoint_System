/**
 * The database that the system uses.
 * The system will pull the database and generate a vector of the items in it.
 * The database uses a singleton design pattern so the same database will always be used.
 * No two forms of the database can exist at once.
 * @brief The database the system uses is a copy of the file that has been turned into a vector.
 * @author Justin Teichman
 * */
#include <database.h>

//Singleton variable to check if the instace been created yet.
Database* Database::_instance = NULL;

/**
 * Singleton constructor
 * This is a singleton constructor, meaning that only one instance of the database class can exist at once.
 * @brief A singleton constructor that generates/returns the sole instance of the database class.
 * @return The instance of the database class.
 * */
Database& Database::instance(){

    if(_instance == NULL){
        _instance = new Database();
    }
    return *_instance;
}

/**
 * Constructor
 * The constructor for the database class is called by the singleton constructor.
 * This can only ever be called once.
 * It opens the file containing the vax database and copies it into a record vector.
 * @brief Creates a record vector from the vax database.
 * */
Database::Database(){
    
    std::ifstream fin;
    fin.open("vaxData.txt");
    std::string line;
    std::vector<std::string> vect;
    while(getline(fin,line)){
             
        vect = readRecord(line);
        Record rec(vect[0],vect[1], vect[2], vect[3]);
        vaxRec.push_back(rec);
    }
}

/**
 * Is given a record and adds it into the record vector.
 * @brief Adds a user into the record vector.
 * @param rec The record that is being added into the vector.
 * @return true if the user was added and false otherwise.
 * */
bool Database::addUser(Record rec){
    
    if(!checkDict(rec)){
        vaxRec.push_back(rec);
        writeToText();
        return true;
    }
    return false;
}

/**
 * Is given a record to delete from the record vector and deletes it.
 * @brief Deletes a record from the vector.
 * @param rec The record that will be deleted.
 * @return true if the record was deleted, false otherwise.
 * */
bool Database::deleteUser(Record rec){

    for (std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
        if(recordEquals(rec,vaxRec.at(i))){
            vaxRec.erase(vaxRec.begin()+i);
            writeToText();
            return true;
        }
    }
    return false;
}

/**
 * Is given the id of a record to be deleted and deletes the record from the vector matching that id.
 * @brief Deletes the record that matches the id given.
 * @param id The id that corresponds to the record to be deleted.
 * @return true if the record with the id was deleted and false otherwise.
 * */
bool Database::deleteUser(std::string id){

    for (std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
        if(vaxRec.at(i).getId() == id){
            vaxRec.erase(vaxRec.begin()+i);
            writeToText();
            return true;
        }
    }
    return false;
}

/**
 * Is given an older record and replaces it with an updated version.
 * Searches for the old record and replaces it with the new one when it is found.
 * @brief Replaces an old record with a new record.
 * @param oldRec The old record that will be replaced.
 * @param newRec The new record that will "added" to the vector.
 * @return true if the record was replaced and false otherwise.
 * */
bool Database::editRecord(Record oldRec, Record newRec){
    
    for(std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
        if(recordEquals(vaxRec.at(i), oldRec)){
            vaxRec.at(i) = newRec;
            writeToText();
            return true;
        }
    }
    return false;
}

/**
 * Returns the vector of records.
 * Will return all records.
 * @brief Returns all records in the vector.
 * @return The vetor holding the records.
 * */
std::vector<Record> Database::getAll(){
    return vaxRec;
}

/**
 * Searches for a record with the id given.
 * Returns the record once found.
 * @brief Returns the record that matches the id given.
 * @param id The id of the record to be returned.
 * @return The record that has the id matching the id given. If no record matches the id, return record 0.
 * */
Record Database::searchById(std::string id){
    for(std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
       if(vaxRec.at(i).getId() == id){
           return vaxRec.at(i);
       } 
    }
    return vaxRec.at(0);
}

/**
 * Searches for if the id given is in found in a record in the vector.
 * If the vector contains a record with the matching id, return true, false otherwise.
 * @brief Returns whether or not a record in the vector has ths given id.
 * @param id The id to be checked for in the vector.
 * @return true if the id is contained in a record in the vector, false otherwise.
 * */
bool Database::findId(std::string id){
    for(std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
       if(vaxRec.at(i).getId() == id){
           return true;
       } 
    }
    return false;
}

/**
 * Searches the vector for records that have the first name given.
 * If a record in the vector has the given first name, it is returned.
 * Multiple records can be returned.
 * @brief Returns all records with the first name matching the parameter given.
 * @param first The first name to match records to.
 * @return A vector of records that have the first name matching the parameter given.
 * */
std::vector<Record> Database::searchByFirst(std::string first){
    std::vector<Record> query;
    for(std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
        if(vaxRec.at(i).getfName() == first){
            query.push_back(vaxRec.at(i));
        }
    }
    return query;
}

/**
 * Searches for if the first name given is in found in a record in the vector.
 * If the vector contains a record with the matching first name, return true, false otherwise.
 * @brief Returns whether or not a record in the vector has ths given first name.
 * @param first The first name to be checked for in the vector.
 * @return true if the first name is contained in a record in the vector, false otherwise.
 * */
bool Database::findFirst(std::string first){
    for(std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
        if(vaxRec.at(i).getfName() == first){
            return true;
        }
    }
    return false;
}

/**
 * Searches the vector for records that have the last name given.
 * If a record in the vector has the given last name, it is returned.
 * Multiple records can be returned.
 * @brief Returns all records with the last name matching the parameter given.
 * @param last The last name to match records to.
 * @return A vector of records that have the last name matching the parameter given.
 * */
std::vector<Record> Database::searchByLast(std::string last){
    std::vector<Record> query;
    for(std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
        if(vaxRec.at(i).getlName() == last){
            query.push_back(vaxRec.at(i));
        }
    }
    return query;
}

/**
 * Searches for if the last name given is in found in a record in the vector.
 * If the vector contains a record with the matching last name, return true, false otherwise.
 * @brief Returns whether or not a record in the vector has ths given last name.
 * @param last The last name to be checked for in the vector.
 * @return true if the last name is contained in a record in the vector, false otherwise.
 * */
bool Database::findlast(std::string last){
    for(std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
        if(vaxRec.at(i).getlName() == last){
            return true;
        }
    }
    return false;
}

/**
 * Searches the vector for records that have a date field matching the date given.
 * If a record has the matching date field, it will be returned.
 * Multiple records can therefore be returned.
 * @brief Returns all records that match to the date given.
 * @param date The date that records are being compared against.
 * @return A vector containing all records with a date field the same as the date given.
 * */
std::vector<Record> Database::searchByDate(std::string date){
    std::vector<Record> query;
    for(std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
        if(vaxRec.at(i).getDate() == date){
            query.push_back(vaxRec.at(i));
        }
    }
    return query;
}

/**
 * Searches the vector for a record that has the date given.
 * If a record is found that has this date, return true, false otherwise.
 * @brief Returns true or false based on if the date given is found inside a record.
 * @param date The date that records are being compared against.
 * @return true if a record is found with the same date, false otherwise.
 * */
bool Database::findDate(std::string date){
    for(std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
        if(vaxRec.at(i).getDate() == date){
            return true;
        }
    }
    return false;
}

/**
 * Searches the vector for records that have first and last name fields matching the first and last names given.
 * If a record has the matching fields, it will be returned.
 * Multiple records can therefore be returned.
 * @brief Returns all records that match to the first and last names given.
 * @param first The first name that records are being compared against.
 * @param last The last name that records are being compared against.
 * @return A vector containing all records with first and last name fields that are the same as the fields given.
 * */
std::vector<Record> Database::searchByFirstLast(std::string first, std::string last){
    std::vector<Record> query;
    for(std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
        if(vaxRec.at(i).getfName() == first && vaxRec.at(i).getlName() == last){
            query.push_back(vaxRec.at(i));
        }
    }
    return query;
}

/**
 * Searches the vector for a record that has the first and last names given.
 * If a record is found that has these first and last names, return true, false otherwise.
 * @brief Returns true or false based on if the first and last names given are found inside a record.
 * @param first The firstname that records are being compared against.
 * @param last The lastname that records are being compared against.
 * @return true if a record is found with the same first and last names, false otherwise.
 * */
bool Database::findFirstLast(std::string first, std::string last){
    for(std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
        if(vaxRec.at(i).getfName() == first && vaxRec.at(i).getlName() == last){
            return true;
        }
    }
    return false;
}

/**
 * Searches the vector for records that have firstname and date fields matching the arguments given.
 * If a record has the matching fields, it will be returned.
 * Multiple records can therefore be returned.
 * @brief Returns all records that match to the firstname and date attributes given.
 * @param first The firstname that records are being compared against.
 * @param date The date that records ar being compared against.
 * @return A vector containing all records with firstname and date fields that are the same as the fields given.
 * */
std::vector<Record> Database::searchByFirstDate(std::string first, std::string date){
    std::vector<Record> query;
    for(std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
        if(vaxRec.at(i).getfName() == first && vaxRec.at(i).getDate() == date){
            query.push_back(vaxRec.at(i));
        }
    }
    return query;
}

/**
 * Searches the vector for a record that has the firstname and date given.
 * If a record is found that has these firstname and date fields, return true, false otherwise.
 * @brief Returns true or false based on if the firstname and date fields given are found inside a record.
 * @param date The date that records are being compared against.
 * @param first The firstname that records are being compared against.
 * @return true if a record is found with the same firstname and date, false otherwise.
 * */
bool Database::findFirstDate(std::string first, std::string date){
    for(std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
        if(vaxRec.at(i).getfName() == first && vaxRec.at(i).getDate() == date){
            return true;
        }
    }
    return false;
}

/**
 * Searches the vector for records that have lastname and date fields matching the arguments given.
 * If a record has the matching fields, it will be returned.
 * Multiple records can therefore be returned.
 * @brief Returns all records that match to the lastname and date attributes given.
 * @param last The lastname that records are being compared against.
 * @param date The date that records ar being compared against.
 * @return A vector containing all records with lastname and date fields that are the same as the fields given.
 * */
std::vector<Record> Database::searchByLastDate(std::string last, std::string date){
   std::vector<Record> query;
    for(std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
        if(vaxRec.at(i).getlName() == last && vaxRec.at(i).getDate() == date){
            query.push_back(vaxRec.at(i));
        }
    }
    return query;
}

/**
 * Searches the vector for a record that has the lastname and date given.
 * If a record is found that has these lastname and date fields, return true, false otherwise.
 * @brief Returns true or false based on if the lastname and date fields given are found inside a record.
 * @param date The date that records are being compared against.
 * @param last The lastname that records are being compared against.
 * @return true if a record is found with the same lastname and date, false otherwise.
 * */
bool Database::findLastDate(std::string last, std::string date){
     for(std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
        if(vaxRec.at(i).getlName() == last && vaxRec.at(i).getDate() == date){
            return true;
        }
    }
    return false;
}

/**
 * Searches the vector for records that have firstname, lastname, and date fields matching the arguments given.
 * If a record has the matching fields, it will be returned.
 * Multiple records can therefore be returned.
 * @brief Returns all records that match to the firstname, lastname, and date attributes given.
 * @param first The firstname that records are being compared against.
 * @param last The lastname that records are being compared against.
 * @param date The date that records ar being compared against.
 * @return A vector containing all records with firstname, lastname, and date fields that are the same as the fields given.
 * */
std::vector<Record> Database::searchByFirstLastDate(std::string first, std::string last, std::string date){
    std::vector<Record> query;
    for(std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
        if(vaxRec.at(i).getfName() == first && vaxRec.at(i).getlName() == last && vaxRec.at(i).getDate() == date){
            query.push_back(vaxRec.at(i));
        }
    }
    return query;
}

/**
 * Searches the vector for a record that has the firstname, lastname, and date given.
 * If a record is found that has these firstname, lastname, and date fields, return true, false otherwise.
 * @brief Returns true or false based on if the firstname, lastname, and date fields given are found inside a record.
 * @param date The date that records are being compared against.
 * @param first The firstname that records are being compared against.
 * @param last The lastname that records are being compared against.
 * @return true if a record is found with the same firstname, lastname and date, false otherwise.
 * */
bool Database::findFirstLastDate(std::string first, std::string last, std::string date){
    for(std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
        if(vaxRec.at(i).getfName() == first && vaxRec.at(i).getlName() == last && vaxRec.at(i).getDate() == date){
            return true;
        }
    }
    return false;
}

/**
 * Reads a line from the record database.
 * Turns the line into a string vector.
 * Will append it to a string vector.
 * Uses the "," delimiter to seperate each record field into a string.
 * This is called form the constructor when the record database is opened to read from for the first (and only) time.
 * @brief Reads a line from the vax database which is added to a string vector.
 * @param line The line of text being processed.
 * @return A vector string of the line of text, processed into data fields.
 * */
std::vector<std::string> Database::readRecord(std::string line){     

    std::string delimiter = ",";
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string attribute;
    std::vector<std::string> res;

    while ((pos_end = line.find (delimiter, pos_start)) != std::string::npos) {
        attribute = line.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (attribute);
    }

    res.push_back (line.substr (pos_start));
    return res;

}

/**
 * Function Name: recordEquals
 * Description: compares two records 
 * Parameters: two record objects
 * This function returns true if the records are the same and false if there are different
*/
bool Database::recordEquals(Record vaxRec, Record inputRec){

    if(vaxRec.getId() == inputRec.getId() && vaxRec.getfName() == inputRec.getfName() && vaxRec.getlName() == inputRec.getlName() && vaxRec.getDate() == inputRec.getDate()){
        return true;
    }else{
        return false;
    }

}

/**
 * Checks if a certain record is in the dictionary.
 * This function return true if the record is in the dictionary and false if it is not.
 * @brief Check the vector for this exact record.
 * @param rec The record that the vector is being checked for.
 * @return true if a matching record is found, false otherwise.
*/
bool Database::checkDict(Record rec){
    for (std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
        if(recordEquals(rec,vaxRec.at(i))){
            return true;
        }
    }
    return false;

}

/**
 * The vector that the system uses is a copy of the database file.
 * If a change is made to the database, it is made to the vector instead.
 * To save changes to the database, the database needs to be overwritten with the updated vector.
 * This method will write the vector to the database of records.
 * @brief Write the record vector the records.txt, overriding the data stored in the file in the process.
 * */
void Database::writeToText(){
    std::ofstream oin;
    std::string temp;
    oin.open("records.txt");


    for(std::vector<int>::size_type i = 0; i < vaxRec.size(); i++){
        temp = vaxRec.at(i).getId() + "," + vaxRec.at(i).getfName() 
        + "," + vaxRec.at(i).getlName() + "," + vaxRec.at(i).getDate();
        if(i == vaxRec.size()-1){
            oin << temp;
        }else{
            oin << temp << std::endl;

        }    
    }

    oin.close();
    remove("vaxData.txt"); // remove copy of old database
    rename("records.txt","vaxData.txt");   // rename new temporary database as database
}


/**
 * Destructor
 * The destructor will destroy the database class when it is done being used.
 * @brief Destroy the database object.
 * */
Database::~Database(){

}
