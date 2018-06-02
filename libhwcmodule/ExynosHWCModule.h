/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_EXYNOS_HWC_MODULE_H_
#define ANDROID_EXYNOS_HWC_MODULE_H_
#include <hardware/hwcomposer.h>
#include <decon-fb.h>

<<<<<<< HEAD
=======
#define HWC_VERSION     HWC_DEVICE_API_VERSION_1_5
#define IDMA_SECURE IDMA_G2

>>>>>>> 0b70dd8 (libhwcmodule: reconfigure overlay to support exynos7420 (remove MPP_VPP_G))
#define VSYNC_DEV_PREFIX "/sys/devices/"
#define VSYNC_DEV_NAME  "13930000.decon_fb/vsync"

#define FIMD_WORD_SIZE_BYTES   16
#define FIMD_BURSTLEN   16
#define FIMD_ADDED_BURSTLEN_BYTES     0
#define FIMD_BW_OVERLAP_CHECK

#define WINUPDATE_MIN_HEIGHT 16

#define SMEM_PATH "/dev/s5p-smem"
#define SECMEM_IOC_SET_VIDEO_EXT_PROC   _IOWR('S', 13, int)

const size_t GSC_DST_CROP_W_ALIGNMENT_RGB888 = 1;
const size_t GSC_W_ALIGNMENT = 16;
const size_t GSC_H_ALIGNMENT = 16;
const size_t GSC_DST_H_ALIGNMENT_RGB888 = 1;

//
// --- _DWORD *__fastcall ExynosMPP::ExynosMPP(_DWORD *a1, int a2, int a3)
//
// v3[3] = dword_B2B0[v5];    <--  mType = AVAILABLE_GSC_UNITS[gscIndex];
//
//     v3            <--  ExynosMPP Instance
//     dword_B2B0    <--  AVAILABLE_GSC_UNITS
//     v5            <--  gscIndex
//
// .rodata:0000B2B0 ; _DWORD dword_B2B0[6]
// .rodata:0000B2B0 dword_B2B0      DCD 0, 2, 1, 1, 5, 4    ; DATA XREF: ExynosMPP::ExynosMPP(ExynosDisplay *,int)+44↑o
//
// REMARK: Third index requested as mType is preceeded by the VMT and two pointers
//
const int AVAILABLE_GSC_UNITS[] = { 0, 2, 1, 1, 5, 4 };

#define MPP_VG          0
#define MPP_VGR         2
#define MPP_MSC         4
#define MPP_VPP_G       10

#define MPP_DEFAULT     MPP_VGR

#define EXTERNAL_MPPS   5

struct exynos_mpp_t {
    int type;
    unsigned int index;
};

/* VPP_G0 is secure dma, It is managed as IDMA_SECURE separately*/
const exynos_mpp_t AVAILABLE_INTERNAL_MPP_UNITS[] = {{MPP_VG, 0}, {MPP_VG, 1}, {MPP_VGR, 0}, {MPP_VGR, 1}};
const exynos_mpp_t AVAILABLE_EXTERNAL_MPP_UNITS[] = {{MPP_MSC, 0}, {MPP_MSC, 0}, {MPP_MSC, 0}, {MPP_MSC, 0}, {MPP_MSC, 0}};

#define DEFAULT_MPP_DST_FORMAT HAL_PIXEL_FORMAT_RGBX_8888

//
// v4 = *(_DWORD *)(a2 + 16);    <--  internalMPP->mType/const int &index
// if ( v4 <= 3 )
//     return dword_1245C[v4];
//
// .rodata:0001245C ; _DWORD dword_1245C[4]
// .rodata:0001245C dword_1245C     DCD 0, 1, 6, 7          ; DATA XREF: ExynosDisplay::getDeconDMAType(ExynosMPPModule *)+20↑o
// .rodata:0001245C                                         ; .text:off_CA70↑o
//
static int MPP_VPP_G_TYPE(const int &index)
{
    switch (index) {
    case 0:
        return IDMA_G0;
    case 1:
        return IDMA_G1;
    case 2:
        return IDMA_G2;
    case 3:
        return IDMA_G3;
    default:
        return -1;
    }
}

#endif
