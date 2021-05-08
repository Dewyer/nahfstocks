#include "TraderAgentBuilder.h"
#include "./first_names_data.h"
#include "./last_names_data.h"

nhflib::Rc<trader::TraderAgent> trader::TraderAgentBuilder::build_random() {
	auto first_name_idx = this->rng->next_usize(0, FIRST_NAME_WORD_LIST_LENGTH-1);
	auto last_name_idx = this->rng->next_usize(0, LAST_NAME_WORD_LIST_LENGTH-1);
	auto first_name = String(first_name_word_list[first_name_idx]);
	auto last_name = String(last_name_word_list[last_name_idx]);

	TraderAgent agent(first_name + " " + last_name);
	return nhflib::make_rc(agent);
}
