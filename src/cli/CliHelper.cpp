#include "CliHelper.h"
#include "./CliQuestioner.h"

cli::CliQuestioner cli::CliHelper::build_question() {
	return CliQuestioner(*this);
}
