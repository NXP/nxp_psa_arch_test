/** @file
 * Copyright (c) 2023, Arm Limited or its affiliates. All rights reserved.
 * SPDX-License-Identifier : Apache-2.0
 * Copyright 2023 NXP
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
**/

#ifndef PSA_ADAC_PLATFORM_H
#define PSA_ADAC_PLATFORM_H

#include <stdint.h>
#include <stddef.h>

#ifdef PSA_ADAC_PLATFORM_CONFIG_FILE
#include PSA_ADAC_PLATFORM_CONFIG_FILE
#else
#include <psa_adac_platform.h>
#endif

#ifndef PSA_ADAC_PLATFORM_BANNER
#define PSA_ADAC_PLATFORM_BANNER "PSA ADAC "
#endif

void platform_init(void);
void psa_adac_platform_init(void);

/**
 *   @brief    - initialize anything relavent to a platform
 *               like any key initialization for crypto operations and etc
 *               this is optional Api to implement
 *   @return   - TRUE/FALSE
**/
__attribute__((weak)) unsigned int pal_platform_init(void)
{
	return (unsigned int)PAL_STATUS_SUCCESS;
}
#endif //PSA_ADAC_PLATFORM_H
