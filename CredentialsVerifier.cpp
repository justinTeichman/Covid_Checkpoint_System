/**
 * This class is used to verify the login credentials that the user entered into the
 * login GUI. It reads the valid usernames and passwords from the "CredentialsDatabase.txt"
 * and compares them to the users entered credentials, and returns if they're valid or not.
 * @brief This class verifies the login credentials entered by the user.
 * @author Justin Weller
 * @date 2021-11-09
 */

// Include the CredentialsVerifier header file
#include "CredentialsVerifier.h"

/**
 * This is the constructor of the CredentialsVerifier class, it is
 * empty as no action needs to be taken upon creation of this class.
 * @brief The constructor of CredentialsVerifier.
*/
CredentialsVerifier::CredentialsVerifier()
{

}

/**
 * This is the destructor of the CredentialsVerifier class. It is
 * empty as no action needs to be taken upon destruction of this class.
 * @brief The destructor of CredentialsVerifier.
*/
CredentialsVerifier::~CredentialsVerifier()
{
    
}

/**
 * This function compares the entered credentials as parameters, to
 * the list of valid credentials in "CredentialsDatabase.txt". If any of them match
 * this function returns true, else, it returns false.
 * @brief Checks if the entered credentials are valid based on the database.
 * @param user: The entered username
 * @param pass: the entered password
 * @return true if the entered credentials were found in the list of valid ones, false otherwise.
*/
bool CredentialsVerifier::verifyCred(std::string user, std::string pass)
{
    std::ifstream in("CredentialsDatabase.txt");

    // If the file doesn't exist
    if(!in)
    {
        std::cout << "CredentialsDatabase.txt was not found" << std::endl;
        return false;
    }

    std::string fileUsername, filePassword;

    // Read through every line of the file
    while(std::getline(in, fileUsername))
    {
        std::getline(in, filePassword);

        // If the credentials entered are found in the database
        if(fileUsername == user && filePassword == pass)
        {
            return true;
        }
    }
    return false; // If the entered credentials weren't found in the database
}