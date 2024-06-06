#include <gtest/gtest.h>
#include "../blindSpotDetection.c"

TEST(TestBlindSpotDetectionInput, GivenInputFile)
{
    FILE* bs_fp;
    bs_fp = fopen("files/BSDetection.txt", "r");
    unsigned long int time_side;
    float threshold;

    bs_fp = readBlindSpotDetectionFile(bs_fp, &time_side, &threshold);

    fclose(bs_fp);
    ASSERT_EQ(6, time_side);
    EXPECT_FLOAT_EQ(1.29, threshold);
    ASSERT_TRUE(bs_fp != nullptr);
}

struct BlindSpotDetectionTestData
{
    unsigned long int l1;
    float th;
    uint8_t exp_answer;

    BlindSpotDetectionTestData(unsigned long int l, float t, uint8_t e)
    {
        l1 = l;
        th = t;
        exp_answer = e;
    }
};

class BlindSpotDetectionParameterizedTestFixture :public ::testing::TestWithParam<BlindSpotDetectionTestData> 
{
};

TEST_P(BlindSpotDetectionParameterizedTestFixture, GivenInputs) {
    BlindSpotDetectionTestData ex = GetParam();
    
    uint8_t ans = activateBlindSpot(ex.l1, ex.th);
    ASSERT_EQ(ans, ex.exp_answer);
}

INSTANTIATE_TEST_CASE_P(
        BlindSpotDetectionTests,
        BlindSpotDetectionParameterizedTestFixture,
        ::testing::Values(
            BlindSpotDetectionTestData(6,1.29,1),
            BlindSpotDetectionTestData(15,0.81,0),
            BlindSpotDetectionTestData(8,1.32,1),
            BlindSpotDetectionTestData(14,1.03,0),
            BlindSpotDetectionTestData(13,0.72,0),
            BlindSpotDetectionTestData(15,1.41,2),
            BlindSpotDetectionTestData(20,0.65,0),
            BlindSpotDetectionTestData(13,0.99,2),
            BlindSpotDetectionTestData(17,1.2,2),
            BlindSpotDetectionTestData(6,0.64,1),
            BlindSpotDetectionTestData(6,1.07,1),
            BlindSpotDetectionTestData(13,1.49,2),
            BlindSpotDetectionTestData(18,1.13,0),
            BlindSpotDetectionTestData(11,0.54,0),
            BlindSpotDetectionTestData(11,0.66,0),
            BlindSpotDetectionTestData(16,1.21,1),
            BlindSpotDetectionTestData(7,0.67,2),
            BlindSpotDetectionTestData(7,1.09,2),
            BlindSpotDetectionTestData(20,0.89,0),
            BlindSpotDetectionTestData(7,1.49,2),
            BlindSpotDetectionTestData(10,1.14,1),
            BlindSpotDetectionTestData(12,0.73,0),
            BlindSpotDetectionTestData(12,1.23,1),
            BlindSpotDetectionTestData(15,1.37,2),
            BlindSpotDetectionTestData(8,1.67,1)));