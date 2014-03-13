#include <locale.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <tesseract/baseapi.h>

#include <iostream>

int main( int argc, char** argv )
{
	setlocale( LC_ALL, "C" );
    if( argc != 2 )
    {
        std::cout << "Please specify the input image!" << std::endl;
        return -1;
    }

    // Load image
    cv::Mat im = cv::imread(argv[1]);
    if( im.empty() )
    {
        std::cout << "Cannot open source image!" << std::endl;
        return -1;
    }

    const char* lang = "por";

    cv::Mat gray;
    cvtColor( im, gray, CV_BGR2GRAY );

    //threshold( gray, gray, 160, 255, cv::THRESH_BINARY );
    threshold( gray, gray, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY_INV );

//    cv::Mat element = getStructuringElement( cv::MORPH_RECT, cv::Size( 2, 2 ) );
//    morphologyEx( gray, gray, cv::MORPH_DILATE, element );
//    morphologyEx( gray, gray, cv::MORPH_ERODE, element );

    // Pass it to Tesseract API
    tesseract::TessBaseAPI tess;
    tess.Init( NULL, lang, tesseract::OEM_DEFAULT );
    tess.SetVariable("tessedit_char_whitelist", "0123456789ehilmuorsõAEILMNOPRSTUV/.=€:,-");
    tess.SetPageSegMode( tesseract::PSM_AUTO );
    tess.SetImage( (uchar*) gray.data, gray.cols, gray.rows, 1, gray.cols );

    // Get the text
    char* out = tess.GetUTF8Text();
    std::cout << out << std::endl;

    cv::namedWindow( "image", CV_WINDOW_NORMAL );
    cv::imshow( "image", gray );

    cv::waitKey(0);
}
