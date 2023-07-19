#include "on_messages.h"

void on_message_create(const dpp::message_create_t& msg, dpp::cluster& bytebot)
{
	if (msg.msg.is_dm()) {
		if (msg.msg.author.id != bytebot.me.id && msg.msg.is_dm()) { //avoid loop for self-replying

			bytebot.start_timer([=, &bytebot](dpp::timer h) {
				msg.reply(message("<:guide:1129765954834939944> ¿Necesitas ayuda? Escríbeme mediante un servidor y estaré encantado de ayudarte.").set_flags(dpp::m_loading).add_component(
					component().add_component(
						component().set_label("Servidor de soporte")
						.set_type(cot_button)
						.set_style(cos_link)
						.set_url(discord_link_inv)
						.set_emoji("🙌")
						.set_id("md_btn_server"))

					.add_component(
						component().set_label("Invitame a tu servidor")
						.set_type(cot_button)
						.set_style(cos_link)
						.set_url(bot_invite)
						.set_emoji("🤖")
						.set_id("md_btn_invite"))


				));

				bytebot.stop_timer(h);
				}, 1);
		}

		if (msg.msg.author.id != bytebot.me.id) {
			std::cout << "[" + dpp::utility::current_date_time() + "] - " << msg.msg.author.username << " || Me ha enviado un DM. (Contenido: " << msg.msg.content << ")" << std::endl;
		}
	}
	else if (msg.msg.content == "/") {

		bytebot.start_timer([=, &bytebot](dpp::timer h) {
			msg.reply("<:warningdisc:1129900021718982757> ¿Quieres ver todo lo que puedo hacer? Escribe **/**, elige alguno de mis comandos y deja que la magia fluya.");
			bytebot.stop_timer(h);
			}, 3);
	}
}