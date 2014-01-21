

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>


int main()
{
    cv::VideoCapture stream1(0);

    if (stream1.isOpened())
    {
        cv::Mat cameraFrame;

        while (true)
        {
            stream1.read(cameraFrame);
            imshow("cam", cameraFrame);

            if (cv::waitKey(30) >= 0)
                break;
        }
    }
    else
        std::cout << "cannot open camera" << std::endl;

    return 0;
}
