#include "on_messages.h"

using namespace std;
using namespace dpp;

void on_message_create(const dpp::message_create_t& msg, dpp::cluster& bytebot)
{
	auto interaction = msg.msg;
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
		msg.reply("<:warningdisc:1129900021718982757> ¿Quieres ver todo lo que puedo hacer? Escribe **/**, elige alguno de mis comandos y deja que la magia fluya.");
	}
	else if(msg.msg.content == "<@" + std::to_string(bytebot.me.id) + ">" && !msg.msg.is_dm()) {
		msg.reply(dpp::message("<:addloader:1130231705794519091> ¡Hola! Parece que me has mencionado, ¿necesitas ayuda? Usa `/bytebot` para saber mas.")
		.add_component(dpp::component()
		.add_component(
			dpp::component().set_label("Servidor de soporte")
			.set_type(dpp::cot_button)
			.set_style(dpp::cos_link)
			.set_url(discord_link_inv)
			.set_emoji("🙌")
			.set_id("md_btn_server")
			)

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
	else if(msg.msg.content == devcommands_prefix + "stop" && !interaction.is_dm()) {
		// dpp::permission ban_perm = interaction.resolved.member_permissions.find(interaction.usr.id)->second;
		//dpp::permission has_perms = interaction.get_resolved_permissions(interaction.author.id)->second;
		if (interaction.author.id == bytebot_developers[0]) {
			msg.reply(dpp::message("<:warningdisc:1129900021718982757> Esta operacion es considerada como **potencialmente peligrosa**, ¿realmente deseas ejecutarla?")
			.add_component(dpp::component()
			.add_component(
				dpp::component().set_label("Continuar")
				.set_type(cot_button)
				.set_style(cos_danger)
				.set_id("continue_getdown_bytebot")
				)
			));

			bytebot.start_timer([&bytebot, &interaction](dpp::timer h) {
				bytebot.message_delete(interaction.id, interaction.channel_id);
				bytebot.stop_timer(h);
				}, 5);
			}
		}
	}
