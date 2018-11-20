#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include "v4ldevice.h"

using namespace cv;

void ShowImage(char* Name, IplImage* Img, int Attribute )
{
    cvNamedWindow(Name, Attribute );
    cvShowImage( Name, Img );
    cvWaitKey(0);
    cvDestroyWindow( Name );
}



int main ()
{

    IplImage* pOpenCVImage;
    IplImage* pColorCVImage;

    CvSize ImageSize;
    unsigned char* ImageBuffer = NULL;
    int wKey = -1;

    ImageSize.width = 640;
    ImageSize.height = 480;

    cvNamedWindow( (char*)"Camera", 1 );


    printf("Program started\n");


    pOpenCVImage = cvCreateImage(ImageSize , IPL_DEPTH_8U, 1 ); // Grayscale
    pColorCVImage = cvCreateImage(ImageSize , IPL_DEPTH_8U, 3 ); // Color image



    open_device((char*)"/dev/video0");
    init_device(ImageSize.width, ImageSize.height);


    printf("Start capturing\n");



    start_capturing();



    while(wKey == -1 )
    {
        ImageBuffer = snapFrame();

        if( ImageBuffer != NULL )
        {
            memcpy( pOpenCVImage->imageData, ImageBuffer, pOpenCVImage->imageSize);
            cvCvtColor(pOpenCVImage,pColorCVImage,CV_BayerGB2RGB); // Create a color image from the raw data

            cvShowImage( (char*)"Camera",pColorCVImage);
            wKey = cvWaitKey(10);
        }
        else
        {
            printf("No image buffer retrieved.\n");
            break;
        }
    }

    cvDestroyWindow( (char*)"Camera" );
    stop_capturing();
    uninit_device();
    close_device();

    printf("Program ended\n");

    return 0;

}
