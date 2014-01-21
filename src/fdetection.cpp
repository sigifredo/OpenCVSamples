
// http://mymobilerobots.com/myblog/academic/tutorial-opencv-2-4-3-face-tracking-detection-using-vs-2010-c/

// OpenCV
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// std
#include <cstdio>
#include <iostream>

// unix
#include <signal.h>

#define NAME        "/tmp/SS"

bool saveVideo = true;

void interruptHandler(int);

int main(int argc, const char** argv)
{
    unsigned int i;
    //setup image files used in the capture process
    cv::Mat captureFrame;
    cv::Mat grayscaleFrame;
    bool faceDetected;

    //create the cascade classifier object used for the face detection
    cv::CascadeClassifier face_cascade;
    //use the haarcascade_frontalface_alt.xml library
    face_cascade.load("haarcascade_frontalface_alt.xml");

    //setup video capture device and link it to the first capture device
    cv::VideoCapture captureDevice(0);

    int ex = static_cast<int>(captureDevice.get(CV_CAP_PROP_FOURCC));     // Get Codec Type- Int form
    cv::Size S = cv::Size((int) captureDevice.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
                  (int) captureDevice.get(CV_CAP_PROP_FRAME_HEIGHT));

    // video writer
    cv::VideoWriter outputVideo;
    outputVideo.open(NAME, -1, captureDevice.get(CV_CAP_PROP_FPS), S, true);

    if (captureDevice.isOpened() && outputVideo.isOpened()) // captureDevice.open(0);
    {
        //create a window to present the results
        cv::namedWindow("outputCapture", 1);

        signal(SIGINT, interruptHandler);
        signal(SIGTERM, interruptHandler);

        //create a loop to capture and find faces
        while (saveVideo)
        {
            faceDetected = false;

            //capture a new image frame
            captureDevice >> captureFrame;

            //convert captured image to gray scale and equalize
            cvtColor(captureFrame, grayscaleFrame, CV_BGR2GRAY);
            equalizeHist(grayscaleFrame, grayscaleFrame);

            //create a vector array to store the face found
            std::vector<cv::Rect> faces;

            //find faces and store them in the vector array
            face_cascade.detectMultiScale(grayscaleFrame, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, cv::Size(30,30));

            //draw a rectangle for all found faces in the vector array on the original image
            for (i = 0; i < faces.size(); i++)
            {
                faceDetected = true;
                cv::Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
                cv::Point pt2(faces[i].x, faces[i].y);

                rectangle(captureFrame, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);
            }

            //print the output
            if (faceDetected)
                outputVideo << captureFrame;

            imshow("outputCapture", captureFrame);

            if (cv::waitKey(30) >= 0)
                break;
        }
    }

    return 0;
}

void interruptHandler(int)
{
    saveVideo = false;
}

