#ifndef pedestrian_detector_h
#define pedestrian_detector_h

#include <opencv2/highgui.hpp>

/**
 * @brief Describes an interface to detect the largest pedestrian in the
 * provided image.
 * @author jean-michel-gonet
 */
class PedestrianDetector {
public:
	virtual ~PedestrianDetector() = default;
	/** @brief Receives and process one image.
	 * Finds the largest pedestrian  in it, and computes its position.
	 * @param image The image.
	 */
	virtual void processImage(cv::Mat image) = 0;
	/** 
	 * @brief Returns the position of the largest pedestrian found
	 * in the last processed image.
	 * The position is expressed with a value between -1 and 1.
	 * -1 means that the pedestrian is located at the left side of the image.
	 * 0 means that the pedestrian is located at the center of the image.
	 * 1 means that the pedestrian is located at the right side of the image.
	 * @return The position of the pedestrian.
	 */
	virtual double getPedestrianPosition() = 0;
	/** @brief Returns the size of the largest pedestrian found
	 * in the last processed image.
	 * The size is expressed with a value between 0 and 1.
	 * 0 means that no pedestrian was found.
	 * 1 means that the pedestrian occupies the whole image.
	 * @return The size of the pedestrian.
	 */
	virtual double getPedestrianSize() = 0;
};


#endif
