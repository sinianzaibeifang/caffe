#include "gtest/gtest.h"

#include "caffe/util/cpu_info.hpp"

namespace caffe {
namespace cpu {

TEST(CpuInfo, isProcessorStructureInitialized) {
  Processor processor;
  EXPECT_EQ(processor.processor, 0);
  EXPECT_EQ(processor.physicalId, 0);
  EXPECT_EQ(processor.siblings, 0);
  EXPECT_EQ(processor.coreId, 0);
  EXPECT_EQ(processor.cpuCores, 0);
  EXPECT_EQ(processor.speedMHz, 0);
}

TEST(CpuInfo, testCpuInfoForEmptyInput) {
  CpuInfo cpuInfo("");
  EXPECT_STREQ(cpuInfo.getFirstLine(), NULL);
  EXPECT_STREQ(cpuInfo.getNextLine(), NULL);
  EXPECT_STREQ(cpuInfo.getNextLine(), NULL);
}

TEST(CpuInfo, testCpuInfoForSingleCharacterInput) {
  CpuInfo cpuInfo("c");
  EXPECT_STREQ(cpuInfo.getFirstLine(), "c");
  EXPECT_STREQ(cpuInfo.getNextLine(), NULL);
  EXPECT_STREQ(cpuInfo.getNextLine(), NULL);
}

TEST(CpuInfo, testCpuInfoForSingleLineInput) {
  CpuInfo cpuInfo("First line");
  EXPECT_STREQ(cpuInfo.getFirstLine(), "First line");
  EXPECT_STREQ(cpuInfo.getNextLine(), NULL);
  EXPECT_STREQ(cpuInfo.getNextLine(), NULL);
}

TEST(CpuInfo, testCpuInfoForTwoLineInput) {
  CpuInfo cpuInfo("First line\nSecond line");
  EXPECT_STREQ(cpuInfo.getFirstLine(), "First line");
  EXPECT_STREQ(cpuInfo.getNextLine(), "Second line");
  EXPECT_STREQ(cpuInfo.getNextLine(), NULL);
  EXPECT_STREQ(cpuInfo.getNextLine(), NULL);
}

TEST(CpuInfo, testCpuInfoForMultiLineInput) {
  CpuInfo cpuInfo("First line\nSecond line\n\nFourth line");
  EXPECT_STREQ(cpuInfo.getFirstLine(), "First line");
  EXPECT_STREQ(cpuInfo.getNextLine(), "Second line");
  EXPECT_STREQ(cpuInfo.getNextLine(), "");
  EXPECT_STREQ(cpuInfo.getNextLine(), "Fourth line");
  EXPECT_STREQ(cpuInfo.getNextLine(), NULL);
  EXPECT_STREQ(cpuInfo.getNextLine(), NULL);
}

}  // namespace cpu
}  // namespace caffe

