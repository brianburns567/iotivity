//******************************************************************
//
// Copyright 2014 Intel Mobile Communications GmbH All Rights Reserved.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


#ifndef OC_RANDOM_H
#define OC_RANDOM_H

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__ANDROID__) || defined(__linux__)
#include <time.h>
#elif defined ARDUINO
// MEGA has 16 input pins whereas Due has only 12 input pins
#define ANALOG_IN (10)
#endif

#define UUID_SIZE (16)
// The characters are 36 long, 37 for the null-term
#define UUID_STRING_SIZE (37)

typedef enum
{
    RAND_UUID_OK = 0,
    RAND_UUID_INVALID_PARAM = -1,
    RAND_UUID_READ_ERROR = -2,
    RAND_UUID_CONVERT_ERROR = -3
} OCRandomUuidResult;
/**
 * Seed the random number generator. Seeding depends on platform.
 * Android and Linux uses current time. Arduino uses Analog reading on pin ANALOG_IN
 * @retval 0 for Success, otherwise some error value
 */
int8_t OCSeedRandom();

/**
 * Generate a uniformly [0,2^32] distributed random number
 * @retval On Success, it returns the random value.
 */
uint32_t OCGetRandom();

/**
 * Generate a uniformly [0,2^8] distributed random number
 * @retval On Success, it returns the random value, otherwise -1 for error.
 */
uint8_t OCGetRandomByte(void);

/**
 * Generate a uniformly distributed 8-bit (byte) array random numbers
 * @param[out] location
 *              memory location to start filling with random bytes
 * @param[in] len
 *              length of array to be filled with random bytes
 */
void OCFillRandomMem(uint8_t * location, uint16_t len);

/*
 * Generate a uniformly distributed number on the defined bounded range
 * @param[in] firstBound
 *              the first bound of the range
 * @param[in] secondBound
 *              the second bound of the range
 */
uint32_t OCGetRandomRange(uint32_t firstBound, uint32_t secondBound);

/**
 * Generate a Uniformly Unique Identifier based on RFC4122 and
 * provide it as a 16 byte byte-array
 *
 * @param[out] uuid
 *               the 16 byte array to fill with the UUID data
 *               of a new UUID
 *
 * @retval RAND_UUID_OK for success, otherwise an error value
 */
OCRandomUuidResult OCGenerateUuid(uint8_t uuid[UUID_SIZE]);

/**
 * Convert a UUID generated by OCGenerateUuid to a C style string
 * based on RFC 4122
 *
 * @param[in]  uuid
 *              The 16 byte array filled with UUID data by OCGenerateUuid
 * @param[out] uuidString
 *              a 37 byte length string to fill with the string
 *              representation of the passed UUID.
 * @retval RAND_UUID_OK for success, otherwise an error value
 */
OCRandomUuidResult OCConvertUuidToString(const uint8_t uuid[UUID_SIZE],
        char uuidString[UUID_STRING_SIZE]);

#ifdef __cplusplus
}
#endif

#endif // OC_RANDOM_H
