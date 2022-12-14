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

#define VSYNC_DEV_PREFIX "/sys/devices/"
#define VSYNC_DEV_NAME  "13930000.decon_fb/vsync"

#define FIMD_WORD_SIZE_BYTES   16
#define FIMD_BURSTLEN   16
#define FIMD_ADDED_BURSTLEN_BYTES     0

#define WINUPDATE_MIN_HEIGHT 16

#define SMEM_PATH "/dev/s5p-smem"
#define SECMEM_IOC_SET_VIDEO_EXT_PROC   _IOWR('S', 13, int)

#define HWC_VERSION HWC_DEVICE_API_VERSION_1_5

/* Max number windows available in Exynos7420 is 7. */
#define NUM_AVAILABLE_HW_WINDOWS	7

/* IDMA_G2 and IDMA_G3 cause decon register crashes on Exynos7420 */
#define DISABLE_IDMA_SECURE

const size_t GSC_DST_W_ALIGNMENT_RGB888 = 1;
const size_t GSC_DST_CROP_W_ALIGNMENT_RGB888 = 1;
const size_t GSC_W_ALIGNMENT = 16;
const size_t GSC_H_ALIGNMENT = 16;
const size_t GSC_DST_H_ALIGNMENT_RGB888 = 1;

const size_t FIMD_GSC_IDX = 0;
const size_t FIMD_EXT_MPP_IDX = 0;
/* HDMI_GSC_IDX is not used but added for build issue */
const size_t HDMI_GSC_IDX = 2;
const size_t HDMI_EXT_MPP_IDX = 1;
const size_t WFD_GSC_IDX = 1;
const size_t WFD_EXT_MPP_IDX = 2;

const int FIMD_GSC_USAGE_IDX[] = {FIMD_GSC_IDX};
const int AVAILABLE_GSC_UNITS[] = { 0, 2, 1, 1, 5, 4 };

#define MPP_VG          0
#define MPP_VGR         2
#define MPP_MSC         4
#define MPP_VPP_G       10

#define EXTERNAL_MPPS   5

struct exynos_mpp_t {
    int type;
    unsigned int index;
};

const exynos_mpp_t AVAILABLE_EXTERNAL_MPP_UNITS[] = {{MPP_MSC, 0}, {MPP_MSC, 0}, {MPP_MSC, 0}, {MPP_MSC, 0}, {MPP_MSC, 0}};

#endif
