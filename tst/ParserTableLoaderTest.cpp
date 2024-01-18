#include "gtest/gtest.h"
#include "utilities/ParserTableLoader.h"

TEST(ParserTableLoaderTest, basisTest) {
    EXPECT_TRUE(true);
    const auto table = ParserTableLoader::getParserTable("tst/ParserTableLoaderJSON/basicTable.json");

    EXPECT_TRUE(table.size() == 4);
}
