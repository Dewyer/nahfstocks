cmake_minimum_required(VERSION 3.17)
project(nahfstocks)

set(CMAKE_CXX_STANDARD 11)

if (MSVC)
    add_compile_options(/W4 /WX /EHa)
else ()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif ()

add_definitions(-D"${TEST_VAR}" -DETHREAD -DMEMTRACE)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

find_package( Threads )

add_executable(nahfstocks
        src/main.cpp
        lib/external/memtrace.h
        lib/external/memtrace.cpp
        lib/string/String.h
        lib/string/String.cpp
        lib/option/Option.h
        tests/Tests.cpp
        tests/Tests.h
        lib/external/gtest_lite.h
        src/exchange/Exchange.cpp
        src/exchange/Exchange.h
        lib/types.h
        src/company/Company.cpp
        src/company/Company.h
        lib/collections/Vector.h
        lib/rand/RandomProvider.cpp
        lib/rand/RandomProvider.h
        src/exchange/exchange_api/ExchangeApi.cpp
        src/exchange/exchange_api/ExchangeApi.h
        src/exchange/exchange_api/TraderRecordInExchange.h
        src/config/Config.h
        tests/lib/lib_tests.cpp
        tests/lib/lib_tests.h
        src/company/names_data.h
        src/company/CompanyBuilder.cpp
        src/company/CompanyBuilder.h
        tests/company/company_tests.cpp
        tests/company/company_tests.h
        src/exchange/ExchangeBuilder.cpp
        src/exchange/ExchangeBuilder.h
        src/simulation/Simulation.cpp
        src/simulation/Simulation.h
        src/trader/TraderAgent.cpp
        src/trader/TraderAgent.h
        lib/memory/Rc.h
        src/trader/TraderAgentBuilder.cpp
        src/trader/TraderAgentBuilder.h
        src/exchange/exchange_api/Order.h
        src/exchange/exchange_api/MarketContext.h
        src/events/EventDispatcher.cpp
        src/events/EventDispatcher.h
        src/events/Event.h
        src/events/EventDispatchingContext.h
        src/cli/SimulationCli.cpp
        src/cli/SimulationCli.h
        src/company/CompanyAgent.cpp
        src/company/CompanyAgent.h
        tests/cc_test.h
        tests/events/events_tests.cpp
        tests/events/events_tests.h
        tests/lib/lib_mocks.h
        tests/company/company_mock.h
        tests/events/events_mock.h
        tests/config/config_mock.h
        tests/trader/trader_tests.cpp
        tests/trader/trader_tests.h
        tests/lib/lib_mocks.cpp
        tests/exchange/exchange_tests.cpp
        tests/exchange/exchange_tests.h
        tests/exchange/exchange_mock.cpp
        tests/exchange/exchange_mock.h
        tests/config/config_mock.cpp
        src/config/Config.cpp
        lib/collections/Map.h
        src/config/ConfigValue.cpp
        src/config/ConfigValue.h
        src/cli/CliHelper.h
        src/cli/CliQuestioner.cpp
        src/cli/CliQuestioner.h
        src/cli/CliHelper.cpp
        src/exchange/ExchangeStats.h
        tests/cli/cli_mock.h
        src/utils/format_money.h
        src/utils/format_money.cpp
        src/cli/CliTableBuilder.cpp
        src/cli/CliTableBuilder.h
        tests/cli/cli_mock.cpp
        src/exchange/exchange_api/Order.cpp
        src/utils/to_string.cpp
        src/utils/to_string.h
        src/trader/last_names_data.h
        src/trader/first_names_data.h
        src/events/Event.cpp
        src/trader/NormalTraderAgent.cpp
        src/trader/NormalTraderAgent.h
        lib/prelude.h)

# target_link_libraries(nahfstocks ${CMAKE_THREAD_LIBS_INIT})
# target_compile_options(nahfstocks PRIVATE -fsanitize=address)
# target_link_directories(nahfstocks PRIVATE "$ENV{ProgramFiles\(x86\)}/Microsoft Visual Studio/2019/Community/VC/Tools/Llvm/x64/lib/clang/11.0.0/lib/windows")
# target_link_libraries(nahfstocks PRIVATE clang_rt.asan_dynamic-x86_64 clang_rt.asan_dynamic_runtime_thunk-x86_64)
# target_link_options(nahfstocks PRIVATE /wholearchive:clang_rt.asan_dynamic_runtime_thunk-x86_64.lib)