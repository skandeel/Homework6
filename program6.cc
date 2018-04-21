// Sohieb Kandeel
// sak160230
// CS 3377.501

#include <iostream>
#include <fstream> // For binary input
#include <iomanip> // For binary input
#include <stdint.h> // for uint
#include "cdk.h"

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "Binary File Contents"

const int maxRecordStringLength = 25;

class BinaryFileRecord{ 
 public:  
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];

};

class BinaryFileHeader{
 public:
  uint32_t magicNumber;
  uint32_t versionsNumber;
  uint64_t numRecords;
};


using namespace std;

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"a", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"a", "a", "b", "c"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix == NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  // Get input from binary file 
  ifstream binInfile("cs3377.bin", ios::in | ios::binary);  
 
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  BinaryFileRecord *myRecord = new BinaryFileRecord();

  // Reading in header contents 
  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));

  // Creating a buffer to transfer information
  char input[maxRecordStringLength];

  // Filling in matrix  

  sprintf(input, "Magic: %X", myHeader->magicNumber);
  setCDKMatrixCell(myMatrix, 1, 1, input);

  sprintf(input, "Versions: %d", myHeader->versionsNumber);
  setCDKMatrixCell(myMatrix, 1, 2, input);

  sprintf(input, "NumRecords: %d", myHeader->numRecords);
  setCDKMatrixCell(myMatrix, 1, 3, input);
 
  setCDKMatrixCell(myMatrix, 2, 1, "strlen: ");
  setCDKMatrixCell(myMatrix, 2, 2, "");

  setCDKMatrixCell(myMatrix, 3, 1, "strlen: ");
  setCDKMatrixCell(myMatrix, 3, 2, "");

  setCDKMatrixCell(myMatrix, 4, 1, "strlen: ");
  setCDKMatrixCell(myMatrix, 4, 2, "");

  setCDKMatrixCell(myMatrix, 5, 1, "strlen: ");
  setCDKMatrixCell(myMatrix, 5, 2, "");
 
  drawCDKMatrix(myMatrix, true);

  // close file input
  binInfile.close();

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
