#include "DNASequencer.h" //for access to the sequenceThisDNAString() and doCalculationsForThisDNAFile() methods

/*

This class is responsible for allowing the user to decide which files should
be read. Upon this decision, this class then reads the file and feeds each line into the
DNA sequencer so that statistics can be calculated on the inputed file's DNA strings.

*/
class ManageReadingOfFile {

bool userWantsToEnterAnotherFile; //will keep track of whether or not the user has selected yes to process another file
bool shouldEndProgram; //used to signal when the program should shut down
void checkIfUserIsDone(); //allows the user to choose if they want to process another file

DNASequencer sequencer; //used to access the sequenceThisDNAString() and doCalculationsForThisDNAFile() methods of this file

public:
  ManageReadingOfFile(); //default constructor
  ~ManageReadingOfFile(); //destructor
  void readFile(int argumentCount, std::string nameOfFileToRead); //will read the input file and feed each line into the DNASequencer so that the statistics can be calculated

};
