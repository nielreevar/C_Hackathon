#include <gtest/gtest.h>
#include "../reverseCameraCategorization.c"

TEST(TestReverseCameraCategories, GivenCategories)
{
    struct Category ct[10];

    int num = readLookupTable("files/lookup_table.txt", ct);

    ASSERT_EQ(3, num);
    ASSERT_STREQ("Red", ct[0].name);
    ASSERT_STREQ("Yellow", ct[1].name);
    ASSERT_STREQ("Green", ct[2].name);
}

TEST(TestReverseCameraCategoriesInput, GivenInputFile)
{
    FILE* rv_fp;
    rv_fp = fopen("files/ReverseData.txt", "r");
    unsigned long int t;

    rv_fp = readReverseCategoryFile(rv_fp, &t);

    fclose(rv_fp);
    ASSERT_EQ(32, t);
    ASSERT_TRUE(rv_fp != nullptr);
}

struct ReverseCategoryTestData
{
    unsigned long int t1;
    const char* exp_answer;

    ReverseCategoryTestData(unsigned long int i1, const char* e)
    {
        t1 = i1;
        exp_answer = e;
    }
};

class ReverseCategoryParameterizedTestFixture :public ::testing::TestWithParam<ReverseCategoryTestData> 
{
};

TEST_P(ReverseCategoryParameterizedTestFixture, GivenInputs) {
    ReverseCategoryTestData ex = GetParam();
    struct Category ct[10];
    strcpy(ct[0].name, "Red"); ct[0].lower_limit = 0; ct[0].upper_limit = 2;
    strcpy(ct[1].name, "Yellow"); ct[1].lower_limit = 2; ct[1].upper_limit = 5;
    strcpy(ct[2].name, "Green"); ct[2].lower_limit = 5; ct[2].upper_limit = 10;
    int num = 3;
    const char* answer = classifyObjectsWhileReversing(ct, num, ex.t1);
    ASSERT_STREQ(answer, ex.exp_answer);
}

INSTANTIATE_TEST_CASE_P(
        ReverseCategoryTests,
        ReverseCategoryParameterizedTestFixture,
        ::testing::Values(
            ReverseCategoryTestData(32,"White"),
            ReverseCategoryTestData(14,"Green"),
            ReverseCategoryTestData(27,"White"),
            ReverseCategoryTestData(41,"White"),
            ReverseCategoryTestData(8,"Yellow"),
            ReverseCategoryTestData(23,"White"),
            ReverseCategoryTestData(6,"Yellow"),
            ReverseCategoryTestData(39,"White"),
            ReverseCategoryTestData(19,"Green"),
            ReverseCategoryTestData(33,"White"),
            ReverseCategoryTestData(11,"Green"),
            ReverseCategoryTestData(37,"White"),
            ReverseCategoryTestData(4,"Red"),
            ReverseCategoryTestData(22,"White"),
            ReverseCategoryTestData(43,"White"),
            ReverseCategoryTestData(9,"Yellow"),
            ReverseCategoryTestData(29,"White"),
            ReverseCategoryTestData(18,"Green"),
            ReverseCategoryTestData(35,"White"),
            ReverseCategoryTestData(3,"Red"),
            ReverseCategoryTestData(25,"White"),
            ReverseCategoryTestData(16,"Green"),
            ReverseCategoryTestData(40,"White"),
            ReverseCategoryTestData(12,"Green"),
            ReverseCategoryTestData(36,"White")
));