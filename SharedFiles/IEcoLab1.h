/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoLab1
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECOLAB1_H__
#define __I_ECOLAB1_H__

#include "IEcoBase1.h"

/* IEcoLab1 IID = {277FC00C-3562-4096-AFCF-C125B94EEC90} */
#ifndef __IID_IEcoLab1
static const UGUID IID_IEcoLab1 = {0x01, 0x10, {0x27, 0x7F, 0xC0, 0x0C, 0x35, 0x62, 0x40, 0x96, 0xAF, 0xCF, 0xC1, 0x25, 0xB9, 0x4E, 0xEC, 0x90}};
#endif /* __IID_IEcoLab1 */

/* Структура для комплексных чисел */
typedef struct EcoComplex {
    double real;
    double imag;
} EcoComplex;

/* Структура для вектора */
typedef struct {
    void *data;        
    size_t size; 
	char type; // 'i' - int, 'l' - long, 'f' - float, 'd' - double, 'F' - long double, 'c' - complex
} EcoVector;

/* Структура для матрицы */
typedef struct {
    double** data;
    int rows;
    int cols;
} EcoMatrix;

typedef struct IEcoLab1* IEcoLab1Ptr_t;

typedef struct IEcoLab1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoLab1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoLab1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoLab1Ptr_t me);

    /* IEcoLab1 */
    int16_t (ECOCALLMETHOD *polyHornerInt)(/* in */ IEcoLab1Ptr_t me, /* in */ int* roots, /* in */ uint32_t numRoots, /* out */ int** coefficients, /* out */ uint32_t* numCoefficients);
	int16_t (ECOCALLMETHOD *polyHornerLong)(/* in */ IEcoLab1Ptr_t me, /* in */ int64_t* roots, /* in */ uint32_t numRoots, /* out */ int64_t** coefficients, /* out */ uint32_t* numCoefficients);
	int16_t (ECOCALLMETHOD *polyHornerFloat)(/* in */ IEcoLab1Ptr_t me, /* in */ float* roots, /* in */ uint32_t numRoots, /* out */ float** coefficients, /* out */ uint32_t* numCoefficients);
	int16_t (ECOCALLMETHOD *polyHornerDouble)(/* in */ IEcoLab1Ptr_t me, /* in */ double* roots, /* in */ uint32_t numRoots, /* out */ double** coefficients, /* out */ uint32_t* numCoefficients);
	int16_t (ECOCALLMETHOD *polyHornerLongDouble)(/* in */ IEcoLab1Ptr_t me, /* in */ long double* roots, /* in */ uint32_t numRoots, /* out */ long double** coefficients, /* out */ uint32_t* numCoefficients);
	int16_t (ECOCALLMETHOD *polyHornerComplex)(/* in */ IEcoLab1Ptr_t me, /* in */ EcoComplex* roots, /* in */ uint32_t numRoots, /* out */ EcoComplex** coefficients, /* out */ uint32_t* numCoefficients);
    int16_t (ECOCALLMETHOD *polyHornerVector)(/* in */ IEcoLab1Ptr_t me, /* in */ EcoVector* roots, /* in */ uint32_t numRoots, /* out */ EcoVector** coefficients, /* out */ uint32_t* numCoefficients);
	int16_t (ECOCALLMETHOD *polyHornerMatrix)(/* in */ IEcoLab1Ptr_t me, /* in */ EcoMatrix* mat, /* out */ EcoVector** coefficients, /* out */ uint32_t* numCoefficients);

	int16_t (ECOCALLMETHOD *bucketSortIntWithK)(/* in */ IEcoLab1Ptr_t me, /* in */ int* arr, /* in */ uint32_t size, /* in */ uint32_t k, /* out */ int** sortedArr);
	int16_t (ECOCALLMETHOD *bucketSortIntAutoK)(/* in */ IEcoLab1Ptr_t me, /* in */ int* arr, /* in */ uint32_t size, /* out */ int** sortedArr);
	int16_t (ECOCALLMETHOD *bucketSortLongWithK)(/* in */ IEcoLab1Ptr_t me, /* in */ int64_t* arr, /* in */ uint32_t size, /* in */ uint32_t k, /* out */ int64_t** sortedArr);
	int16_t (ECOCALLMETHOD *bucketSortLongAutoK)(/* in */ IEcoLab1Ptr_t me, /* in */ int64_t* arr, /* in */ uint32_t size, /* out */ int64_t** sortedArr);
	int16_t (ECOCALLMETHOD *bucketSortFloatWithK)(/* in */ IEcoLab1Ptr_t me, /* in */ float* arr, /* in */ uint32_t size, /* in */ uint32_t k, /* out */ float** sortedArr);
	int16_t (ECOCALLMETHOD *bucketSortFloatAutoK)(/* in */ IEcoLab1Ptr_t me, /* in */ float* arr, /* in */ uint32_t size, /* out */ float** sortedArr);
	int16_t (ECOCALLMETHOD *bucketSortDoubleWithK)(/* in */ IEcoLab1Ptr_t me, /* in */ double* arr, /* in */ uint32_t size, /* in */ uint32_t k, /* out */ double** sortedArr);
	int16_t (ECOCALLMETHOD *bucketSortDoubleAutoK)(/* in */ IEcoLab1Ptr_t me, /* in */ double* arr, /* in */ uint32_t size, /* out */ double** sortedArr);
	int16_t (ECOCALLMETHOD *bucketSortLongDoubleWithK)(/* in */ IEcoLab1Ptr_t me, /* in */ long double* arr, /* in */ uint32_t size, /* in */ uint32_t k, /* out */ long double** sortedArr);
	int16_t (ECOCALLMETHOD *bucketSortLongDoubleAutoK)(/* in */ IEcoLab1Ptr_t me, /* in */ long double* arr, /* in */ uint32_t size, /* out */ long double** sortedArr);

} IEcoLab1VTbl, *IEcoLab1VTblPtr;

interface IEcoLab1 {
    struct IEcoLab1VTbl *pVTbl;
} IEcoLab1;


#endif /* __I_ECOLAB1_H__ */
