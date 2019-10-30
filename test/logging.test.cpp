#include "logging.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace SwearJar;
using namespace ::testing;

class LoggingTest : public ::testing::Test {
    void SetUp() {
        LogManager::reset();
        mgr = LogManager::get();
    }
    void TearDown() {
        LogManager::reset();
    }

protected:
    LogManager* mgr = nullptr;
};

TEST_F(LoggingTest, isDisabledByDefault) {
    // Then
    EXPECT_FALSE(mgr->enabled());
}

TEST_F(LoggingTest, getSetThreshold) {
    // Given
    LogLevel l = LogLevel::All;

    ASSERT_NE(l, mgr->threshold());

    // When
    mgr->threshold(l);

    // Then
    EXPECT_EQ(l, mgr->threshold());
}

TEST_F(LoggingTest, logReturnsStringStreamBelowThreshold) {
    // Given
    mgr->enabled(true);

    // When
    std::ostream& logStream = mgr->log(LogLevel::Debug);

    // Then
    EXPECT_TRUE(dynamic_cast<std::stringstream*>(&logStream));
}

TEST_F(LoggingTest, logReturnsOfstreamAboveThreshold) {
    // Given
    mgr->enabled(true);

    // When
    std::ostream& logStream = mgr->log(LogLevel::Force);

    // Then
    EXPECT_TRUE(dynamic_cast<std::ofstream*>(&logStream));
}

TEST_F(LoggingTest, logReturnsStringstreamIfNotEnabled) {
    // Given
    mgr->enabled(false);

    // When
    std::ostream& logStream = mgr->log(LogLevel::Force);

    // Then
    EXPECT_TRUE(dynamic_cast<std::stringstream*>(&logStream));
}
