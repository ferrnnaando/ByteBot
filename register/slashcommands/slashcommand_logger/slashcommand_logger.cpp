#include<iostream>
#include<dpp/dpp.h>

void slashcmd_reg(const dpp::interaction& interaction) {
	std::cout << "[" + dpp::utility::current_date_time() + "] - " << interaction.usr.username << " || Slashcommand /" << interaction.get_command_name() << " ejecutado." << std::endl;
}