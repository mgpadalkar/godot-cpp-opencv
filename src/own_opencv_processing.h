#ifndef OPENCVPROCESSING_H
#define OPENCVPROCESSING_H

#include <opencv2/imgproc.hpp>

// our class for doing processing in OpenCV
class OpenCVProcessing
{

    public:
        OpenCVProcessing();
        ~OpenCVProcessing();

        cv::Mat process_image(cv::Mat input, bool do_process);
};

#endif
