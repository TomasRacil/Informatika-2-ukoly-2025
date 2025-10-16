#include <iostream>
#include <fstream>

std::string myText;
std::ifstream CteniSouboru("zadani1.txt");
int patro;
int ridici;
 // Create and open a text file
//ofstream MyFile("filename.txt");
int main() {
    // Write to the file
  //MyFile << "Files can be tricky, but it is fun enough!";


    while (std::getline(CteniSouboru, myText)) {

    //char c = myText[0];
  // Output the text from the file
    for(char& c : myText) {
      ridici++;
    if(c =='(')
    {
        patro++;
    }
    else{
        patro--;
    }

    if(patro == -1)
    {
      std::cout << "\n" << ridici << "\n";
    }
}
}



  // Close the file
  CteniSouboru.close();

  std::cout << "\n" << "Patro je " << patro <<  "\n";
}