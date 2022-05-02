/**
 * This CredentialsVerifier.h file declares the class blueprint of the
 * CredentialsVerifier class which is used for verifying the entered login credentials. 
 * It also includes all the necessary libraries and files for this class.
 * @brief The header file for the CredentialsVerifier class.
 * @author Justin Weller
 * @date 2021-11-09
*/

// Include Guards
#ifndef CREDENTIALSVERIFIER_H
#define CREDENTIALSVERIFIER_H

// Include all the required system and standard libraries
#include <string>
#include <fstream>
#include <iostream>

// This is the blueprint for the CredentialsVerifier class
class CredentialsVerifier
{
// Declares all the public members within the class
public:
  CredentialsVerifier();
  ~CredentialsVerifier();
  bool verifyCred(std::string user, std::string pass);
};

#endif // This header has been included