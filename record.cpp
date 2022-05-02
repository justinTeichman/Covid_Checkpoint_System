/** 
 * This class is used to encapsulate vaccination records in the system.
 * A logical vaccination record will be stored internally as an object of type record.
 * @brief A record of a vaccination.
 * @author Justin Teichman
 * @date November 11, 2021
 */

#include "record.h"

/**
 * Constructor
 * The constructor for when all attributes of a record are known on creation.
 * @brief Constructor for a record object.
 * @param id The string representation of a user's ID. It is unique to them.
 * @param first The user's first name.
 * @param last The user's last name.
 * @param vaxDate The date the user received their second vaccine dose.
 * */
Record::Record(std::string id, std::string first, std::string last, std::string vaxDate){
    
    vaxId = id;
    fName = first;
    lName = last;
    date = vaxDate;

}

/**
 * Constructor
 * The constructor that is called when no attributes about the record are known
 * */
Record::Record(){
    
}

/** 
 * Sets the ID of the record.
 * @brief ID mutator method.
 * @param id The new ID of the record.
 */
void Record::setId(std::string id){
    vaxId = id;
}

/**
 * Sets the first name of the record.
 * @brief fName mutator method.
 * @param first The new fName of the record.
 */
void Record::setfName(std::string first){
    fName = first;
}

/**
 * Sets the last name of the record.
 * @brief lName mutator method.
 * @param last The new lName of the record.
 * */
void Record::setlName(std::string last){
    lName = last;
}

/**
 * Sets the date of the second dose acqusition for the record.
 * @brief date mutator method.
 * @param vaxDate The new date of the record.
 * */
void Record::setDate(std::string vaxDate){
    date = vaxDate;
}

/** 
 * Returns the id of the record.
 * @brief ID accessor method.
 * @return The id of the record.
 */
std::string Record::getId() const{
    return vaxId;
}

/**
 * Returns the first name of the record.
 * @brief fName accessor method.
 * @return The fName of the record.
 */
std::string Record::getfName() const{
    return fName;
}

/**
 * Returns the last name of the record.
 * @brief lName accessor method.
 * @return The lName of the record.
 * */
std::string Record::getlName() const{
    return lName;
}

/**
 * Returns the second dose date of the record.
 * @brief date accessor method.
 * @return The date of the record.
 * */
std::string Record::getDate() const{
    return date;
}

/**
 * Overrides the == operator to function with record objects.
 * It will check if two records (this record and another passed into it) are identical by all four variables: id, fName, lName, and date.
 * @brief Overrides == so it works on record objects.
 * @param other The other record to be compared against.
 * @return True if the records are the same, false otherwise.
 * */
bool Record::operator==(const Record& other) const{
	return (this->getId() == other.getId() && this->getfName() == other.getfName() &&
		    this->getlName() == other.getlName() && this->getDate() == other.getDate());
}

/**
 * Overrides the != operator to function with record objects.
 * It will check if two records (this record and another passed into it) are different by all four variables: id, fName, lName, and date.
 * @brief Overrides != so it works on record objects.
 * @param other The other record to be compared against.
 * @return True if the records are the different, false otherwise.
 * */
bool Record::operator!=(const Record& other) const{
	return !(*this == other);
}
