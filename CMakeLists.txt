cmake_minimum_required(VERSION 3.17)
project(nahfstocks)

set(CMAKE_CXX_STANDARD 11)

if (MSVC)
    add_compile_options(/W4 /WX)
else ()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif ()

add_definitions(-D"${TEST_VAR}")

add_executable(nahfstocks
        src/main.cpp
        lib/string/String.h
        lib/string/String.cpp
        lib/option/Option.h
        tests/Tests.cpp
        tests/Tests.h
        lib/external/gtest_lite.h
        lib/external/memtrace.h
        lib/external/memtrace.cpp
        src/exchange/Exchange.cpp
        src/exchange/Exchange.h
        src/company/ICompany.h
        lib/types.h
        src/company/Company.cpp
        src/company/Company.h
        src/trader/ITrader.h
        lib/collections/Vector.h
        lib/rand/RandomProvider.cpp
        lib/rand/RandomProvider.h
        src/exchange/exchange_api/ExchangeApi.cpp
        src/exchange/exchange_api/ExchangeApi.h
        src/exchange/exchange_api/IExchangeApi.h
        src/exchange/exchange_api/TraderRecordInExchange.cpp
        src/exchange/exchange_api/TraderRecordInExchange.h
        src/exchange/ExchangeConfig.h
        tests/lib/lib_tests.cpp
        tests/lib/lib_tests.h
        src/company/ICompany.cpp
        lib/algorithms.h
        src/company/names_data.h
        src/company/CompanyBuilder.cpp
        src/company/CompanyBuilder.h
        src/config/Config.cpp
        src/config/Config.h
        tests/company/company_tests.cpp
        tests/company/company_tests.h
        src/exchange/ExchangeBuilder.cpp
        src/exchange/ExchangeBuilder.h)