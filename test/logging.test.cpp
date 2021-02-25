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

TEST_F(LoggingTest, LoggerRecordsLevelError) {
    // Given
    std::stringstream& logStream =
        dynamic_cast<std::stringstream&>(mgr->log(LogLevel::Force));

    // When
    { Logger log(LogLevel::Error, "", 0); }

    // Then
    EXPECT_THAT(logStream.str(), HasSubstr("ERROR"));
}

TEST_F(LoggingTest, LoggerRecordsLevelWarn) {
    // Given
    std::stringstream& logStream =
        dynamic_cast<std::stringstream&>(mgr->log(LogLevel::Force));

    // When
    { Logger log(LogLevel::Warn, "", 0); }

    // Then
    EXPECT_THAT(logStream.str(), HasSubstr("WARN"));
}

TEST_F(LoggingTest, LoggerRecordsLevelInfo) {
    // Given
    std::stringstream& logStream =
        dynamic_cast<std::stringstream&>(mgr->log(LogLevel::Force));

    // When
    { Logger log(LogLevel::Info, "", 0); }

    // Then
    EXPECT_THAT(logStream.str(), HasSubstr("INFO"));
}

TEST_F(LoggingTest, LoggerRecordsNoLevelIfInvalid) {
    // Given
    std::stringstream& logStream =
        dynamic_cast<std::stringstream&>(mgr->log(LogLevel::Force));

    // When
    { Logger log(LogLevel::None, "", 0); }

    // Then
    EXPECT_THAT(logStream.str(), HasSubstr("[]"));
}

TEST_F(LoggingTest, LoggerRecordsMessages) {
    // Given
    std::stringstream& logStream =
        dynamic_cast<std::stringstream&>(mgr->log(LogLevel::Force));

    // When
    {
        Logger log(LogLevel::Error, "", 0);

        log.output() << "Foo Bar Baz";
    }

    // Then
    EXPECT_THAT(logStream.str(), HasSubstr("Foo Bar Baz"));
}

TEST_F(LoggingTest, LoggerRecordsFilename) {
    // Given
    std::stringstream& logStream =
        dynamic_cast<std::stringstream&>(mgr->log(LogLevel::Force));

    // When
    { Logger log(LogLevel::Error, "/foo/bar/baz.cpp", 20); }

    // Then
    EXPECT_THAT(logStream.str(), HasSubstr("baz.cpp"));
    EXPECT_THAT(logStream.str(), HasSubstr(":20"));
}
