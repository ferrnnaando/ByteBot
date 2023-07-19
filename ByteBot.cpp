#include "headers/mainheader.h"

#include "register/slashcommands/slashcommand_on_ready/slashcommands.h"
#include "register/slashcommands/slashcommand_logger/logger.h"
#include "register/embeds/embed_declarations.h"

int main() {
	dotenv::init();
	const std::string BOT_TOKEN{std::getenv("token")};
	//Create bot cluster
	dpp::cluster bytebot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);
	dpp::webhook bytebot_wh(reports_webhook);
	
	//Output log information
	bytebot.on_log(utility::cout_logger());

	 bytebot.on_ready([&bytebot](const ready_t& event) {
		 ready_handler(bytebot);
	});
		
	//Handleer for messages events
	bytebot.on_message_create([&bytebot](const dpp::message_create_t& msg) {
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
	});

	//Handler for slash commands
	bytebot.on_slashcommand([&bytebot, &bytebot_wh](const slashcommand_t& event) { //DO find arrays with find and end.
			dpp::interaction interaction = event.command;
			dpp::command_interaction cmd_data = interaction.get_command_interaction();
			auto subcommand = cmd_data;

			const std::string owner_guild_id = std::to_string(interaction.get_guild().owner_id);
			const std::string guild_name = interaction.get_guild().name;
			const std::string formated_bytebot_moderator = "<@" + std::to_string(bytebot.me.id) + ">";

			std::time_t timestamp_guild = interaction.get_guild().get_creation_time();
			std::tm* fecha_hora_guild = std::gmtime(&timestamp_guild);
			char buffer_guild[80];
			std::strftime(buffer_guild, sizeof(buffer_guild), "%Y-%m-%d a las %H:%M:%S horas.", fecha_hora_guild);
			std::string formatted_date_guild = "```" + std::string(buffer_guild) + "```";

			if (interaction.usr.id == blacklisted_users[0] || interaction.usr.id == blacklisted_users[1]) {
				
				
				std::cout << "[" + utility::current_date_time() + "] - " << interaction.usr.username << " || Intento ejecutar un comando, pero su ID se encuentra prohibida del uso de ByteBot." << std::endl;
				event.reply(message(event.command.get_channel().id, blacklist_embed(interaction)).set_flags(ephemeral));

			}
			else {
				if (interaction.get_command_name() == "informacion") {
					slashcmd_reg(interaction);
					event.reply(message(interaction.get_channel().id, bytebot_embed(interaction)).set_flags(ephemeral));

				}
				else if (interaction.get_command_name() == "comandos") {
					slashcmd_reg(interaction);
					event.reply(message(event.command.get_channel().id, commands_embed(interaction)));

				}
				else if (interaction.get_command_name() == "infoservidor") {
					std::string partnered_guild_str;

					const dpp::guild& g = interaction.get_guild();

					std::string guild_owner_formatted = "<@" + std::to_string(g.owner_id) + ">";
					std::string guild_id = "```" + std::to_string(g.id) + "```";
					std::string guild_name = "```" + interaction.get_guild().name + "```";
					std::string guild_description_formatted = "```" + g.description + "```";

					auto guild_created_at = g.get_creation_time();
					bool guild_is_partnered = g.is_partnered();
					std::string guild_2fa_level = "```" + std::to_string(g.mfa_level) + "```";

					const std::vector<dpp::snowflake>& channels = g.channels;
					const std::vector<dpp::snowflake>& roles = g.roles;
					const std::vector<dpp::snowflake>& emojis = g.emojis;
					// Obtiene el recuento de canales en el gremio utilizando el método `size()`
					std::size_t channelCount = channels.size();
					std::size_t roleCount = roles.size();
					std::size_t emojiCount = emojis.size();
					std::string total_guild_channels = "```" + std::to_string(channelCount) + "```";
					std::string total_guild_roles = "```" + std::to_string(roleCount) + "```";
					std::string total_guild_emojis = "```" + std::to_string(emojiCount) + "```";

					switch (guild_is_partnered) {
					case 0 || false:
						partnered_guild_str = "```No.```";
						break;
					case 1 || true:
						partnered_guild_str = "```Si.```";
						break;

					default:
						break;
					}

					event.reply(message(interaction.get_channel().id, infoservidor(
						interaction, guild_owner_formatted, guild_name, partnered_guild_str, guild_is_partnered, total_guild_channels, total_guild_roles,
						total_guild_emojis, channels, roles, emojis, g, guild_id, formatted_date_guild, guild_description_formatted, guild_2fa_level
					)));

					slashcmd_reg(interaction);
				}
				else if (interaction.get_command_name() == "avatar") {

					if (subcommand.options.empty()) {
						event.reply(message(interaction.get_channel().id, avatar_embed(interaction)));
					}
					else {
						dpp::user avatar = interaction.get_resolved_user(subcommand.get_value<dpp::snowflake>(0));
						event.reply(message(interaction.get_channel().id, usuario_avatar_embed(interaction, avatar)));

					}
					slashcmd_reg(interaction);

				}
				else if (interaction.get_command_name() == "banear") {
					dpp::permission ban_perm = interaction.resolved.member_permissions.find(interaction.usr.id)->second;

					if (ban_perm.has(dpp::p_ban_members) || ban_perm.has(dpp::p_administrator)) {
						dpp::user usuario = interaction.get_resolved_user(subcommand.get_value<dpp::snowflake>(0));
						std::string ban_issue = std::get<std::string>(event.get_parameter("motivo")) + "```";
						std::string member_staff = "<@" + std::to_string(interaction.usr.id) + ">";

						if (std::to_string(usuario.id) == "1126691771506757713") {

							event.reply(message(interaction.channel_id, "<:warningdisc:1129900021718982757> ¡Vaya!Parece que has intentado banearme, lamento no haber sido de tu agrado o no haber cumplido con tus expectativas, pero puedo asegurarte que logrararás más ayudando a que ByteBot mejore enviando un reporte que expulsándome.¡Animate!Será solo un momento").set_flags(dpp::m_ephemeral).add_component(
								dpp::component().add_component(
									dpp::component().set_label("Continuar")
									.set_type(cot_button)
									.set_style(cos_danger)
									.set_id("continue_ban_bot_id")
								)

								.add_component(
									dpp::component().set_label("Contribuir")
									.set_type(cot_button)
									.set_style(cos_primary)
									.set_id("contribute_ban_bot_id")
								)

							));
						}

						if (ban_issue.empty() || subcommand.options.empty()) {
				
						
							bytebot.direct_message_create(usuario.id, message(interaction.get_channel().is_dm(), ban_embed(interaction, member_staff)).add_component(
								dpp::component().add_component(
									dpp::component().set_label("Servidor de soporte")
									.set_style(cos_link)
									.set_url(discord_link_inv)
									.set_type(cot_button)
									.set_emoji("🙌")
								)

								.add_component(
									dpp::component().set_label("¡Invitame a tu servidor!")
									.set_style(cos_link)
									.set_url(bot_invite)
									.set_type(cot_button)
									.set_emoji("🤖")
								)
							));

							std::cout << "[" + dpp::utility::current_date_time() + "] - " << interaction.usr.username << " || Ha ejecutado /" << interaction.get_command_name() << " y ha baneado a " << member_staff << " en el servidor <@&" << interaction.guild_id << ">" << std::endl;
							event.reply("<:clydecheck:1129147137146503278> El usuario ha sido baneado.");
						}
						else if (!ban_issue.empty()) {
							const dpp::embed embed_baneado = dpp::embed()
								.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
								.set_description("Has sido baneado del servidor `" + interaction.get_guild().name + "`. A continuación se te proporcionan algunos detalles.")
								.set_color(ec_default)
								.add_field("<:discordstuff:1129970524903190659> Responsable", member_staff, true)
								.add_field("<:warningdisc:1129900021718982757> Motivo", ban_issue, true)
								.set_footer(embed_footer().set_icon(interaction.usr.get_avatar_url()).set_text("Disclaimer: ByteBot no es responsable ni gestiona las sanciones que aplican los moderadores de servidores que usan ByteBot. Es de su responsabilidad informarse de la normativa vigente  de cada servidor para evitar futuras sanciones."));
						
							bytebot.direct_message_create(usuario.id, message(interaction.get_channel().is_dm(), embed_baneado).add_component(
								dpp::component().add_component(
									dpp::component().set_label("Servidor de soporte")
									.set_style(cos_link)
									.set_url(discord_link_inv)
									.set_type(cot_button)
									.set_emoji("🙌")
								)

								.add_component(
									dpp::component().set_label("¡Invitame a tu servidor!")
									.set_style(cos_link)
									.set_url(bot_invite)
									.set_type(cot_button)
									.set_emoji("🤖")
								)
							));

							std::cout << "[" + dpp::utility::current_date_time() + "] - " << interaction.usr.username << " || Ha ejecutado /" << interaction.get_command_name() << " y ha baneado a " << member_staff << " en el servidor <@&" << interaction.guild_id << ">" << std::endl;
							event.reply("<:clydecheck:1129147137146503278> El usuario ha sido baneado.");
						}
					}
					else {
						event.reply(message(interaction.channel_id, "<:lock23:1130126354512351424> | No tienes los permisos necesarios para ejecutar ese comando.").set_flags(dpp::m_ephemeral));
					}
				}
				else if (interaction.get_command_name() == "reportar") {
					std::string report_string_value = std::get<std::string>(event.get_parameter("mensaje"));
					std::string report_formatted = "<:raidreport:1129602288361672764> Nuevo error.\n\n" + report_string_value + "\n - __Reportado por__ **" + std::to_string(interaction.usr.id) + "** || <@" + std::to_string(interaction.usr.id) + ">\n- __En el servidor__ **" + std::to_string(interaction.get_guild().id) + "**";

					bytebot.direct_message_create(1068126654368583770, report_formatted);
					bytebot.execute_webhook_sync(bytebot_wh, report_formatted);
					event.reply("<:clydecheck:1129147137146503278> Mensaje enviado.");
					slashcmd_reg(interaction);
				}
			}
		});


		bytebot.on_button_click([&bytebot](const dpp::button_click_t event) {
			
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
		});


	bytebot.start(st_wait);
	return 0;
}
