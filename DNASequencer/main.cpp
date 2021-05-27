#include <stdlib.h>  //for access to srand
#include <time.h>   //for access to time()
#include "ManageReadingOfFile.h" //so that I can use the readFile() method in this class right here

int main(int argc, char const *argv[]) {

  ManageReadingOfFile fileManager; //so that I can use the readFile() method

  srand(time(NULL)); //seeds the random number generator to insure that each time the program is executed, different values are produced: http://www.math.uaa.alaska.edu/~afkjm/csce211/fall2018/handouts/RandomFunctions.pdf

  if (argc > 1) { //argc is always 1 because the first element in it is the command given to run this program, so if the user gives a file name than argc will be greater than 1

    fileManager.readFile(argc, argv[1]); //if the user gave a file name in the command name, this tells the file manager to attempt to read it

  }
  else {

    fileManager.readFile(argc, ""); //this will tell the fileManager that the user did not enter any filename in the command line, which will allow the program to ask the user if they want to enter a file name

  }

  return 0;

}
