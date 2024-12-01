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

#include <inttypes.h>
#include <stdbool.h>


typedef enum { Ok, Error } Result;

/**
 * @brief Unsigned 16bit dynamic matrix structure
 *
 */
typedef struct {
    uint_fast16_t rows;
    uint_fast16_t cols;
    uint_fast16_t *cells;
    bool is_allocated;
} U16_DMAT;

/**
 * @brief summaryhere
 *
 */

U16_DMAT DU16_New(unsigned int rows, unsigned int cols);
U16_DMAT DU16_NewIdentity(unsigned int rows, unsigned int cols);

Result DU16_AllocateMemory(U16_DMAT *mat);
Result DU16_FreeMatrix(U16_DMAT *mat);
Result DU16_SetAllTo(U16_DMAT *mat, uint16_t value);
Result DU16_MultiplyByNum(U16_DMAT *mat, uint16_t value);
Result DU16_MultiplyInPlace(U16_DMAT *mata, U16_DMAT *matb);
U16_DMAT DU16_MultiplyMatricies(U16_DMAT *mata, U16_DMAT *matb);

uint_fast16_t *DU16_CellIndex(U16_DMAT *mat, unsigned int row, unsigned int col);

#endif // MMMC_H
