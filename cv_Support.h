/*
	If not defined, define the cvSupport hedaerfile.

	THIS HEADER FILE INCLUDES ALL THE NECESSARY CLASSES AND FUNCTIONS TO CREATE AN OBJECT FOR
	VIDEO PROCESSING WITH OPENCV.
*/
#ifndef cv_Support
#define cv_Support
#include <iostream>//Standard packages are included if not included before.
#include <string>//C++ String package for string manipulations
#include <time.h>//To access the system dae and time.
//openCV package headers.
#include <opencv2/opencv.hpp>
#include <conio.h> 
using namespace std;
using namespace cv;
//Class for video loading is created with necessary functions.
class LoadVideo {
private:
	string vidFileName;//Video file name.
	int frameWidth;//width of the frame .
	int frameHeight;//Height of the frame.
	bool isFrameSet;//To check whether Frames are explicitly set or not.
	bool doSave;//If set, save the video
	Mat frame; // Mat type variable for storing opencv images.
	VideoCapture cap; // Video capturing object.
public:
	LoadVideo(); //Default constructor.
	LoadVideo(string fileName);//Default constructor with method overloading to set the file name to be read.
	void setFrameSize(int f_width, int f_height);//This function will set the desiered Frame size.(for explicit changes).
	int loadAndCheck();//Check existance of the given file and if exist, return 1.
	void cvProcessBegin(VideoWriter vWriter);//preocessing will start in this function (given argument is only for debugging.)
	VideoWriter cvVideoWrite(string sFileName, int fpsRate);

};
//Default constructor.
LoadVideo::LoadVideo() {
	//All the initial definitions are here.
	vidFileName = "";
	frameWidth = 1024;
	frameHeight = 768;
	isFrameSet = 0;
	doSave = 0;
}
//Default constructor with method overloading to set the file name to be read.
LoadVideo::LoadVideo(string fileName) {
	//All the initial definitions are here with a qualified file name.
	vidFileName = fileName;
	frameWidth = 1024;
	frameHeight = 768;
	isFrameSet = 0;
	doSave = 0;
}
//This function will set the desiered Frame size.(for explicit changes).
void LoadVideo::setFrameSize(int f_width, int f_height) {
	frameWidth = f_width;
	frameHeight = f_height;
	isFrameSet = 1;
}
//Check existance of the given file and if exist, return 1.
int LoadVideo::loadAndCheck() {
	cap.open(vidFileName);
	if (cap.isOpened() == 0)
	{
		cout << "File not Found!" << endl;
		return 0;//(if 0, Error!)For debugging only
	}
	else {
		cout << "File loaded Successfully" << endl;
	}
	if (isFrameSet == 0) //if file size is not set, then set it to half of the original size.
	{
		frameHeight = static_cast<int>((cap.get(CAP_PROP_FRAME_HEIGHT)) / 2);
		frameWidth = static_cast<int>((cap.get(CAP_PROP_FRAME_WIDTH)) / 2);
	}
	return 1;
}
//preocessing will start in this function (given argument "isReady" is only for debugging.)
void LoadVideo::cvProcessBegin(VideoWriter vWriter) {
	while (1) //Forever Loop
	{
		cap.read(frame); //Read the frame from the file
		if (frame.empty())//If not any more then close the process
		{
			cout << "End of the File!" << endl;
			cap.release();
			vWriter.release();
			destroyAllWindows();
			break;
		}
		/*<-------------------------------------- WARNING!!! --------------------------------------------->
			if you are using Visual Studio, you have to change the following setting of the Visual Studio
			from the project properties.
			1) goto ---> Project ---> ffmpeg properties ---> C/C++ -> Advanced

			2) then change the "Disable Specific Warning" by editing it with the error number "4996" without
			   quotations.

			AFTER THAT YOU ARE GOOD TO GO WITH <time.h> functions
		*/
		//Get system time through the time functions.
		time_t currtime;
		struct tm* tInfo;
		char buffer[100];
		time(&currtime);
		tInfo = localtime(&currtime);

		//output of the time is re-formatted to necessary form.
		//First the Date.
		strftime(buffer, sizeof(buffer), "%d.%m.%Y", tInfo);
		string strDate(buffer);

		//Then the time
		strftime(buffer, sizeof(buffer), "%H:%M:%S", tInfo);
		string strTime(buffer);
		//frame is re-sized according to the specified conditions.
		resize(frame, frame, Size(frameWidth, frameHeight));
		putText(frame, strDate, Point(0, 20), CV_FONT_HERSHEY_TRIPLEX, 0.5, Scalar(150, 255, 255), 1);
		putText(frame, strTime, Point(0, 40), CV_FONT_HERSHEY_TRIPLEX, 0.5, Scalar(150, 255, 255), 1);
		namedWindow("Play", WINDOW_NORMAL);
		if (doSave)
		{
			vWriter.write(frame);
		}
		imshow("Play", frame);
		if (waitKey(1) == 27)
		{
			cap.release();
			vWriter.release();
			destroyAllWindows();
			break;//is "esc" pressed, if pressed, then stop the process.
		}
	}
}
//This function will set the necessary parameters for the saved video
VideoWriter LoadVideo::cvVideoWrite(string sFileName, int fpsRate) {
	VideoWriter videoWrite(sFileName, VideoWriter::fourcc('M', 'J', 'P', 'G'), fpsRate, Size(frameWidth, frameHeight));
	if (videoWrite.isOpened() == 0)
	{
		cerr << "Error! Video file cannot be saved" << endl;
	}
	doSave = 1;
	return videoWrite;
}
#endif
