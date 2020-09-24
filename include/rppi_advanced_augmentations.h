#ifndef RPPI_ADVANCED_AUGMENTATIONS_H
#define RPPI_ADVANCED_AUGMENTATIONS_H

#include "rppdefs.h"
#include "rpp.h"
#ifdef __cplusplus
extern "C"
{
#endif // cpusplus

/// Non Linear Blend.
/// \param srcPtr1
/// \param srcPtr2
/// \param srcSize - Array of it
/// \param dstPtr
/// \param alpha - non linear blending parameter
/// \param outputForamtToggle - NCHW to NHWC toggling and Vice Versa
/// \param rppHandle
/// \return
RppStatus
rppi_non_linear_blend_u8_pkd3_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp32f *std_dev,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_non_linear_blend_f32_pkd3_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp32f *std_dev,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_non_linear_blend_f16_pkd3_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp32f *std_dev,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_non_linear_blend_i8_pkd3_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp32f *std_dev,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_non_linear_blend_u8_pln3_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp32f *std_dev,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_non_linear_blend_f32_pln3_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp32f *std_dev,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_non_linear_blend_f16_pln3_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp32f *std_dev,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_non_linear_blend_i8_pln3_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp32f *std_dev,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_non_linear_blend_u8_pln1_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp32f *std_dev,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_non_linear_blend_f32_pln1_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp32f *std_dev,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_non_linear_blend_f16_pln1_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp32f *std_dev,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_non_linear_blend_i8_pln1_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp32f *std_dev,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);


/// Water.
/// \param srcPtr
/// \param srcSize - Array of it
/// \param dstPtr
/// \param ampl_x - amplitude in x axis
/// \param ampl_y - amplitude in y axis
/// \param freq_x - frequency in x axis
/// \param freq_y - frequency in y axis
/// \param phase_x - phase in x axis
/// \param phase_y - phase in y axis
/// \param outputForamtToggle - NCHW to NHWC toggling and Vice Versa
/// \param rppHandle
/// \return
RppStatus
rppi_water_u8_pkd3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     Rpp32f *ampl_x, Rpp32f *ampl_y, Rpp32f *freq_x, Rpp32f *freq_y, Rpp32f *phase_x, Rpp32f *phase_y,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_water_f32_pkd3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     Rpp32f *ampl_x, Rpp32f *ampl_y, Rpp32f *freq_x, Rpp32f *freq_y, Rpp32f *phase_x, Rpp32f *phase_y,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_water_f16_pkd3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     Rpp32f *ampl_x, Rpp32f *ampl_y, Rpp32f *freq_x, Rpp32f *freq_y, Rpp32f *phase_x, Rpp32f *phase_y,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_water_i8_pkd3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     Rpp32f *ampl_x, Rpp32f *ampl_y, Rpp32f *freq_x, Rpp32f *freq_y, Rpp32f *phase_x, Rpp32f *phase_y,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_water_u8_pln3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     Rpp32f *ampl_x, Rpp32f *ampl_y, Rpp32f *freq_x, Rpp32f *freq_y, Rpp32f *phase_x, Rpp32f *phase_y,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_water_f32_pln3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     Rpp32f *ampl_x, Rpp32f *ampl_y, Rpp32f *freq_x, Rpp32f *freq_y, Rpp32f *phase_x, Rpp32f *phase_y,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_water_f16_pln3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     Rpp32f *ampl_x, Rpp32f *ampl_y, Rpp32f *freq_x, Rpp32f *freq_y, Rpp32f *phase_x, Rpp32f *phase_y,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_water_i8_pln3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     Rpp32f *ampl_x, Rpp32f *ampl_y, Rpp32f *freq_x, Rpp32f *freq_y, Rpp32f *phase_x, Rpp32f *phase_y,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_water_u8_pln1_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     Rpp32f *ampl_x, Rpp32f *ampl_y, Rpp32f *freq_x, Rpp32f *freq_y, Rpp32f *phase_x, Rpp32f *phase_y,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_water_f32_pln1_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     Rpp32f *ampl_x, Rpp32f *ampl_y, Rpp32f *freq_x, Rpp32f *freq_y, Rpp32f *phase_x, Rpp32f *phase_y,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_water_f16_pln1_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     Rpp32f *ampl_x, Rpp32f *ampl_y, Rpp32f *freq_x, Rpp32f *freq_y, Rpp32f *phase_x, Rpp32f *phase_y,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_water_i8_pln1_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     Rpp32f *ampl_x, Rpp32f *ampl_y, Rpp32f *freq_x, Rpp32f *freq_y, Rpp32f *phase_x, Rpp32f *phase_y,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
// Erase.
/// \param srcPtr1
/// \param srcSize - Array of it
/// \param dstPtr
/// \param anchor_box_info - array of anchor boxes to be erase (m1 + m2 + m3 + ...+ mn)
/// \param colors - array of colors to be filled in anchor boxes
/// \param num_of_boxes - number of anchor boxes corresponding to each image
/// \param outputForamtToggle - NCHW to NHWC toggling and Vice Versa
/// \param rppHandle
/// \return		

RppStatus
rppi_erase_u8_pkd3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     RppPtr_t anchor_box_info, RppPtr_t colors, RppPtr_t box_offset, Rpp32u *num_of_boxes, 
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_erase_u8_pln3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     RppPtr_t anchor_box_info, RppPtr_t colors, RppPtr_t box_offset, Rpp32u *num_of_boxes, 
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_erase_u8_pln1_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     RppPtr_t anchor_box_info, RppPtr_t colors, RppPtr_t box_offset, Rpp32u *num_of_boxes, 
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_erase_f32_pkd3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     RppPtr_t anchor_box_info, RppPtr_t colors, RppPtr_t box_offset, Rpp32u *num_of_boxes, 
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_erase_f32_pln3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     RppPtr_t anchor_box_info, RppPtr_t colors, RppPtr_t box_offset, Rpp32u *num_of_boxes, 
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_erase_f32_pln1_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     RppPtr_t anchor_box_info, RppPtr_t colors, RppPtr_t box_offset, Rpp32u *num_of_boxes, 
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_erase_f16_pkd3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     RppPtr_t anchor_box_info, RppPtr_t colors, RppPtr_t box_offset, Rpp32u *num_of_boxes, 
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_erase_f16_pln3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     RppPtr_t anchor_box_info, RppPtr_t colors, RppPtr_t box_offset, Rpp32u *num_of_boxes, 
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_erase_f16_pln1_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     RppPtr_t anchor_box_info, RppPtr_t colors, RppPtr_t box_offset, Rpp32u *num_of_boxes, 
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_erase_i8_pkd3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     RppPtr_t anchor_box_info, RppPtr_t colors, RppPtr_t box_offset, Rpp32u *num_of_boxes, 
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_erase_i8_pln3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     RppPtr_t anchor_box_info, RppPtr_t colors, RppPtr_t box_offset, Rpp32u *num_of_boxes, 
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_erase_i8_pln1_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
                                     RppPtr_t anchor_box_info, RppPtr_t colors, RppPtr_t box_offset, Rpp32u *num_of_boxes, 
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);

/// Color Cast.
/// \param srcPtr1
/// \param srcSize - Array of it
/// \param dstPtr
/// \param r - color cast parameter
/// \param g - color cast parameter
/// \param b - color cast parameter
/// \param alpha - color cast parameter
/// \param outputForamtToggle - NCHW to NHWC toggling and Vice Versa
/// \param rppHandle
/// \return

RppStatus
rppi_color_cast_u8_pkd3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp8u *r, Rpp8u *g, Rpp8u *b, Rpp32f *alpha,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_color_cast_f32_pkd3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp8u *r, Rpp8u *g, Rpp8u *b, Rpp32f *alpha,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_color_cast_f16_pkd3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp8u *r, Rpp8u *g, Rpp8u *b, Rpp32f *alpha,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_color_cast_i8_pkd3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp8u *r, Rpp8u *g, Rpp8u *b, Rpp32f *alpha,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_color_cast_u8_pln3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp8u *r, Rpp8u *g, Rpp8u *b, Rpp32f *alpha,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_color_cast_f32_pln3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp8u *r, Rpp8u *g, Rpp8u *b, Rpp32f *alpha,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_color_cast_f16_pln3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp8u *r, Rpp8u *g, Rpp8u *b, Rpp32f *alpha,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_color_cast_i8_pln3_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp8u *r, Rpp8u *g, Rpp8u *b, Rpp32f *alpha,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_color_cast_u8_pln1_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp8u *r, Rpp8u *g, Rpp8u *b, Rpp32f *alpha,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_color_cast_f32_pln1_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp8u *r, Rpp8u *g, Rpp8u *b, Rpp32f *alpha,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_color_cast_f16_pln1_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp8u *r, Rpp8u *g, Rpp8u *b, Rpp32f *alpha,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_color_cast_i8_pln1_batchPD_gpu(RppPtr_t srcPtr, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp8u *r, Rpp8u *g, Rpp8u *b, Rpp32f *alpha,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);


/// Crop and Patch.
/// \param srcPtr1
/// \param srcPtr2
/// \param srcSize - Array of it
/// \param dstPtr
/// \param x11 - Crop and Patch parameter
/// \param y11 - Crop and Patch parameter
/// \param x12 - Crop and Patch parameter
/// \param y12 - Crop and Patch parameter
/// \param x21 - Crop and Patch parameter
/// \param y21 - Crop and Patch parameter
/// \param x22 - Crop and Patch parameter
/// \param y22 - Crop and Patch parameter
/// \param outputForamtToggle - NCHW to NHWC toggling and Vice Versa
/// \param rppHandle
/// \return

RppStatus
rppi_crop_and_patch_u8_pkd3_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
									 Rpp32u *x11, Rpp32u *y11, Rpp32u *x12, Rpp32u *y12, Rpp32u *x21, Rpp32u *y21, Rpp32u *x22, Rpp32u *y22,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_crop_and_patch_f32_pkd3_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
									 Rpp32u *x11, Rpp32u *y11, Rpp32u *x12, Rpp32u *y12, Rpp32u *x21, Rpp32u *y21, Rpp32u *x22, Rpp32u *y22,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_crop_and_patch_f16_pkd3_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
 									 Rpp32u *x11, Rpp32u *y11, Rpp32u *x12, Rpp32u *y12, Rpp32u *x21, Rpp32u *y21, Rpp32u *x22, Rpp32u *y22,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_crop_and_patch_i8_pkd3_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
 									 Rpp32u *x11, Rpp32u *y11, Rpp32u *x12, Rpp32u *y12, Rpp32u *x21, Rpp32u *y21, Rpp32u *x22, Rpp32u *y22,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_crop_and_patch_u8_pln3_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
 									 Rpp32u *x11, Rpp32u *y11, Rpp32u *x12, Rpp32u *y12, Rpp32u *x21, Rpp32u *y21, Rpp32u *x22, Rpp32u *y22,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_crop_and_patch_f32_pln3_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
 									 Rpp32u *x11, Rpp32u *y11, Rpp32u *x12, Rpp32u *y12, Rpp32u *x21, Rpp32u *y21, Rpp32u *x22, Rpp32u *y22,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_crop_and_patch_f16_pln3_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
 									 Rpp32u *x11, Rpp32u *y11, Rpp32u *x12, Rpp32u *y12, Rpp32u *x21, Rpp32u *y21, Rpp32u *x22, Rpp32u *y22,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_crop_and_patch_i8_pln3_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
 									 Rpp32u *x11, Rpp32u *y11, Rpp32u *x12, Rpp32u *y12, Rpp32u *x21, Rpp32u *y21, Rpp32u *x22, Rpp32u *y22,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_crop_and_patch_u8_pln1_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
 									 Rpp32u *x11, Rpp32u *y11, Rpp32u *x12, Rpp32u *y12, Rpp32u *x21, Rpp32u *y21, Rpp32u *x22, Rpp32u *y22,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_crop_and_patch_f32_pln1_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
 									 Rpp32u *x11, Rpp32u *y11, Rpp32u *x12, Rpp32u *y12, Rpp32u *x21, Rpp32u *y21, Rpp32u *x22, Rpp32u *y22,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_crop_and_patch_f16_pln1_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
 									 Rpp32u *x11, Rpp32u *y11, Rpp32u *x12, Rpp32u *y12, Rpp32u *x21, Rpp32u *y21, Rpp32u *x22, Rpp32u *y22,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);
RppStatus
rppi_crop_and_patch_i8_pln1_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr,
 									 Rpp32u *x11, Rpp32u *y11, Rpp32u *x12, Rpp32u *y12, Rpp32u *x21, Rpp32u *y21, Rpp32u *x22, Rpp32u *y22,
									 Rpp32u outputFormatToggle, Rpp32u nbatchSize, rppHandle_t rppHandle);



#ifdef __cplusplus
}
#endif
#endif // RPPI_ADVANCED_AUGMENTATIONS