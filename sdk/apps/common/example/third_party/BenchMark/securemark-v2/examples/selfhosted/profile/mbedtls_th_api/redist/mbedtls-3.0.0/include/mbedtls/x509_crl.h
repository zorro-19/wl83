/**
 * \file x509_crl.h
 *
 * \brief X.509 certificate revocation list parsing
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
#ifndef MBEDTLS_X509_CRL_H
#define MBEDTLS_X509_CRL_H
#include "mbedtls/private_access.h"

#include "mbedtls/build_info.h"

#include "mbedtls/x509.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup x509_module
 * \{ */

/**
 * \name Structures and functions for parsing CRLs
 * \{
 */

/**
 * Certificate revocation list entry.
 * Contains the CA-specific serial numbers and revocation dates.
 */
typedef struct mbedtls_x509_crl_entry {
    mbedtls_x509_buf MBEDTLS_PRIVATE(raw);

    mbedtls_x509_buf MBEDTLS_PRIVATE(serial);

    mbedtls_x509_time MBEDTLS_PRIVATE(revocation_date);

    mbedtls_x509_buf MBEDTLS_PRIVATE(entry_ext);

    struct mbedtls_x509_crl_entry *MBEDTLS_PRIVATE(next);
}
mbedtls_x509_crl_entry;

/**
 * Certificate revocation list structure.
 * Every CRL may have multiple entries.
 */
typedef struct mbedtls_x509_crl {
    mbedtls_x509_buf MBEDTLS_PRIVATE(raw);           /**< The raw certificate data (DER). */
    mbedtls_x509_buf MBEDTLS_PRIVATE(tbs);           /**< The raw certificate body (DER). The part that is To Be Signed. */

    int MBEDTLS_PRIVATE(version);            /**< CRL version (1=v1, 2=v2) */
    mbedtls_x509_buf MBEDTLS_PRIVATE(sig_oid);       /**< CRL signature type identifier */

    mbedtls_x509_buf MBEDTLS_PRIVATE(issuer_raw);    /**< The raw issuer data (DER). */

    mbedtls_x509_name MBEDTLS_PRIVATE(issuer);       /**< The parsed issuer data (named information object). */

    mbedtls_x509_time MBEDTLS_PRIVATE(this_update);
    mbedtls_x509_time MBEDTLS_PRIVATE(next_update);

    mbedtls_x509_crl_entry MBEDTLS_PRIVATE(entry);   /**< The CRL entries containing the certificate revocation times for this CA. */

    mbedtls_x509_buf MBEDTLS_PRIVATE(crl_ext);

    mbedtls_x509_buf MBEDTLS_PRIVATE(sig_oid2);
    mbedtls_x509_buf MBEDTLS_PRIVATE(sig);
    mbedtls_md_type_t MBEDTLS_PRIVATE(sig_md);           /**< Internal representation of the MD algorithm of the signature algorithm, e.g. MBEDTLS_MD_SHA256 */
    mbedtls_pk_type_t MBEDTLS_PRIVATE(sig_pk);           /**< Internal representation of the Public Key algorithm of the signature algorithm, e.g. MBEDTLS_PK_RSA */
    void *MBEDTLS_PRIVATE(sig_opts);             /**< Signature options to be passed to mbedtls_pk_verify_ext(), e.g. for RSASSA-PSS */

    struct mbedtls_x509_crl *MBEDTLS_PRIVATE(next);
}
mbedtls_x509_crl;

/**
 * \brief          Parse a DER-encoded CRL and append it to the chained list
 *
 * \param chain    points to the start of the chain
 * \param buf      buffer holding the CRL data in DER format
 * \param buflen   size of the buffer
 *                 (including the terminating null byte for PEM data)
 *
 * \return         0 if successful, or a specific X509 or PEM error code
 */
int mbedtls_x509_crl_parse_der(mbedtls_x509_crl *chain,
                               const unsigned char *buf, size_t buflen);
/**
 * \brief          Parse one or more CRLs and append them to the chained list
 *
 * \note           Multiple CRLs are accepted only if using PEM format
 *
 * \param chain    points to the start of the chain
 * \param buf      buffer holding the CRL data in PEM or DER format
 * \param buflen   size of the buffer
 *                 (including the terminating null byte for PEM data)
 *
 * \return         0 if successful, or a specific X509 or PEM error code
 */
int mbedtls_x509_crl_parse(mbedtls_x509_crl *chain, const unsigned char *buf, size_t buflen);

#if defined(MBEDTLS_FS_IO)
/**
 * \brief          Load one or more CRLs and append them to the chained list
 *
 * \note           Multiple CRLs are accepted only if using PEM format
 *
 * \param chain    points to the start of the chain
 * \param path     filename to read the CRLs from (in PEM or DER encoding)
 *
 * \return         0 if successful, or a specific X509 or PEM error code
 */
int mbedtls_x509_crl_parse_file(mbedtls_x509_crl *chain, const char *path);
#endif /* MBEDTLS_FS_IO */

#if !defined(MBEDTLS_X509_REMOVE_INFO)
/**
 * \brief          Returns an informational string about the CRL.
 *
 * \param buf      Buffer to write to
 * \param size     Maximum size of buffer
 * \param prefix   A line prefix
 * \param crl      The X509 CRL to represent
 *
 * \return         The length of the string written (not including the
 *                 terminated nul byte), or a negative error code.
 */
int mbedtls_x509_crl_info(char *buf, size_t size, const char *prefix,
                          const mbedtls_x509_crl *crl);
#endif /* !MBEDTLS_X509_REMOVE_INFO */

/**
 * \brief          Initialize a CRL (chain)
 *
 * \param crl      CRL chain to initialize
 */
void mbedtls_x509_crl_init(mbedtls_x509_crl *crl);

/**
 * \brief          Unallocate all CRL data
 *
 * \param crl      CRL chain to free
 */
void mbedtls_x509_crl_free(mbedtls_x509_crl *crl);

/* \} name */
/* \} addtogroup x509_module */

#ifdef __cplusplus
}
#endif

#endif /* mbedtls_x509_crl.h */
