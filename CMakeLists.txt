cmake_minimum_required(VERSION 3.17)
project(nahfstocks)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-Wall -Werror -pedantic)

add_definitions(-D"${TEST_VAR}")

add_executable(nahfstocks
        src/main.cpp
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
        lib/collections/Vector.cpp
        lib/collections/Vector.h
        lib/rand/RandomProvider.cpp
        lib/rand/RandomProvider.h
        src/exchange/exchange_api/ExchangeApi.cpp
        src/exchange/exchange_api/ExchangeApi.h
        src/exchange/exchange_api/IExchangeApi.h src/exchange/exchange_api/TraderRecordInExchange.cpp src/exchange/exchange_api/TraderRecordInExchange.h src/exchange/ExchangeConfig.h)