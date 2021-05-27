#include "ManageWritingToFile.h" //for access to the methods defined in this header file
#include <fstream> //for access to ofstream and writing to file methods
#include <iostream>

using namespace std;//for access to std::strings

ManageWritingToFile::ManageWritingToFile() { //default constructor

}

ManageWritingToFile::~ManageWritingToFile() {//destructor

}

//writes all of the calculated statistics on the dna input file onto a file named diegoavena.out., and writes all of the 1000 generated DNA strands onto 1000 lines whose lengths follow the lengths calculated by the DNAGenerator object
void ManageWritingToFile::RecordStatisticsOntoFile(float sumOfDNAStrandLengths, float meanOfDNAStrandLengths, float varianceOfDNAStrandLengths, float standardDeviationOfDNAStrandLengths,
float AProb, float CProb, float TProb, float GProb, float AAProb, float ACProb, float ATProb, float AGProb, float CCProb, float CAProb, float CTProb, float CGProb,
float TTProb, float TAProb, float TCProb, float TGProb, float GGProb, float GAProb, float GCProb, float GTProb,
float quantityOfA, float quantityOfC, float quantityOfT, float quantityOfG) {

  bool fileToBeWrittenIntoExists = CheckIfFileAlreadyExists(); //check  if the file that is written into exists yet

  ofstream fileToWriteTo("diegoavena.out", ios::app); //for help on how to write to files, I referenced: http://www.cplusplus.com/doc/tutorial/files/

  if (fileToBeWrittenIntoExists == false) {

    //the file does not exist and we need to put a name on it as a new blank file will be created:
    fileToWriteTo << "NAME: Diego Avena" <<endl;
    fileToWriteTo << "STUDENT ID: 2299333"<<endl;

  }

  fileToWriteTo << endl << endl << "HERE THE STATISTICS FROM THE DNA :"<<endl<<endl;
  fileToWriteTo << "MEAN DNA LENGTH: "<<meanOfDNAStrandLengths<<endl;
  fileToWriteTo << "SUM OF THE DNA LENGTHS: "<<sumOfDNAStrandLengths<<endl;
  fileToWriteTo << "VARIANCE OF THE DNA LENGTHS: "<<varianceOfDNAStrandLengths<<endl;
  fileToWriteTo << "STANDARD DEVIATION OF DNA LENGTHS: "<<standardDeviationOfDNAStrandLengths<<endl;

  fileToWriteTo << endl << endl;

  fileToWriteTo << "PROBABILITIES OF EACH NUCLEOTIDE: " <<endl;
  fileToWriteTo << "A: " << AProb << "%" << endl;
  fileToWriteTo << "C: " << CProb << "%" << endl;
  fileToWriteTo << "T: " << TProb << "%" << endl;
  fileToWriteTo << "G: " << GProb << "%" << endl;

  fileToWriteTo << endl << endl;

  fileToWriteTo << "PROBABILITIES OF EACH NUCLEOTIDE PAIR: " << endl;

  fileToWriteTo << "AA " << AAProb << "%" << endl;
  fileToWriteTo << "AC " << ACProb << "%" << endl;
  fileToWriteTo << "AT " << ATProb << "%" << endl;
  fileToWriteTo << "AG " << AGProb << "%" << endl;

  fileToWriteTo << endl;

  fileToWriteTo << "CC " << CCProb << "%" << endl;
  fileToWriteTo << "CA " << CAProb << "%" << endl;
  fileToWriteTo << "CT " << CTProb << "%" << endl;
  fileToWriteTo << "CG " << CGProb << "%" << endl;

  fileToWriteTo << endl;

  fileToWriteTo << "TT " << TTProb << "%" << endl;
  fileToWriteTo << "TA " << TAProb << "%" << endl;
  fileToWriteTo << "TC " << TCProb << "%" << endl;
  fileToWriteTo << "TG " << TGProb << "%" << endl;

  fileToWriteTo << endl;

  fileToWriteTo << "GG " << GGProb << "%" << endl;
  fileToWriteTo << "GA " << GAProb << "%" << endl;
  fileToWriteTo << "GC " << GCProb << "%" << endl;
  fileToWriteTo << "GT " << GTProb << "%" << endl;

  fileToWriteTo <<endl<<endl;

  fileToWriteTo <<"HERE ARE 1000 DNA STRINGS GENERATED WITH THE SAME FREQUENCY OF NUCLEOTIDES AS ABOVE:"<<endl;
  generator.initializeProbabilitiesOfEachNucleotide(AProb, CProb, TProb, GProb);

  string generatedDNAStrings = generator.generateDNA(meanOfDNAStrandLengths, standardDeviationOfDNAStrandLengths); //stores the 1000 generated DNA strings (these strings are not yet divided into their lines)
  string theLengthsOfTheDNAStrings = generator.getTheLengthsOfTheGeneratedDNAStrands(); //stores the 1000 different lengths generated for each DNA string

  //debugging purposes
  cout<<"The lengths of each generated string are as follows: "<<theLengthsOfTheDNAStrings<<endl<<", this should be reflected by the 1000 lines written on diegoavena.out (the last number shown here should be the length of the final dna strand in the generated lines)"<<endl;

  int lengthOfTheLine = 0;
  int currentLocationInStringOfDNALengths = 0;
  int currentLocationInGeneratedDNAString = 0;
  string textVersionOfOurLength = "";

  //it is the job of this code to devide the strings in 1000 lines on the file, according to the 1000 lengths generated:
  while (currentLocationInGeneratedDNAString <= generatedDNAStrings.length()) {

    for (int i = currentLocationInStringOfDNALengths; i < theLengthsOfTheDNAStrings.length(); i++) { //obtain the correct length for the current DNA string that is being written onto diegoavena.out

      if ((theLengthsOfTheDNAStrings.substr(i, 1) == " ") && (lengthOfTheLine != 0)) {

        //we are at the " " that comes after each number, break out of the loop, we have the correct length for this DNA string
        currentLocationInStringOfDNALengths = i;
        lengthOfTheLine = stoi(textVersionOfOurLength);
        break;

      }
      else if (theLengthsOfTheDNAStrings.substr(i, 1) != " ") {

        //we are at an index that has a digit in it, grab it:
        textVersionOfOurLength += theLengthsOfTheDNAStrings[i];
        lengthOfTheLine = stoi(textVersionOfOurLength);

      }

    }

    fileToWriteTo << generatedDNAStrings.substr(currentLocationInGeneratedDNAString, lengthOfTheLine) << endl;
    currentLocationInGeneratedDNAString += lengthOfTheLine; //increment the current location we are at in the generated string chunk
    textVersionOfOurLength = "";
    lengthOfTheLine = 0;

  }

  fileToWriteTo << "-----------------------------------------------------------------------------------------"<<endl;

  fileToWriteTo.close();

}

//checks if the file to be written into exists so that the program knows when my name and student id should be written
bool ManageWritingToFile::CheckIfFileAlreadyExists() {

  ifstream fileToCheckForExistence("diegoavena.out");
  if (fileToCheckForExistence.is_open()) {

    //the file exists:
    fileToCheckForExistence.close();
    return true;

  }
  else {

    //the file does not exists and needs to be created before writing onto it:
    return false;

  }

}
