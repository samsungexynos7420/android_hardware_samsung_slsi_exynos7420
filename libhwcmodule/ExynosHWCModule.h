/*
 * Copyright (C) 2012 The Android Open Source Project
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

#define HWC_VERSION     HWC_DEVICE_API_VERSION_1_5

//
// confirmed by decompiling stock-HWC
//
//       if ( *((_BYTE *)v2 + 1844)
//           && v2[54] == v48 - 2
//           && (*(int (__fastcall **)(_DWORD *, int, int))(*v2 + 144))(v2, v117, v118) == 1 )
//       {
//           v9 = v2[62];
//           v10 = *(_DWORD *)(v2[12] + 256);
//           *(_DWORD *)(*(_DWORD *)(v2[17] + 4 * *(_DWORD *)(v3 + 16) - 4) + 16) = 6;
//           if ( v9 < v10 )
//               v10 = v9;
//       }
//
// REMARK:  ```(...) = 6;``` corresponds with ```mLayerInfos[contents->numHwLayers - 1]->mDmaType = IDMA_SECURE;```
//
#define IDMA_SECURE     IDMA_G2

// quite sure this doesn't need further confirmation
#define VSYNC_DEV_PREFIX "/sys/devices/"
#define VSYNC_DEV_NAME  "13930000.decon_fb/vsync"

#define TRY_SECOND_VSYNC_DEV
#ifdef TRY_SECOND_VSYNC_DEV
#define VSYNC_DEV_NAME2  "exynos5-fb.1/vsync"
#define VSYNC_DEV_MIDDLE2  "platform/exynos-sysmmu.30/exynos-sysmmu.11/"
#endif

// Decon WB
// Used for virtual display. Some of these values might be wrong, but im pretty sure about most of them
//
// Currently, virtual display is unstable and can crash the hwcomposer. Some of these values might be
// the cause, but I think the problem lies elsewhere
#define DECON_WB_DEV_NAME   "/dev/graphics/fb1"
#define DECON_ODMA_WB		8
#define DECON_EXT_BASE_WINDOW   1
#define DECON_WB_SUBDEV_NAME   "exynos-decon1"
#define DECON_PAD_WB    6
#define DECON_2_MAX_OVERLAY_COUNT    4

//
// confirmed by decompiling stock-HWC/using default values
//
// REMARK: optimizations removed single FIMD burstlen values, used default values
//         to achieve found value
//
//     if ( (unsigned int)(v36 * (v38 - v40) / 8) <= 0xFF )
//
// REMARK: burstlen values got optimized to 0xFF, default values
//         are used to get to [ 16, 16, 0 ]
//
#define FIMD_WORD_SIZE_BYTES   16
#define FIMD_BURSTLEN   16
#define FIMD_ADDED_BURSTLEN_BYTES     0

//
// confirmed by decompiling stock-HWC
//
//     if ( v186 - v91 >= 16 )
//     {
//         v92 = *(_DWORD *)(v8 + 28);
//     }
//     else
//     {
//         v92 = *(_DWORD *)(v8 + 28);
//         if ( v91 + 16 <= v92 )
//             v90 = v91 + 16;
//         else
//             v91 = v186 - 16;
//     }
//
// REMARK: inverted ```if (HEIGHT(updateRect) < WINUPDATE_MIN_HEIGHT) { ... }```
//
#define WINUPDATE_MIN_HEIGHT 16

#define HDMI_RESERVE_MEM_DEV_NAME "/sys/class/ion_cma/ion_video_ext/isolate"
#define SMEM_PATH "/dev/s5p-smem"
#define SECMEM_IOC_SET_VIDEO_EXT_PROC   _IOWR('S', 13, int)

const size_t GSC_DST_CROP_W_ALIGNMENT_RGB888 = 1;
const size_t GSC_W_ALIGNMENT = 16;
const size_t GSC_H_ALIGNMENT = 16;
const size_t GSC_DST_H_ALIGNMENT_RGB888 = 1;

//
// confirmed by decompiling stock-HWC
//
// --- _DWORD *__fastcall ExynosMPP::ExynosMPP(_DWORD *a1, int a2, int a3)
//
//     v3[3] = dword_B2B0[v5];    <--  mType = AVAILABLE_GSC_UNITS[gscIndex];
//
//         v3            <--  ExynosMPP Instance
//         dword_B2B0    <--  AVAILABLE_GSC_UNITS
//         v5            <--  gscIndex
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

#define MPP_DEFAULT     MPP_VGR

const size_t FIMD_EXT_MPP_IDX = 0;
const size_t HDMI_EXT_MPP_IDX = 1;
const size_t WFD_EXT_MPP_IDX = 2;

struct exynos_mpp_t {
    int type;
    unsigned int index;
};

//
// confirmed by decompiling stock-HWC
//
// .rodata:000124BC ; _DWORD dword_124BC[8]
// .rodata:000124BC dword_124BC     DCD 0, 0, 0, 1, 2, 0, 2, 1
// .rodata:000124BC                                         ; DATA XREF: ExynosDisplayResourceManagerModule::ExynosDisplayResourceManagerModule(exynos5_hwc_composer_device_1_t *)+2E↑o
// .rodata:000124BC                                         ; .text:off_DA70↑o
//
//
// Current state:
//     - 7 working HW windows
//     - mInternalDMAs used for IDMA_GX instead of MPP_VPP_G 
//
//  - G		--  Working as intended and stable
//    - G0
//    - G1
//    - G2	-- Bound to window 6. Used as secure DMA and handled separately.
//  - VG          --  Working as intended and stable, unable to work with blending
//    - VG0
//    - VG1
//  - VGR         --  Working as intended and stable
//    - VGR0
//    - VGR1
//
const exynos_mpp_t AVAILABLE_INTERNAL_MPP_UNITS[] = {{MPP_VG, 0}, {MPP_VG, 1}, {MPP_VGR, 0}, {MPP_VGR, 1}};

//
// confirmed by decompiling stock-HWC
//
// .rodata:000124DC ; _DWORD dword_124DC[10]
// .rodata:000124DC dword_124DC     DCD 4, 0, 4, 0, 4, 0, 4, 0, 4, 0
// .rodata:000124DC                                         ; DATA XREF: ExynosDisplayResourceManagerModule::ExynosDisplayResourceManagerModule(exynos5_hwc_composer_device_1_t *)+96↑o
// .rodata:000124DC                                         ; .text:off_DA78↑o
//
const exynos_mpp_t AVAILABLE_EXTERNAL_MPP_UNITS[] = {{MPP_MSC, 0}, {MPP_MSC, 0}, {MPP_MSC, 0}, {MPP_MSC, 0}, {MPP_MSC, 0}};


#define DEFAULT_MPP_DST_FORMAT HAL_PIXEL_FORMAT_RGBX_8888

//
// confirmed by decompiling stock-HWC
//
//     v4 = *(_DWORD *)(a2 + 16);    <--  internalMPP->mType/const int &index
//     if ( v4 <= 3 )
//         return dword_1245C[v4];
//
// .rodata:0001245C ; _DWORD dword_1245C[4]
// .rodata:0001245C dword_1245C     DCD 0, 1, 6, 7          ; DATA XREF: ExynosDisplay::getDeconDMAType(ExynosMPPModule *)+20↑o
// .rodata:0001245C                                         ; .text:off_CA70↑o
//
__attribute__((unused))
static int MPP_VPP_G_TYPE(const int &index)
{
    switch (index) {
    case 0:
        return IDMA_G0;
    case 1:
        return IDMA_G1;
    // used as secure DMA - bound to window 6
    case 2:
        return IDMA_G2;
    // reserved for libvpphdmi
    case 3:
        return IDMA_G3;

    default:
        return -1;
    }
}

#endif
