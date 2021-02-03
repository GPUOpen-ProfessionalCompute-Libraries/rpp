#include <stdio.h> 
#include <dirent.h>
#include <string.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "/opt/rocm/rpp/include/rppi.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
using namespace cv;
using namespace std;
#include <CL/cl.hpp>
int main(int argc, char **argv)
{
    const int MIN_ARG_COUNT = 5;
    printf("\nUsage: ./batchDD_ocl <src1 folder> <src2 folder (place same as src1 folder for single image functionalities)> <dst folder> <case number = 0:64>\n");
    if (argc < MIN_ARG_COUNT)
    {
        printf("\nImproper Usage! Needs all arguments!\n");
        return -1;
    }

    printf("\nsrc1 = %s", argv[1]);
    printf("\nsrc2 = %s", argv[2]);
    printf("\ndst = %s", argv[3]);
    printf("\ncase number (1:64) = %s", argv[4]);

    char *src = argv[1];
    char *src_second = argv[2];
    char *dst = argv[3];
    int test_case = atoi(argv[4]);

    int ip_channel = 3;

    char funcType[1000] = {"batchDD_ROID_OCL_PKD3"};

    char funcName[1000];
    switch (test_case)
    {
    case 0:
        strcpy(funcName, "brightness");
        break;
    case 1:
        strcpy(funcName, "contrast");
        break;
    case 2:
        strcpy(funcName, "blur");
        break;
    case 3:
        strcpy(funcName, "jitter");
        break;
    case 4:
        strcpy(funcName, "blend");
        break;
    case 5:
        strcpy(funcName, "color_temperature");
        break;
    case 6:
        strcpy(funcName, "gamma_correction");
        break;
    case 7:
        strcpy(funcName, "fog");
        break;
    case 8:
        strcpy(funcName, "snow");
        break;
    case 9:
        strcpy(funcName, "lens_correction");
        break;
    case 10:
        strcpy(funcName, "noise");
        break;
    case 11:
        strcpy(funcName, "pixelate");
        break;
    case 12:
        strcpy(funcName, "exposure");
        break;
    case 13:
        strcpy(funcName, "fisheye");
        break;
    case 14:
        strcpy(funcName, "vignette");
        break;
    case 15:
        strcpy(funcName, "flip");
        break;
    case 16:
        strcpy(funcName, "rotate");
        break;
    case 17:
        strcpy(funcName, "warp_affine");
        break;
    case 18:
        strcpy(funcName, "resize");
        break;
    case 19:
        strcpy(funcName, "resize_crop");
        break;
    case 20:
        strcpy(funcName, "hueRGB");
        break;
    case 21:
        strcpy(funcName, "saturationRGB");
        break;
    case 22:
        strcpy(funcName, "absolute_difference");
        break;
    case 23:
        strcpy(funcName, "accumulate");
        break;
    case 24:
        strcpy(funcName, "accumulate_squared");
        break;
    case 25:
        strcpy(funcName, "accumulate_weighted");
        break;
    case 26:
        strcpy(funcName, "add");
        break;
    case 27:
        strcpy(funcName, "subtract");
        break;
    case 28:
        strcpy(funcName, "bitwise_AND");
        break;
    case 29:
        strcpy(funcName, "exclusive_OR");
        break;
    case 30:
        strcpy(funcName, "inclusive_OR");
        break;
    case 31:
        strcpy(funcName, "bitwise_NOT");
        break;
    case 32:
        strcpy(funcName, "box_filter");
        break;
    case 33:
        strcpy(funcName, "dilate");
        break;
    case 34:
        strcpy(funcName, "erode");
        break;
    case 35:
        strcpy(funcName, "gaussian_filter");
        break;
    case 36:
        strcpy(funcName, "local_binary_pattern");
        break;
    case 37:
        strcpy(funcName, "magnitude");
        break;
    case 38:
        strcpy(funcName, "max");
        break;
    case 39:
        strcpy(funcName, "median_filter");
        break;
    case 40:
        strcpy(funcName, "min");
        break;
    case 41:
        strcpy(funcName, "nonlinear_filter");
        break;
    case 42:
        strcpy(funcName, "non_max_suppression");
        break;
    case 43:
        strcpy(funcName, "phase");
        break;
    case 44:
        strcpy(funcName, "multiply");
        break;
    case 45:
        strcpy(funcName, "scale");
        break;
    case 46:
        strcpy(funcName, "sobel_filter");
        break;
    case 47:
        strcpy(funcName, "thresholding");
        break;
    case 48:
        strcpy(funcName, "warp_perspective");
        break;
    }

    

    char func[1000];
    strcpy(func, funcName);
    strcat(func, funcType);
    printf("\n\nRunning %s...", func);

    int missingFuncFlag = 0;

    int i = 0, j = 0;
    int minHeight = 30000, minWidth = 30000, maxHeight = 0, maxWidth = 0;
    unsigned long long count = 0;
    unsigned long long ioBufferSize = 0;
    
    static int noOfImages = 0;


    Mat image,image_second;

    struct dirent *de;
    char src1[1000];
    strcpy(src1, src);
    strcat(src1, "/");
    char src1_second[1000];
    strcpy(src1_second, src_second);
    strcat(src1_second, "/");
    strcat(funcName,funcType);
    strcat(dst,"/");
    strcat(dst,funcName);
 

    DIR *dr = opendir(src); 
    while ((de = readdir(dr)) != NULL) 
    {
        if(strcmp(de->d_name,".") == 0 || strcmp(de->d_name,"..") == 0)
            continue;
        noOfImages += 1;
    }
    closedir(dr);

    RppiSize *srcSize = (RppiSize *)calloc(noOfImages, sizeof(RppiSize));
    RppiSize *dstSize = (RppiSize *)calloc(noOfImages, sizeof(RppiSize));
    const int images = noOfImages;
    char imageNames[images][1000];
    RppiROI *roiPoints = (RppiROI *)calloc(noOfImages, sizeof(RppiROI));

    DIR *dr1 = opendir(src);
    while ((de = readdir(dr1)) != NULL) 
    {
        if(strcmp(de->d_name,".") == 0 || strcmp(de->d_name,"..") == 0) 
            continue;
        strcpy(imageNames[count],de->d_name);
        char temp[1000];
        strcpy(temp,src1);
        strcat(temp, imageNames[count]);
        if(ip_channel == 3)
        {
            image = imread(temp, 1);
        }
        else
        {
            image = imread(temp, 0);
        }
        srcSize[count].height = image.rows;
        srcSize[count].width = image.cols;
        ioBufferSize += (unsigned long long)srcSize[count].height * (unsigned long long)srcSize[count].width * (unsigned long long)ip_channel;

	while(1)
        {
            roiPoints[count].x = rand() % srcSize[count].width; 
            roiPoints[count].y = rand() % srcSize[count].height; 
            roiPoints[count].roiHeight = (rand() % srcSize[count].height) * 3; 
            roiPoints[count].roiWidth = (rand() % srcSize[count].width) * 3;
            roiPoints[count].roiHeight -= roiPoints[count].y; 
            roiPoints[count].roiWidth -= roiPoints[count].x;
            if((roiPoints[count].y + roiPoints[count].roiHeight > roiPoints[count].y && roiPoints[count].x + roiPoints[count].roiWidth > roiPoints[count].x) && (roiPoints[count].y + roiPoints[count].roiHeight < srcSize[count].height && roiPoints[count].x + roiPoints[count].roiWidth < srcSize[count].width))
                break;
        }
        count++;
    }
    closedir(dr1); 

    Rpp8u *input = (Rpp8u *)calloc(ioBufferSize, sizeof(Rpp8u));
    Rpp8u *input_second = (Rpp8u *)calloc(ioBufferSize, sizeof(Rpp8u));
    Rpp8u *output = (Rpp8u *)calloc(ioBufferSize, sizeof(Rpp8u));

    
    DIR *dr2 = opendir(src);
    count = 0;
    i = 0;
    while ((de = readdir(dr2)) != NULL) 
    {
        if(strcmp(de->d_name,".") == 0 || strcmp(de->d_name,"..") == 0) 
            continue;
        char temp[1000];
        strcpy(temp,src1);
        strcat(temp, de->d_name);   
        char temp_second[1000];
        strcpy(temp_second,src1_second);
        strcat(temp_second, de->d_name);     
        if(ip_channel == 3)
        {
            image = imread(temp, 1);
            image_second = imread(temp_second, 1);
        }
        else
        {
            image = imread(temp, 0);
            image_second = imread(temp_second, 0);
        }
        Rpp8u *ip_image = image.data;
        Rpp8u *ip_image_second = image_second.data;
        for(j = 0 ; j < srcSize[i].height * srcSize[i].width * ip_channel ; j++)
        {
            input[count] = ip_image[j];
            input_second[count] = ip_image_second[j];
            count++;
        }
        i++;
    }
    closedir(dr2); 
    


	cl_mem d_input, d_input_second, d_output;
    cl_platform_id platform_id;
    cl_device_id device_id;
    cl_context theContext;
    cl_command_queue theQueue;
    cl_int err;
    err = clGetPlatformIDs(1, &platform_id, NULL);
    err |= clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);
    theContext = clCreateContext(0, 1, &device_id, NULL, NULL, &err);
    theQueue = clCreateCommandQueue(theContext, device_id, 0, &err);
    d_input = clCreateBuffer(theContext, CL_MEM_READ_ONLY, ioBufferSize * sizeof(Rpp8u), NULL, NULL);
    d_input_second = clCreateBuffer(theContext, CL_MEM_READ_ONLY, ioBufferSize * sizeof(Rpp8u), NULL, NULL);
    d_output = clCreateBuffer(theContext, CL_MEM_READ_ONLY, ioBufferSize * sizeof(Rpp8u), NULL, NULL);
    err |= clEnqueueWriteBuffer(theQueue, d_input, CL_TRUE, 0, ioBufferSize * sizeof(Rpp8u), input, 0, NULL, NULL);
    err |= clEnqueueWriteBuffer(theQueue, d_input_second, CL_TRUE, 0, ioBufferSize * sizeof(Rpp8u), input_second, 0, NULL, NULL);
    rppHandle_t handle;
	rppCreateWithStreamAndBatchSize(&handle, theQueue, noOfImages);
 
	clock_t start, end;
    double cpu_time_used;

    string test_case_name;

	switch (test_case)
    {
    case 0:
    {
        test_case_name = "brightness";

        Rpp32f alpha[images];
        Rpp32f beta[images];
        for (i = 0; i < images; i++)
        {
            alpha[i] = 1.75;
            beta[i] = 50;
        }

        start = clock();
            rppi_brightness_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, alpha, beta, roiPoints, noOfImages, handle);
        end = clock();

        break;
    }
    case 1:
    {
        test_case_name = "contrast";

        Rpp32u newMin[images];
        Rpp32u newMax[images];
        for (i = 0; i < images; i++)
        {
            newMin[i] = 30;
            newMax[i] = 100;
        }

        start = clock();

            rppi_contrast_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, newMin, newMax, roiPoints, noOfImages, handle);

        end = clock();

        break;
    }
    case 2:
    {
        test_case_name = "blur";

        Rpp32u kernelSize[images];
        for (i = 0; i < images; i++)
        {
            kernelSize[i] = 5;
        }

        start = clock();

        
            rppi_blur_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, kernelSize, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 3:
    {
        test_case_name = "jitter";

        Rpp32u kernelSize[images];
        for (i = 0; i < images; i++)
        {
            kernelSize[i] = 5;
        }

        start = clock();

        
            rppi_jitter_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, kernelSize, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 4:
    {
        test_case_name = "blend";

        Rpp32f alpha[images];
        for (i = 0; i < images; i++)
        {
            alpha[i] = 0.5;
        }

        start = clock();

        
            rppi_blend_u8_pkd3_batchDD_ROID_gpu(d_input, d_input_second, srcSize, d_output, alpha, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 5:
    {
        test_case_name = "color_temperature";

        Rpp32s adjustmentValue[images];
        for (i = 0; i < images; i++)
        {
            adjustmentValue[i] = 70;
        }

        start = clock();

        
            rppi_color_temperature_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, adjustmentValue, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 6:
    {
        test_case_name = "gamma_correction";

        Rpp32f gamma[images];
        for (i = 0; i < images; i++)
        {
            gamma[i] = 1.9;
        }

        start = clock();

        
            rppi_gamma_correction_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, gamma, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 7:
    {
        test_case_name = "fog";

        Rpp32f fogValue[images];
        for (i = 0; i < images; i++)
        {
            fogValue[i] = 0.2;
        }

        start = clock();

        
           // rppi_fog_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, fogValue, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 8:
    {
        test_case_name = "snow";

        Rpp32f snowPercentage[images];
        for (i = 0; i < images; i++)
        {
            snowPercentage[i] = 0.6;
        }

        start = clock();

        
            rppi_snow_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, snowPercentage, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 9:
    {
        test_case_name = "lens_correction";

        Rpp32f strength[images];
        Rpp32f zoom[images];
        for (i = 0; i < images; i++)
        {
            strength[i] = 0.8;
            zoom[i] = 1;
        }

        start = clock();

        
            rppi_lens_correction_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, strength, zoom, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 10:
    {
        test_case_name = "noise";

        Rpp32f noiseProbability[images];
        for (i = 0; i < images; i++)
        {
            noiseProbability[i] = 0.2;
        }

        start = clock();

        
            rppi_noise_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, noiseProbability, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 11:
    {
        test_case_name = "pixelate";

        start = clock();

        
            rppi_pixelate_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 12:
    {
        test_case_name = "exposure";

        Rpp32f exposureFactor[images];
        for (i = 0; i < images; i++)
        {
            exposureFactor[i] = 1.4;
        }

        start = clock();

        
            rppi_exposure_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, exposureFactor, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 13:
    {
        test_case_name = "fisheye";

        start = clock();

        
            rppi_fisheye_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 14:
    {
        test_case_name = "vignette";

        Rpp32f stdDev[images];
        for (i = 0; i < images; i++)
        {
            stdDev[i] = 75.0;
        }

        start = clock();

        
            rppi_vignette_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, stdDev, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 15:
    {
        test_case_name = "flip";

        Rpp32u flipAxis[images];
        for (i = 0; i < images; i++)
        {
            flipAxis[i] = 1;
        }

        start = clock();

        
            rppi_flip_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, flipAxis, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 16:
    {
        test_case_name = "rotate";

        Rpp32f angle[images];
        for (i = 0; i < images; i++)
        {
            angle[i] = 50;
        }

        start = clock();

        
            rppi_rotate_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, dstSize,  angle, roiPoints, noOfImages, handle);
        
        end = clock();

        break;
    }
    case 17:
    {
        test_case_name = "warp_affine";

        Rpp32f affine_array[6 * images];
        for (i = 0; i < images; i = i + 6)
        {
            affine_array[i] = 0.83;
            affine_array[i + 1] = 0.5;
            affine_array[i + 2] = 0.0;
            affine_array[i + 3] = -0.5;
            affine_array[i + 4] = 0.83;
            affine_array[i + 5] = 0.0;
        }

        start = clock();

        
            rppi_warp_affine_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, dstSize,affine_array, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 18:
    {
        test_case_name = "resize";


        start = clock();

        
            rppi_resize_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, dstSize,roiPoints, noOfImages, handle);
        
        end = clock();

        break;
    }
    case 19:
    {
        test_case_name = "resize_crop";

        Rpp32u x1[images];
        Rpp32u y1[images];
        Rpp32u x2[images];
        Rpp32u y2[images];
        for (i = 0; i < images; i++)
        {
            x1[i] = 0;
            y1[i] = 0;
            x2[i] = 50;
            y2[i] = 50;
            
        }
        

        start = clock();

        
        //    rppi_resize_crop_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, dstSize,  x1, x2, y1, y2, roiPoints, noOfImages, handle);
        
        end = clock();

        break;
    }
    case 20:
    {
        test_case_name = "hueRGB";

        Rpp32f hueShift[images];
        for (i = 0; i < images; i++)
        {
            hueShift[i] = 60;
        }

        start = clock();

        
            rppi_hueRGB_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, hueShift, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 21:
    {
        test_case_name = "saturationRGB";

        Rpp32f saturationFactor[images];
        for (i = 0; i < images; i++)
        {
            saturationFactor[i] = 5;
        }

        start = clock();

        
            rppi_saturationRGB_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, saturationFactor, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    
    
    case 22:
    {
        test_case_name = "absolute_difference";

        start = clock();

        
            rppi_absolute_difference_u8_pkd3_batchDD_ROID_gpu(d_input, d_input_second, srcSize, d_output, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 23:
    {
        test_case_name = "accumulate";

        start = clock();

        
            rppi_accumulate_u8_pkd3_batchDD_ROID_gpu(d_input, d_input_second, srcSize, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 24:
    {
        test_case_name = "accumulate_squared";

        start = clock();

        
            rppi_accumulate_squared_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 25:
    {
        test_case_name = "accumulate_weighted";

        Rpp32f alpha[images];
        for (i = 0; i < images; i++)
        {
            alpha[i] = 0.5;
        }

        start = clock();

        
            rppi_accumulate_weighted_u8_pkd3_batchDD_ROID_gpu(d_input, d_input_second, srcSize, alpha, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 26:
    {
        test_case_name = "add";

        start = clock();

        
            rppi_add_u8_pkd3_batchDD_ROID_gpu(d_input, d_input_second, srcSize, d_output, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 27:
    {
        test_case_name = "subtract";

        start = clock();

        
            rppi_subtract_u8_pkd3_batchDD_ROID_gpu(d_input, d_input_second, srcSize, d_output, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 28:
    {
        test_case_name = "bitwise_AND";

        start = clock();

        
            rppi_bitwise_AND_u8_pkd3_batchDD_ROID_gpu(d_input, d_input_second, srcSize, d_output, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 29:
    {
        test_case_name = "exclusive_OR";

        start = clock();

        
            rppi_exclusive_OR_u8_pkd3_batchDD_ROID_gpu(d_input, d_input_second, srcSize, d_output, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 30:
    {
        test_case_name = "inclusive_OR";

        start = clock();

        
            rppi_inclusive_OR_u8_pkd3_batchDD_ROID_gpu(d_input, d_input_second, srcSize, d_output, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 31:
    {
        test_case_name = "bitwise_NOT";

        start = clock();

        
            rppi_bitwise_NOT_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 32:
    {
        test_case_name = "box_filter";

        Rpp32u kernelSize[images];
        for (i = 0; i < images; i++)
        {
            kernelSize[i] = 5;
        }

        start = clock();

        
            rppi_box_filter_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, kernelSize, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    
    case 33:
    {
        test_case_name = "dilate";

        Rpp32u kernelSize[images];
        for (i = 0; i < images; i++)
        {
            kernelSize[i] = 5;
        }

        start = clock();

        
            rppi_dilate_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, kernelSize, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    
    case 34:
    {
        test_case_name = "erode";

        Rpp32u kernelSize[images];
        for (i = 0; i < images; i++)
        {
            kernelSize[i] = 5;
        }

        start = clock();

        
            rppi_erode_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, kernelSize, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    
    case 35:
    {
        test_case_name = "gaussian_filter";

        Rpp32u kernelSize[images];
        Rpp32f stdDev[images];
        for (i = 0; i < images; i++)
        {
            kernelSize[i] = 5;
            stdDev[i] = 5.0;
        }

        start = clock();

        
            rppi_gaussian_filter_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, stdDev, kernelSize, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    
    case 36:
    {
        test_case_name = "local_binary_pattern";

        start = clock();

        
            rppi_local_binary_pattern_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 37:
    {
        test_case_name = "magnitude";

        start = clock();

        
            rppi_magnitude_u8_pkd3_batchDD_ROID_gpu(d_input, d_input_second, srcSize, d_output, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 38:
    {
        test_case_name = "max";

        start = clock();

        
            rppi_max_u8_pkd3_batchDD_ROID_gpu(d_input, d_input_second, srcSize, d_output, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 39:
    {
        test_case_name = "median_filter";

        Rpp32u kernelSize[images];
        for (i = 0; i < images; i++)
        {
            kernelSize[i] = 5;
        }

        start = clock();

        
            rppi_median_filter_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, kernelSize, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 40:
    {
        test_case_name = "min";

        start = clock();

        
            rppi_min_u8_pkd3_batchDD_ROID_gpu(d_input, d_input_second, srcSize, d_output, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 41:
    {
        test_case_name = "nonlinear_filter";

        Rpp32u kernelSize[images];
        for (i = 0; i < images; i++)
        {
            kernelSize[i] = 5;
        }

        start = clock();

        
            rppi_nonlinear_filter_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, kernelSize, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 42:
    {
        test_case_name = "non_max_suppression";

        Rpp32u kernelSize[images];
        for (i = 0; i < images; i++)
        {
            kernelSize[i] = 5;
        }

        start = clock();

        
            rppi_non_max_suppression_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, kernelSize, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 43:
    {
        test_case_name = "phase";

        start = clock();

        
            rppi_phase_u8_pkd3_batchDD_ROID_gpu(d_input, d_input_second, srcSize, d_output, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 44:
    {
        test_case_name = "multiply";

        start = clock();

        
            rppi_multiply_u8_pkd3_batchDD_ROID_gpu(d_input, d_input_second, srcSize, d_output, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 45:
    {
        test_case_name = "scale";

        Rpp32f percentage[images];
        for (i = 0; i < images; i++)
        {
            percentage[i] = 100;
        }

        start = clock();

        
            rppi_scale_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, dstSize,  percentage, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 46:
    {
        test_case_name = "sobel_filter";

        Rpp32u sobelType[images];
        for (i = 0; i < images; i++)
        {
            sobelType[i] = 1;
        }

        start = clock();

        
            rppi_sobel_filter_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, sobelType, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 47:
    {
        test_case_name = "thresholding";

        Rpp8u min[images];
        Rpp8u max[images];
        for (i = 0; i < images; i++)
        {
            min[i] = 30;
            max[i] = 100;
        }

        start = clock();

        
            rppi_thresholding_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, min, max, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }
    case 48:
    {
        test_case_name = "warp_perspective";

        const int size_perspective = images * 9;
        Rpp32f perspective[64 * 9];
        for (i = 0; i < images; i++)
        {
            perspective[0 + i * 9] = 0.93;
            perspective[1 + i * 9] = 0.5;
            perspective[2 + i * 9] = 0.0;
            perspective[3 + i * 9] = -0.5;
            perspective[4 + i * 9] = 0.93;
            perspective[5 + i * 9] = 0.0;
            perspective[6 + i * 9] = 0.005;
            perspective[7 + i * 9] = 0.005;
            perspective[8 + i * 9] = 1;
        }

        start = clock();

        
            rppi_warp_perspective_u8_pkd3_batchDD_ROID_gpu(d_input, srcSize, d_output, dstSize, perspective, roiPoints, noOfImages, handle);
        

        end = clock();

        break;
    }


	default:
        break;
  }


    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    //omp_time_used = end_omp - start_omp;
    cout << "\nGPU Time - BatchDD_ROID : " << cpu_time_used << endl;
    //cout << "\nOMP Time - BatchPD : " << omp_time_used;;
    clEnqueueReadBuffer(theQueue, d_output, CL_TRUE, 0, ioBufferSize * sizeof(Rpp8u), output, 0, NULL, NULL);
    
    rppDestroyGPU(handle);

    mkdir(dst, 0700);
    strcat(dst, "/");
    count = 0;
    for(j = 0 ; j < noOfImages ; j++)
    {
        int op_size = srcSize[j].height * srcSize[j].width * ip_channel;
        Rpp8u *temp_output = (Rpp8u *)calloc(op_size, sizeof(Rpp8u));
        for(i = 0 ; i < op_size ; i++)
        {
            temp_output[i] = output[count];
            count++;
        }
        char temp[1000];
        strcpy(temp,dst);
        strcat(temp, imageNames[j]);
        Mat mat_op_image;
        if(ip_channel == 3)
        {
            mat_op_image = Mat(srcSize[j].height, srcSize[j].width, CV_8UC3, temp_output);
            imwrite(temp, mat_op_image);
        }
        if(ip_channel == 1)
        {
            mat_op_image = Mat(srcSize[j].height, srcSize[j].width, CV_8UC1, temp_output);
            imwrite(temp, mat_op_image);
        }
        free(temp_output);
    }

    free(srcSize);
    free(input);
    free(output);
    free(input_second);
	 return 0; 
}
