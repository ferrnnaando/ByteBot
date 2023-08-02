#include "on_button_click.h"

#ifdef __linux__ 
void term_bytebot_command(const dpp::button_click_t& event) {
	pid_t pID = getpid();
	event.reply("<:warningdisc:1129900021718982757> El bot ha sido apagado con éxito."); 
	const char* reload_command = ("kill -15 " + std::to_string(pID)).c_str(); 
	bool reload = system(reload_command); 

	if (reload == 0 || false) {
			event.reply("<:warningdisc:1129900021718982757> Hubo un error intentando apagar el bot, revisa la consola con `##print`"); 
	}
	/*else {
		const char *init_command = "bash scripts/build.sh main";
		system(init_command);
		std::string bot_on = "Bot iniciado.";
		bytebot.direct_message_create(interaction.usr.id, message(interaction.get_channel().is_dm(), "AAAA").add_component(dpp::component().add_component(dpp::component().set_label("Servidor de soporte").set_style(cos_link).set_url(discord_link_inv).set_type(cot_button).set_emoji("🙌")).add_component(dpp::component().set_label("¡Invitame a tu servidor!").set_style(cos_link).set_url(bot_invite).set_type(cot_button).set_emoji("🤖"))));
	}*/
}
#elif _WIN32
	void term_bytebot_command(const dpp::button_click_t& event){
		event.reply("<:warningdisc:1129900021718982757> El bot ha sido apagado con éxito."); 
		
		if(ExitProcess(0)) {
		} else {
			event.reply("<:warningdisc:1129900021718982757> Hubo un error intentando apagar el bot, revisa la consola."); 
		}
	}
#endif

void on_button_click(const dpp::button_click_t& event, dpp::cluster& bytebot)
{
	dpp::interaction interaction = event.command;

	if (event.custom_id == "contribute_ban_bot_id") {
		event.reply(dpp::message(event.command.channel_id, "<:addloader:1130231705794519091> ¡Gracias! No te arrepentirás de seguir un proceso tan simple y que ayuda tanto. Reporta tu error con el comando `/report` enviandolo de forma directa a los desarrolladores de ByteBot o reportalo personalmente en nuestro servidor de Discord y obtén una insignia única.").set_flags(dpp::m_ephemeral).add_component(
			dpp::component().add_component(
				dpp::component().set_label("Servidor de soporte")
				.set_style(dpp::cos_link)
				.set_url(discord_link_inv)
				.set_type(dpp::cot_button)
				.set_emoji("🙌")
			)
		));
	}
	else if (event.custom_id == "continue_ban_bot_id") {
		event.reply(dpp::message(event.command.channel_id, "<:warningdisc:1129900021718982757> Está bien... Si así lo deseas, adios.").set_flags(dpp::m_ephemeral));
	}
	else if(event.custom_id == "continue_getdown_bytebot") {
		if (std::find(std::begin(bytebot_developers), std::end(bytebot_developers), std::to_string(interaction.usr.id))) {
			term_bytebot_command(event);

		} else {
			event.reply(dpp::message(interaction.channel_id, "<:lock23:1130126354512351424> Algo salió mal.").set_flags(ephemeral));
		}
	}
}