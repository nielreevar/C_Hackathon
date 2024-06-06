#include <gtest/gtest.h>
#include "../drivingRangeEstimator.c"

TEST(TestDrivingRangeEstimatorInput, GivenInputFile)
{
    FILE* dr_fp;
    dr_fp = fopen("files/DREstimator.txt", "r");
    struct CarFuel cf;
    dr_fp = readDrivingRangeEstimatorFile(dr_fp, &cf);

    fclose(dr_fp);
    EXPECT_FLOAT_EQ(60, cf.fuel_cap);
    EXPECT_FLOAT_EQ(50, cf.fuel_level);
    EXPECT_FLOAT_EQ(9.12, cf.kmpl);
    EXPECT_FLOAT_EQ(2190, cf.engine_rpm);
    ASSERT_TRUE(dr_fp != nullptr);
}

struct DrivingRangeEstimatorTestData
{
    float n1, n2, n3, n4;
    int exp_answer;

    DrivingRangeEstimatorTestData(float f1, float f2, float f3, float f4, int e)
    {
        n1 = f1;
        n2 = f2;
        n3 = f3;
        n4 = f4;
        exp_answer = e;
    }
};

class DrivingRangeEstimatorParameterizedTestFixture :public ::testing::TestWithParam<DrivingRangeEstimatorTestData> 
{
};

TEST_P(DrivingRangeEstimatorParameterizedTestFixture, GivenInputs) {
    DrivingRangeEstimatorTestData ex = GetParam();
    struct CarFuel cf;
    cf.fuel_cap = ex.n1;
    cf.fuel_level = ex.n2;
    cf.kmpl = ex.n3;
    cf.engine_rpm = ex.n4;

    int answer = calculateDrivingRange(cf);
    ASSERT_EQ(answer, ex.exp_answer);
}

INSTANTIATE_TEST_CASE_P(
        DrivingRangeEstimatorTests,
        DrivingRangeEstimatorParameterizedTestFixture,
        ::testing::Values(
            DrivingRangeEstimatorTestData(60,50,9.12,2190,228),
            DrivingRangeEstimatorTestData(51,75,12.38,2724,394),
            DrivingRangeEstimatorTestData(58,10,12.27,3585,47),
            DrivingRangeEstimatorTestData(60,100,12.06,2395,603),
            DrivingRangeEstimatorTestData(51,25,14.24,2974,151),
            DrivingRangeEstimatorTestData(59,50,9.65,2589,237),
            DrivingRangeEstimatorTestData(57,100,10.87,3188,516),
            DrivingRangeEstimatorTestData(53,10,10.47,2116,46),
            DrivingRangeEstimatorTestData(51,25,11.17,3170,118),
            DrivingRangeEstimatorTestData(60,100,13.44,2314,671),
            DrivingRangeEstimatorTestData(50,10,12.79,2196,53),
            DrivingRangeEstimatorTestData(59,75,9.14,2657,337),
            DrivingRangeEstimatorTestData(56,10,10.98,1639,61),
            DrivingRangeEstimatorTestData(53,75,11.73,2762,388),
            DrivingRangeEstimatorTestData(58,25,12.03,2750,145),
            DrivingRangeEstimatorTestData(57,50,11.13,3987,211),
            DrivingRangeEstimatorTestData(57,25,14.43,2298,171),
            DrivingRangeEstimatorTestData(55,75,14.02,2613,481),
            DrivingRangeEstimatorTestData(55,100,11.83,1816,650),
            DrivingRangeEstimatorTestData(56,10,11.24,2881,52),
            DrivingRangeEstimatorTestData(49,100,14.47,3671,472),
            DrivingRangeEstimatorTestData(59,75,11.83,3194,436),
            DrivingRangeEstimatorTestData(55,100,10.59,2659,485),
            DrivingRangeEstimatorTestData(61,50,13.89,3525,282),
            DrivingRangeEstimatorTestData(57,10,13.61,3882,51)));