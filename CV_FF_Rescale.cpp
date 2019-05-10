/*
	ALL INSTRUCTIONS HAVE BEEN PROVIDED IN THE "INSTRUCTION.txt" FILE.
	FOLLOW THEM BEFORE RUN THE APPLICATION

	DATE AND TIME WILL BE DISPLAYED IN YELLOW COLOR.
	THEREFORE WITH YELLOW BACKGROUNDS IN THE VIDEO TIME AND DATE MIGTH BARELY VISIBLE.
	THIS CAN BE CHANGEd BY CHANGING THE Scaler values of putText function IN THE cvSupport.h

	-------------------------- CONTROLLERS --------------------------
	PRESS "ESC" BUTTON TO STOP THE VIDEO WHILE IT IS PLAYING TO STOP 
	BEFORE IT IS ENDED.
	AFTER THE VIDEO IS CLOSED, NEW FILE WILL BE AUTOMATICALLY SAVED BY
	THE PROGRAM.

	Author @ BUDDHIKA ABEYSEKERA
	Check out me on: LinkedIn	:https://www.linkedin.com/in/babey/
			 GitHub		:https://github.com/mbabeysekera/
*/
//Include all necessary genaral header files.
#include <iostream>
#include <string>
#include <vector>
//video processing with openCV header file
#include "cv_Support.h" 
using namespace std;
using namespace cv;
int main()
{
	//Create the class object to load and process the video file.
	//set Your video file location as a string.
	string fileNameDir = "D:/EXAMPLE_FILE.mp4"; 
	LoadVideo dance(fileNameDir);
	//dance.setFrameSize(640, 480); //This is optional. If you want, you can cnahge the frame size manually. 
									//othewise it will be half of the original frame size
	dance.loadAndCheck();
	// set Your video file save location as a string.
    // Specify the file name with ".avi" extension.
	VideoWriter sendDetails = dance.cvVideoWrite("D:/RESCALED_COPY.avi", 25);
	//There was a problem with saving the file in MPEG4 (.mp4) form. Thats why the file extension set to ".avi".
	dance.cvProcessBegin(sendDetails);
	return 0;
}
