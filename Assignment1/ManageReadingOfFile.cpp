#include "ManageReadingOfFile.h" //for access to the methods defined in the header file
#include <fstream> //for access to ifstream so that a file can be read
#include <iostream> //for access to cin and cout so that messages can be given to the user on the console

using namespace std;

ManageReadingOfFile :: ManageReadingOfFile() { //default constructor

}

ManageReadingOfFile :: ~ManageReadingOfFile() { //destructor

}

void ManageReadingOfFile :: readFile(int argumentCount, string nameOfFileToRead){ //reads the inputed dna file provided it exists and sends each line to the DNA sequencer so that the statistics can be calculated.

  userWantsToEnterAnotherFile = false; //used to indicate when the user has selected yes to enter enother file
  shouldEndProgram = false; //used to signal when the while loop below should be broken out of so that the program can end

  while (true) {

    string line; //will be used to store the lines we have in file we are reading from
    string fileName; //the name of the file that will be read

    if (userWantsToEnterAnotherFile == true || argumentCount < 2) {

      if (argumentCount < 2) { //the program went in here because the user did not give the name of a file to read from in the command line

        checkIfUserIsDone(); //check if the user wants to try entering a file in, or if they want to quit

        if (shouldEndProgram) {

          //the user wants to quit, need to break out of the while loop so that the program can end
          break;

        }

      }

      cout<<"Enter the name of a file to read:";
      cin>>fileName; //set filename to the name of the file the user wants to process
      userWantsToEnterAnotherFile = false;

    }
    else {

      fileName = nameOfFileToRead; //stores the command line parameter that represents the name of the file we will be reading from.

    }

    cout <<"Looking for file named "+fileName<<'\n';

    ifstream fileToReadFrom(fileName);

    if (fileToReadFrom.is_open()) { //the file was successfully opened

      sequencer.SetThereIsAtLeastOneValidLine(false); //set this value to false since when we just start reading a file we do not know whether or not there is a single valid line yet

      while (getline(fileToReadFrom, line)) {

        //there are still more lines to read in the file
        sequencer.sequenceThisDNAString(line); //send this line to the sequencer so that statistics can be updated

      }

      if (sequencer.CheckIfThereWasAtLeastOneValidLine()) { //need to make sure there was at least 1 valid line, otherwise when the calculations are done if there we no valid lines the program will not run properly

        sequencer.doCalculationsForThisDNAFile(); //all lines have been read by this point, so I can now do things like calulcate the probabilities, mean, etc.
        fileToReadFrom.close();

      }
      else {

        cout<<"There were no valid lines at all in this file..."<<endl;

      }

      cout<<"Done processing file!"<<endl;
      checkIfUserIsDone(); //allow the user to choose whether or not they want to try another file

    }
    else {

      //enter here when the user does give a file in the command line and it does not exist at the specified directory, or when the user gives a file name when prompted and that file does not exist at the specified directory
      cout<<"File could not be opened, you may have entered the wrong file name or the file simply does not exist"<<'\n';
      checkIfUserIsDone(); //allow the user to choose whether or not they want to try another file

    }

    if (shouldEndProgram) {

      //the user is done processing files and the program needs to exit this while loop so that it can shut down
      break;

    }

  }

}

//allows the user to choose whether or not they want to attempt to process another file
void ManageReadingOfFile::checkIfUserIsDone() {

  char userResponse; //stores the user's response

  while (true) { //placed in a while loop to insure this question is repeated if the user enters an invalid response that does not contain either an n or a y

    char userResponse;
    cout<<"Would you like to enter a new file? Enter y for yes and n for no"<<"\n";
    cin>>userResponse;

    if (tolower(userResponse) == 'n') {

      //the program needs to shut down
      cout<<"Goodbye!"<<'\n';
      shouldEndProgram = true;
      break;

    }
    else if (tolower(userResponse) == 'y'){

      //the program needs to prompt the user for the name of the file they want to process
      userWantsToEnterAnotherFile = true;
      break;

    }

  }

}
