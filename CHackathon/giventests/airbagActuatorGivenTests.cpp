#include <gtest/gtest.h>
#include "../airbagActuator.c"

TEST(TestAirbagActuatorInput, GivenInputFile)
{
    FILE* ab_fp;
    ab_fp = fopen("files/ABActuator.txt", "r");
    struct Airbag ab;
    ab_fp = readAirbagActuatorFile(ab_fp, &ab);

    fclose(ab_fp);
    EXPECT_FLOAT_EQ(2.47, ab.start_time);
    EXPECT_FLOAT_EQ(88.36, ab.init_speed);
    EXPECT_FLOAT_EQ(3.82, ab.end_time);
    EXPECT_FLOAT_EQ(2.75, ab.final_speed);
    EXPECT_FLOAT_EQ(1.67, ab.gforce);
    ASSERT_TRUE(ab_fp != nullptr);
}

struct AirbagActuatorTestData
{
    float n1, n2, n3, n4, n5;
    int exp_answer;

    AirbagActuatorTestData(float f1, float f2, float f3, float f4, float f5, int e)
    {
        n1 = f1;
        n2 = f2;
        n3 = f3;
        n4 = f4;
        n5 = f5;
        exp_answer = e;
    }
};

class AirbagActuatorParameterizedTestFixture :public ::testing::TestWithParam<AirbagActuatorTestData> 
{
};

TEST_P(AirbagActuatorParameterizedTestFixture, GivenInputs) {
    AirbagActuatorTestData ex = GetParam();
    struct Airbag ab;
    ab.start_time = ex.n1;
    ab.init_speed = ex.n2;
    ab.end_time = ex.n3;
    ab.final_speed = ex.n4;
    ab.gforce = ex.n5;

    int answer = activateAirbags(ab);
    ASSERT_EQ(answer, ex.exp_answer);
}

INSTANTIATE_TEST_CASE_P(
        AirbagActuatorTests,
        AirbagActuatorParameterizedTestFixture,
        ::testing::Values(
            AirbagActuatorTestData(2.47,88.36,3.82,2.75,1.67,1),
            AirbagActuatorTestData(1.18,82.74,2.52,5.21,1.41,1),
            AirbagActuatorTestData(3.36,85.21,4.49,3.89,1.91,1),
            AirbagActuatorTestData(4.05,76.95,5.17,7.43,1.58,1),
            AirbagActuatorTestData(1.65,86.12,2.71,1.57,1.73,1),
            AirbagActuatorTestData(0.73,76.8,1.68,6.12,1.37,1),
            AirbagActuatorTestData(2.01,75.27,3.06,0.96,1.29,1),
            AirbagActuatorTestData(2.18,73.18,3.03,4.35,1.89,1),
            AirbagActuatorTestData(1.3,88.47,2.4,3.78,1.61,1),
            AirbagActuatorTestData(1.65,85.63,2.72,6.67,1.79,1),
            AirbagActuatorTestData(2.15,78.09,3.61,0.82,1.28,1),
            AirbagActuatorTestData(1.03,83.55,2.4,7.1,1.82,0),
            AirbagActuatorTestData(0.65,86.89,1.58,4.94,1.35,1),
            AirbagActuatorTestData(0.43,77.31,1.34,2.3,1.62,1),
            AirbagActuatorTestData(1.72,89.02,3.06,7.86,1.75,0),
            AirbagActuatorTestData(1.51,89.41,3,3.41,1.43,1),
            AirbagActuatorTestData(1.15,67.98,2.35,1.23,1.97,0),
            AirbagActuatorTestData(1.32,89.76,2.54,5.63,1.68,1),
            AirbagActuatorTestData(0.45,79.65,1.22,0.5,1.52,1),
            AirbagActuatorTestData(1.47,88.01,3.01,2.09,1.46,1),
            AirbagActuatorTestData(2.1,66.33,3.48,6.54,1.32,0),
            AirbagActuatorTestData(2.11,80.79,3.29,7.98,1.96,0),
            AirbagActuatorTestData(2.21,72.45,3.24,4.77,1.56,1),
            AirbagActuatorTestData(0.68,82.18,1.45,1.88,1.85,1),
            AirbagActuatorTestData(0.31,71.5,1.29,6.2,1.38,1)));