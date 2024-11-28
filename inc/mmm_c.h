/**
 * @file mmm_c.h
 * @author Jake G
 * @date 27 Nov 2024
 * @brief File contains the public API for the MMM_C library.
 *
 * This file holds all the code/functions needed to preform matrix operations.
 *
 */
#ifndef MMMC_H
#define MMMC_H

#include <stdint.h>

typedef enum { Ok, Error } Result;

/**
 * @brief Unsigned 16bit dynamic matrix structure
 *
 */
typedef struct {
  uint16_t rows;
  uint16_t cols;
  uint16_t *cells;
} U16_DMAT;

/**
 * @brief summaryhere
 *
 */

U16_DMAT DU16_NewZeros(uint16_t rows, uint16_t cols);
U16_DMAT DU16_NewOnes(uint16_t rows, uint16_t cols);
U16_DMAT DU16_NewIdentity(uint16_t rows, uint16_t cols);

Result DU16_AllocateMemory(U16_DMAT *mat);
Result DU16_FreeMatrix(U16_DMAT *mat);
Result DU16_MultiplyInPlace(U16_DMAT *mata, U16_DMAT *matb);

#endif // MMMC_H
