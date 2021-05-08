#include "CliHelper.h"
#include "./CliQuestioner.h"
#include "./CliTableBuilder.h"

cli::CliQuestioner cli::CliHelper::build_question() {
	return CliQuestioner(*this);
}

cli::CliTableBuilder cli::CliHelper::build_table() {
	return CliTableBuilder(*this);
}
