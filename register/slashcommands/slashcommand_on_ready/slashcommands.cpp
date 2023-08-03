#include "slashcommands.h"

using namespace std;
using namespace dpp;

void print_logger(dpp::cluster &bytebot)
{
#ifdef __linux__
	std::cout << "[" << utility::current_date_time() << "]"
			  << " INFO: Running on Linux" << std::endl;
#elif defined(_WIN32) || defined(_WIN64)
	std::cout << "[" << utility::current_date_time() << "]"
			  << " INFO: Running on Windows" << std::endl;
#endif

	std::cout << "[" << utility::current_date_time() << "] INFO: Default OAuth2 URL is " << utility::bot_invite_url(application_id) << std::endl;
}

void on_ready(dpp::cluster &bytebot)
{
	bytebot.set_presence(presence(ps_idle, at_listening, "/bytebot en " + std::to_string(bytebot.current_user_get_guilds_sync().size()) + " servidores")); // define bot status
	if (run_once<struct register_bot_commands>())
	{ // Avoid re-running on-ready declaration everytime that the bots makes a full reconnection
		dpp::slashcommand informacion("informacion", "Comando principal de ByteBot el cual te dira que hacer conmigo", bytebot.me.id);
		dpp::slashcommand comandos("comandos", "Muestra de lo que soy capaz", bytebot.me.id);

		dpp::slashcommand infousuario("infousuario", description_slashcmd_infousuario, bytebot.me.id);
		infousuario.add_option(dpp::command_option(co_user, "usuario", option_slashcmd_infousuario, false));

		dpp::slashcommand infoservidor("infoservidor", description_slashcmd_infoservidor, bytebot.me.id);
		infoservidor.add_option(dpp::command_option(co_string, "id", option_slashcmd_infoservidor, false));

		dpp::slashcommand avatar("avatar", description_slashcmd_avatar, bytebot.me.id);
		avatar.add_option(dpp::command_option(co_user, "usuario", option_slashcmd_avatar, false));

		dpp::slashcommand banear("banear", description_slashcmd_banear, bytebot.me.id);
		banear.add_option(dpp::command_option(co_user, "usuario", option_slashcmd_banear, true)
			  .add_option(dpp::command_option(co_string, "motivo", option2_slashcmd_infoservidor, true)));

		slashcommand reportar("reportar", description_slashcmd_report, bytebot.me.id);
		reportar.add_option(dpp::command_option(co_string, "mensaje", option_slashcmd_report, true));

		slashcommand admin("admin", description_slashcmd_admin, bytebot.me.id);
		admin.add_option(dpp::command_option(dpp::co_sub_command, "add", "Crea cualquier cosa que imagines para darle utilidad a tu servidor e interacción.", false)
							 //.add_option(dpp::command_option_choice("aa", "aa", "aa", false)));
							 .add_option(dpp::command_option(dpp::co_boolean, "ar_button", "aa", true)));

		slashcommand dev("dev", description_slashcmd_dev, bytebot.me.id);
		dev.add_option(dpp::command_option(co_string, "input", option_slashcmd_dev, true));

		bytebot.global_command_create(informacion);
		bytebot.global_command_create(comandos);
		bytebot.global_command_create(infousuario);
		bytebot.global_command_create(infoservidor);
		bytebot.global_command_create(avatar);
		bytebot.global_command_create(banear);
		bytebot.global_command_create(reportar);
		bytebot.global_command_create(admin);
		bytebot.global_command_create(dev);
		// bytebot.guild_command_create(banearte);
		// bytebot.global_bulk_command_create({ comandos, informacion, infousuario, infoservidor, avatar, banear , reportar });
	}
}