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
rppi_non_linear_blend_f32_pn3_batchPD_gpu(RppPtr_t srcPtr1, RppPtr_t srcPtr2, RppiSize *srcSize, RppiSize maxSrcSize, RppPtr_t dstPtr, Rpp32f *std_dev,
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
#ifdef __cplusplus
}
#endif
#endif // RPPI_ADVANCED_AUGMENTATIONS