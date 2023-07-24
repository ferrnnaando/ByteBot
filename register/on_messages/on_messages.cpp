#include "on_messages.h"

void on_message_create(const dpp::message_create_t& msg, dpp::cluster& bytebot)
{
	if (msg.msg.is_dm()) {
		if (msg.msg.author.id != bytebot.me.id) { //avoid loop for self-replying

			bytebot.start_timer([=, &bytebot](dpp::timer h) {
				msg.reply(dpp::message("<:guide:1129765954834939944> ¿Necesitas ayuda? Escríbeme mediante un servidor y estaré encantado de ayudarte.").set_flags(dpp::m_loading).add_component(
					dpp::component().add_component(
						dpp::component().set_label("Servidor de soporte")
						.set_type(dpp::cot_button)
						.set_style(dpp::cos_link)
						.set_url(discord_link_inv)
						.set_emoji("🙌")
						.set_id("md_btn_server"))

					.add_component(
						dpp::component().set_label("Invitame a tu servidor")
						.set_type(dpp::cot_button)
						.set_style(dpp::cos_link)
						.set_url(bot_invite)
						.set_emoji("🤖")
						.set_id("md_btn_invite")
						)
				));

				bytebot.stop_timer(h);
				}, 1);
		}
	}
	else if (msg.msg.content == "/" && !msg.msg.is_dm()) {
			msg.reply(message(msg.msg.channel_id, "<:warningdisc:1129900021718982757> ¿Quieres ver todo lo que puedo hacer? Escribe **/**, elige alguno de mis comandos y deja que la magia fluya.")
			.set_flags(ephemeral));

	}
	else if(msg.msg.content == "<@" + std::to_string(bytebot.me.id) + ">" && !msg.msg.is_dm()) {
		msg.reply(dpp::message("<:addloader:1130231705794519091> ¡Hola! Parece que me has mencionado, ¿necesitas ayuda? Usa `/bytebot` para saber mas.")
		.set_flags(ephemeral)
		.add_component(dpp::component().add_component(
			dpp::component().set_label("Servidor de soporte")
			.set_type(dpp::cot_button)
			.set_style(dpp::cos_link)
			.set_url(discord_link_inv)
			.set_emoji("🙌")
			.set_id("md_btn_server"))

					.add_component(
						dpp::component().set_label("Invitame a tu servidor")
						.set_type(dpp::cot_button)
						.set_style(dpp::cos_link)
						.set_url(bot_invite)
						.set_emoji("🤖")
						.set_id("md_btn_invite")
						)
				));
	}
}
