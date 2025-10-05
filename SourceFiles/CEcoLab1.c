/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab1.h"
#include <math.h>

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoLab1
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_QueryInterface(/* in */ IEcoLab1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLab1) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoLab1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab1_AddRef(/* in */ IEcoLab1Ptr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoLab1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab1_Release(/* in */ IEcoLab1Ptr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab1((IEcoLab1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция polyHornerInt
 * </сводка>
 *
 * <описание>
 *   Функция poly - получение коэффициентов полинома по набору его корней (по методу Горнера), поддерживает тип данных int
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_polyHornerInt(/* in */ IEcoLab1Ptr_t me, /* in */ int* roots, /* in */ uint32_t numRoots, /* out */ int** coefficients, /* out */ uint32_t* numCoefficients) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    uint32_t i = 0;
    uint32_t j = 0;
	int* coeffs = 0;

    /* Проверка указателей */
    if (me == 0 || roots == 0 || coefficients == 0 || numCoefficients == 0) {
        return ERR_ECO_POINTER;
    }

    /* Выделение памяти для коэффициентов */
    coeffs = (int*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (numRoots + 1) * sizeof(int));
    if (coeffs == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }
    
    /* Инициализация коэффициентов */
    coeffs[0] = 1.0;
    for (i = 1; i <= numRoots; i++) {
        coeffs[i] = 0.0;
    }

	/* Основной алгоритм */
    for (i = 0; i < numRoots; i++) {
        int root = roots[i];
        for (j = i + 1; j > 0; j--) {
            coeffs[j] += - root * coeffs[j - 1];
        }
    }

    *coefficients = coeffs;
    *numCoefficients = numRoots + 1;
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция polyHornerLong
 * </сводка>
 *
 * <описание>
 *   Функция poly - получение коэффициентов полинома по набору его корней (по методу Горнера), поддерживает тип данных long
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_polyHornerLong(/* in */ IEcoLab1Ptr_t me, /* in */ int64_t* roots, /* in */ uint32_t numRoots, /* out */ int64_t** coefficients, /* out */ uint32_t* numCoefficients) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    uint32_t i = 0;
    uint32_t j = 0;
	int64_t* coeffs = 0;

    /* Проверка указателей */
    if (me == 0 || roots == 0 || coefficients == 0 || numCoefficients == 0) {
        return ERR_ECO_POINTER;
    }

    /* Выделение памяти для коэффициентов */
    coeffs = (int64_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (numRoots + 1) * sizeof(int64_t));
    if (coeffs == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }
    
    /* Инициализация коэффициентов */
    coeffs[0] = 1.0;
    for (i = 1; i <= numRoots; i++) {
        coeffs[i] = 0.0;
    }

	/* Основной алгоритм */
    for (i = 0; i < numRoots; i++) {
        int64_t root = roots[i];
        for (j = i + 1; j > 0; j--) {
            coeffs[j] += - root * coeffs[j - 1];
        }
    }

    *coefficients = coeffs;
    *numCoefficients = numRoots + 1;
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция polyHornerFloat
 * </сводка>
 *
 * <описание>
 *   Функция poly - получение коэффициентов полинома по набору его корней (по методу Горнера), поддерживает тип данных float
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_polyHornerFloat(/* in */ IEcoLab1Ptr_t me, /* in */ float* roots, /* in */ uint32_t numRoots, /* out */ float** coefficients, /* out */ uint32_t* numCoefficients) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    uint32_t i = 0;
    uint32_t j = 0;
	float* coeffs = 0;

    /* Проверка указателей */
    if (me == 0 || roots == 0 || coefficients == 0 || numCoefficients == 0) {
        return ERR_ECO_POINTER;
    }

    /* Выделение памяти для коэффициентов */
    coeffs = (float*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (numRoots + 1) * sizeof(float));
    if (coeffs == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }
    
    /* Инициализация коэффициентов */
    coeffs[0] = 1.0;
    for (i = 1; i <= numRoots; i++) {
        coeffs[i] = 0.0;
    }

	/* Основной алгоритм */
    for (i = 0; i < numRoots; i++) {
        float root = roots[i];
        for (j = i + 1; j > 0; j--) {
            coeffs[j] += - root * coeffs[j - 1];
        }
    }

    *coefficients = coeffs;
    *numCoefficients = numRoots + 1;
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция polyHornerDouble
 * </сводка>
 *
 * <описание>
 *   Функция poly - получение коэффициентов полинома по набору его корней (по методу Горнера), поддерживает тип данных double
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_polyHornerDouble(/* in */ IEcoLab1Ptr_t me, /* in */ double* roots, /* in */ uint32_t numRoots, /* out */ double** coefficients, /* out */ uint32_t* numCoefficients) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    uint32_t i = 0;
    uint32_t j = 0;
	double* coeffs = 0;

    /* Проверка указателей */
    if (me == 0 || roots == 0 || coefficients == 0 || numCoefficients == 0) {
        return ERR_ECO_POINTER;
    }

    /* Выделение памяти для коэффициентов */
    coeffs = (double*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (numRoots + 1) * sizeof(double));
    if (coeffs == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }
    
    /* Инициализация коэффициентов */
    coeffs[0] = 1.0;
    for (i = 1; i <= numRoots; i++) {
        coeffs[i] = 0.0;
    }

	/* Основной алгоритм */
    for (i = 0; i < numRoots; i++) {
        double root = roots[i];
        for (j = i + 1; j > 0; j--) {
            coeffs[j] += - root * coeffs[j - 1];
        }
    }

    *coefficients = coeffs;
    *numCoefficients = numRoots + 1;
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция polyHornerLongDouble
 * </сводка>
 *
 * <описание>
 *   Функция poly - получение коэффициентов полинома по набору его корней (по методу Горнера), поддерживает тип данных long double
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_polyHornerLongDouble(/* in */ IEcoLab1Ptr_t me, /* in */ long double* roots, /* in */ uint32_t numRoots, /* out */ long double** coefficients, /* out */ uint32_t* numCoefficients) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    uint32_t i = 0;
    uint32_t j = 0;
	long double* coeffs = 0;

    /* Проверка указателей */
    if (me == 0 || roots == 0 || coefficients == 0 || numCoefficients == 0) {
        return ERR_ECO_POINTER;
    }

    /* Выделение памяти для коэффициентов */
    coeffs = (long double*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (numRoots + 1) * sizeof(long double));
    if (coeffs == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }
    
    /* Инициализация коэффициентов */
    coeffs[0] = 1.0;
    for (i = 1; i <= numRoots; i++) {
        coeffs[i] = 0.0;
    }

	/* Основной алгоритм */
    for (i = 0; i < numRoots; i++) {
        long double root = roots[i];
        for (j = i + 1; j > 0; j--) {
            coeffs[j] += - root * coeffs[j - 1];
        }
    }

    *coefficients = coeffs;
    *numCoefficients = numRoots + 1;
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Вспомогательная функция для сложения комплексных чисел
 * </сводка>
 *
 */
static EcoComplex complex_add(EcoComplex a, EcoComplex b) {
    EcoComplex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return result;
}

/*
 *
 * <сводка>
 *   Вспомогательная функция для умножения комплексных чисел
 * </сводка>
 *
 */
static EcoComplex complex_multiply(EcoComplex a, EcoComplex b) {
    EcoComplex result;
    result.real = a.real * b.real - a.imag * b.imag;
    result.imag = a.real * b.imag + a.imag * b.real;
    return result;
}

/*
 *
 * <сводка>
 *   Функция polyHornerComplex
 * </сводка>
 *
 * <описание>
 *   Функция poly - получение коэффициентов полинома по набору его корней (по методу Горнера), поддерживает тип данных EcoComplex
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_polyHornerComplex(/* in */ IEcoLab1Ptr_t me, /* in */ EcoComplex* roots, /* in */ uint32_t numRoots, /* out */ EcoComplex** coefficients, /* out */ uint32_t* numCoefficients) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    uint32_t i = 0;
    uint32_t j = 0;
	EcoComplex* coeffs = 0;

    /* Проверка указателей */
    if (me == 0 || roots == 0 || coefficients == 0 || numCoefficients == 0) {
        return ERR_ECO_POINTER;
    }

    /* Выделение памяти для коэффициентов */
    coeffs = (EcoComplex*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (numRoots + 1) * sizeof(EcoComplex));
    if (coeffs == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }
    
    /* Инициализация коэффициентов */
    coeffs[0].real = 1.0;
    coeffs[0].imag = 0.0;
    for (i = 1; i <= numRoots; i++) {
        coeffs[i].real = 0.0;
        coeffs[i].imag = 0.0;
    }

	/* Основной алгоритм */
    for (i = 0; i < numRoots; i++) {
        EcoComplex root = roots[i];
        for (j = i + 1; j > 0; j--) {
			EcoComplex product = complex_multiply(root, coeffs[j - 1]);
			product.real = -product.real;
            product.imag = -product.imag;
			coeffs[j] = complex_add(coeffs[j], product);
        }
    }

    *coefficients = coeffs;
    *numCoefficients = numRoots + 1;
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция polyHornerVector
 * </сводка>
 *
 * <описание>
 *   Функция poly - получение коэффициентов полинома по набору его корней (по методу Горнера), поддерживает тип данных EcoVector
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_polyHornerVector(/* in */ IEcoLab1Ptr_t me, /* in */ EcoVector* roots, /* in */ uint32_t numRoots, /* out */ EcoVector** coefficients, /* out */ uint32_t* numCoefficients) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    int16_t result = ERR_ECO_SUCCESES;
	EcoVector* coeffs = 0;
    
    /* Проверка указателей */
    if (me == 0 || roots == 0 || coefficients == 0 || numCoefficients == 0) {
        return ERR_ECO_POINTER;
    }

    /* Создаем выходной вектор для коэффициентов */
    coeffs = (EcoVector*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(EcoVector));
    if (coeffs == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }

    coeffs->size = numRoots + 1;
    coeffs->type = roots->type;
	coeffs->data = 0;

    /* В зависимости от типа данных вызываем соответствующую функцию */
    switch (roots->type) {
        case 'i': { /* int */
            int* intCoeffs = 0;
            uint32_t numIntCoeffs = 0;
            
            result = me->pVTbl->polyHornerInt(me, (int*)roots->data, numRoots, &intCoeffs, &numIntCoeffs);
            if (result == ERR_ECO_SUCCESES) {
                coeffs->data = intCoeffs;
            }
            break;
        }
        
        case 'l': { /* long (int64_t) */
            int64_t* longCoeffs = 0;
            uint32_t numLongCoeffs = 0;
            
            result = me->pVTbl->polyHornerLong(me, (int64_t*)roots->data, numRoots, &longCoeffs, &numLongCoeffs);
            if (result == ERR_ECO_SUCCESES) {
                coeffs->data = longCoeffs;
            }
            break;
        }
        
        case 'f': { /* float */
            float* floatCoeffs = 0;
            uint32_t numFloatCoeffs = 0;
            
            result = me->pVTbl->polyHornerFloat(me, (float*)roots->data, numRoots, &floatCoeffs, &numFloatCoeffs);
            if (result == ERR_ECO_SUCCESES) {
                coeffs->data = floatCoeffs;
            }
            break;
        }
        
        case 'd': { /* double */
            double* doubleCoeffs = 0;
            uint32_t numDoubleCoeffs = 0;
            
            result = me->pVTbl->polyHornerDouble(me, (double*)roots->data, numRoots, &doubleCoeffs, &numDoubleCoeffs);
            if (result == ERR_ECO_SUCCESES) {
                coeffs->data = doubleCoeffs;
            }
            break;
        }
        
        case 'F': { /* long double */
            long double* longDoubleCoeffs = 0;
            uint32_t numLongDoubleCoeffs = 0;
            
            result = me->pVTbl->polyHornerLongDouble(me, (long double*)roots->data, numRoots, &longDoubleCoeffs, &numLongDoubleCoeffs);
            if (result == ERR_ECO_SUCCESES) {
                coeffs->data = longDoubleCoeffs;
            }
            break;
        }
        
        case 'c': { /* complex */
            EcoComplex* complexCoeffs = 0;
            uint32_t numComplexCoeffs = 0;
            
            result = me->pVTbl->polyHornerComplex(me, (EcoComplex*)roots->data, numRoots, &complexCoeffs, &numComplexCoeffs);
            if (result == ERR_ECO_SUCCESES) {
                coeffs->data = complexCoeffs;
            }
            break;
        }
        
        default:
            /* Освобождаем память и возвращаем ошибку для неизвестного типа */
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, coeffs);
    }

    /* Если произошла ошибка в специализированной функции, освобождаем память */
    if (result != ERR_ECO_SUCCESES) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, coeffs);
        return result;
    }

    *coefficients = coeffs;
    *numCoefficients = 1; /* Возвращаем один вектор с коэффициентами */
    
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция polyHornerMatrix
 * </сводка>
 *
 * <описание>
 *   Функция poly - получение коэффициентов полинома по набору его корней (по методу Горнера), поддерживает тип данных EcoMatrix
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_polyHornerMatrix(/* in */ IEcoLab1Ptr_t me, /* in */ EcoMatrix* mat, /* out */ EcoVector** coefficients, /* out */ uint32_t* numCoefficients) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    uint32_t i = 0, j = 0, k = 0, l = 0, n = 0, idx = 0;
    EcoVector* coeffs = 0;
    EcoMatrix* B = 0;
    double* p = 0;
    double* Bk_data = 0;
    double* Bk_prev_data = 0;
    double* A_data = 0;
    double* result_data = 0;
	double* B0_data;
    double trace = 0.0;
    double sum = 0.0;
    
    /* Проверка указателей */
    if (me == 0 || mat == 0 || coefficients == 0 || numCoefficients == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка что матрица квадратная */
    if (mat->rows != mat->cols) {
        return ERR_ECO_INVALIDARG;
    }

    n = mat->rows;

    /* Создаем выходной вектор для коэффициентов */
    coeffs = (EcoVector*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(EcoVector));
    if (coeffs == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }

    coeffs->size = n + 1;
    coeffs->type = 'd';
    coeffs->data = pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (n + 1) * sizeof(double));
    
    if (coeffs->data == 0) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, coeffs);
        return ERR_ECO_OUTOFMEMORY;
    }

    /* Временные массивы */
    B = (EcoMatrix*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (n + 1) * sizeof(EcoMatrix));
    p = (double*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (n + 1) * sizeof(double));
    
    if (B == 0 || p == 0) {
        if (B) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, B);
        if (p) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, p);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, coeffs->data);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, coeffs);
        return ERR_ECO_OUTOFMEMORY;
    }

    /* Инициализация B[0] как единичной матрицы */
    B[0].rows = n;
    B[0].cols = n;
    B[0].data = pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, n * n * sizeof(double));
    
    if (B[0].data == 0) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, B);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, p);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, coeffs->data);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, coeffs);
        return ERR_ECO_OUTOFMEMORY;
    }
    
    /* Заполняем единичную матрицу */
    B0_data = (double*)B[0].data;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            B0_data[i * n + j] = (i == j) ? 1.0 : 0.0;
        }
    }
    p[0] = 1.0;

    /* Основной алгоритм */
    A_data = (double*)mat->data;
    
    for (k = 1; k <= n; k++) {
        /* Вычисление p[k] = trace(A * B[k-1]) / k */
        trace = 0.0;
        Bk_prev_data = (double*)B[k-1].data;
        
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                sum = 0.0;
                for (l = 0; l < n; l++) {
                    sum += A_data[i * n + l] * Bk_prev_data[l * n + j];
                }
                /* След матрицы - сумма диагональных элементов */
                if (i == j) {
                    trace += sum;
                }
            }
        }
        p[k] = trace / k;

        /* Вычисление B[k] = A * B[k-1] - p[k] * I */
        if (k < n) {
            B[k].rows = n;
            B[k].cols = n;
            B[k].data = pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, n * n * sizeof(double));
            
            if (B[k].data == 0) {
                /* Освобождение памяти в случае ошибки */
                for (idx = 0; idx < k; idx++) {
                    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, B[idx].data);
                }
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, B);
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, p);
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, coeffs->data);
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, coeffs);
                return ERR_ECO_OUTOFMEMORY;
            }

            Bk_data = (double*)B[k].data;
            
            for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
                    sum = 0.0;
                    for (l = 0; l < n; l++) {
                        sum += A_data[i * n + l] * Bk_prev_data[l * n + j];
                    }
                    Bk_data[i * n + j] = sum;
                    if (i == j) {
                        Bk_data[i * n + j] -= p[k];
                    }
                }
            }
        }
    }

    /* Формирование коэффициентов характеристического полинома */
    /* Характеристический полином: λ^n - p[1]λ^(n-1) - p[2]λ^(n-2) - ... - p[n] */
    result_data = (double*)coeffs->data;
    
    /* Старший коэффициент всегда 1 */
    result_data[0] = 1.0;
    
    /* Остальные коэффициенты с чередованием знаков */
    for (i = 1; i <= n; i++) {
        result_data[i] = -p[i];
    }

    /* Освобождение памяти временных матриц B */
    for (i = 0; i < n; i++) {  /* B[n] не выделялась */
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, B[i].data);
    }
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, B);
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, p);

    *coefficients = coeffs;
    *numCoefficients = 1;
    
    return ERR_ECO_SUCCESES;
}



/*
 *
 * <сводка>
 *   Функция bucketSortIntWithK
 * </сводка>
 *
 * <описание>
 *   Функция сортировки целых чисел (int) методом Bucket Sort с заданным количеством корзин k
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_bucketSortIntWithK(/* in */ IEcoLab1Ptr_t me, /* in */ int* arr, /* in */ uint32_t size, /* in */ uint32_t k, /* out */ int** sortedArr) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    int* result;
	uint32_t i, j, bucketIndex, newCapacity, index;
	int** buckets;
	uint32_t* bucketSizes;
	uint32_t* bucketCapacities;
	double range;
	int* newBucket;
	int minVal, maxVal, key, d;

    /* Проверка указателей */
    if (me == 0 || arr == 0 || sortedArr == 0) {
        return ERR_ECO_POINTER;
    }

     /* Проверка размера массива */
    if (size == 0) {
        *sortedArr = 0;
        return ERR_ECO_SUCCESES;
    }

    /* Проверка количества корзин */
    if (k == 0) {
        return ERR_ECO_INVALIDARG;
    }

    /* Если массив состоит из одного элемента */
    if (size == 1) {
        *sortedArr = arr;
        return ERR_ECO_SUCCESES;
    }

    /* Находим минимальное и максимальное значение */
    minVal = arr[0];
    maxVal = arr[0];
    for (i = 1; i < size; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    /* Если все элементы одинаковые */
    if (minVal == maxVal) {
        *sortedArr = arr;
        return ERR_ECO_SUCCESES;
    }

    /* Если k больше размера массива, ограничиваем k размером массива */
    if (k > size) {
        k = size;
    }

    /* Выделяем память для корзин */
    buckets = (int**)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, k * sizeof(int*));
    bucketSizes = (uint32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, k * sizeof(uint32_t));
    bucketCapacities = (uint32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, k * sizeof(uint32_t));
    
    if (buckets == 0 || bucketSizes == 0 || bucketCapacities == 0) {
        if (buckets) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
        if (bucketSizes) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
        if (bucketCapacities) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);
        return ERR_ECO_OUTOFMEMORY;
    }

    /* Инициализация корзин */
    for (i = 0; i < k; i++) {
        bucketSizes[i] = 0;
        bucketCapacities[i] = 10; /* Начальная емкость */
        buckets[i] = (int*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, bucketCapacities[i] * sizeof(int));
        if (buckets[i] == 0) {
            /* Освобождаем уже выделенную память в случае ошибки */
            for (j = 0; j < i; j++) {
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[j]);
            }
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);
            return ERR_ECO_OUTOFMEMORY;
        }
    }

    /* Распределение элементов по корзинам */
    range = (double)(maxVal - minVal + 1);
    for (i = 0; i < size; i++) {
        /* Определяем индекс корзины */
        bucketIndex = (uint32_t)((arr[i] - minVal) * k / range);
        if (bucketIndex >= k) {
            bucketIndex = k - 1;
        }

        /* Проверяем, нужно ли увеличить емкость корзины */
        if (bucketSizes[bucketIndex] >= bucketCapacities[bucketIndex]) {
            newCapacity = bucketCapacities[bucketIndex] * 2;
            newBucket = (int*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, newCapacity * sizeof(int));
            if (newBucket == 0) {
                /* Освобождаем память в случае ошибки */
                for (j = 0; j < k; j++) {
                    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[j]);
                }
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);
                return ERR_ECO_OUTOFMEMORY;
            }

            /* Копируем существующие элементы */
            for (j = 0; j < bucketSizes[bucketIndex]; j++) {
                newBucket[j] = buckets[bucketIndex][j];
            }

            /* Освобождаем старую память и обновляем указатель */
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[bucketIndex]);
            buckets[bucketIndex] = newBucket;
            bucketCapacities[bucketIndex] = newCapacity;
        }

        /* Добавляем элемент в корзину */
        buckets[bucketIndex][bucketSizes[bucketIndex]++] = arr[i];
    }

    /* Сортируем каждую корзину (используем insertion sort для простоты) */
    for (i = 0; i < k; i++) {
        if (bucketSizes[i] > 0) {
            /* Insertion sort для текущей корзины */
            for (j = 1; j < bucketSizes[i]; j++) {
                key = buckets[i][j];
                d = j - 1;
                
                while (d >= 0 && buckets[i][d] > key) {
                    buckets[i][d + 1] = buckets[i][d];
                    d--;
                }
                buckets[i][d + 1] = key;
            }
        }
    }

    /* Собираем отсортированный массив из корзин */
    result = (int*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, size * sizeof(int));
    if (result == 0) {
        /* Освобождаем память корзин в случае ошибки */
        for (i = 0; i < k; i++) {
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[i]);
        }
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);
        return ERR_ECO_OUTOFMEMORY;
    }

    index = 0;
    for (i = 0; i < k; i++) {
        for (j = 0; j < bucketSizes[i]; j++) {
            result[index++] = buckets[i][j];
        }
    }

    /* Освобождаем память корзин */
    for (i = 0; i < k; i++) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[i]);
    }
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);

    *sortedArr = result;
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция bucketSortIntAutoK
 * </сводка>
 *
 * <описание>
 *   Функция сортировки целых чисел (int) методом Bucket Sort без заданного k (вычисляем по формуле (sqrt(n))
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_bucketSortIntAutoK(/* in */ IEcoLab1Ptr_t me, /* in */ int* arr, /* in */ uint32_t size, /* out */ int** sortedArr) {
    uint32_t k = (uint32_t)sqrt(size);
    if (k < 1) k = 1;
    return CEcoLab1_bucketSortIntWithK(me, arr, size, k, sortedArr);
}

/*
 *
 * <сводка>
 *   Функция bucketSortLongWithK
 * </сводка>
 *
 * <описание>
 *   Функция сортировки целых чисел (long) методом Bucket Sort с заданным количеством корзин k
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_bucketSortLongWithK(/* in */ IEcoLab1Ptr_t me, /* in */ int64_t* arr, /* in */ uint32_t size, /* in */ uint32_t k, /* out */ int64_t** sortedArr) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    int64_t* result;
	uint32_t i, j, bucketIndex, newCapacity, index;
	int d;
	int64_t** buckets;
	uint32_t* bucketSizes;
	uint32_t* bucketCapacities;
	double range;
	int64_t* newBucket;
	int64_t minVal, maxVal, key;

    /* Проверка указателей */
    if (me == 0 || arr == 0 || sortedArr == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка размера массива */
    if (size == 0) {
        *sortedArr = 0;
        return ERR_ECO_SUCCESES;
    }

    /* Проверка количества корзин */
    if (k == 0) {
        return ERR_ECO_INVALIDARG;
    }

    /* Если массив состоит из одного элемента */
    if (size == 1) {
        *sortedArr = arr;
        return ERR_ECO_SUCCESES;
    }

    /* Находим минимальное и максимальное значение */
    minVal = arr[0];
    maxVal = arr[0];
    for (i = 1; i < size; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    /* Если все элементы одинаковые */
    if (minVal == maxVal) {
        *sortedArr = arr;
        return ERR_ECO_SUCCESES;
    }

    /* Если k больше размера массива, ограничиваем k размером массива */
    if (k > size) {
        k = size;
    }

    /* Выделяем память для корзин */
    buckets = (int64_t**)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, k * sizeof(int64_t*));
    bucketSizes = (uint32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, k * sizeof(uint32_t));
    bucketCapacities = (uint32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, k * sizeof(uint32_t));
    
    if (buckets == 0 || bucketSizes == 0 || bucketCapacities == 0) {
        if (buckets) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
        if (bucketSizes) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
        if (bucketCapacities) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);
        return ERR_ECO_OUTOFMEMORY;
    }

    /* Инициализация корзин */
    for (i = 0; i < k; i++) {
        bucketSizes[i] = 0;
        bucketCapacities[i] = 10; /* Начальная емкость */
        buckets[i] = (int64_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, bucketCapacities[i] * sizeof(int64_t));
        if (buckets[i] == 0) {
            /* Освобождаем уже выделенную память в случае ошибки */
            for (j = 0; j < i; j++) {
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[j]);
            }
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);
            return ERR_ECO_OUTOFMEMORY;
        }
    }

    /* Распределение элементов по корзинам */
    range = (long double)(maxVal - minVal + 1);
    for (i = 0; i < size; i++) {
        /* Определяем индекс корзины */
        bucketIndex = (uint32_t)((arr[i] - minVal) * k / range);
        if (bucketIndex >= k) {
            bucketIndex = k - 1;
        }

        /* Проверяем, нужно ли увеличить емкость корзины */
        if (bucketSizes[bucketIndex] >= bucketCapacities[bucketIndex]) {
            newCapacity = bucketCapacities[bucketIndex] * 2;
            newBucket = (int64_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, newCapacity * sizeof(int64_t));
            if (newBucket == 0) {
                /* Освобождаем память в случае ошибки */
                for (j = 0; j < k; j++) {
                    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[j]);
                }
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);
                return ERR_ECO_OUTOFMEMORY;
            }

            /* Копируем существующие элементы */
            for (j = 0; j < bucketSizes[bucketIndex]; j++) {
                newBucket[j] = buckets[bucketIndex][j];
            }

            /* Освобождаем старую память и обновляем указатель */
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[bucketIndex]);
            buckets[bucketIndex] = newBucket;
            bucketCapacities[bucketIndex] = newCapacity;
        }

        /* Добавляем элемент в корзину */
        buckets[bucketIndex][bucketSizes[bucketIndex]++] = arr[i];
    }

    /* Сортируем каждую корзину (используем insertion sort для простоты) */
    for (i = 0; i < k; i++) {
        if (bucketSizes[i] > 0) {
            /* Insertion sort для текущей корзины */
            for (j = 1; j < bucketSizes[i]; j++) {
                key = buckets[i][j];
                d = j - 1;
                
                while (d >= 0 && buckets[i][d] > key) {
                    buckets[i][d + 1] = buckets[i][d];
                    d--;
                }
                buckets[i][d + 1] = key;
            }
        }
    }

    /* Собираем отсортированный массив из корзин */
    result = (int64_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, size * sizeof(int64_t));
    if (result == 0) {
        /* Освобождаем память корзин в случае ошибки */
        for (i = 0; i < k; i++) {
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[i]);
        }
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);
        return ERR_ECO_OUTOFMEMORY;
    }

    index = 0;
    for (i = 0; i < k; i++) {
        for (j = 0; j < bucketSizes[i]; j++) {
            result[index++] = buckets[i][j];
        }
    }

    /* Освобождаем память корзин */
    for (i = 0; i < k; i++) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[i]);
    }
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);

    *sortedArr = result;
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция bucketSortLongAutoK
 * </сводка>
 *
 * <описание>
 *   Функция сортировки целых чисел (Long) методом Bucket Sort без заданного k (вычисляем по формуле (sqrt(n))
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_bucketSortLongAutoK(/* in */ IEcoLab1Ptr_t me, /* in */ int64_t* arr, /* in */ uint32_t size, /* out */ int64_t** sortedArr) {
    uint32_t k = (uint32_t)sqrt(size);
    if (k < 1) k = 1;
    return CEcoLab1_bucketSortLongWithK(me, arr, size, k, sortedArr);
}

/*
 *
 * <сводка>
 *   Функция bucketSortFloatWithK
 * </сводка>
 *
 * <описание>
 *   Функция сортировки вещественных чисел (float) методом Bucket Sort с заданным количеством корзин k
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_bucketSortFloatWithK(/* in */ IEcoLab1Ptr_t me, /* in */ float* arr, /* in */ uint32_t size, /* in */ uint32_t k, /* out */ float** sortedArr) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    float* result;
	uint32_t i, j, bucketIndex, newCapacity, index;
	float** buckets;
	uint32_t* bucketSizes;
	uint32_t* bucketCapacities;
	float range;
	float* newBucket;
	float minVal, maxVal, key;
	int d;

    /* Проверка указателей */
    if (me == 0 || arr == 0 || sortedArr == 0) {
        return ERR_ECO_POINTER;
    }

     /* Проверка размера массива */
    if (size == 0) {
        *sortedArr = 0;
        return ERR_ECO_SUCCESES;
    }

    /* Проверка количества корзин */
    if (k == 0) {
        return ERR_ECO_INVALIDARG;
    }

    /* Если массив состоит из одного элемента */
    if (size == 1) {
        *sortedArr = arr;
        return ERR_ECO_SUCCESES;
    }

    /* Находим минимальное и максимальное значение */
    minVal = arr[0];
    maxVal = arr[0];
    for (i = 1; i < size; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    /* Если все элементы одинаковые */
    if (minVal == maxVal) {
        *sortedArr = arr;
        return ERR_ECO_SUCCESES;
    }

    /* Если k больше размера массива, ограничиваем k размером массива */
    if (k > size) {
        k = size;
    }

    /* Выделяем память для корзин */
    buckets = (float**)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, k * sizeof(float*));
    bucketSizes = (uint32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, k * sizeof(uint32_t));
    bucketCapacities = (uint32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, k * sizeof(uint32_t));
    
    if (buckets == 0 || bucketSizes == 0 || bucketCapacities == 0) {
        if (buckets) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
        if (bucketSizes) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
        if (bucketCapacities) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);
        return ERR_ECO_OUTOFMEMORY;
    }

    /* Инициализация корзин */
    for (i = 0; i < k; i++) {
        bucketSizes[i] = 0;
        bucketCapacities[i] = 10; /* Начальная емкость */
        buckets[i] = (float*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, bucketCapacities[i] * sizeof(float));
        if (buckets[i] == 0) {
            /* Освобождаем уже выделенную память в случае ошибки */
            for (j = 0; j < i; j++) {
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[j]);
            }
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);
            return ERR_ECO_OUTOFMEMORY;
        }
    }

    /* Распределение элементов по корзинам */
    range = (float)(maxVal - minVal + 1);
    for (i = 0; i < size; i++) {
        /* Определяем индекс корзины */
        bucketIndex = (uint32_t)((arr[i] - minVal) * k / range);
        if (bucketIndex >= k) {
            bucketIndex = k - 1;
        }

        /* Проверяем, нужно ли увеличить емкость корзины */
        if (bucketSizes[bucketIndex] >= bucketCapacities[bucketIndex]) {
            newCapacity = bucketCapacities[bucketIndex] * 2;
            newBucket = (float*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, newCapacity * sizeof(float));
            if (newBucket == 0) {
                /* Освобождаем память в случае ошибки */
                for (j = 0; j < k; j++) {
                    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[j]);
                }
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);
                return ERR_ECO_OUTOFMEMORY;
            }

            /* Копируем существующие элементы */
            for (j = 0; j < bucketSizes[bucketIndex]; j++) {
                newBucket[j] = buckets[bucketIndex][j];
            }

            /* Освобождаем старую память и обновляем указатель */
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[bucketIndex]);
            buckets[bucketIndex] = newBucket;
            bucketCapacities[bucketIndex] = newCapacity;
        }

        /* Добавляем элемент в корзину */
        buckets[bucketIndex][bucketSizes[bucketIndex]++] = arr[i];
    }

    /* Сортируем каждую корзину (используем insertion sort для простоты) */
    for (i = 0; i < k; i++) {
        if (bucketSizes[i] > 0) {
            /* Insertion sort для текущей корзины */
            for (j = 1; j < bucketSizes[i]; j++) {
                key = buckets[i][j];
                d = j - 1;
                
                while (d >= 0 && buckets[i][d] > key) {
                    buckets[i][d + 1] = buckets[i][d];
                    d--;
                }
                buckets[i][d + 1] = key;
            }
        }
    }

    /* Собираем отсортированный массив из корзин */
    result = (float*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, size * sizeof(float));
    if (result == 0) {
        /* Освобождаем память корзин в случае ошибки */
        for (i = 0; i < k; i++) {
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[i]);
        }
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);
        return ERR_ECO_OUTOFMEMORY;
    }

    index = 0;
    for (i = 0; i < k; i++) {
        for (j = 0; j < bucketSizes[i]; j++) {
            result[index++] = buckets[i][j];
        }
    }

    /* Освобождаем память корзин */
    for (i = 0; i < k; i++) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[i]);
    }
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);

    *sortedArr = result;
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция bucketSortFloatAutoK
 * </сводка>
 *
 * <описание>
 *   Функция сортировки вещественных чисел (float) методом Bucket Sort без заданного k (вычисляем по формуле (sqrt(n))
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_bucketSortFloatAutoK(/* in */ IEcoLab1Ptr_t me, /* in */ float* arr, /* in */ uint32_t size, /* out */ float** sortedArr) {
    uint32_t k = (uint32_t)sqrt(size);
    if (k < 1) k = 1;
    return CEcoLab1_bucketSortFloatWithK(me, arr, size, k, sortedArr);
}

/*
 *
 * <сводка>
 *   Функция bucketSortDoubleWithK
 * </сводка>
 *
 * <описание>
 *   Функция сортировки вещественных чисел (double) методом Bucket Sort с заданным количеством корзин k
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_bucketSortDoubleWithK(/* in */ IEcoLab1Ptr_t me, /* in */ double* arr, /* in */ uint32_t size, /* in */ uint32_t k, /* out */ double** sortedArr) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    double* result;
	uint32_t i, j, bucketIndex, newCapacity, index;
	double** buckets;
	uint32_t* bucketSizes;
	uint32_t* bucketCapacities;
	double range;
	double* newBucket;
	double minVal, maxVal, key;
	int d;

    /* Проверка указателей */
    if (me == 0 || arr == 0 || sortedArr == 0) {
        return ERR_ECO_POINTER;
    }

     /* Проверка размера массива */
    if (size == 0) {
        *sortedArr = 0;
        return ERR_ECO_SUCCESES;
    }

    /* Проверка количества корзин */
    if (k == 0) {
        return ERR_ECO_INVALIDARG;
    }

    /* Если массив состоит из одного элемента */
    if (size == 1) {
        *sortedArr = arr;
        return ERR_ECO_SUCCESES;
    }

    /* Находим минимальное и максимальное значение */
    minVal = arr[0];
    maxVal = arr[0];
    for (i = 1; i < size; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    /* Если все элементы одинаковые */
    if (minVal == maxVal) {
        *sortedArr = arr;
        return ERR_ECO_SUCCESES;
    }

    /* Если k больше размера массива, ограничиваем k размером массива */
    if (k > size) {
        k = size;
    }

    /* Выделяем память для корзин */
    buckets = (double**)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, k * sizeof(double*));
    bucketSizes = (uint32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, k * sizeof(uint32_t));
    bucketCapacities = (uint32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, k * sizeof(uint32_t));
    
    if (buckets == 0 || bucketSizes == 0 || bucketCapacities == 0) {
        if (buckets) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
        if (bucketSizes) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
        if (bucketCapacities) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);
        return ERR_ECO_OUTOFMEMORY;
    }

    /* Инициализация корзин */
    for (i = 0; i < k; i++) {
        bucketSizes[i] = 0;
        bucketCapacities[i] = 10; /* Начальная емкость */
        buckets[i] = (double*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, bucketCapacities[i] * sizeof(double));
        if (buckets[i] == 0) {
            /* Освобождаем уже выделенную память в случае ошибки */
            for (j = 0; j < i; j++) {
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[j]);
            }
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);
            return ERR_ECO_OUTOFMEMORY;
        }
    }

    /* Распределение элементов по корзинам */
    range = (double)(maxVal - minVal + 1);
    for (i = 0; i < size; i++) {
        /* Определяем индекс корзины */
        bucketIndex = (uint32_t)((arr[i] - minVal) * k / range);
        if (bucketIndex >= k) {
            bucketIndex = k - 1;
        }

        /* Проверяем, нужно ли увеличить емкость корзины */
        if (bucketSizes[bucketIndex] >= bucketCapacities[bucketIndex]) {
            newCapacity = bucketCapacities[bucketIndex] * 2;
            newBucket = (double*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, newCapacity * sizeof(double));
            if (newBucket == 0) {
                /* Освобождаем память в случае ошибки */
                for (j = 0; j < k; j++) {
                    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[j]);
                }
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);
                return ERR_ECO_OUTOFMEMORY;
            }

            /* Копируем существующие элементы */
            for (j = 0; j < bucketSizes[bucketIndex]; j++) {
                newBucket[j] = buckets[bucketIndex][j];
            }

            /* Освобождаем старую память и обновляем указатель */
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[bucketIndex]);
            buckets[bucketIndex] = newBucket;
            bucketCapacities[bucketIndex] = newCapacity;
        }

        /* Добавляем элемент в корзину */
        buckets[bucketIndex][bucketSizes[bucketIndex]++] = arr[i];
    }

    /* Сортируем каждую корзину (используем insertion sort для простоты) */
    for (i = 0; i < k; i++) {
        if (bucketSizes[i] > 0) {
            /* Insertion sort для текущей корзины */
            for (j = 1; j < bucketSizes[i]; j++) {
                key = buckets[i][j];
                d = j - 1;
                
                while (d >= 0 && buckets[i][d] > key) {
                    buckets[i][d + 1] = buckets[i][d];
                    d--;
                }
                buckets[i][d + 1] = key;
            }
        }
    }

    /* Собираем отсортированный массив из корзин */
    result = (double*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, size * sizeof(double));
    if (result == 0) {
        /* Освобождаем память корзин в случае ошибки */
        for (i = 0; i < k; i++) {
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[i]);
        }
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);
        return ERR_ECO_OUTOFMEMORY;
    }

    index = 0;
    for (i = 0; i < k; i++) {
        for (j = 0; j < bucketSizes[i]; j++) {
            result[index++] = buckets[i][j];
        }
    }

    /* Освобождаем память корзин */
    for (i = 0; i < k; i++) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[i]);
    }
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);

    *sortedArr = result;
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция bucketSortDoubleAutoK
 * </сводка>
 *
 * <описание>
 *   Функция сортировки вещественных чисел (double) методом Bucket Sort без заданного k (вычисляем по формуле (sqrt(n))
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_bucketSortDoubleAutoK(/* in */ IEcoLab1Ptr_t me, /* in */ double* arr, /* in */ uint32_t size, /* out */ double** sortedArr) {
    uint32_t k = (uint32_t)sqrt(size);
    if (k < 1) k = 1;
    return CEcoLab1_bucketSortDoubleWithK(me, arr, size, k, sortedArr);
}

/*
 *
 * <сводка>
 *   Функция bucketSortLongDoubleWithK
 * </сводка>
 *
 * <описание>
 *   Функция сортировки вещественных чисел (long double) методом Bucket Sort с заданным количеством корзин k
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_bucketSortLongDoubleWithK(/* in */ IEcoLab1Ptr_t me, /* in */ long double* arr, /* in */ uint32_t size, /* in */ uint32_t k, /* out */ long double** sortedArr) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    long double* result;
	uint32_t i, j, bucketIndex, newCapacity, index;
	long double** buckets;
	uint32_t* bucketSizes;
	uint32_t* bucketCapacities;
	long double range;
	long double* newBucket;
	long double minVal, maxVal, key;
	int d;

    /* Проверка указателей */
    if (me == 0 || arr == 0 || sortedArr == 0) {
        return ERR_ECO_POINTER;
    }

     /* Проверка размера массива */
    if (size == 0) {
        *sortedArr = 0;
        return ERR_ECO_SUCCESES;
    }

    /* Проверка количества корзин */
    if (k == 0) {
        return ERR_ECO_INVALIDARG;
    }

    /* Если массив состоит из одного элемента */
    if (size == 1) {
        *sortedArr = arr;
        return ERR_ECO_SUCCESES;
    }

    /* Находим минимальное и максимальное значение */
    minVal = arr[0];
    maxVal = arr[0];
    for (i = 1; i < size; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    /* Если все элементы одинаковые */
    if (minVal == maxVal) {
        *sortedArr = arr;
        return ERR_ECO_SUCCESES;
    }

    /* Если k больше размера массива, ограничиваем k размером массива */
    if (k > size) {
        k = size;
    }

    /* Выделяем память для корзин */
    buckets = (long double**)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, k * sizeof(long double*));
    bucketSizes = (uint32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, k * sizeof(uint32_t));
    bucketCapacities = (uint32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, k * sizeof(uint32_t));
    
    if (buckets == 0 || bucketSizes == 0 || bucketCapacities == 0) {
        if (buckets) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
        if (bucketSizes) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
        if (bucketCapacities) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);
        return ERR_ECO_OUTOFMEMORY;
    }

    /* Инициализация корзин */
    for (i = 0; i < k; i++) {
        bucketSizes[i] = 0;
        bucketCapacities[i] = 10; /* Начальная емкость */
        buckets[i] = (long double*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, bucketCapacities[i] * sizeof(long double));
        if (buckets[i] == 0) {
            /* Освобождаем уже выделенную память в случае ошибки */
            for (j = 0; j < i; j++) {
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[j]);
            }
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);
            return ERR_ECO_OUTOFMEMORY;
        }
    }

    /* Распределение элементов по корзинам */
    range = (long double)(maxVal - minVal + 1);
    for (i = 0; i < size; i++) {
        /* Определяем индекс корзины */
        bucketIndex = (uint32_t)((arr[i] - minVal) * k / range);
        if (bucketIndex >= k) {
            bucketIndex = k - 1;
        }

        /* Проверяем, нужно ли увеличить емкость корзины */
        if (bucketSizes[bucketIndex] >= bucketCapacities[bucketIndex]) {
            newCapacity = bucketCapacities[bucketIndex] * 2;
            newBucket = (long double*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, newCapacity * sizeof(long double));
            if (newBucket == 0) {
                /* Освобождаем память в случае ошибки */
                for (j = 0; j < k; j++) {
                    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[j]);
                }
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);
                return ERR_ECO_OUTOFMEMORY;
            }

            /* Копируем существующие элементы */
            for (j = 0; j < bucketSizes[bucketIndex]; j++) {
                newBucket[j] = buckets[bucketIndex][j];
            }

            /* Освобождаем старую память и обновляем указатель */
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[bucketIndex]);
            buckets[bucketIndex] = newBucket;
            bucketCapacities[bucketIndex] = newCapacity;
        }

        /* Добавляем элемент в корзину */
        buckets[bucketIndex][bucketSizes[bucketIndex]++] = arr[i];
    }

    /* Сортируем каждую корзину (используем insertion sort для простоты) */
    for (i = 0; i < k; i++) {
        if (bucketSizes[i] > 0) {
            /* Insertion sort для текущей корзины */
            for (j = 1; j < bucketSizes[i]; j++) {
                key = buckets[i][j];
                d = j - 1;
                
                while (d >= 0 && buckets[i][d] > key) {
                    buckets[i][d + 1] = buckets[i][d];
                    d--;
                }
                buckets[i][d + 1] = key;
            }
        }
    }

    /* Собираем отсортированный массив из корзин */
    result = (long double*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, size * sizeof(long double));
    if (result == 0) {
        /* Освобождаем память корзин в случае ошибки */
        for (i = 0; i < k; i++) {
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[i]);
        }
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);
        return ERR_ECO_OUTOFMEMORY;
    }

    index = 0;
    for (i = 0; i < k; i++) {
        for (j = 0; j < bucketSizes[i]; j++) {
            result[index++] = buckets[i][j];
        }
    }

    /* Освобождаем память корзин */
    for (i = 0; i < k; i++) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets[i]);
    }
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buckets);
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketSizes);
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, bucketCapacities);

    *sortedArr = result;
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция bucketSortLongDoubleAutoK
 * </сводка>
 *
 * <описание>
 *   Функция сортировки вещественных чисел (long double) методом Bucket Sort без заданного k (вычисляем по формуле (sqrt(n))
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_bucketSortLongDoubleAutoK(/* in */ IEcoLab1Ptr_t me, /* in */ long double* arr, /* in */ uint32_t size, /* out */ long double** sortedArr) {
    uint32_t k = (uint32_t)sqrt(size);
    if (k < 1) k = 1;
    return CEcoLab1_bucketSortLongDoubleWithK(me, arr, size, k, sortedArr);
}



/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD initCEcoLab1(/*in*/ IEcoLab1Ptr_t me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    IEcoInterfaceBus1* pIBus = 0;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;



    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return result;
}

/* Create Virtual Table IEcoLab1 */
IEcoLab1VTbl g_x277FC00C35624096AFCFC125B94EEC90VTbl = {
    CEcoLab1_QueryInterface,
    CEcoLab1_AddRef,
    CEcoLab1_Release,
    CEcoLab1_polyHornerInt,
	CEcoLab1_polyHornerLong,
	CEcoLab1_polyHornerFloat,
	CEcoLab1_polyHornerDouble,
	CEcoLab1_polyHornerLongDouble,
	CEcoLab1_polyHornerComplex,
	CEcoLab1_polyHornerVector,
	CEcoLab1_polyHornerMatrix,

	CEcoLab1_bucketSortIntWithK,
	CEcoLab1_bucketSortIntAutoK,
	CEcoLab1_bucketSortLongWithK,
	CEcoLab1_bucketSortLongAutoK,
	CEcoLab1_bucketSortFloatWithK,
	CEcoLab1_bucketSortFloatAutoK,
	CEcoLab1_bucketSortDoubleWithK,
	CEcoLab1_bucketSortDoubleAutoK,
	CEcoLab1_bucketSortLongDoubleWithK,
	CEcoLab1_bucketSortLongDoubleAutoK
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCEcoLab1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab1** ppIEcoLab1) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoLab1* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;

    /* Проверка указателей */
    if (ppIEcoLab1 == 0 || pIUnkSystem == 0) {
        return result;
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem, (void **)&pISys);

    /* Проверка */
    if (result != 0 && pISys == 0) {
        return result;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab1*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoLab1 */
    pCMe->m_pVTblIEcoLab1 = &g_x277FC00C35624096AFCFC125B94EEC90VTbl;

    /* Инициализация данных */
    pCMe->m_Name = 0;

    /* Возврат указателя на интерфейс */
    *ppIEcoLab1 = (IEcoLab1*)pCMe;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCEcoLab1(/* in */ IEcoLab1* pIEcoLab1) {
    CEcoLab1* pCMe = (CEcoLab1*)pIEcoLab1;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab1 != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
