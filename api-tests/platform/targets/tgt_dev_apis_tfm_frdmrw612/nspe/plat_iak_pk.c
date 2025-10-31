/*
 * Copyright (c) 2017-2022 Arm Limited. All rights reserved.
 * Copyright 2024 NXP
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "pal_attestation_crypto.h"
#include "tfm_builtin_key_ids.h"

/* Function to provide a potential implementation for devices which are 
using keys based upon secure element  during IAK */
extern int32_t tfm_initial_attest_get_public_key(uint8_t          *public_key_buff,
                                                 size_t            public_key_buf_size,
                                                 size_t           *public_key_len,
                                                 psa_ecc_family_t *elliptic_family_type)
{
    psa_key_handle_t handle = TFM_BUILTIN_KEY_ID_IAK;
    psa_status_t crypto_res;
    psa_key_type_t key_type;
    psa_key_attributes_t attr;

    crypto_res = psa_get_key_attributes(handle, &attr);
    if (crypto_res != PSA_SUCCESS) {
        return PAL_ATTEST_ERROR;
    }

    key_type = psa_get_key_type(&attr);

    if (!PSA_KEY_TYPE_IS_ECC(key_type)) {
        return PAL_ATTEST_ERROR;
    }

    /* Configures the supported ECC family */
    *elliptic_family_type = PSA_KEY_TYPE_ECC_GET_FAMILY(key_type);

    /* Call the psa_export-public key to get the public key from TF-M. */
    crypto_res = psa_export_public_key(handle, public_key_buff,
                                       public_key_buf_size,
                                       public_key_len);
    if (crypto_res != PSA_SUCCESS) {
        return PAL_ATTEST_ERROR;
    }
    return PAL_ATTEST_SUCCESS; 
}
