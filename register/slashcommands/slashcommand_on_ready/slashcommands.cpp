#include "slashcommands.h"
using namespace std;
using namespace dpp;

void on_ready(dpp::cluster& bytebot) {
	bytebot.set_presence(presence(ps_idle, at_listening, "/bytebot en " + std::to_string(bytebot.current_user_get_guilds_sync().size()) + " servidores")); //define bot status	

	
		if (run_once<struct register_bot_commands>()) { //Avoid re-running on-ready declaration everytime that the bots makes a full reconnection

			//########################################################################################################################

			dpp::slashcommand informacion("informacion", "Comando principal de ByteBot el cual te dira que hacer conmigo", bytebot.me.id);
			dpp::slashcommand comandos("comandos", "Muestra de lo que soy capaz", bytebot.me.id);

			dpp::slashcommand infousuario("infousuario", description_slashcmd_infousuario, bytebot.me.id);
			infousuario.add_option(dpp::command_option(co_user, "usuario", option_slashcmd_infousuario, false));

			dpp::slashcommand infoservidor("infoservidor", description_slashcmd_infoservidor, bytebot.me.id);

			dpp::slashcommand avatar("avatar", option_usuario_slashcmd_avatar, bytebot.me.id);
			avatar.add_option(dpp::command_option(co_user, "usuario", description_slashcmd_avatar, false));

			dpp::slashcommand banear("banear", "Banea a un usuario del servidor", bytebot.me.id);
			banear.add_option(dpp::command_option(co_user, "usuario", "Especifica al usuario que deseas banear.", true)
				.add_option(dpp::command_option(co_string, "motivo", "Especifica un motivo por el que banear al usuario.", true)));



			slashcommand reportar("reportar", description_slashcmd_report, bytebot.me.id);
			reportar.add_option(dpp::command_option(co_string, "mensaje", option_usuario_slashcmd_report, true));

			//########################################################################################################################

			//main slashcmd

			bytebot.global_command_create(informacion);
			bytebot.global_command_create(comandos);
			bytebot.global_command_create(infousuario);
			bytebot.global_command_create(infoservidor);
			bytebot.global_command_create(avatar);
			bytebot.global_command_create(banear);
			bytebot.global_command_create(reportar);
			//bytebot.guild_command_create(banearte);
			//bytebot.global_bulk_command_create({ comandos, informacion, infousuario, infoservidor, avatar, banear , reportar });
		}
}