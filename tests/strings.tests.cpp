TEST_CASE("String operations", "[string]") {
    SECTION("To upper case") {
        std::string result = strOp::toUpperCase("Hello World!");
        std::string expected = "HELLO WORLD!";
        REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
    }

    SECTION("To lower case") {
        std::string result = strOp::toLowerCase("Hello World!");
        std::string expected = "hello world!";
        REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
    }

    SECTION("Trim") {
        std::string result = strOp::trim("   Hello World!   ");
        std::string expected = "Hello World!";
        REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
    }

    SECTION("Trim left") {
        std::string result = strOp::trimLeft("   Hello World!   ");
        std::string expected = "Hello World!   ";
        REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
    }

    SECTION("Trim right") {
        std::string result = strOp::trimRight("   Hello World!   ");
        std::string expected = "   Hello World!";
        REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
    }

    SECTION("Split") {
        std::string result = strOp::join(strOp::split("Hello World!", " "), ", ");
        std::string expected = "Hello, World!";
        REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
    }

    SECTION("Substring") {
        std::string result = strOp::substring("Hello World!", 6, 11);
        std::string expected = "World";
        REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
    }

    SECTION("Replace once") {
        std::string result = strOp::replaceOnce("Hello World World!", "World", "Universe");
        std::string expected = "Hello Universe World!";
        REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
    }

    SECTION("Replace all") {
        std::string result = strOp::replaceAll("Hello World World!", "World", "Universe");
        std::string expected = "Hello Universe Universe!";
        REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
    }

    SECTION("Replace all in between") {
        std::string result = strOp::replaceAllInBetween("Hello World World!","World", "Universe", 6, 11);
        std::string expected = "Hello Universe World!";
        REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
    }

    SECTION("Equals ignore case") {
        std::string result = std::to_string(strOp::equalsIgnoreCase("Hello World!", "hello world!"));
        std::string expected = "1";
        REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
    }

    SECTION("Starts with") {
        std::string result = std::to_string(strOp::startsWith("Hello World!", "Hello"));
        std::string expected = "1";
        REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
    }

    SECTION("Ends with") {
        std::string result = std::to_string(strOp::endsWith("Hello World!", "World!"));
        std::string expected = "1";
        REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
    }

    SECTION("Contains") {
        std::string result = std::to_string(strOp::contains("Hello World!", "World"));
        std::string expected = std::to_string(true);
        REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
    }

    SECTION("Repeat") {
        std::string result = strOp::repeat("Hello World! ", 3);
        std::string expected = "Hello World! Hello World! Hello World! ";
        REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
    }

    SECTION("Pad left") {
        std::string result = strOp::padLeft("Hello World!", 20, '*');
        std::string expected = "********Hello World!";
        REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
    }

    SECTION("Pad right") {
        std::string result = strOp::padRight("Hello World!", 20, '*');
        std::string expected = "Hello World!********";
        REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
    }

    SECTION("Pad center") {
        std::string result = strOp::padCenter("Hello World!", 20, '*');
        std::string expected = "****Hello World!****";
        REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
    }

    SECTION("Count occurrences") {
        std::string result = std::to_string(strOp::countOccurrences("Hello World!", 'o'));
        std::string expected = "2";
        REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
    }

    SECTION("Remove all occurrences") {
        std::string result = strOp::removeAllOccurrences("Hello World!", 'o');
        std::string expected = "Hell Wrld!";
        REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
    }
}