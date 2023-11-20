#include <baseapi.h>
#include <allheaders.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main()
{
    // vars
    char* outText;
    ofstream outputFile;
    string imgfile;
    char* nextData = NULL;

    // Open the output file
    outputFile.open("output.csv");

    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();

    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(NULL, "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // ask for image path
    cout << "Enter Image File Path without quotes: ";
    getline(cin, imgfile);


    // Open input image with leptonica library
    Pix* image = pixRead(imgfile.c_str());            // Change directory of image
    api->SetImage(image);

    // Get OCR result
    outText = api->GetUTF8Text();

    // tokenize tesseract "string"

    char* wordToken = strtok_s(outText, "|", &nextData);
    while (wordToken != nullptr)
    {
        if (strstr(wordToken, "\n") != nullptr)
            //if (wordToken == "\n")       // remove later if not working
        {
            cout << wordToken << endl;
            outputFile << wordToken;
        }
        //else if (wordToken != "|")       // remove later if not working
        else                               
        {
            cout << wordToken << endl;
            outputFile << wordToken;
            outputFile << ", ";
        }

        // go to next value
        wordToken = strtok_s(nullptr, "|", &nextData);
    }

    // Destroy used object and release memory
    api->End();
    delete api;
    delete[] outText;
    pixDestroy(&image);

    // Closing the file
    outputFile.close();

    return 0;
}