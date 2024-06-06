#include <gtest/gtest.h>
#include "../tyrePressureMonitor.c"

TEST(TestTyrePressureMonitorInput, GivenInputFile)
{
    struct Tyre ty;
    struct Tyre expected_ty = {237, 171, 185273099};
    ty = readTyreMonitorRecord("files/TPMonitor.dat", 3);

    ASSERT_EQ(ty.front_pressure, expected_ty.front_pressure);
    ASSERT_EQ(ty.rear_pressure, expected_ty.rear_pressure);
    ASSERT_EQ(ty.threshold, expected_ty.threshold);
}

struct TyrePressureMonitorTestData
{
    uint8_t front, rear;
    unsigned int threshold;
    unsigned char exp_answer;

    TyrePressureMonitorTestData(uint8_t f, uint8_t r, unsigned int t, unsigned char e)
    {
        front = f;
        rear = r;
        threshold = t;
        exp_answer = e;
    }
};

class TyrePressureMonitorParameterizedTestFixture :public ::testing::TestWithParam<TyrePressureMonitorTestData> 
{
};

TEST_P(TyrePressureMonitorParameterizedTestFixture, GivenInputs) {
    TyrePressureMonitorTestData ex = GetParam();
    
    struct Tyre ty;
    ty.front_pressure = ex.front;
    ty.rear_pressure = ex.rear;
    ty.threshold = ex.threshold;
    
    unsigned char ans = monitorTyrePressure(ty);
    ASSERT_EQ(ans, ex.exp_answer);
}

INSTANTIATE_TEST_CASE_P(
        TyrePressureMonitorTests,
        TyrePressureMonitorParameterizedTestFixture,
        ::testing::Values(
            TyrePressureMonitorTestData(202,202,185273099,10),
            TyrePressureMonitorTestData(233,172,185273099,6),
            TyrePressureMonitorTestData(237,171,185273099,4),
            TyrePressureMonitorTestData(254,173,185273099,4),
            TyrePressureMonitorTestData(188,223,185273099,0),
            TyrePressureMonitorTestData(202,169,185273099,46),
            TyrePressureMonitorTestData(175,238,185273099,1),
            TyrePressureMonitorTestData(233,172,185273099,6),
            TyrePressureMonitorTestData(184,248,185273099,10),
            TyrePressureMonitorTestData(203,222,185273099,0),
            TyrePressureMonitorTestData(174,237,185273099,1),
            TyrePressureMonitorTestData(201,151,185273099,46),
            TyrePressureMonitorTestData(237,182,185273099,8),
            TyrePressureMonitorTestData(191,255,185273099,0),
            TyrePressureMonitorTestData(222,204,185273099,0),
            TyrePressureMonitorTestData(168,217,185273099,43),
            TyrePressureMonitorTestData(235,134,185273099,12),
            TyrePressureMonitorTestData(218,250,185273099,10),
            TyrePressureMonitorTestData(206,237,185273099,0),
            TyrePressureMonitorTestData(189,248,185273099,8),
            TyrePressureMonitorTestData(169,239,185273099,3),
            TyrePressureMonitorTestData(200,183,185273099,10),
            TyrePressureMonitorTestData(253,212,185273099,8),
            TyrePressureMonitorTestData(186,170,185273099,46),
            TyrePressureMonitorTestData(170,237,185273099,3)));
