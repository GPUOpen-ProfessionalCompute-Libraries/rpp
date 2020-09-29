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
#include <omp.h>
#include <half.hpp>
#include <fstream>

using namespace cv;
using namespace std;
using half_float::half;

typedef half Rpp16f;

#define RPPPIXELCHECK(pixel) (pixel < (Rpp32f)0) ? ((Rpp32f)0) : ((pixel < (Rpp32f)255) ? pixel : ((Rpp32f)255))

int main(int argc, char **argv)
{
    const int MIN_ARG_COUNT = 8;
    
    if (argc < MIN_ARG_COUNT)
    {
        printf("\nImproper Usage! Needs all arguments!\n");
        printf("\nUsage: ./BatchPD_host_pkd3 <src1 folder> <src2 folder (place same as src1 folder for single image functionalities)> <dst folder> <u8 = 0 / f16 = 1 / f32 = 2 / u8->f16 = 3 / u8->f32 = 4 / i8 = 5 / u8->i8 = 6> <outputFormatToggle (pkd->pkd = 0 / pkd->pln = 1)> <case number = 1:7> <verbosity = 0/1>\n");
        return -1;
    }

    if (atoi(argv[7]) == 1)
    {
        printf("\nInputs for this test case are:");
        printf("\nsrc1 = %s", argv[1]);
        printf("\nsrc2 = %s", argv[2]);
        printf("\ndst = %s", argv[3]);
        printf("\nu8 / f16 / f32 / u8->f16 / u8->f32 / i8 / u8->i8 (0/1/2/3/4/5/6) = %s", argv[4]);
        printf("\noutputFormatToggle (pkd->pkd = 0 / pkd->pln = 1) = %s", argv[5]);
        printf("\ncase number (1:7) = %s", argv[6]);
    }

    char *src = argv[1];
    char *src_second = argv[2];
    char *dst = argv[3];
    int ip_bitDepth = atoi(argv[4]);
    unsigned int outputFormatToggle = atoi(argv[5]);
    int test_case = atoi(argv[6]);

    int ip_channel = 3;

    char funcType[1000] = {"BatchPD_HOST_PKD3"};

    if (outputFormatToggle == 0)
    {
        strcat(funcType, "_toPKD3");
    }
    else if (outputFormatToggle == 1)
    {
        strcat(funcType, "_toPLN3");
    }

    char funcName[1000];
    switch (test_case)
    {
    case 1:
        strcpy(funcName, "water");
        break;
    case 2:
        strcpy(funcName, "non_linear_blend");
        break;
    case 3:
        strcpy(funcName, "color_cast");
        break;
    case 4:
        strcpy(funcName, "erase");
        break;
    case 5:
        strcpy(funcName, "warp_affine");
        break;
    case 6:
        strcpy(funcName, "crop_and_patch");
        break;
    case 7:
        strcpy(funcName, "lut");
        break;
    }

    if (ip_bitDepth == 0)
    {
        strcat(funcName, "_u8_");
    }
    else if (ip_bitDepth == 1)
    {
        strcat(funcName, "_f16_");
    }
    else if (ip_bitDepth == 2)
    {
        strcat(funcName, "_f32_");
    }
    else if (ip_bitDepth == 3)
    {
        strcat(funcName, "_u8_f16_");
    }
    else if (ip_bitDepth == 4)
    {
        strcat(funcName, "_u8_f32_");
    }
    else if (ip_bitDepth == 5)
    {
        strcat(funcName, "_i8_");
    }
    else if (ip_bitDepth == 6)
    {
        strcat(funcName, "_u8_i8_");
    }

    char func[1000];
    strcpy(func, funcName);
    strcat(func, funcType);
    printf("\nRunning %s...", func);

    int missingFuncFlag = 0;

    int i = 0, j = 0;
    int minHeight = 30000, minWidth = 30000, maxHeight = 0, maxWidth = 0;
    int minDstHeight = 30000, minDstWidth = 30000, maxDstHeight = 0, maxDstWidth = 0;
    unsigned long long count = 0;
    unsigned long long ioBufferSize = 0;
    unsigned long long oBufferSize = 0;
    static int noOfImages = 0;

    Mat image, image_second;

    struct dirent *de;
    char src1[1000];
    strcpy(src1, src);
    strcat(src1, "/");
    char src1_second[1000];
    strcpy(src1_second, src_second);
    strcat(src1_second, "/");
    strcat(funcName, funcType);
    strcat(dst, "/");
    strcat(dst, funcName);

    DIR *dr = opendir(src);
    while ((de = readdir(dr)) != NULL)
    {
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
            continue;
        noOfImages += 1;
    }
    closedir(dr);

    RppiSize *srcSize = (RppiSize *)calloc(noOfImages, sizeof(RppiSize));
    RppiSize *dstSize = (RppiSize *)calloc(noOfImages, sizeof(RppiSize));
    const int images = noOfImages;
    char imageNames[images][1000];

    DIR *dr1 = opendir(src);
    while ((de = readdir(dr1)) != NULL)
    {
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
            continue;
        strcpy(imageNames[count], de->d_name);
        char temp[1000];
        strcpy(temp, src1);
        strcat(temp, imageNames[count]);
        
        image = imread(temp, 1);
        
        srcSize[count].height = image.rows;
        srcSize[count].width = image.cols;
        if (maxHeight < srcSize[count].height)
            maxHeight = srcSize[count].height;
        if (maxWidth < srcSize[count].width)
            maxWidth = srcSize[count].width;
        if (minHeight > srcSize[count].height)
            minHeight = srcSize[count].height;
        if (minWidth > srcSize[count].width)
            minWidth = srcSize[count].width;

        dstSize[count].height = image.rows;
        dstSize[count].width = image.cols;
        if (maxDstHeight < dstSize[count].height)
            maxDstHeight = dstSize[count].height;
        if (maxDstWidth < dstSize[count].width)
            maxDstWidth = dstSize[count].width;
        if (minDstHeight > dstSize[count].height)
            minDstHeight = dstSize[count].height;
        if (minDstWidth > dstSize[count].width)
            minDstWidth = dstSize[count].width;

        count++;
    }
    closedir(dr1);

    ioBufferSize = (unsigned long long)maxHeight * (unsigned long long)maxWidth * (unsigned long long)ip_channel * (unsigned long long)noOfImages;
    oBufferSize = (unsigned long long)maxDstHeight * (unsigned long long)maxDstWidth * (unsigned long long)ip_channel * (unsigned long long)noOfImages;

    Rpp8u *input = (Rpp8u *)calloc(ioBufferSize, sizeof(Rpp8u));
    Rpp8u *input_second = (Rpp8u *)calloc(ioBufferSize, sizeof(Rpp8u));
    Rpp8u *output = (Rpp8u *)calloc(oBufferSize, sizeof(Rpp8u));

    Rpp16f *inputf16 = (Rpp16f *)calloc(ioBufferSize, sizeof(Rpp16f));
    Rpp16f *inputf16_second = (Rpp16f *)calloc(ioBufferSize, sizeof(Rpp16f));
    Rpp16f *outputf16 = (Rpp16f *)calloc(ioBufferSize, sizeof(Rpp16f));

    Rpp32f *inputf32 = (Rpp32f *)calloc(ioBufferSize, sizeof(Rpp32f));
    Rpp32f *inputf32_second = (Rpp32f *)calloc(ioBufferSize, sizeof(Rpp32f));
    Rpp32f *outputf32 = (Rpp32f *)calloc(ioBufferSize, sizeof(Rpp32f));

    Rpp8s *inputi8 = (Rpp8s *)calloc(ioBufferSize, sizeof(Rpp8s));
    Rpp8s *inputi8_second = (Rpp8s *)calloc(ioBufferSize, sizeof(Rpp8s));
    Rpp8s *outputi8 = (Rpp8s *)calloc(ioBufferSize, sizeof(Rpp8s));

    RppiSize maxSize, maxDstSize;
    maxSize.height = maxHeight;
    maxSize.width = maxWidth;
    maxDstSize.height = maxDstHeight;
    maxDstSize.width = maxDstWidth;

    DIR *dr2 = opendir(src);
    DIR *dr2_second = opendir(src_second);
    count = 0;
    i = 0;
    while ((de = readdir(dr2)) != NULL)
    {
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
            continue;

        count = (unsigned long long)i * (unsigned long long)maxHeight * (unsigned long long)maxWidth * (unsigned long long)ip_channel;

        char temp[1000];
        strcpy(temp, src1);
        strcat(temp, de->d_name);

        char temp_second[1000];
        strcpy(temp_second, src1_second);
        strcat(temp_second, de->d_name);

        image = imread(temp, 1);
        image_second = imread(temp_second, 1);

        Rpp8u *ip_image = image.data;
        Rpp8u *ip_image_second = image_second.data;
        for (j = 0; j < srcSize[i].height; j++)
        {
            for (int x = 0; x < srcSize[i].width; x++)
            {
                for (int y = 0; y < ip_channel; y++)
                {
                    input[count + ((j * maxWidth * ip_channel) + (x * ip_channel) + y)] = ip_image[(j * srcSize[i].width * ip_channel) + (x * ip_channel) + y];
                    input_second[count + ((j * maxWidth * ip_channel) + (x * ip_channel) + y)] = ip_image_second[(j * srcSize[i].width * ip_channel) + (x * ip_channel) + y];
                }
            }
        }
        i++;
    }
    closedir(dr2);

    if (ip_bitDepth == 1)
    {
        Rpp8u *inputTemp, *input_secondTemp;
        Rpp16f *inputf16Temp, *inputf16_secondTemp;

        inputTemp = input;
        input_secondTemp = input_second;

        inputf16Temp = inputf16;
        inputf16_secondTemp = inputf16_second;

        for (int i = 0; i < ioBufferSize; i++)
        {
            *inputf16Temp = ((Rpp16f)*inputTemp) / 255.0;
            *inputf16_secondTemp = ((Rpp16f)*input_secondTemp) / 255.0;
            inputTemp++;
            inputf16Temp++;
            input_secondTemp++;
            inputf16_secondTemp++;
        }
    }
    else if (ip_bitDepth == 2)
    {
        Rpp8u *inputTemp, *input_secondTemp;
        Rpp32f *inputf32Temp, *inputf32_secondTemp;

        inputTemp = input;
        input_secondTemp = input_second;

        inputf32Temp = inputf32;
        inputf32_secondTemp = inputf32_second;

        for (int i = 0; i < ioBufferSize; i++)
        {
            *inputf32Temp = ((Rpp32f)*inputTemp) / 255.0;
            *inputf32_secondTemp = ((Rpp32f)*input_secondTemp) / 255.0;
            inputTemp++;
            inputf32Temp++;
            input_secondTemp++;
            inputf32_secondTemp++;
        }
    }
    else if (ip_bitDepth == 5)
    {
        Rpp8u *inputTemp, *input_secondTemp;
        Rpp8s *inputi8Temp, *inputi8_secondTemp;

        inputTemp = input;
        input_secondTemp = input_second;

        inputi8Temp = inputi8;
        inputi8_secondTemp = inputi8_second;

        for (int i = 0; i < ioBufferSize; i++)
        {
            *inputi8Temp = (Rpp8s) (((Rpp32s) *inputTemp) - 128);
            *inputi8_secondTemp = (Rpp8s) (((Rpp32s) *input_secondTemp) - 128);
            inputTemp++;
            inputi8Temp++;
            input_secondTemp++;
            inputi8_secondTemp++;
        }
    }

    rppHandle_t handle;
    rppCreateWithBatchSize(&handle, noOfImages);
    clock_t start, end;
    double start_omp, end_omp;
    double cpu_time_used, omp_time_used;

    string test_case_name;

    switch (test_case)
    {
    case 1:
    {
        test_case_name = "water";

        Rpp32f ampl_x[images];
        Rpp32f ampl_y[images];
        Rpp32f freq_x[images];
        Rpp32f freq_y[images];
        Rpp32f phase_x[images];
        Rpp32f phase_y[images];

        for (i = 0; i < images; i++)
        {
            ampl_x[i] = 1.0;
            ampl_y[i] = 1.0;
            freq_x[i] = 0.8;
            freq_y[i] = 1.2;
            phase_x[i] = 10.0;
            phase_y[i] = 5;
        }

        start = clock();
        start_omp = omp_get_wtime();
        if (ip_bitDepth == 0)
            rppi_water_u8_pkd3_batchPD_host(input, srcSize, maxSize, output, ampl_x, ampl_y, freq_x, freq_y, phase_x, phase_y, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 1)
            rppi_water_f16_pkd3_batchPD_host(inputf16, srcSize, maxSize, outputf16, ampl_x, ampl_y, freq_x, freq_y, phase_x, phase_y, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 2)
            rppi_water_f32_pkd3_batchPD_host(inputf32, srcSize, maxSize, outputf32, ampl_x, ampl_y, freq_x, freq_y, phase_x, phase_y, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 3)
            missingFuncFlag = 1;
        else if (ip_bitDepth == 4)
            missingFuncFlag = 1;
        else if (ip_bitDepth == 5)
            rppi_water_i8_pkd3_batchPD_host(inputi8, srcSize, maxSize, outputi8, ampl_x, ampl_y, freq_x, freq_y, phase_x, phase_y, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 6)
            missingFuncFlag = 1;
        else
            missingFuncFlag = 1;
        end_omp = omp_get_wtime();
        end = clock();

        break;
    }
    case 2:
    {
        test_case_name = "non_linear_blend";

        Rpp32f std_dev[images];
        for (i = 0; i < images; i++)
        {
            std_dev[i] = 350.0;
        }

        start = clock();
        start_omp = omp_get_wtime();
        if (ip_bitDepth == 0)
            rppi_non_linear_blend_u8_pkd3_batchPD_host(input, input_second, srcSize, maxSize, output, std_dev, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 1)
            rppi_non_linear_blend_f16_pkd3_batchPD_host(inputf16, inputf16_second, srcSize, maxSize, outputf16, std_dev, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 2)
            rppi_non_linear_blend_f32_pkd3_batchPD_host(inputf32, inputf32_second, srcSize, maxSize, outputf32, std_dev, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 3)
            missingFuncFlag = 1;
        else if (ip_bitDepth == 4)
            missingFuncFlag = 1;
        else if (ip_bitDepth == 5)
            rppi_non_linear_blend_i8_pkd3_batchPD_host(inputi8, inputi8_second, srcSize, maxSize, outputi8, std_dev, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 6)
            missingFuncFlag = 1;
        else
            missingFuncFlag = 1;
        end_omp = omp_get_wtime();
        end = clock();

        break;
    }
    case 3:
    {
        test_case_name = "color_cast";

        Rpp8u r[images];
        Rpp8u g[images];
        Rpp8u b[images];
        Rpp32f alpha[images];
        for (i = 0; i < images; i++)
        {
            r[i] = 0;
            g[i] = 0;
            b[i] = 100;
            alpha[i] = 0.5;
        }

        start = clock();
        start_omp = omp_get_wtime();
        if (ip_bitDepth == 0)
            rppi_color_cast_u8_pkd3_batchPD_host(input, srcSize, maxSize, output, r, g, b, alpha, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 1)
            rppi_color_cast_f16_pkd3_batchPD_host(inputf16, srcSize, maxSize, outputf16, r, g, b, alpha, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 2)
            rppi_color_cast_f32_pkd3_batchPD_host(inputf32, srcSize, maxSize, outputf32, r, g, b, alpha, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 3)
            missingFuncFlag = 1;
        else if (ip_bitDepth == 4)
            missingFuncFlag = 1;
        else if (ip_bitDepth == 5)
            rppi_color_cast_i8_pkd3_batchPD_host(inputi8, srcSize, maxSize, outputi8, r, g, b, alpha, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 6)
            missingFuncFlag = 1;
        else
            missingFuncFlag = 1;
        end_omp = omp_get_wtime();
        end = clock();

        break;
    }
    case 4:
    {
        test_case_name = "erase";

        Rpp32u boxesInEachImage = 3;
        
        Rpp32u anchor_box_info[images * boxesInEachImage * 4];
        Rpp32u box_offset[images];
        Rpp32u num_of_boxes[images];
        Rpp8u colorsu8[images * boxesInEachImage * 3];
        Rpp32f colorsf32[images * boxesInEachImage * 3];
        Rpp16f colorsf16[images * boxesInEachImage * 3];
        Rpp8s colorsi8[images * boxesInEachImage * 3];
        
        for (i = 0; i < images; i++)
        {
            box_offset[i] = i * boxesInEachImage;
            num_of_boxes[i] = boxesInEachImage;

            anchor_box_info[(boxesInEachImage * 4 * i)] = 0.125 * srcSize[i].width;
            anchor_box_info[(boxesInEachImage * 4 * i) + 1] = 0.125 * srcSize[i].height;
            anchor_box_info[(boxesInEachImage * 4 * i) + 2] = 0.375 * srcSize[i].width;
            anchor_box_info[(boxesInEachImage * 4 * i) + 3] = 0.375 * srcSize[i].height;

            anchor_box_info[(boxesInEachImage * 4 * i) + 4] = 0.125 * srcSize[i].width;
            anchor_box_info[(boxesInEachImage * 4 * i) + 5] = 0.625 * srcSize[i].height;
            anchor_box_info[(boxesInEachImage * 4 * i) + 6] = 0.875 * srcSize[i].width;
            anchor_box_info[(boxesInEachImage * 4 * i) + 7] = 0.875 * srcSize[i].height;

            anchor_box_info[(boxesInEachImage * 4 * i) + 8] = 0.75 * srcSize[i].width;
            anchor_box_info[(boxesInEachImage * 4 * i) + 9] = 0.125 * srcSize[i].height;
            anchor_box_info[(boxesInEachImage * 4 * i) + 10] = 0.875 * srcSize[i].width;
            anchor_box_info[(boxesInEachImage * 4 * i) + 11] = 0.5 * srcSize[i].height;

            colorsu8[(boxesInEachImage * 3 * i)] = (Rpp8u) 240;
            colorsu8[(boxesInEachImage * 3 * i) + 1] = (Rpp8u) 0;
            colorsu8[(boxesInEachImage * 3 * i) + 2] = (Rpp8u) 0;

            colorsu8[(boxesInEachImage * 3 * i) + 3] = (Rpp8u) 0;
            colorsu8[(boxesInEachImage * 3 * i) + 4] = (Rpp8u) 240;
            colorsu8[(boxesInEachImage * 3 * i) + 5] = (Rpp8u) 0;

            colorsu8[(boxesInEachImage * 3 * i) + 6] = (Rpp8u) 0;
            colorsu8[(boxesInEachImage * 3 * i) + 7] = (Rpp8u) 0;
            colorsu8[(boxesInEachImage * 3 * i) + 8] = (Rpp8u) 240;

            colorsf32[(boxesInEachImage * 3 * i)] = (Rpp32f) (240.0 / 255.0);
            colorsf32[(boxesInEachImage * 3 * i) + 1] = (Rpp32f) (0.0 / 255.0);
            colorsf32[(boxesInEachImage * 3 * i) + 2] = (Rpp32f) (0.0 / 255.0);

            colorsf32[(boxesInEachImage * 3 * i) + 3] = (Rpp32f) (0.0 / 255.0);
            colorsf32[(boxesInEachImage * 3 * i) + 4] = (Rpp32f) (240.0 / 255.0);
            colorsf32[(boxesInEachImage * 3 * i) + 5] = (Rpp32f) (0.0 / 255.0);

            colorsf32[(boxesInEachImage * 3 * i) + 6] = (Rpp32f) (0.0 / 255.0);
            colorsf32[(boxesInEachImage * 3 * i) + 7] = (Rpp32f) (0.0 / 255.0);
            colorsf32[(boxesInEachImage * 3 * i) + 8] = (Rpp32f) (240.0 / 255.0);

            colorsf16[(boxesInEachImage * 3 * i)] = (Rpp16f) (240.0 / 255.0);
            colorsf16[(boxesInEachImage * 3 * i) + 1] = (Rpp16f) (0.0 / 255.0);
            colorsf16[(boxesInEachImage * 3 * i) + 2] = (Rpp16f) (0.0 / 255.0);

            colorsf16[(boxesInEachImage * 3 * i) + 3] = (Rpp16f) (0.0 / 255.0);
            colorsf16[(boxesInEachImage * 3 * i) + 4] = (Rpp16f) (240.0 / 255.0);
            colorsf16[(boxesInEachImage * 3 * i) + 5] = (Rpp16f) (0.0 / 255.0);

            colorsf16[(boxesInEachImage * 3 * i) + 6] = (Rpp16f) (0.0 / 255.0);
            colorsf16[(boxesInEachImage * 3 * i) + 7] = (Rpp16f) (0.0 / 255.0);
            colorsf16[(boxesInEachImage * 3 * i) + 8] = (Rpp16f) (240.0 / 255.0);

            colorsi8[(boxesInEachImage * 3 * i)] = (Rpp8s) (240 - 128);
            colorsi8[(boxesInEachImage * 3 * i) + 1] = (Rpp8s) (0 - 128);
            colorsi8[(boxesInEachImage * 3 * i) + 2] = (Rpp8s) (0 - 128);

            colorsi8[(boxesInEachImage * 3 * i) + 3] = (Rpp8s) (0 - 128);
            colorsi8[(boxesInEachImage * 3 * i) + 4] = (Rpp8s) (240 - 128);
            colorsi8[(boxesInEachImage * 3 * i) + 5] = (Rpp8s) (0 - 128);

            colorsi8[(boxesInEachImage * 3 * i) + 6] = (Rpp8s) (0 - 128);
            colorsi8[(boxesInEachImage * 3 * i) + 7] = (Rpp8s) (0 - 128);
            colorsi8[(boxesInEachImage * 3 * i) + 8] = (Rpp8s) (240 - 128);
        }

        start = clock();
        start_omp = omp_get_wtime();
        if (ip_bitDepth == 0)
            rppi_erase_u8_pkd3_batchPD_host(input, srcSize, maxSize, output, anchor_box_info, colorsu8, box_offset, num_of_boxes, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 1)
            rppi_erase_f16_pkd3_batchPD_host(inputf16, srcSize, maxSize, outputf16, anchor_box_info, colorsf16, box_offset, num_of_boxes, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 2)
            rppi_erase_f32_pkd3_batchPD_host(inputf32, srcSize, maxSize, outputf32, anchor_box_info, colorsf32, box_offset, num_of_boxes, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 3)
            missingFuncFlag = 1;
        else if (ip_bitDepth == 4)
            missingFuncFlag = 1;
        else if (ip_bitDepth == 5)
            rppi_erase_i8_pkd3_batchPD_host(inputi8, srcSize, maxSize, outputi8, anchor_box_info, colorsi8, box_offset, num_of_boxes, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 6)
            missingFuncFlag = 1;
        else
            missingFuncFlag = 1;
        end_omp = omp_get_wtime();
        end = clock();

        break;
    }
    case 5:
    {
        test_case_name = "warp_affine";

        Rpp32f affine_array[6 * images];
        for (i = 0; i < 6 * images; i = i + 6)
        {
            affine_array[i] = 1.23;
            affine_array[i + 1] = 0.5;
            affine_array[i + 2] = 0.0;
            affine_array[i + 3] = -0.8;
            affine_array[i + 4] = 0.83;
            affine_array[i + 5] = 0.0;
        }

        start = clock();
        start_omp = omp_get_wtime();
        if (ip_bitDepth == 0)
            rppi_warp_affine_u8_pkd3_batchPD_host(input, srcSize, maxSize, output, dstSize, maxDstSize, affine_array, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 1)
            rppi_warp_affine_f16_pkd3_batchPD_host(inputf16, srcSize, maxSize, outputf16, dstSize, maxDstSize, affine_array, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 2)
            rppi_warp_affine_f32_pkd3_batchPD_host(inputf32, srcSize, maxSize, outputf32, dstSize, maxDstSize, affine_array, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 3)
            missingFuncFlag = 1;
        else if (ip_bitDepth == 4)
            missingFuncFlag = 1;
        else if (ip_bitDepth == 5)
            rppi_warp_affine_i8_pkd3_batchPD_host(inputi8, srcSize, maxSize, outputi8, dstSize, maxDstSize, affine_array, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 6)
            missingFuncFlag = 1;
        else
            missingFuncFlag = 1;
        end_omp = omp_get_wtime();
        end = clock();

        break;
    }
    case 6:
    {
        test_case_name = "crop_and_patch";

        Rpp32u x11[images];
        Rpp32u y11[images];
        Rpp32u x12[images];
        Rpp32u y12[images];
        Rpp32u x21[images];
        Rpp32u y21[images];
        Rpp32u x22[images];
        Rpp32u y22[images];
        for (i = 0; i < images; i++)
        {
            x11[i] = (Rpp32u) (((Rpp32f) srcSize[i].width) * 0.25);
            y11[i] = (Rpp32u) (((Rpp32f) srcSize[i].height) * 0.25);
            x12[i] = (Rpp32u) (((Rpp32f) srcSize[i].width) * 0.5);
            y12[i] = (Rpp32u) (((Rpp32f) srcSize[i].height) * 0.5);

            x21[i] = (Rpp32u) (((Rpp32f) srcSize[i].width) * 0.5);
            y21[i] = (Rpp32u) (((Rpp32f) srcSize[i].height) * 0.5);
            x22[i] = (Rpp32u) (((Rpp32f) srcSize[i].width) * 0.75);
            y22[i] = (Rpp32u) (((Rpp32f) srcSize[i].height) * 0.75);
        }

        start = clock();
        start_omp = omp_get_wtime();
        if (ip_bitDepth == 0)
            rppi_crop_and_patch_u8_pkd3_batchPD_host(input, input_second, srcSize, maxSize, output, x11, y11, x12, y12, x21, y21, x22, y22, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 1)
            rppi_crop_and_patch_f16_pkd3_batchPD_host(inputf16, inputf16_second, srcSize, maxSize, outputf16, x11, y11, x12, y12, x21, y21, x22, y22, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 2)
            rppi_crop_and_patch_f32_pkd3_batchPD_host(inputf32, inputf32_second, srcSize, maxSize, outputf32, x11, y11, x12, y12, x21, y21, x22, y22, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 3)
            missingFuncFlag = 1;
        else if (ip_bitDepth == 4)
            missingFuncFlag = 1;
        else if (ip_bitDepth == 5)
            rppi_crop_and_patch_i8_pkd3_batchPD_host(inputi8, inputi8_second, srcSize, maxSize, outputi8, x11, y11, x12, y12, x21, y21, x22, y22, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 6)
            missingFuncFlag = 1;
        else
            missingFuncFlag = 1;
        end_omp = omp_get_wtime();
        end = clock();

        break;
    }
    case 7:
    {
        test_case_name = "lut";

        Rpp8u lut8u[images * 256];
        Rpp8s lut8s[images * 256];

        for (i = 0; i < images; i++)
        {
            for (j = 0; j < 256; j++)
            {
                lut8u[(i * 256) + j] = (Rpp8u)(255 - j);
                lut8s[(i * 256) + j] = (Rpp8s)(255 - j - 128);
            }
            
        }

        start = clock();
        start_omp = omp_get_wtime();
        if (ip_bitDepth == 0)
            rppi_lut_u8_pkd3_batchPD_host(input, srcSize, maxSize, output, lut8u, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 1)
            missingFuncFlag = 1;
        else if (ip_bitDepth == 2)
            missingFuncFlag = 1;
        else if (ip_bitDepth == 3)
            missingFuncFlag = 1;
        else if (ip_bitDepth == 4)
            missingFuncFlag = 1;
        else if (ip_bitDepth == 5)
            rppi_lut_i8_pkd3_batchPD_host(inputi8, srcSize, maxSize, outputi8, lut8s, outputFormatToggle, noOfImages, handle);
        else if (ip_bitDepth == 6)
            missingFuncFlag = 1;
        else
            missingFuncFlag = 1;
        end_omp = omp_get_wtime();
        end = clock();

        break;
    }
    default:
        missingFuncFlag = 1;
        break;
    }

    if (missingFuncFlag == 1)
    {
        printf("\nThe functionality %s doesn't yet exist in RPP\n", func);
        return -1;
    }

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    omp_time_used = end_omp - start_omp;
    cout << "\nCPU Time - BatchPD : " << cpu_time_used;
    cout << "\nOMP Time - BatchPD : " << omp_time_used;
    printf("\n");

    string fileName = std::to_string(ip_bitDepth);
    ofstream outputFile (fileName + ".csv");

    if (ip_bitDepth == 0)
    {
        Rpp8u *outputTemp;
        outputTemp = output;

        if (outputFile.is_open())
        {
            for (int i = 0; i < oBufferSize; i++)
            {
                outputFile << (Rpp32u) *outputTemp << ",";
                outputTemp++;
            }
            outputFile.close();
        }
        else
            cout << "Unable to open file!";

    }
    else if ((ip_bitDepth == 1) || (ip_bitDepth == 3))
    {
        Rpp8u *outputTemp;
        outputTemp = output;
        Rpp16f *outputf16Temp;
        outputf16Temp = outputf16;

        if (outputFile.is_open())
        {
            for (int i = 0; i < oBufferSize; i++)
            {
                outputFile << *outputf16Temp << ",";
                *outputTemp = (Rpp8u)RPPPIXELCHECK(*outputf16Temp * 255.0);
                outputf16Temp++;
                outputTemp++;
            }
            outputFile.close();
        }
        else
            cout << "Unable to open file!";

    }
    else if ((ip_bitDepth == 2) || (ip_bitDepth == 4))
    {
        Rpp8u *outputTemp;
        outputTemp = output;
        Rpp32f *outputf32Temp;
        outputf32Temp = outputf32;
        
        if (outputFile.is_open())
        {
            for (int i = 0; i < oBufferSize; i++)
            {
                outputFile << *outputf32Temp << ",";
                *outputTemp = (Rpp8u)RPPPIXELCHECK(*outputf32Temp * 255.0);
                outputf32Temp++;
                outputTemp++;
            }
            outputFile.close();
        }
        else
            cout << "Unable to open file!";
    }
    else if ((ip_bitDepth == 5) || (ip_bitDepth == 6))
    {
        Rpp8u *outputTemp;
        outputTemp = output;
        Rpp8s *outputi8Temp;
        outputi8Temp = outputi8;
        
        if (outputFile.is_open())
        {
            for (int i = 0; i < oBufferSize; i++)
            {
                outputFile << (Rpp32s) *outputi8Temp << ",";
                *outputTemp = (Rpp8u) RPPPIXELCHECK(((Rpp32s) *outputi8Temp) + 128);
                outputi8Temp++;
                outputTemp++;
            }
            outputFile.close();
        }
        else
            cout << "Unable to open file!";
    }

    if (outputFormatToggle == 1)
    {
        Rpp8u *outputCopy = (Rpp8u *)calloc(oBufferSize, sizeof(Rpp8u));
        memcpy(outputCopy, output, oBufferSize * sizeof(Rpp8u));
        
        Rpp8u *outputTemp, *outputCopyTemp;
        outputTemp = output;
        outputCopyTemp = outputCopy;

        Rpp32u imageDimMax = maxDstSize.width * maxDstSize.height;

        for (int count = 0; count < noOfImages; count++)
        {
            Rpp32u colIncrementPln = maxDstSize.width - dstSize[count].width;
            Rpp32u rowIncrementPln = (maxDstSize.height - dstSize[count].height) * maxDstSize.width;
            Rpp32u colIncrementPkd = colIncrementPln * ip_channel;
            Rpp32u rowIncrementPkd = rowIncrementPln * ip_channel;

            Rpp8u *outputCopyTempR, *outputCopyTempG, *outputCopyTempB;
            outputCopyTempR = outputCopyTemp;
            outputCopyTempG = outputCopyTempR + imageDimMax;
            outputCopyTempB = outputCopyTempG + imageDimMax;

            for (int i = 0; i < dstSize[count].height; i++)
            {
                for (int j = 0; j < dstSize[count].width; j++)
                {
                    *outputTemp = *outputCopyTempR;
                    outputTemp++;
                    outputCopyTempR++;
                    *outputTemp = *outputCopyTempG;
                    outputTemp++;
                    outputCopyTempG++;
                    *outputTemp = *outputCopyTempB;
                    outputTemp++;
                    outputCopyTempB++;
                }
                memset(outputTemp, (Rpp8u) 0, colIncrementPkd * sizeof(Rpp8u));
                outputTemp += colIncrementPkd;
                outputCopyTempR += colIncrementPln;
                outputCopyTempG += colIncrementPln;
                outputCopyTempB += colIncrementPln;
            }
            memset(outputTemp, (Rpp8u) 0, rowIncrementPkd * sizeof(Rpp8u));
            outputTemp += rowIncrementPkd;
            outputCopyTemp += (imageDimMax * ip_channel);
        }

        free(outputCopy);
    }

    rppDestroyHost(handle);

    mkdir(dst, 0700);
    strcat(dst, "/");
    count = 0;
    for (j = 0; j < noOfImages; j++)
    {
        int op_size = maxHeight * maxWidth * ip_channel;
        Rpp8u *temp_output = (Rpp8u *)calloc(op_size, sizeof(Rpp8u));
        for (i = 0; i < op_size; i++)
        {
            temp_output[i] = output[count];
            count++;
        }
        char temp[1000];
        strcpy(temp, dst);
        strcat(temp, imageNames[j]);
        Mat mat_op_image;
        mat_op_image = Mat(maxHeight, maxWidth, CV_8UC3, temp_output);
        imwrite(temp, mat_op_image);
        free(temp_output);
    }

    free(srcSize);
    free(dstSize);
    free(input);
    free(input_second);
    free(output);
    free(inputf16);
    free(inputf16_second);
    free(outputf16);
    free(inputf32);
    free(inputf32_second);
    free(outputf32);

    return 0;
}
