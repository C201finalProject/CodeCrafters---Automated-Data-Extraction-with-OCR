#include <baseapi.h>
#include <allheaders.h>
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    char* outText;
    fstream outputFile;

    // Open the output file
    outputFile.open("output.txt");

    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();

    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(NULL, "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open input image with leptonica library
    Pix* image = pixRead("C:/Users/blain/OneDrive/Desktop/201/l-pitt-city-dir-artical-web1.jpg");   //Change directory of image
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