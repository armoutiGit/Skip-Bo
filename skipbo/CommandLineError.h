#ifndef _COMMAND_LINE_ERROR_H
#define _COMMAND_LINE_ERROR_H

#include<iostream>
#include<fstream>

/* Function to handle invalid # of arguments, invalid first argument, invalid # of playeres, and bad stock size errors
 * @param argc number of command line arguments
 * @param argv array of command line arguments
 * @return 0 for success, 1 for failure
*/
int CommandLineError(int argc, char** argv);

/* Function makes a test stream to check if "filename" can be opened
 * @param filename file to be checked
 * @return 0 for file can be opened, 1 for file cannot be opened
*/
int fileCheckOpen(std::string filename);


#endif