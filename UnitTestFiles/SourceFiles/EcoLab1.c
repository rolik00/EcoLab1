/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <stdlib.h>

/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"

/*
 *
 * <сводка>
 *   Функция проверки результата для polyHornerInt
 * </сводка>
 *
 */
void check_int_test_result(int* actual, int* expected, uint32_t count, const char* test_name) {
    uint32_t i = 0;
    for (i = 0; i < count; i++) {
        if (actual[i] != expected[i]) {
            printf("%c %s: TEST FAILED!\n", 120, test_name);
			return;
        }
    }
    printf("%c %s: TEST PASSED!\n", 251, test_name);
}

/*
 *
 * <сводка>
 *   Функция тестирования polyHornerInt
 * </сводка>
 *
 */
void test_polyHornerInt(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem) {
    printf("=== Testing polyHornerInt ===\n");
    
    /* Тест 1: Один корень */
    printf("Test 1: Single root [2]\n");
    {
        int roots[] = {2};
        uint32_t n = 1;
        int* coeffs = 0;
        uint32_t coeffs_count = 0;
		int expected_result[] = {1, -2};
		uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerInt(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%d, ", coeffs[i]);
				else printf("%d", coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1, -2]\n");
			check_int_test_result(coeffs, expected_result, coeffs_count, "Test 1");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 2: Два корня */
    printf("Test 2: Two roots [1, 2]\n");
    {
        int roots[] = {1, 2};
        uint32_t n = 2;
        int* coeffs = 0;
        uint32_t coeffs_count = 0;
		int expected_result[] = {1, -3, 2};
		uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerInt(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%d, ", coeffs[i]);
				else printf("%d", coeffs[i]);
            }
            printf("]\n");
			printf("Expected result: [1, -3, 2]\n");
			check_int_test_result(coeffs, expected_result, coeffs_count, "Test 2");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 3: Три корня */
    printf("Test 3: Three roots [1, 2, 3]\n");
    {
        int roots[] = {1, 2, 3};
        uint32_t n = 3;
        int* coeffs = 0;
        uint32_t coeffs_count = 0;
		int expected_result[] = {1, -6, 11, -6};
		uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerInt(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%d, ", coeffs[i]);
				else printf("%d", coeffs[i]);
            }
            printf("]\n");
			printf("Expected result: [1, -6, 11, -6]\n");
			check_int_test_result(coeffs, expected_result, coeffs_count, "Test 3");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 4: Отрицательные корни */
    printf("Test 4: Negative roots [-1, -2]\n");
    {
        int roots[] = {-1, -2};
        uint32_t n = 2;
        int* coeffs = 0;
        uint32_t coeffs_count = 0;
		int expected_result[] = {1, 3, 2};
		uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerInt(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%d, ", coeffs[i]);
				else printf("%d", coeffs[i]);
            }
            printf("]\n");
			printf("Expected result: [1, 3, 2]\n");
			check_int_test_result(coeffs, expected_result, coeffs_count, "Test 4");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 5: Нулевой корень */
    printf("Test 5: Zero root [0, 1]\n");
    {
        int roots[] = {0, 1};
        uint32_t n = 2;
        int* coeffs = 0;
        uint32_t coeffs_count = 0;
		int expected_result[] = {1, -1, 0};
		uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerInt(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%d, ", coeffs[i]);
				else printf("%d", coeffs[i]);
            }
            printf("]\n");
			printf("Expected result: [1, -1, 0]\n");
			check_int_test_result(coeffs, expected_result, coeffs_count, "Test 5");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    printf("=== polyHornerInt testing completed ===\n\n");
}

/*
 *
 * <сводка>
 *   Функция проверки результата для polyHornerLong
 * </сводка>
 *
 */
void check_long_test_result(int64_t* actual, int64_t* expected, uint32_t count, const char* test_name) {
    uint32_t i = 0;
    for (i = 0; i < count; i++) {
        if (actual[i] != expected[i]) {
            printf("%c %s: TEST FAILED!\n", 120, test_name);
			return;
        }
    }
    printf("%c %s: TEST PASSED!\n", 251, test_name);
}

/*
 *
 * <сводка>
 *   Функция тестирования polyHornerLong
 * </сводка>
 *
 */
void test_polyHornerLong(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem) {
    printf("=== Testing polyHornerLong ===\n");
    
    /* Тест 1: Два корня */
    printf("Test 1: Two roots [1000, 2000]\n");
    {
        int64_t roots[] = {1000, 2000};
        uint32_t n = 2;
        int64_t* coeffs = 0;
        uint32_t coeffs_count = 0;
		int64_t expected_result[] = {1, -3000, 2000000};
		uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerLong(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%lld, ", coeffs[i]);
				else printf("%lld", coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1, -3000, 2000000]\n");
			check_long_test_result(coeffs, expected_result, coeffs_count, "Test 1");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 2: Отрицательные корни */
    printf("Test 2: Negative roots [-1000, -2000]\n");
    {
        int64_t roots[] = {-1000, -2000};
        uint32_t n = 2;
        int64_t* coeffs = 0;
        uint32_t coeffs_count = 0;
		int64_t expected_result[] = {1, 3000, 2000000};
		uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerLong(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%lld, ", coeffs[i]);
				else printf("%lld", coeffs[i]);
            }
            printf("]\n");
			printf("Expected result: [1, 3000, 2000000]\n");
			check_long_test_result(coeffs, expected_result, coeffs_count, "Test 2");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 3: Смешанные знаки */
    printf("Test 3: Mixed signs [-500, 1000]\n");
    {
        int64_t roots[] = {-500, 1000};
        uint32_t n = 2;
        int64_t* coeffs = 0;
        uint32_t coeffs_count = 0;
		int64_t expected_result[] = {1, -500, -500000};
		uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerLong(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%lld, ", coeffs[i]);
				else printf("%lld", coeffs[i]);
            }
            printf("]\n");
			printf("Expected result: [1, -500, -500000]\n");
			check_long_test_result(coeffs, expected_result, coeffs_count, "Test 3");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 4: Три корня */
    printf("Test 4: Three roots [10293, 234, 2492]\n");
    {
        int64_t roots[] = {10293, 234, 2492};
        uint32_t n = 3;
        int64_t* coeffs = 0;
        uint32_t coeffs_count = 0;
		int64_t expected_result[] = {1, -13019, 28641846, -6002136504};
		uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerLong(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%lld, ", coeffs[i]);
				else printf("%lld", coeffs[i]);
            }
            printf("]\n");
			printf("Expected result: [1, -13019, 28641846, -6002136504]\n");
			check_long_test_result(coeffs, expected_result, coeffs_count, "Test 4");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 5: Нулевой корень */
    printf("Test 5: Zero root [0, 500]\n");
    {
        int64_t roots[] = {0, 500};
        uint32_t n = 2;
        int64_t* coeffs = 0;
        uint32_t coeffs_count = 0;
		int64_t expected_result[] = {1, -500, 0};
		uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerLong(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%lld, ", coeffs[i]);
				else printf("%lld", coeffs[i]);
            }
            printf("]\n");
			printf("Expected result: [1, -500, 0]\n");
			check_long_test_result(coeffs, expected_result, coeffs_count, "Test 5");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    printf("=== polyHornerLong testing completed ===\n\n");
}

/*
 *
 * <сводка>
 *   Функция проверки результата для polyHornerFloat
 * </сводка>
 *
 */
void check_float_test_result(float* actual, float* expected, uint32_t count, const char* test_name) {
    uint32_t i = 0;
	const float tolerance = 0.0001f;
    for (i = 0; i < count; i++) {
        if (fabs(actual[i] - expected[i]) > tolerance) {
            printf("%c %s: TEST FAILED!\n", 120, test_name);
			return;
        }
    }
    printf("%c %s: TEST PASSED!\n", 251, test_name);
}

/*
 *
 * <сводка>
 *   Функция тестирования polyHornerFloat
 * </сводка>
 *
 */
void test_polyHornerFloat(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem) {
    printf("=== Testing polyHornerFloat ===\n");
    
    /* Тест 1: Два корня */
    printf("Test 1: Two roots [2.0, 3.0]\n");
    {
        float roots[] = {2.0f, 3.0f};
        uint32_t n = 2;
        float* coeffs = 0;
        uint32_t coeffs_count = 0;
		float expected_result[] = {1.0f, -5.0f, 6.0f};
		uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerFloat(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.4f, ", coeffs[i]);
				else printf("%.4f", coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0000, -5.0000, 6.0000]\n");
			check_float_test_result(coeffs, expected_result, coeffs_count, "Test 1");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 2: Дробные корни */
    printf("Test 2: Fractional roots [0.5, 1.5]\n");
    {
        float roots[] = {0.5f, 1.5f};
        uint32_t n = 2;
        float* coeffs = 0;
        uint32_t coeffs_count = 0;
		float expected_result[] = {1.0f, -2.0f, 0.75f};
		uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerFloat(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.4f, ", coeffs[i]);
				else printf("%.4f", coeffs[i]);
            }
            printf("]\n");
			printf("Expected result: [1.0000, -2.0000, 0.7500]\n");
			check_float_test_result(coeffs, expected_result, coeffs_count, "Test 2");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 3: Отрицательные дробные корни */
    printf("Test 3: Negative fractional roots [-1.5, -2.5]\n");
    {
        float roots[] = {-1.5f, -2.5f};
        uint32_t n = 2;
        float* coeffs = 0;
        uint32_t coeffs_count = 0;
		float expected_result[] = {1.0f, 4.0f, 3.75f};
		uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerFloat(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.4f, ", coeffs[i]);
				else printf("%.4f", coeffs[i]);
            }
            printf("]\n");
			printf("Expected result: [1.0000, 4.0000, 3.7500]\n");
			check_float_test_result(coeffs, expected_result, coeffs_count, "Test 3");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 4: Три дробных корня */
    printf("Test 4: Three fractional roots [0.25, 0.5, 1.0]\n");
    {
        float roots[] = {0.25f, 0.5f, 1.0f};
        uint32_t n = 3;
        float* coeffs = 0;
        uint32_t coeffs_count = 0;
		float expected_result[] = {1.0f, -1.75f, 0.875f, -0.125f};
		uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerFloat(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.4f, ", coeffs[i]);
				else printf("%.4f", coeffs[i]);
            }
            printf("]\n");
			printf("Expected result: [1.0000, -1.7500, 0.8750, -0.1250]\n");
			check_float_test_result(coeffs, expected_result, coeffs_count, "Test 4");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 5: Смешанные знаки с дробями */
    printf("Test 5: Mixed signs with fractions [-0.5, 1.5]\n");
    {
        float roots[] = {-0.5f, 1.5f};
        uint32_t n = 2;
        float* coeffs = 0;
        uint32_t coeffs_count = 0;
		float expected_result[] = {1.0f, -1.0f, -0.75f};
		uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerFloat(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.4f, ", coeffs[i]);
				else printf("%.4f", coeffs[i]);
            }
            printf("]\n");
			printf("Expected result: [1.0000, -1.0000, -0.7500]\n");
			check_float_test_result(coeffs, expected_result, coeffs_count, "Test 5");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }

	/* Тест 6: Нулевой корень с дробями */
    printf("Test 6: Zero root with fractions [0.0f, 2.5f]\n");
    {
        float roots[] = {0.0f, 2.5f};
        uint32_t n = 2;
        float* coeffs = 0;
        uint32_t coeffs_count = 0;
        float expected_result[] = {1.0f, -2.5f, 0.0f};
        uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerFloat(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.4f, ", coeffs[i]);
                else printf("%.4f", coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0000, -2.5000, 0.0000]\n");
            check_float_test_result(coeffs, expected_result, coeffs_count, "Test 6");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 7: Маленькие дробные числа */
    printf("Test 7: Small fractions [0.1f, 0.2f, 0.3f]\n");
    {
        float roots[] = {0.1f, 0.2f, 0.3f};
        uint32_t n = 3;
        float* coeffs = 0;
        uint32_t coeffs_count = 0;
        float expected_result[] = {1.0f, -0.6f, 0.11f, -0.006f};
        uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerFloat(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.4f, ", coeffs[i]);
                else printf("%.4f", coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0000, -0.6000, 0.1100, -0.0060]\n");
            check_float_test_result(coeffs, expected_result, coeffs_count, "Test 7");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    printf("=== polyHornerFloat testing completed ===\n\n");
}

/*
 *
 * <сводка>
 *   Функция проверки результата для polyHornerDouble
 * </сводка>
 *
 */
void check_double_test_result(double* actual, double* expected, uint32_t count, const char* test_name) {
    uint32_t i = 0;
    const double tolerance = 0.000001;
    for (i = 0; i < count; i++) {
        if (fabs(actual[i] - expected[i]) > tolerance) {
            printf("%c %s: TEST FAILED!\n", 120, test_name);
            return;
        }
    }
    printf("%c %s: TEST PASSED!\n", 251, test_name);
}

/*
 *
 * <сводка>
 *   Функция тестирования polyHornerDouble
 * </сводка>
 *
 */
void test_polyHornerDouble(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem) {
    printf("=== Testing polyHornerDouble ===\n");
    
    /* Тест 1: Два корня */
    printf("Test 1: Two roots [2.0, 3.0]\n");
    {
        double roots[] = {2.0, 3.0};
        uint32_t n = 2;
        double* coeffs = 0;
        uint32_t coeffs_count = 0;
        double expected_result[] = {1.0, -5.0, 6.0};
        uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerDouble(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.4f, ", coeffs[i]);
                else printf("%.4f", coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0000, -5.0000, 6.0000]\n");
            check_double_test_result(coeffs, expected_result, coeffs_count, "Test 1");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 2: Точные дробные корни */
    printf("Test 2: Precise fractional roots [0.5, 1.5]\n");
    {
        double roots[] = {0.5, 1.5};
        uint32_t n = 2;
        double* coeffs = 0;
        uint32_t coeffs_count = 0;
        double expected_result[] = {1.0, -2.0, 0.75};
        uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerDouble(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.4f, ", coeffs[i]);
                else printf("%.4f", coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0000, -2.0000, 0.7500]\n");
            check_double_test_result(coeffs, expected_result, coeffs_count, "Test 2");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 3: Большие числа с высокой точностью */
    printf("Test 3: Large numbers with high precision [12345.6789, 98765.4321]\n");
    {
        double roots[] = {12345.6789, 98765.4321};
        uint32_t n = 2;
        double* coeffs = 0;
        uint32_t coeffs_count = 0;
        double expected_result[] = {1.0, -111111.111, 1219326311.126353};
        uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerDouble(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.4f, ", coeffs[i]);
                else printf("%.4f", coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0000, -111111.1110, 1219326311.1264]\n");
            check_double_test_result(coeffs, expected_result, coeffs_count, "Test 3");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 4: Очень маленькие числа */
    printf("Test 4: Very small numbers [0.000001, 0.000002]\n");
    {
        double roots[] = {0.000001, 0.000002};
        uint32_t n = 2;
        double* coeffs = 0;
        uint32_t coeffs_count = 0;
        double expected_result[] = {1.0, -0.000003, 0.000000000002};
        uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerDouble(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.12f, ", coeffs[i]);
                else printf("%.12f", coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.000000000000, -0.000003000000, 0.000000000002]\n");
            check_double_test_result(coeffs, expected_result, coeffs_count, "Test 4");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 5: Три корня с высокой точностью */
    printf("Test 5: Three roots with high precision [1.234567, 2.345678, 3.456789]\n");
    {
        double roots[] = {1.234567, 2.345678, 3.456789};
        uint32_t n = 3;
        double* coeffs = 0;
        uint32_t coeffs_count = 0;
        double expected_result[] = {1.0, -7.037034, 15.272048, -10.010504};
        uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerDouble(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.4f, ", coeffs[i]);
                else printf("%.4f", coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0000, -7.0370, 15.2720, -10.0105]\n");
            check_double_test_result(coeffs, expected_result, coeffs_count, "Test 5");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 6: Смешанные знаки с высокой точностью */
    printf("Test 6: Mixed signs with high precision [-123.456, 789.012]\n");
    {
        double roots[] = {-123.456, 789.012};
        uint32_t n = 2;
        double* coeffs = 0;
        uint32_t coeffs_count = 0;
        double expected_result[] = {1.0, -665.556, -97408.265472};
        uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerDouble(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.4f, ", coeffs[i]);
                else printf("%.4f", coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0000, -665.5560, -97408.2655]\n");
            check_double_test_result(coeffs, expected_result, coeffs_count, "Test 6");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 7: Иррациональные числа */
    printf("Test 7: Irrational numbers [M_PI, M_E]\n");
    {
        double roots[] = {M_PI, M_E};
        uint32_t n = 2;
        double* coeffs = 0;
        uint32_t coeffs_count = 0;
        double expected_result[] = {1.0, -(M_PI + M_E), M_PI * M_E};
        uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerDouble(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.4f, ", coeffs[i]);
                else printf("%.4f", coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0000, -5.8599, 8.5397]\n");
            check_double_test_result(coeffs, expected_result, coeffs_count, "Test 7");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 8: Нулевой корень с высокой точностью */
    printf("Test 8: Zero root with high precision [0.0, 123.456789]\n");
    {
        double roots[] = {0.0, 123.456789};
        uint32_t n = 2;
        double* coeffs = 0;
        uint32_t coeffs_count = 0;
        double expected_result[] = {1.0, -123.456789, 0.0};
        uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerDouble(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.4f, ", coeffs[i]);
                else printf("%.4f", coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0000, -123.4568, 0.0000]\n");
            check_double_test_result(coeffs, expected_result, coeffs_count, "Test 8");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    printf("=== polyHornerDouble testing completed ===\n\n");
}

/*
 *
 * <сводка>
 *   Функция проверки результата для polyHornerLongDouble
 * </сводка>
 *
 */
void check_long_double_test_result(long double* actual, long double* expected, uint32_t count, const char* test_name) {
    uint32_t i = 0;
    for (i = 0; i < count; i++) {
        if (fabsl(actual[i] - expected[i]) > 1e-6) {
            printf("%c %s: TEST FAILED!\n", 120, test_name);
            return;
        }
    }
    printf("%c %s: TEST PASSED!\n", 251, test_name);
}

/*
 *
 * <сводка>
 *   Функция тестирования polyHornerLongDouble
 * </сводка>
 *
 */
void test_polyHornerLongDouble(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem) {
    printf("=== Testing polyHornerLongDouble ===\n");
    
    /* Тест 1: Два корня */
    printf("Test 1: Two roots [12345670.89, 90876543.21]\n");
    {
        long double roots[] = {12345670.89, 90876543.21};
        uint32_t n = 2;
        long double* coeffs = 0;
        uint32_t coeffs_count = 0;
        long double expected_result[] = {1.0, -103222214.1, 1121931894091524.1569};
        uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerLongDouble(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.4Lf, ", coeffs[i]);
                else printf("%.4Lf", coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0000, -103222214.1000, 1121931894091524.1569]\n");
            check_long_double_test_result(coeffs, expected_result, coeffs_count, "Test 1");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 2: Три корня */
    printf("Test 2: Three roots [345.76, 45567.742, 3.962]\n");
    {
        long double roots[] = {345.76, 45567.742, 3.962};
        uint32_t n = 3;
        long double* coeffs = 0;
        uint32_t coeffs_count = 0;
        long double expected_result[] = {1.0, -45917.464, 15937411.768844, -62423300.801671};
        uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerLongDouble(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.4Lf, ", coeffs[i]);
                else printf("%.4Lf", coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0000, -45917.4640, 15937411.7688, -62423300.8017]\n");
            check_long_double_test_result(coeffs, expected_result, coeffs_count, "Test 2");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 3: Отрицательные корни */
    printf("Test 3: Negative roots [-26398.853, -37523.74]\n");
    {
        long double roots[] = {-26398.853, -37523.74};
        uint32_t n = 2;
        long double* coeffs = 0;
        uint32_t coeffs_count = 0;
        long double expected_result[] = {1.0, 63922.593, 990583696.27022};
        uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerLongDouble(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.4Lf, ", coeffs[i]);
                else printf("%.4Lf", coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0000, 63922.5930, 990583696.2702]\n");
            check_long_double_test_result(coeffs, expected_result, coeffs_count, "Test 3");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 4: Смешанные знаки */
    printf("Test 4: Mixed signs [-26398.853, 37523.74]\n");
    {
        long double roots[] = {-26398.853, 37523.74};
        uint32_t n = 2;
        long double* coeffs = 0;
        uint32_t coeffs_count = 0;
        long double expected_result[] = {1.0, -11124.887, -990583696.27022};
        uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerLongDouble(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.4Lf, ", coeffs[i]);
                else printf("%.4Lf", coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0000, -11124.8870, -990583696.2702]\n");
            check_long_double_test_result(coeffs, expected_result, coeffs_count, "Test 4");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
    /* Тест 5: Нулевой корень */
    printf("Test 5: Zero root [0.0, -97654.87654]\n");
    {
        long double roots[] = {0.0, -97654.87654};
        uint32_t n = 2;
        long double* coeffs = 0;
        uint32_t coeffs_count = 0;
        long double expected_result[] = {1.0, 97654.87654, 0.0};
        uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerLongDouble(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.4Lf, ", coeffs[i]);
                else printf("%.4Lf", coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0000, 0.0000, 97654.8765]\n");
            check_long_double_test_result(coeffs, expected_result, coeffs_count, "Test 5");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }
    
	/* Тест  6: Пустой массив корней */
    printf("Test 6: Empty roots array\n");
    {
        long double roots[] = {0.0};
        uint32_t n = 0;
        long double* coeffs = 0;
        uint32_t coeffs_count = 0;
        long double expected_result[] = {1.0, 0.0, 97654.87654};
        uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerLongDouble(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) printf("%.4Lf, ", coeffs[i]);
                else printf("%.4Lf", coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0000]\n");
            check_long_double_test_result(coeffs, expected_result, coeffs_count, "Test 6");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }

    printf("=== polyHornerLongDouble testing completed ===\n\n");
}

/*
 *
 * <сводка>
 *   Функция проверки результата для polyHornerComplex
 * </сводка>
 *
 */
void check_complex_test_result(EcoComplex* actual, EcoComplex* expected, uint32_t count, const char* test_name) {
    uint32_t i = 0;
    for (i = 0; i < count; i++) {
        if (actual[i].imag != expected[i].imag || actual[i].real != expected[i].real) {
            printf("%c %s: TEST FAILED!\n", 120, test_name);
            return;
        }
    }
    printf("%c %s: TEST PASSED!\n", 251, test_name);
}

/*
 *
 * <сводка>
 *   Функция вывода комплексного числа
 * </сводка>
 *
 */
void print_complex(EcoComplex c) {
	if (c.imag == 0) {
		printf("%.1f", c.real);
	} else if (c.imag > 0) {
        printf("%.1f + %.1fi", c.real, c.imag);
    } else {
        printf("%.1f - %.1fi", c.real, -c.imag);
    }
}

/*
 *
 * <сводка>
 *   Функция тестирования polyHornerComplex
 * </сводка>
 *
 */
void test_polyHornerComplex(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem) {
    printf("=== Testing polyHornerComplex ===\n");
    
    /* Тест 1: Два корня */
    printf("Test 1: Two roots [2-4i, 8-6i]\n");
    {
		EcoComplex roots[] = {{2.0, -4.0}, {8.0, -6.0}};
        uint32_t n = 2;
        EcoComplex* coeffs = 0;
        uint32_t coeffs_count = 0;
        EcoComplex expected_result[] = {{1.0, 0.0}, {-10, 10}, {-8, -44}};
        uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerComplex(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) {
					print_complex(coeffs[i]);
					printf(", ");
				}
                else print_complex(coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0, -10.0 - 10.0i, -8.0 - 44.0i]\n");
            check_complex_test_result(coeffs, expected_result, coeffs_count, "Test 1");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }

	/* Тест 2: Комплексно-сопряженные корни */
    printf("Test 2: Complex conjugate roots [i, -i]\n");
    {
        EcoComplex roots[] = {{0.0, 1.0}, {0.0, -1.0}};
        uint32_t n = 2;
        EcoComplex* coeffs = 0;
        uint32_t coeffs_count = 0;
        EcoComplex expected_result[] = {{1.0, 0.0}, {0.0, 0.0}, {1.0, 0.0}};
		uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerComplex(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) {
					print_complex(coeffs[i]);
					printf(", ");
				}
                else print_complex(coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0, 0.0, 1.0]\n");
            check_complex_test_result(coeffs, expected_result, coeffs_count, "Test 2");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }

	/* Тест 3: Смешанные действительные и комплексные корни */
    printf("Test 3: Mixed real and complex roots [1, i]\n");
    {
        EcoComplex roots[] = {{1.0, 0.0}, {0.0, 1.0}};
        uint32_t n = 2;
        EcoComplex* coeffs = 0;
        uint32_t coeffs_count = 0;
        EcoComplex expected_result[] = {{1.0, 0.0}, {-1.0, -1.0}, {0.0, 1.0}};
		uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerComplex(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) {
					print_complex(coeffs[i]);
					printf(", ");
				}
                else print_complex(coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0, -1.0 - 1.0i, 0.0 - 1.0i]\n");
            check_complex_test_result(coeffs, expected_result, coeffs_count, "Test 3");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }

	/* Тест 4: Три корня */
    printf("Test 4: Three roots [2.5-1.5i, 3+4i, 0.5+i]\n");
    {
		EcoComplex roots[] = {{2.5, -1.5}, {3.0, 4.0}, {0.5, 1.0}};
        uint32_t n = 3;
        EcoComplex* coeffs = 0;
        uint32_t coeffs_count = 0;
        EcoComplex expected_result[] = {{1.0, 0.0}, {-6.0, -3.5}, {13.75, 12.25}, {-1.25, -16.25}};
		uint32_t i = 0;
        
        int16_t result = pIEcoLab1->pVTbl->polyHornerComplex(pIEcoLab1, roots, n, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs_count; i++) {
                if (i < coeffs_count - 1) {
					print_complex(coeffs[i]);
					printf(", ");
				}
                else print_complex(coeffs[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0, -6.0 - 3.5i, 13.75 + 12.25i, -1.25 - 16.25i]\n");
            check_complex_test_result(coeffs, expected_result, coeffs_count, "Test 4");
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
    }

    printf("=== polyHornerComplex testing completed ===\n\n");
}

/*
 *
 * <сводка>
 *   Функция тестирования polyHornerVector
 * </сводка>
 *
 */
void test_polyHornerVector(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem) {
    printf("=== Testing polyHornerVector ===\n");
    
    /* Тест 1: Вектор с целыми числами (int) */
    printf("Test 1: Integer vector [1, 2]\n");
    {
        int data[] = {1, 2};
        EcoVector roots;
		int16_t result;
        EcoVector* coeffs = 0;
        uint32_t numCoeffs = 0;
        int expected_result[] = {1, -3, 2};
        uint32_t i = 0;
        int test_passed = 1;

		roots.data = data;
        roots.size = 2; 
        roots.type = 'i';
        
        result = pIEcoLab1->pVTbl->polyHornerVector(pIEcoLab1, &roots, roots.size, &coeffs, &numCoeffs);
        if (result == 0 && coeffs != 0 && coeffs->data != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs->size; i++) {
                if (i < coeffs->size - 1) printf("%d, ", ((int*)coeffs->data)[i]);
                else printf("%d", ((int*)coeffs->data)[i]);
            }
            printf("]\n");
            printf("Expected result: [1, -3, 2]\n");
        
            // Проверка результата
            for (i = 0; i < coeffs->size; i++) {
                if (((int*)coeffs->data)[i] != expected_result[i]) {
                    test_passed = 0;
                    break;
                }
            }
            printf("Test 1: %s\n\n", test_passed ? "PASSED" : "FAILED");
        
            pIMem->pVTbl->Free(pIMem, ((int*)coeffs->data));
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n\n", result);
        }
    }

    /* Тест 2: Вектор с длинными целыми (int64_t) */
    printf("Test 2: Long integer vector [1000, 2000]\n");
    {
        int64_t data[] = {1000, 2000};
        EcoVector roots;
		int16_t result;
        EcoVector* coeffs = 0;
        uint32_t numCoeffs = 0;
        int64_t expected_result[] = {1, -3000, 2000000};
        uint32_t i = 0;
        int test_passed = 1;

		roots.data = data;
        roots.size = 2; 
        roots.type = 'l';
        
        result = pIEcoLab1->pVTbl->polyHornerVector(pIEcoLab1, &roots, roots.size, &coeffs, &numCoeffs);
        if (result == 0 && coeffs != 0 && coeffs->data != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs->size; i++) {
                if (i < coeffs->size - 1) printf("%lld, ", ((int64_t*)coeffs->data)[i]);
                else printf("%lld", ((int64_t*)coeffs->data)[i]);
            }
            printf("]\n");
            printf("Expected result: [1, -3000, 2000000]\n");
        
            // Проверка результата
            for (i = 0; i < coeffs->size; i++) {
                if (((int64_t*)coeffs->data)[i] != expected_result[i]) {
                    test_passed = 0;
                    break;
                }
            }
            printf("Test 2: %s\n\n", test_passed ? "PASSED" : "FAILED");
        
            pIMem->pVTbl->Free(pIMem, ((int64_t*)coeffs->data));
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n\n", result);
        }
    }

    /* Тест 3: Вектор с числами с плавающей точкой (float) */
    printf("Test 3: Float vector [0.5f, 1.5f]\n");
    {
        float data[] = {0.5f, 1.5f};
        EcoVector roots;
		int16_t result;
        EcoVector* coeffs = 0;
        uint32_t numCoeffs = 0;
        float expected_result[] = {1.0f, -2.0f, 0.75f};
        float tolerance = 0.0001f;
        uint32_t i = 0;
        int test_passed = 1;

		roots.data = data;
        roots.size = 2; 
        roots.type = 'f';
    
        result = pIEcoLab1->pVTbl->polyHornerVector(pIEcoLab1, &roots, roots.size, &coeffs, &numCoeffs);
        if (result == 0 && coeffs != 0 && coeffs->data != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs->size; i++) {
                if (i < coeffs->size - 1) printf("%.4f, ", ((float*)coeffs->data)[i]);
                else printf("%.4f", ((float*)coeffs->data)[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0000, -2.0000, 0.7500]\n");
            
            // Проверка результата с учетом погрешности
            for (i = 0; i < coeffs->size; i++) {
                if (fabsf(((float*)coeffs->data)[i] - expected_result[i]) > tolerance) {
                   test_passed = 0;
                   break;
                }
            }
            printf("Test 3: %s\n\n", test_passed ? "PASSED" : "FAILED");
            
            pIMem->pVTbl->Free(pIMem, ((float*)coeffs->data));
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n\n", result);
        }
    }

    /* Тест 4: Вектор с числами двойной точности (double) */
    printf("Test 4: Double vector [2.0, 3.0]\n");
    {
        double data[] = {2.0, 3.0};
        EcoVector roots;
		int16_t result;
        EcoVector* coeffs = 0;
        uint32_t numCoeffs = 0;
        double expected_result[] = {1.0, -5.0, 6.0};
        double tolerance = 0.0001;
        uint32_t i = 0;
        int test_passed = 1;

		roots.data = data;
        roots.size = 2; 
        roots.type = 'd';
    
        result = pIEcoLab1->pVTbl->polyHornerVector(pIEcoLab1, &roots, roots.size, &coeffs, &numCoeffs);
        if (result == 0 && coeffs != 0 && coeffs->data != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs->size; i++) {
                if (i < coeffs->size - 1) printf("%.4f, ", ((double*)coeffs->data)[i]);
                else printf("%.4f", ((double*)coeffs->data)[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0000, -5.0000, 6.0000]\n");
        
            // Проверка результата с учетом погрешности
            for (i = 0; i < coeffs->size; i++) {
                if (fabs(((double*)coeffs->data)[i] - expected_result[i]) > tolerance) {
                    test_passed = 0;
                    break;
                }
            }
            printf("Test 4: %s\n\n", test_passed ? "PASSED" : "FAILED");
        
            pIMem->pVTbl->Free(pIMem, ((double*)coeffs->data));
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n\n", result);
        }
    }

    /* Тест 5: Вектор с длинными double */
    printf("Test 5: Long double vector [12345670.89, 90876543.21]\n");
    {
        long double data[] = {12345670.89L, 90876543.21L}; 
        EcoVector roots;
		int16_t result;
        EcoVector* coeffs = 0;
        uint32_t numCoeffs = 0;
        long double expected_result[] = {1.0L, -103222214.1L, 1121931894091524.1569L};
        long double tolerance = 0.0001L;
        uint32_t i = 0;
        int test_passed = 1;

		roots.data = data;
        roots.size = 2; 
        roots.type = 'F'; 
        
        result = pIEcoLab1->pVTbl->polyHornerVector(pIEcoLab1, &roots, roots.size, &coeffs, &numCoeffs);
        if (result == 0 && coeffs != 0 && coeffs->data != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs->size; i++) {
                if (i < coeffs->size - 1) printf("%.4Lf, ", ((long double*)coeffs->data)[i]);
                else printf("%.4Lf", ((long double*)coeffs->data)[i]);
            }
            printf("]\n");
            printf("Expected result: [1.0000, -103222214.1000, 1121931894091524.1569]\n");
        
            // Проверка результата с учетом погрешности
            for (i = 0; i < coeffs->size; i++) {
                if (fabsl(((long double*)coeffs->data)[i] - expected_result[i]) > tolerance) {
                    test_passed = 0;
                    break;
                }
            }
            printf("Test 5: %s\n\n", test_passed ? "PASSED" : "FAILED");
            
            pIMem->pVTbl->Free(pIMem, ((long double*)coeffs->data));
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n\n", result);
        }
    }

    /* Тест 6: Вектор с комплексными числами */
    printf("Test 6: Complex vector [2-4i, 8-6i]\n");
    {
        EcoComplex data[] = {{2.0, -4.0}, {8.0, -6.0}}; 
        EcoVector roots;
		int16_t result;
        EcoVector* coeffs = 0;
        uint32_t numCoeffs = 0;
        EcoComplex expected_result[] = {{1.0, 0.0}, {-10.0, 10.0}, {-8.0, -44.0}};
        uint32_t i = 0;
        int test_passed = 1;

		roots.data = data;
        roots.size = 2; 
        roots.type = 'c';
    
        result = pIEcoLab1->pVTbl->polyHornerVector(pIEcoLab1, &roots, roots.size, &coeffs, &numCoeffs);
        if (result == 0 && coeffs != 0 && coeffs->data != 0) {
            printf("Actual result: [");
            for (i = 0; i < coeffs->size; i++) {
                EcoComplex c = ((EcoComplex*)coeffs->data)[i];
                if (i < coeffs->size - 1) {  
                    print_complex(c);  
                    printf(", ");
                }
                else {
                    print_complex(c);
                }
            }
            printf("]\n");
            printf("Expected result: [1.0+0.0i, -10.0+10.0i, -8.0-44.0i]\n");
        
            // Проверка результата с учетом погрешности
            for (i = 0; i < coeffs->size; i++) {
                EcoComplex actual = ((EcoComplex*)coeffs->data)[i];
                EcoComplex expected = expected_result[i];
                if (actual.real != expected.real || actual.imag != expected.imag) {
                    test_passed = 0;
                    break;
                }
            }
            printf("Test 6: %s\n\n", test_passed ? "PASSED" : "FAILED");
        
            pIMem->pVTbl->Free(pIMem, ((EcoComplex*)coeffs->data));
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n\n", result);
        }
    }
}

/*
 *
 * <сводка>
 *   Функция тестирования polyHornerMatrix
 * </сводка>
 *
 */
void test_polyHornerMatrix(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem) {
    printf("=== Testing polyHornerMatrix ===\n");
    
    /* Тест 1: Матрица 2x2 */
    printf("Test 1: 2x2 Matrix\n");
    {
        EcoMatrix mat;
		double* data;
		EcoVector* coeffs = 0;
        uint32_t coeffs_count = 0, i = 0;
        double expected_result[] = {1.0, -5.0, -2.0};
        double* coeffs_data;
		int16_t result;
       
        data = (double*)pIMem->pVTbl->Alloc(pIMem, 4 * sizeof(double));
        data[0] = 1.0; data[1] = 2.0;
        data[2] = 3.0; data[3] = 4.0;
        mat.data = data;
		mat.rows = 2;
        mat.cols = 2;
        
        result = pIEcoLab1->pVTbl->polyHornerMatrix(pIEcoLab1, &mat, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0 && coeffs->data != 0) {
            printf("Matrix:\n");
            printf("[%.1f, %.1f]\n", data[0], data[1]);
            printf("[%.1f, %.1f]\n", data[2], data[3]);
            
            printf("Actual characteristic polynomial coefficients: [");
            coeffs_data = (double*)coeffs->data;
            for (i = 0; i < coeffs->size; i++) {
                printf("%.1f", coeffs_data[i]);
                if (i < coeffs->size - 1) printf(", ");
            }
            printf("]\n");
            
            printf("Expected coefficients: [1.0, -5.0, -2.0]\n");
            check_double_test_result(coeffs_data, expected_result, coeffs_count, "Test 1");
            pIMem->pVTbl->Free(pIMem, coeffs->data);
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
        pIMem->pVTbl->Free(pIMem, data);
    }

    /* Тест 2: Единичная матрица 2x2 */
    printf("Test 2: Identity 2x2 Matrix\n");
    {
		EcoMatrix mat;
		double* data;
		EcoVector* coeffs = 0;
        uint32_t coeffs_count = 0, i = 0;
        double expected_result[] = {1.0, -2.0, 1.0};
        double* coeffs_data;
		int16_t result;
       
        data = (double*)pIMem->pVTbl->Alloc(pIMem, 4 * sizeof(double));
        data[0] = 1.0; data[1] = 0.0;
        data[2] = 0.0; data[3] = 1.0;
        mat.data = data;
		mat.rows = 2;
        mat.cols = 2;
        
        result = pIEcoLab1->pVTbl->polyHornerMatrix(pIEcoLab1, &mat, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0 && coeffs->data != 0) {
            printf("Matrix:\n");
            printf("[%.1f, %.1f]\n", data[0], data[1]);
            printf("[%.1f, %.1f]\n", data[2], data[3]);
            
            printf("Actual characteristic polynomial coefficients: [");
            coeffs_data = (double*)coeffs->data;
            for (i = 0; i < coeffs->size; i++) {
                printf("%.1f", coeffs_data[i]);
                if (i < coeffs->size - 1) printf(", ");
            }
            printf("]\n");
            
            printf("Expected coefficients: [1.0, -2.0, 1.0]\n");
            check_double_test_result(coeffs_data, expected_result, coeffs_count, "Test 2");
            pIMem->pVTbl->Free(pIMem, coeffs->data);
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
        pIMem->pVTbl->Free(pIMem, data);
    }

    /* Тест 3: Матрица 3x3 */
    printf("Test 3: 3x3 Matrix\n");
    {
        EcoMatrix mat;
        EcoVector* coeffs = 0;
        uint32_t coeffs_count = 0, i = 0;
        double expected_result[] = {1.0, -11.0, 34.0, -24.0};
		double* data;
		int16_t result;
		double* coeffs_data;
        
        data = (double*)pIMem->pVTbl->Alloc(pIMem, 9 * sizeof(double));
        data[0] = 1.0; data[1] = 2.0; data[2] = 3.0;
        data[3] = 0.0; data[4] = 4.0; data[5] = 5.0;
        data[6] = 0.0; data[7] = 0.0; data[8] = 6.0;
        mat.data = data;
		mat.rows = 3;
        mat.cols = 3;
        
        result = pIEcoLab1->pVTbl->polyHornerMatrix(pIEcoLab1, &mat, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0 && coeffs->data != 0) {
            printf("Matrix:\n");
            printf("[%.1f, %.1f, %.1f]\n", data[0], data[1], data[2]);
            printf("[%.1f, %.1f, %.1f]\n", data[3], data[4], data[5]);
            printf("[%.1f, %.1f, %.1f]\n", data[6], data[7], data[8]);
            
            printf("Actual characteristic polynomial coefficients: [");
            coeffs_data = (double*)coeffs->data;
            for (i = 0; i < coeffs->size; i++) {
                printf("%.1f", coeffs_data[i]);
                if (i < coeffs->size - 1) printf(", ");
            }
            printf("]\n");
            
            printf("Expected coefficients: [1.0, -11.0, 34.0, -24.0]\n");
            check_double_test_result(coeffs_data, expected_result, coeffs_count, "Test 3");
            pIMem->pVTbl->Free(pIMem, coeffs->data);
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
        pIMem->pVTbl->Free(pIMem, data);
    }

    /* Тест 4: Нулевая матрица 2x2 */
    printf("Test 4: Zero 2x2 Matrix\n");
    {
        EcoMatrix mat;
		double* data;
		EcoVector* coeffs = 0;
        uint32_t coeffs_count = 0, i = 0;
		double expected_result[] = {1.0, 0.0, 0.0};
		int16_t result;
		double* coeffs_data;
        
        data = (double*)pIMem->pVTbl->Alloc(pIMem, 4 * sizeof(double));
        data[0] = 0.0; data[1] = 0.0;
        data[2] = 0.0; data[3] = 0.0;
        mat.data = data;
		mat.rows = 2;
        mat.cols = 2;
        
        result = pIEcoLab1->pVTbl->polyHornerMatrix(pIEcoLab1, &mat, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0 && coeffs->data != 0) {
            printf("Matrix:\n");
            printf("[%.1f, %.1f]\n", data[0], data[1]);
            printf("[%.1f, %.1f]\n", data[2], data[3]);
            
            printf("Actual characteristic polynomial coefficients: [");
            coeffs_data = (double*)coeffs->data;
            for (i = 0; i < coeffs->size; i++) {
                printf("%.1f", coeffs_data[i]);
                if (i < coeffs->size - 1) printf(", ");
            }
            printf("]\n"); 
            printf("Expected coefficients: [1.0, 0.0, 0.0]\n");
            check_double_test_result(coeffs_data, expected_result, coeffs_count, "Test 4");
            pIMem->pVTbl->Free(pIMem, coeffs->data);
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
        pIMem->pVTbl->Free(pIMem, data);
    }

    /* Тест 5: Симметричная матрица 2x2 */
    printf("Test 5: Symmetric 2x2 Matrix\n");
    {
        EcoMatrix mat;
        double* data;
        EcoVector* coeffs = 0;
        uint32_t coeffs_count = 0, i = 0;
		double expected_result[] = {1.0, -7.0, 1.0};
		int16_t result;
		double* coeffs_data;
        
        data = (double*)pIMem->pVTbl->Alloc(pIMem, 4 * sizeof(double));
        data[0] = 5.0; data[1] = 3.0;
        data[2] = 3.0; data[3] = 2.0;
        mat.data = data;
		mat.rows = 2;
        mat.cols = 2;
        
        result = pIEcoLab1->pVTbl->polyHornerMatrix(pIEcoLab1, &mat, &coeffs, &coeffs_count);
        if (result == 0 && coeffs != 0 && coeffs->data != 0) {
            printf("Matrix:\n");
            printf("[%.1f, %.1f]\n", data[0], data[1]);
            printf("[%.1f, %.1f]\n", data[2], data[3]);
            
            printf("Actual characteristic polynomial coefficients: [");
            coeffs_data = (double*)coeffs->data;
            for (i = 0; i < coeffs->size; i++) {
                printf("%.1f", coeffs_data[i]);
                if (i < coeffs->size - 1) printf(", ");
            }
            printf("]\n");
            printf("Expected coefficients: [1.0, -7.0, 1.0]\n");
            check_double_test_result(coeffs_data, expected_result, coeffs_count, "Test 5");
            pIMem->pVTbl->Free(pIMem, coeffs->data);
            pIMem->pVTbl->Free(pIMem, coeffs);
        } else {
            printf("Error: %d\n", result);
        }
        pIMem->pVTbl->Free(pIMem, data);
    }

    printf("=== polyHornerMatrix testing completed ===\n\n");
}

/*
 *
 * <сводка>
 *   Функция генерации случайного double
 * </сводка>
 *
 */
double rand_double(double min, double max) {
    return min + (rand() / (RAND_MAX / (max - min)));
}

/*
 *
 * <сводка>
 *   Функция сравнения скорости алгоритмов (здесь проверяем время работы polyHornerDouble)
 * </сводка>
 *
 */
void compare_algorithms(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem) {
    const int iterations = 1000;
    const int max_i = 13;
	int i, j, iter, degree;
    double* roots;
    double* coeffs;
    uint32_t coeffs_count;
    clock_t start;
    double result_time;
    int16_t result;
    
    srand(time(NULL));

    printf("Degree\tHorner Time (ms)\n");
    printf("----------------------\n");

    for (i = 0; i <= max_i; i++) {
        degree = (int)pow(2, i);
        
        /* Создаем случайные корни */
        roots = (double*)pIMem->pVTbl->Alloc(pIMem, degree * sizeof(double));
        if (roots == 0) {
            printf("Memory allocation failed for degree %d\n", degree);
            continue;
        }
        
        for (j = 0; j < degree; j++) {
            roots[j] = rand_double(-10.0, 10.0);
        }

        /* Вычисляем коэффициенты с помощью polyHornerDouble */
        coeffs = 0;
        coeffs_count = 0;
        
        start = clock();
        for (iter = 0; iter < iterations; iter++) {
            int16_t result = pIEcoLab1->pVTbl->polyHornerDouble(pIEcoLab1, roots, degree, &coeffs, &coeffs_count);
            if (result != 0 && coeffs != 0) {
                pIMem->pVTbl->Free(pIMem, coeffs);
                coeffs = 0;
            }
        }
        result_time = ((double)(clock() - start)) / CLOCKS_PER_SEC * 1000 / iterations;

        printf("%d\t%.3f\n", degree, result_time);

        /* Освобождаем память */
        if (coeffs != 0) {
            pIMem->pVTbl->Free(pIMem, coeffs);
        }
        pIMem->pVTbl->Free(pIMem, roots);
    }
}




/*
 *
 * <сводка>
 *   Функция проверки результата
 * </сводка>
 *
 */
void asserts(void** actual, void** expected, uint32_t count) {
    uint32_t i = 0;
    for (i = 0; i < count; i++) {
        if (actual[i] != expected[i]) {
            printf("TEST FAILED!\n");
            return;
        }
    }
    printf("TEST PASSED!\n");
}

/*
 *
 * <сводка>
 *   Функция проверки работы всех алгоритмов
 * </сводка>
 *
 */
void test_allFunctions(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem) {
    /* bucketSortIntWithK  */
    printf("\n=== Testing bucketSortIntWithK ===\n");
    {
        int arr[] = { 2, 5, 1, 0, -3, 8, 2 };
        uint32_t n = 7, i = 0;
        int* sortedArr = 0;
        int expected_result[] = { -3, 0, 1, 2, 2, 5, 8 };
        int k = 3;
        int16_t result;

        printf("Input:\narr = [2, 5, 1, 0, -3, 8, 2], k = 3\n");

        result = pIEcoLab1->pVTbl->bucketSortIntWithK(pIEcoLab1, arr, n, k, &sortedArr);
        if (result == 0 && sortedArr != 0) {
            printf("Returned result: [");
            for (i = 0; i < n; i++) {
                printf("%d", sortedArr[i]);
                if (i < n - 1) printf(", ");
            }
            printf("]\n");
            printf("Expected result: [-3, 0, 1, 2, 2, 5, 8]\n");
            asserts(sortedArr, expected_result, n);
            pIMem->pVTbl->Free(pIMem, sortedArr);
        }
        else {
            printf("Error: %d\n", result);
        }
    }

	/* bucketSortIntAutoK  */
    printf("\n=== Testing bucketSortIntAutoK ===\n");
    {
        int arr[] = { 5, 3, 10, 3, 1, -39, -20 };
        uint32_t n = 7, i = 0;
        int* sortedArr = 0;
        int expected_result[] = { -39, -20, 1, 3, 3, 5, 10 };
        int16_t result;

        printf("Input:\narr = [5, 3, 10, 3, 1, -39, -20]\n");

        result = pIEcoLab1->pVTbl->bucketSortIntAutoK(pIEcoLab1, arr, n, &sortedArr);
        if (result == 0 && sortedArr != 0) {
            printf("Returned result: [");
            for (i = 0; i < n; i++) {
                printf("%d", sortedArr[i]);
                if (i < n - 1) printf(", ");
            }
            printf("]\n");
            printf("Expected result: [-39, -20, 1, 3, 3, 5, 10]\n");
            asserts(sortedArr, expected_result, n);
            pIMem->pVTbl->Free(pIMem, sortedArr);
        }
        else {
            printf("Error: %d\n", result);
        }
    }

	/* bucketSortLongWithK  */
    printf("\n=== Testing bucketSortLongWithK ===\n");
    {
        int64_t arr[] = { 20000, 50000, -10012, 0, -3653, 89753, 203 };
        uint32_t n = 7, i = 0;
        int64_t* sortedArr = 0;
        int64_t expected_result[] = { -10012, -3653, 0, 203, 20000, 50000, 89753 };
        int k = 3;
        int16_t result;

        printf("Input:\narr = [20000, 50000, -10012, 0, -3653, 89753, 203], k = 3\n");

        result = pIEcoLab1->pVTbl->bucketSortLongWithK(pIEcoLab1, arr, n, k, &sortedArr);
        if (result == 0 && sortedArr != 0) {
            printf("Returned result: [");
            for (i = 0; i < n; i++) {
                printf("%lld", sortedArr[i]);
                if (i < n - 1) printf(", ");
            }
            printf("]\n");
            printf("Expected result: [-10012, -3653, 0, 203, 20000, 50000, 89753]\n");
            asserts(sortedArr, expected_result, n);
            pIMem->pVTbl->Free(pIMem, sortedArr);
        }
        else {
            printf("Error: %d\n", result);
        }
    }

	/* bucketSortLongAutoK  */
    printf("\n=== Testing bucketSortLongAutoK ===\n");
    {
        int64_t arr[] = { 463735, 36253, 18430, -43, 193, -309, -2000 };
        uint32_t n = 7, i = 0;
        int64_t* sortedArr = 0;
        int64_t expected_result[] = { -2000 , -309, -43, 193, 18430, 36253, 463735 };
        int16_t result;

        printf("Input:\narr = [463735, 36253, 18430, -43, 193, -309, -2000]\n");

        result = pIEcoLab1->pVTbl->bucketSortLongAutoK(pIEcoLab1, arr, n, &sortedArr);
        if (result == 0 && sortedArr != 0) {
            printf("Returned result: [");
            for (i = 0; i < n; i++) {
                printf("%lld", sortedArr[i]);
                if (i < n - 1) printf(", ");
            }
            printf("]\n");
            printf("Expected result: [-2000 , -309, -43, 193, 18430, 36253, 463735]\n");
            asserts(sortedArr, expected_result, n);
            pIMem->pVTbl->Free(pIMem, sortedArr);
        }
        else {
            printf("Error: %d\n", result);
        }
    }

	/* bucketSortFloatWithK  */
    printf("\n=== Testing bucketSortFloatWithK ===\n");
    {
        float arr[] = { 1.2, -0.05, -8.2, 9.3, 5.4, 0.5, 9.32 };
        uint32_t n = 7, i = 0;
        float* sortedArr = 0;
        float expected_result[] = {  -8.2, -0.05, 0.5, 1.2, 5.4, 9.3, 9.32 };
        int k = 3;
        int16_t result;

        printf("Input:\narr = [1.20, -0.05, -8.20, 9.30, 5.40, 0.50, 9.32], k = 3\n");

        result = pIEcoLab1->pVTbl->bucketSortFloatWithK(pIEcoLab1, arr, n, k, &sortedArr);
        if (result == 0 && sortedArr != 0) {
            printf("Returned result: [");
            for (i = 0; i < n; i++) {
                printf("%.2f", sortedArr[i]);
                if (i < n - 1) printf(", ");
            }
            printf("]\n");
            printf("Expected result: [-8.20, -0.05, 0.50, 1.20, 5.40, 9.30, 9.32]\n");
            asserts(sortedArr, expected_result, n);
            pIMem->pVTbl->Free(pIMem, sortedArr);
        }
        else {
            printf("Error: %d\n", result);
        }
    }

	/* bucketSortFloatAutoK  */
    printf("\n=== Testing bucketSortFloatAutoK ===\n");
    {
        float arr[] = { 4.23, 4.56, -0.34, 0.98, -5.7, 4.65, 4.66 };
        uint32_t n = 7, i = 0;
        float* sortedArr = 0;
        float expected_result[] = { -5.7, -0.34, 0.98, 4.23, 4.56, 4.65, 4.66 };
        int16_t result;

        printf("Input:\narr = [4.23, 4.56, -0.34, 0.98, -5.70, 4.65, 4.66]\n");

        result = pIEcoLab1->pVTbl->bucketSortFloatAutoK(pIEcoLab1, arr, n, &sortedArr);
        if (result == 0 && sortedArr != 0) {
            printf("Returned result: [");
            for (i = 0; i < n; i++) {
                printf("%.2f", sortedArr[i]);
                if (i < n - 1) printf(", ");
            }
            printf("]\n");
            printf("Expected result: [-5.70, -0.34, 0.98, 4.23, 4.56, 4.65, 4.66]\n");
            asserts(sortedArr, expected_result, n);
            pIMem->pVTbl->Free(pIMem, sortedArr);
        }
        else {
            printf("Error: %d\n", result);
        }
    }
	
	/* bucketSortDoubleWithK  */
    printf("\n=== Testing bucketSortDoubleWithK ===\n");
    {
        double arr[] = { 123.45, 45.678, -976.34, -5.45, 3456.34, -4665.24, 4956.73 };
        uint32_t n = 7, i = 0;
        double* sortedArr = 0;
        double expected_result[] = { -4665.24, -976.34, -5.45, 45.678, 123.45, 3456.34, 4956.73 };
        int k = 3;
        int16_t result;

        printf("Input:\narr = [123.45, 45.68, -976.34, -5.45, 3456.34, -4665.24, 4956.73], k = 3\n");

        result = pIEcoLab1->pVTbl->bucketSortDoubleWithK(pIEcoLab1, arr, n, k, &sortedArr);
        if (result == 0 && sortedArr != 0) {
            printf("Returned result: [");
            for (i = 0; i < n; i++) {
                printf("%.2f", sortedArr[i]);
                if (i < n - 1) printf(", ");
            }
            printf("]\n");
            printf("Expected result: [-4665.24, -976.34, -5.45, 45.68, 123.45, 3456.34, 4956.73]\n");
            asserts(sortedArr, expected_result, n);
            pIMem->pVTbl->Free(pIMem, sortedArr);
        }
        else {
            printf("Error: %d\n", result);
        }
    }

	/* bucketSortDoubleAutoK  */
    printf("\n=== Testing bucketSortDoubleAutoK ===\n");
    {
        double arr[] = { 123.45, 567.89, 90.87, -876.54, -54.32, 234.56, -345.67 };
        uint32_t n = 7, i = 0;
        double* sortedArr = 0;
        double expected_result[] = { -876.54, -345.67, -54.32, 90.87, 123.45, 234.56, 567.89 };
        int16_t result;

        printf("Input:\narr = [123.45, 567.89, 90.87, -876.54, -54.32, 234.56, -345.67]\n");

        result = pIEcoLab1->pVTbl->bucketSortDoubleAutoK(pIEcoLab1, arr, n, &sortedArr);
        if (result == 0 && sortedArr != 0) {
            printf("Returned result: [");
            for (i = 0; i < n; i++) {
                printf("%.2f", sortedArr[i]);
                if (i < n - 1) printf(", ");
            }
            printf("]\n");
            printf("Expected result: [-876.54, -345.67, -54.32, 90.87, 123.45, 234.56, 567.89]\n");
            asserts(sortedArr, expected_result, n);
            pIMem->pVTbl->Free(pIMem, sortedArr);
        }
        else {
            printf("Error: %d\n", result);
        }
    }

	/* bucketSortLongDoubleWithK  */
    printf("\n=== Testing bucketSortLongDoubleWithK ===\n");
    {
        long double arr[] = { 1234567.89, 90876543.21, 23456788.98, -98657452.34, -45678567.64, 28377565.86, 789654.34 };
        uint32_t n = 7, i = 0;
        long double* sortedArr = 0;
        long double expected_result[] = { -98657452.34, -45678567.64, 789654.34, 1234567.89, 23456788.98, 28377565.86, 90876543.21 };
        int k = 3;
        int16_t result;

        printf("Input:\narr = [1234567.89, 90876543.21, 23456788.98, -98657452.34, -45678567.64, 28377565.86], k = 3\n");

        result = pIEcoLab1->pVTbl->bucketSortLongDoubleWithK(pIEcoLab1, arr, n, k, &sortedArr);
        if (result == 0 && sortedArr != 0) {
            printf("Returned result: [");
            for (i = 0; i < n; i++) {
                printf("%.2Lf", sortedArr[i]);
                if (i < n - 1) printf(", ");
            }
            printf("]\n");
            printf("Expected result: [-98657452.34, -45678567.64, 789654.34, 1234567.89, 23456788.98, 28377565.86, 90876543.21]\n");
            asserts(sortedArr, expected_result, n);
            pIMem->pVTbl->Free(pIMem, sortedArr);
        }
        else {
            printf("Error: %d\n", result);
        }
    }

	/* bucketSortLongDoubleAutoK  */
    printf("\n=== Testing bucketSortLongDoubleAutoK ===\n");
    {
        long double arr[] = { 12345670.89, 90876543.21, -26398.853, -37523.74, -26398.853, 37523.74, -97654.87654 };
        uint32_t n = 7, i = 0;
        long double* sortedArr = 0;
        long double expected_result[] = { -97654.87654, -37523.74, -26398.853, -26398.853, 37523.74, 12345670.89, 90876543.21 };
        int16_t result;

        printf("Input:\narr = [12345670.89, 90876543.21, -26398.85, -37523.74, -26398.85, 37523.74, -97654.88]\n");

        result = pIEcoLab1->pVTbl->bucketSortLongDoubleAutoK(pIEcoLab1, arr, n, &sortedArr);
        if (result == 0 && sortedArr != 0) {
            printf("Returned result: [");
            for (i = 0; i < n; i++) {
                printf("%.2Lf", sortedArr[i]);
                if (i < n - 1) printf(", ");
            }
            printf("]\n");
            printf("Expected result: [-97654.88, -37523.74, -26398.85, -26398.85, 37523.74, 12345670.89, 90876543.21]\n");
            asserts(sortedArr, expected_result, n);
            pIMem->pVTbl->Free(pIMem, sortedArr);
        }
        else {
            printf("Error: %d\n", result);
        }
    }
}

/*
 *
 * <сводка>
 *   Функция сравнения для qsort (int)
 * </сводка>
 *
 */
int __cdecl compare_int(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

/*
 *
 * <сводка>
 *   Функция сравнения для qsort (int64_t)
 * </сводка>
 *
 */
int __cdecl compare_long(const void* a, const void* b) {
    int64_t diff = (*(int64_t*)a - *(int64_t*)b);
    return (diff > 0) ? 1 : ((diff < 0) ? -1 : 0);
}

/*
 *
 * <сводка>
 *   Функция сравнения для qsort (float)
 * </сводка>
 *
 */
int __cdecl compare_float(const void* a, const void* b) {
    float diff = (*(float*)a - *(float*)b);
    return (diff > 0) ? 1 : ((diff < 0) ? -1 : 0);
}

/*
 *
 * <сводка>
 *   Функция сравнения для qsort (double)
 * </сводка>
 *
 */
int __cdecl compare_double(const void* a, const void* b) {
    double diff = (*(double*)a - *(double*)b);
    return (diff > 0) ? 1 : ((diff < 0) ? -1 : 0);
}

/*
 *
 * <сводка>
 *   Функция сравнения для qsort (long double)
 * </сводка>
 *
 */
int __cdecl compare_long_double(const void* a, const void* b) {
    long double diff = (*(long double*)a - *(long double*)b);
    return (diff > 0) ? 1 : ((diff < 0) ? -1 : 0);
}

/*
 *
 * <сводка>
 *   Функция генерации случайного массива int
 * </сводка>
 *
 */
int* generate_random_int_array(uint32_t size, int min, int max) {
    int* arr = (int*)malloc(size * sizeof(int));
	uint32_t i = 0;
    if (arr) {
        for (i = 0; i < size; i++) {
            arr[i] = min + rand() % (max - min + 1);
        }
    }
    return arr;
}

/*
 *
 * <сводка>
 *   Функция генерации случайного массива int64_t
 * </сводка>
 *
 */
int64_t* generate_random_long_array(uint32_t size, int64_t min, int64_t max) {
    int64_t* arr = (int64_t*)malloc(size * sizeof(int64_t));
	uint32_t i = 0;
    if (arr) {
        for (i = 0; i < size; i++) {
            arr[i] = min + (int64_t)rand() % (max - min + 1);
        }
    }
    return arr;
}

/*
 *
 * <сводка>
 *   Функция генерации случайного массива float
 * </сводка>
 *
 */
float* generate_random_float_array(uint32_t size, float min, float max) {
    float* arr = (float*)malloc(size * sizeof(float));
	uint32_t i = 0;
    if (arr) {
        for (i = 0; i < size; i++) {
            arr[i] = min + (float)rand() / RAND_MAX * (max - min);
        }
    }
    return arr;
}

/*
 *
 * <сводка>
 *   Функция генерации случайного массива double
 * </сводка>
 *
 */
double* generate_random_double_array(uint32_t size, double min, double max) {
    double* arr = (double*)malloc(size * sizeof(double));
	uint32_t i = 0;
    if (arr) {
        for (i = 0; i < size; i++) {
            arr[i] = min + (double)rand() / RAND_MAX * (max - min);
        }
    }
    return arr;
}

/*
 *
 * <сводка>
 *   Функция генерации случайного массива long double
 * </сводка>
 *
 */
long double* generate_random_long_double_array(uint32_t size, long double min, long double max) {
    long double* arr = (long double*)malloc(size * sizeof(long double));
	uint32_t i = 0;
    if (arr) {
        for (i = 0; i < size; i++) {
            arr[i] = min + (long double)rand() / RAND_MAX * (max - min);
        }
    }
    return arr;
}

/*
 *
 * <сводка>
 *   Функция compareBucketSortWithQSort
 * </сводка>
 *
 * <описание>
 *   Функция сравнения производительности bucketSort и qsort для разных типов данных и размеров массивов
 * </описание>
 *
 */
void compareBucketSortWithQSort(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem) {
    uint32_t sizes[] = {1, 10, 100, 1000, 2000, 5000, 6000, 7000, 8000};
    uint32_t numSizes = sizeof(sizes) / sizeof(sizes[0]);
    const uint32_t iterations = 1000;
	uint32_t s, size, iter, i;
	double bucket_time = 0.0, qsort_time = 0.0;
	clock_t start, end;
    
    srand((unsigned int)time(NULL));
    
    printf("\n=== Performance Comparison: BucketSort vs QSort ===\n");
    printf("Averaged over %d iterations\n\n", iterations);
    
    /* Тестирование для типа int */
    printf("========== Testing INT ==========\n");
    printf("Size\tBucketSort (ms)\tQSort (ms)\n");
    printf("---------------------------------\n");
    
    for (s = 0; s < numSizes; s++) {
        size = sizes[s];
        bucket_time = 0.0, qsort_time = 0.0;
        
        for (iter = 0; iter < iterations; iter++) {
            /* Генерация случайного массива */
            int* arr1 = generate_random_int_array(size, -1000000, 1000000);
            int* arr2 = generate_random_int_array(size, -1000000, 1000000);
            int* sorted = NULL;
			if (arr1 && arr2) {
                /* Тестирование BucketSort */
                start = clock();
                pIEcoLab1->pVTbl->bucketSortIntAutoK(pIEcoLab1, arr1, size, &sorted);
                end = clock();
                bucket_time += ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
                
                if (sorted) {
                    pIMem->pVTbl->Free(pIMem, sorted);
                }
                
                /* Тестирование QSort */
                start = clock();
                qsort(arr2, size, sizeof(int), compare_int);
                end = clock();
                qsort_time += ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
            }
            
            if (arr1) free(arr1);
            if (arr2) free(arr2);
        }
        
        bucket_time /= iterations;
        qsort_time /= iterations;
        
        printf("%d\t%.3f\t\t%.3f\n", size, bucket_time, qsort_time);
    }
    
	/* Тестирование для типа int64_t */
    printf("\n==== Testing LONG (int64_t) ====\n");
    printf("Size\tBucketSort (ms)\t QSort (ms)\n");
    printf("----------------------------------\n");
    
    for (s = 0; s < numSizes; s++) {
        size = sizes[s];
        bucket_time = 0.0, qsort_time = 0.0;
        
        for (iter = 0; iter < iterations; iter++) {
            /* Генерация случайного массива */
            int64_t* arr1 = generate_random_long_array(size, -1000000LL, 1000000LL);
            int64_t* arr2 = generate_random_long_array(size, -1000000LL, 1000000LL);
            int64_t* sorted = NULL;

            if (arr1 && arr2) {
                /* Тестирование BucketSort */
                start = clock();
                pIEcoLab1->pVTbl->bucketSortLongAutoK(pIEcoLab1, arr1, size, &sorted);
                end = clock();
                bucket_time += ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
                
                if (sorted) {
                    pIMem->pVTbl->Free(pIMem, sorted);
                }
                
                /* Тестирование QSort */
                start = clock();
                qsort(arr2, size, sizeof(int64_t), compare_long);
                end = clock();
                qsort_time += ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
            }
            
            if (arr1) free(arr1);
            if (arr2) free(arr2);
        }
        
        bucket_time /= iterations;
        qsort_time /= iterations;
        
        printf("%d\t%.3f\t\t%.3f\n", size, bucket_time, qsort_time);
    }
    
    /* Тестирование для типа float */
    printf("\n======== Testing FLOAT ========\n");
    printf("Size\tBucketSort (ms)\tQSort (ms)\n");
    printf("---------------------------------\n");
    
    for (s = 0; s < numSizes; s++) {
        size = sizes[s];
        bucket_time = 0.0, qsort_time = 0.0;
        
        for (iter = 0; iter < iterations; iter++) {
            /* Генерация случайного массива */
            float* arr1 = generate_random_float_array(size, -1000.0f, 1000.0f);
            float* arr2 = generate_random_float_array(size, -1000.0f, 1000.0f);
            float* sorted = NULL;

            if (arr1 && arr2) {
                /* Тестирование BucketSort */
                start = clock();
                pIEcoLab1->pVTbl->bucketSortFloatAutoK(pIEcoLab1, arr1, size, &sorted);
                end = clock();
                bucket_time += ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
                
                if (sorted) {
                    pIMem->pVTbl->Free(pIMem, sorted);
                }
                
                /* Тестирование QSort */
                start = clock();
                qsort(arr2, size, sizeof(float), compare_float);
                end = clock();
                qsort_time += ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
            }
            
            if (arr1) free(arr1);
            if (arr2) free(arr2);
        }
        
        bucket_time /= iterations;
        qsort_time /= iterations;
        
        printf("%d\t%.3f\t\t%.3f\n", size, bucket_time, qsort_time);
    }
    
    /* Тестирование для типа double */
    printf("\n======== Testing DOUBLE ========\n");
    printf("Size\tBucketSort (ms)\t QSort (ms)\n");
    printf("----------------------------------\n");
    
    for (s = 0; s < numSizes; s++) {
        size = sizes[s];
        bucket_time = 0.0, qsort_time = 0.0;
        
        for (iter = 0; iter < iterations; iter++) {
            /* Генерация случайного массива */
            double* arr1 = generate_random_double_array(size, -1000.0, 1000.0);
            double* arr2 = generate_random_double_array(size, -1000.0, 1000.0);
            double* sorted = NULL;
                
            if (arr1 && arr2) {
                /* Тестирование BucketSort */
                start = clock();
                pIEcoLab1->pVTbl->bucketSortDoubleAutoK(pIEcoLab1, arr1, size, &sorted);
                end = clock();
                bucket_time += ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
                
                if (sorted) {
                    pIMem->pVTbl->Free(pIMem, sorted);
                }
                
                /* Тестирование QSort */
                start = clock();
                qsort(arr2, size, sizeof(double), compare_double);
                end = clock();
                qsort_time += ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
            }
            
            if (arr1) free(arr1);
            if (arr2) free(arr2);
        }
        
        bucket_time /= iterations;
        qsort_time /= iterations;
        
        printf("%d\t%.3f\t\t%.3f\n", size, bucket_time, qsort_time);
    }
    
    /* Тестирование для типа long double */
    printf("\n===== Testing LONG DOUBLE =====\n");
    printf("Size\tBucketSort (ms)\tQSort (ms)\n");
    printf("---------------------------------\n");
    
    for (s = 0; s < numSizes; s++) {
        size = sizes[s];
        bucket_time = 0.0, qsort_time = 0.0;
        
        for (iter = 0; iter < iterations; iter++) {
            /* Генерация случайного массива */
            long double* arr1 = generate_random_long_double_array(size, -1000.0L, 1000.0L);
            long double* arr2 = generate_random_long_double_array(size, -1000.0L, 1000.0L);
            long double* sorted = NULL;
                
            if (arr1 && arr2) {
                /* Тестирование BucketSort */
                start = clock();
                pIEcoLab1->pVTbl->bucketSortLongDoubleAutoK(pIEcoLab1, arr1, size, &sorted);
                end = clock();
                bucket_time += ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
                
                if (sorted) {
                    pIMem->pVTbl->Free(pIMem, sorted);
                }
                
                /* Тестирование QSort */
                start = clock();
                qsort(arr2, size, sizeof(long double), compare_long_double);
                end = clock();
                qsort_time += ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
            }
            
            if (arr1) free(arr1);
            if (arr2) free(arr2);
        }
        
        bucket_time /= iterations;
        qsort_time /= iterations;
        
        printf("%d\t%.3f\t\t%.3f\n", size, bucket_time, qsort_time);
    }
    
    printf("\n=== Performance Comparison Completed ===\n");
}





/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    char_t* name = 0;
    char_t* copyName = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1 = 0;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Выделение блока памяти */
    name = (char_t *)pIMem->pVTbl->Alloc(pIMem, 10);

    /* Заполнение блока памяти */
    pIMem->pVTbl->Fill(pIMem, name, 'a', 9);


    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

	/* Запуск тестов */
    /*test_polyHornerInt(pIEcoLab1, pIMem);
	test_polyHornerLong(pIEcoLab1, pIMem);
	test_polyHornerFloat(pIEcoLab1, pIMem);
	test_polyHornerDouble(pIEcoLab1, pIMem);
	test_polyHornerLongDouble(pIEcoLab1, pIMem);
	test_polyHornerComplex(pIEcoLab1, pIMem);
	test_polyHornerVector(pIEcoLab1, pIMem);
	test_polyHornerMatrix(pIEcoLab1, pIMem);
	compare_algorithms(pIEcoLab1, pIMem);*/

	test_allFunctions(pIEcoLab1, pIMem);
	compareBucketSortWithQSort(pIEcoLab1, pIMem);

    /* Освлбождение блока памяти */
    pIMem->pVTbl->Free(pIMem, name);

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

