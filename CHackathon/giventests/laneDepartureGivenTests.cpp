#include <gtest/gtest.h>
#include "../laneDeparture.c"

TEST(TestLaneDepartureInput, GivenInputFile)
{
    FILE* ld_fp;
    ld_fp = fopen("files/LaneDeparture.txt", "r");
    float f1, f2, f3, f4;

    ld_fp = readLaneDepartureFile(ld_fp, &f1, &f2, &f3, &f4);

    fclose(ld_fp);
    EXPECT_FLOAT_EQ(3.53, f1);
    EXPECT_FLOAT_EQ(1.66, f2);
    EXPECT_FLOAT_EQ(1.91, f3);
    EXPECT_FLOAT_EQ(0.04, f4);
    ASSERT_TRUE(ld_fp != nullptr);
}

struct LaneDepartureTestData
{
    float n1, n2, n3, n4;
    int exp_answer;

    LaneDepartureTestData(float f1, float f2, float f3, float f4, int e)
    {
        n1 = f1;
        n2 = f2;
        n3 = f3;
        n4 = f4;
        exp_answer = e;
    }
};

class LaneDepartureParameterizedTestFixture :public ::testing::TestWithParam<LaneDepartureTestData> 
{
};

TEST_P(LaneDepartureParameterizedTestFixture, GivenInputs) {
    LaneDepartureTestData ex = GetParam();
    
    int answer = determineLaneDeparture(ex.n1, ex.n2, ex.n3, ex.n4);
    ASSERT_EQ(answer, ex.exp_answer);
}

INSTANTIATE_TEST_CASE_P(
        LaneDepartureTests,
        LaneDepartureParameterizedTestFixture,
        ::testing::Values(
            LaneDepartureTestData(3.53,1.66,1.91,0.04,1),
            LaneDepartureTestData(3.88,1.63,1.12,1.13,0),
            LaneDepartureTestData(3.36,1.87,1.7,0.21,1),
            LaneDepartureTestData(3.53,1.94,1.95,0.36,1),
            LaneDepartureTestData(3.61,1.77,1.47,0.37,1),
            LaneDepartureTestData(3.65,1.84,0.82,0.99,0),
            LaneDepartureTestData(3.67,1.69,1.44,0.54,0),
            LaneDepartureTestData(3.87,1.96,1.64,0.27,1),
            LaneDepartureTestData(3.89,1.8,1.8,0.29,1),
            LaneDepartureTestData(3.82,1.71,1.39,0.72,0),
            LaneDepartureTestData(3.44,1.83,1.19,0.42,0),
            LaneDepartureTestData(3.56,1.97,1.58,0.01,1),
            LaneDepartureTestData(3.38,1.94,1.52,0.08,1),
            LaneDepartureTestData(3.74,1.82,1.66,0.26,1),
            LaneDepartureTestData(3.6,1.63,1.18,0.79,0),
            LaneDepartureTestData(3.48,1.86,1.27,0.35,1),
            LaneDepartureTestData(3.68,1.7,1.67,0.31,1),
            LaneDepartureTestData(3.8,1.78,1.29,0.73,0),
            LaneDepartureTestData(3.55,1.88,1.66,0.01,1),
            LaneDepartureTestData(3.75,1.89,1.46,0.4,1),
            LaneDepartureTestData(3.57,1.96,1.23,0.38,1),
            LaneDepartureTestData(3.49,1.87,0.91,0.71,0),
            LaneDepartureTestData(3.49,1.68,1.59,0.22,1),
            LaneDepartureTestData(3.39,1.9,1.08,0.41,0),
            LaneDepartureTestData(3.86,1.95,1.06,0.85,0)));