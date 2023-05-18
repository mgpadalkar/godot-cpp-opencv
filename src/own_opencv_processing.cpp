#include "own_opencv_processing.h"

// constructor
OpenCVProcessing::OpenCVProcessing()
{
}


// destructor
OpenCVProcessing::~OpenCVProcessing()
{
}


// our function for processing
cv::Mat OpenCVProcessing::process_image(cv::Mat input, bool do_process)
{
    // do nothing if do_process is false
    cv::Mat output = input.clone();
    if (!do_process)
        return output;

    // get Canny edges
    cv::Mat tmp;
    cv::blur(input, tmp, cv::Size(3, 3)); // blur first
    cv::Canny(tmp, output, 0, 100, 3); // edge detection of blurred image
    return output;
}
