#include <baseapi.h>
#include <allheaders.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    char* outText;
    fstream outputFile;
    string imgfile;

    // Open the output file
    outputFile.open("output.txt");

    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();

    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(NULL, "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    cout << "Enter Image File Path without quotes: ";
    getline(cin, imgfile);

    // Open input image with leptonica library
    Pix* image = pixRead(imgfile.c_str());   //Change directory of image
    api->SetImage(image);

    // Get OCR result
    outText = api->GetUTF8Text();
    outputFile << "OCR output: " << endl << outText;  //This is first line of output

    // Destroy used object and release memory
    api->End();
    delete api;
    delete[] outText;
    pixDestroy(&image);

    // Closing the file
    outputFile.close();

    return 0;
}