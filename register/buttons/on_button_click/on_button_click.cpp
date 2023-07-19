#include "on_button_click.h"

void on_button_click(const dpp::button_click_t& event, dpp::cluster& bytebot)
{
	if (event.custom_id == "contribute_ban_bot_id") {
		event.reply(message(event.command.channel_id, "<:addloader:1130231705794519091> ¡Gracias! No te arrepentirás de seguir un proceso tan simple y que ayuda tanto. Reporta tu error con el comando `/report` enviandolo de forma directa a los desarrolladores de ByteBot o reportalo personalmente en nuestro servidor de Discord y obtén una insignia única.").set_flags(dpp::m_ephemeral).add_component(
			dpp::component().add_component(
				dpp::component().set_label("Servidor de soporte")
				.set_style(cos_link)
				.set_url(discord_link_inv)
				.set_type(cot_button)
				.set_emoji("🙌")
			)
		));
	}
	else if (event.custom_id == "continue_ban_bot_id") {

		event.reply(message(event.command.channel_id, "<:warningdisc:1129900021718982757> Está bien... Si así lo deseas, vuelve a ejecutar el comando para banearme.").set_flags(dpp::m_ephemeral));
	}
}