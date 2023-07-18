#include "../headers/mainheader.h"

void on_ready(dpp::cluster &bytebot) {
	bytebot.on_ready([&bytebot](const ready_t& event) {
		//if (bytebot.me.id == event.from->get_guild_count());


		bytebot.set_presence(presence(ps_idle, at_listening, "/bytebot en" + std::to_string(bytebot.current_user_get_guilds_sync().size()) + " servidores")); //define bot status

		if (run_once<struct register_bot_commands>()) { //Avoid re-running on-ready declaration everytime that the bots makes a full reconnection

			//########################################################################################################################

			dpp::slashcommand infousuario("infousuario", description_slashcmd_infousuario, bytebot.me.id);
			infousuario.add_option(command_option(co_user, "usuario", option_slashcmd_infousuario, false));

			slashcommand infoservidor("infoservidor", description_slashcmd_infoservidor, bytebot.me.id);

			slashcommand avatar("avatar", option_usuario_slashcmd_avatar, bytebot.me.id);
			avatar.add_option(command_option(co_user, "usuario", description_slashcmd_avatar, false));

			slashcommand ban("ban", "Banea a un usuario del servidor", bytebot.me.id);
			ban.add_option(command_option(co_user, "usuario", description_slashcmd_ban, true));
			ban.add_option(command_option(co_string, "motivo", "Especifica un motivo por el que banear al usuario.", false));

			slashcommand report("report", description_slashcmd_report, bytebot.me.id);
			report.add_option(command_option(co_string, "mensaje", option_usuario_slashcmd_report, true));

			//########################################################################################################################

			//main slashcmd
			bytebot.global_command_create(slashcommand("commands", "Muestra de lo que soy capaz", bytebot.me.id));
			bytebot.global_command_create(slashcommand("bytebot", "Comando principal de ByteBot el cual te dirá que hacer conmigo", bytebot.me.id));

			bytebot.global_bulk_command_create({ infousuario, infoservidor, avatar, ban , report });
			bytebot.global_bulk_command_create({ ban });

		}
	});
}
 