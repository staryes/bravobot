/*
 * test_slic.cpp.
 *
 * Written by: Pascal Mettes.
 *
 * This file creates an over-segmentation of a provided image based on the SLIC
 * superpixel algorithm, as implemented in slic.h and slic.cpp.
 */
 
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <float.h>
using namespace std;

#include "slic.h"

int main(int argc, char *argv[]) {
    /* Load the image and convert to Lab colour space. */
    IplImage *image = cvLoadImage(argv[1], 1);
    IplImage *lab_image = cvCloneImage(image);
    cvCvtColor(image, lab_image, CV_BGR2Lab);
    
    /* Yield the number of superpixels and weight-factors from the user. */
    int w = image->width, h = image->height;
    int nr_superpixels = atoi(argv[2]);
    int nc = atoi(argv[3]);

    double step = sqrt((w * h) / (double) nr_superpixels);
    
    /* Perform the SLIC superpixel algorithm. */
    Slic slic;
    slic.generate_superpixels(lab_image, step, nc);
    slic.create_connectivity(lab_image);
    
    /* Display the contours and show the result. */
    IplImage *coloured_image = cvCloneImage(image);
    slic.two_level_cluster(coloured_image, 0, 1.5, 3, 0.5);
    slic.display_contours(coloured_image, CV_RGB(255,0,0));
    cvShowImage("result", coloured_image);
    cvWaitKey(0);
    cvSaveImage(argv[4], coloured_image);
}
