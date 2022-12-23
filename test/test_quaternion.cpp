#include <unity.h>

void test_a_thing() {
    TEST_ASSERT_TRUE(true);
}

int main( int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_a_thing);
    UNITY_END();
}
