

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>


int main()
{
    cv::VideoCapture stream1(0);

    if (!stream1.isOpened())
        std::cout << "cannot open camera" << std::endl;

    while (true)
    {
        cv::Mat cameraFrame;
        stream1.read(cameraFrame);
        imshow("cam", cameraFrame);

        if (cv::waitKey(30) >= 0)
            break;
    }

    return 0;
}
