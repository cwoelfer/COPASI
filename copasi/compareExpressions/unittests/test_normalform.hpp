// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_normalform.hpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/08/23 09:03:48 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef TEST_NORMALFORM_HPP__
#define TEST_NORMALFORM_HPP__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CNormalFraction;

class test_normalform : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(test_normalform);
    CPPUNIT_TEST(test_item_number);
    CPPUNIT_TEST(test_item_variable);
    CPPUNIT_TEST(test_item_constant);
    CPPUNIT_TEST(test_item_function);

    CPPUNIT_TEST(test_sum_numbers);
    CPPUNIT_TEST(test_sum_variables);
    CPPUNIT_TEST(test_sum_constants);
    CPPUNIT_TEST(test_sum_functions);
    CPPUNIT_TEST(test_sum_functions_reversed);
    CPPUNIT_TEST(test_sum_mixed_1);
    CPPUNIT_TEST(test_sum_mixed_1_reversed);
    CPPUNIT_TEST(test_sum_mixed_2);
    CPPUNIT_TEST(test_sum_mixed_2_reversed);

    CPPUNIT_TEST(test_product_numbers);
    CPPUNIT_TEST(test_product_variables);
    CPPUNIT_TEST(test_product_variables_reversed);
    CPPUNIT_TEST(test_product_constants);
    CPPUNIT_TEST(test_product_constants_reversed);
    CPPUNIT_TEST(test_product_functions);
    CPPUNIT_TEST(test_product_functions_reversed);
    CPPUNIT_TEST(test_product_mixed_1);
    CPPUNIT_TEST(test_product_mixed_1_reversed);
    CPPUNIT_TEST(test_product_mixed_2);
    CPPUNIT_TEST(test_product_mixed_2_reversed);

    CPPUNIT_TEST(test_fraction_numbers);
    CPPUNIT_TEST(test_fraction_variables);
    CPPUNIT_TEST(test_fraction_constants);
    CPPUNIT_TEST(test_fraction_functions);
    CPPUNIT_TEST(test_fraction_mixed_1);
    CPPUNIT_TEST(test_fraction_mixed_2);

    CPPUNIT_TEST(test_itempower_numbers);
    CPPUNIT_TEST(test_itempower_variables);
    CPPUNIT_TEST(test_itempower_constants);
    CPPUNIT_TEST(test_itempower_functions);

    CPPUNIT_TEST(test_generalpower_number_and_variable);
    CPPUNIT_TEST(test_generalpower_variable_and_variable);
    CPPUNIT_TEST(test_generalpower_function_and_function);
    CPPUNIT_TEST(test_generalpower_constant_and_constant);
    CPPUNIT_TEST(test_generalpower_mixed_1);
    CPPUNIT_TEST(test_generalpower_mixed_2);
    CPPUNIT_TEST(test_generalpower_mixed_3);
    CPPUNIT_TEST(test_generalpower_mixed_4);

    CPPUNIT_TEST(test_generalmodulus_number_and_variable);
    CPPUNIT_TEST(test_generalmodulus_variable_and_variable);
    CPPUNIT_TEST(test_generalmodulus_function_and_function);
    CPPUNIT_TEST(test_generalmodulus_constant_and_constant);
    CPPUNIT_TEST(test_generalmodulus_mixed_1);
    CPPUNIT_TEST(test_generalmodulus_mixed_2);
    CPPUNIT_TEST(test_generalmodulus_mixed_3);
    CPPUNIT_TEST(test_generalmodulus_mixed_4);

    CPPUNIT_TEST(test_simple_stepwise_numbers);
    CPPUNIT_TEST(test_simple_stepwise_fractions);
    CPPUNIT_TEST(test_simple_nested_stepwise_numbers);
    CPPUNIT_TEST(test_simple_nested_stepwise_fractions);
    CPPUNIT_TEST(test_nested_stepwise_fractions);

    CPPUNIT_TEST_SUITE_END();

  protected:
    CNormalFraction* pFraction;

  public:
    void setUp();

    void tearDown();

    void test_item_number();
    void test_item_variable();
    void test_item_constant();
    void test_item_function();

    void test_sum_numbers();
    void test_sum_variables();
    void test_sum_constants();
    void test_sum_functions();
    void test_sum_functions_reversed();
    void test_sum_mixed_1();
    void test_sum_mixed_1_reversed();
    void test_sum_mixed_2();
    void test_sum_mixed_2_reversed();

    void test_product_numbers();
    void test_product_variables();
    void test_product_variables_reversed();
    void test_product_constants();
    void test_product_constants_reversed();
    void test_product_functions();
    void test_product_functions_reversed();
    void test_product_mixed_1();
    void test_product_mixed_1_reversed();
    void test_product_mixed_2();
    void test_product_mixed_2_reversed();

    void test_fraction_numbers();
    void test_fraction_variables();
    void test_fraction_constants();
    void test_fraction_functions();
    void test_fraction_mixed_1();
    void test_fraction_mixed_2();

    void test_itempower_numbers();
    void test_itempower_variables();
    void test_itempower_constants();
    void test_itempower_functions();

    void test_generalpower_number_and_variable();
    void test_generalpower_variable_and_variable();
    void test_generalpower_function_and_function();
    void test_generalpower_constant_and_constant();
    void test_generalpower_mixed_1();
    void test_generalpower_mixed_2();
    void test_generalpower_mixed_3();
    void test_generalpower_mixed_4();

    void test_generalmodulus_number_and_variable();
    void test_generalmodulus_variable_and_variable();
    void test_generalmodulus_function_and_function();
    void test_generalmodulus_constant_and_constant();
    void test_generalmodulus_mixed_1();
    void test_generalmodulus_mixed_2();
    void test_generalmodulus_mixed_3();
    void test_generalmodulus_mixed_4();

    void test_simple_stepwise_numbers();
    void test_simple_stepwise_fractions();
    void test_simple_nested_stepwise_numbers();
    void test_simple_nested_stepwise_fractions();
    void test_nested_stepwise_fractions();
  };

#endif /* TEST_NORMALFORM_HPP__ */
