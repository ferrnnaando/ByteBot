#include "headers/mainheader.h"

#include "register/slashcommands/slashcommand_on_ready/slashcommands.h"
#include "register/slashcommands/slashcommand_logger/logger.h"
#include "register/buttons/on_button_click/on_button_click.h"
#include "register/embeds/embed_declarations.h"
#include "register/on_messages/on_messages.h"

using namespace std;
using namespace dpp;

int main(){
    dotenv::init();
	const std::string BOT_TOKEN{std::getenv("token")};
	dpp::cluster bytebot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);
	dpp::webhook bytebot_wh(reports_webhook);
	
	bytebot.on_log(utility::cout_logger());

	 bytebot.on_ready([&bytebot](const ready_t& event) {
		 on_ready(bytebot);
	});
		
	bytebot.on_message_create([&bytebot](const dpp::message_create_t& msg) {
		on_message_create(msg, bytebot);
	});

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

		std::time_t timestamp_user = interaction.usr.get_creation_time();
					std::tm* fecha_hora_user = std::gmtime(&timestamp_user);
					char buffer_user[80];
					std::strftime(buffer_user, sizeof(buffer_user), "%Y-%m-%d a las %H:%M:%S horas.", fecha_hora_user);
					std::string formatted_date_user = "```" + std::string(buffer_user) + "```";

		if (interaction.usr.id == blacklisted_users[0] || interaction.usr.id == blacklisted_users[1]) {
			std::cout << "[" + utility::current_date_time() + "] - " << interaction.usr.username << " || Intento ejecutar un comando, pero su ID se encuentra prohibida del uso de ByteBot." << std::endl;
			event.reply(dpp::message(event.command.get_channel().id, blacklist_embed(interaction)).set_flags(ephemeral));

		}
		else {
			if (interaction.get_command_name() == "informacion") {
				event.reply(dpp::message(interaction.get_channel().id, bytebot_embed(interaction)).set_flags(ephemeral));

			}
			else if (interaction.get_command_name() == "comandos") {
				event.reply(dpp::message(event.command.get_channel().id, commands_embed(interaction)));

			}
			else if (interaction.get_command_name() == "infousuario") {
				if (subcommand.options.empty()) {
					const auto username = "```" + interaction.usr.username + "```";
					const std::string username_avatar_formatted = "[Ver aquí](" + interaction.usr.get_avatar_url() + ").";
					const auto username_discriminator = "```" + std::to_string(interaction.usr.discriminator) + "```";
					const auto username_have_nitro_basic = interaction.usr.has_nitro_basic();
					const auto username_have_nitro_classic = interaction.usr.has_nitro_classic();
					const auto username_have_nitro_full = interaction.usr.has_nitro_full();
					const auto is_bot_verified = interaction.usr.is_verified_bot();
					const auto is_house_brilliance = interaction.usr.is_house_brilliance();
					const auto is_house_bravery = interaction.usr.is_house_bravery();
					const auto is_house_balance = interaction.usr.is_house_balance();
					const auto is_early_supporter = interaction.usr.is_early_supporter();

					const std::string user_id_formatted = "```" + std::to_string(interaction.usr.id) + "```";

					std::string have_nitro, is_bot_verified_str, hypesquad_str;

					if (is_house_balance) {
						hypesquad_str = "```Sí. (House Balance)```";

					}
					else if (is_house_bravery) {
						hypesquad_str = "```Sí. (House Bravery)```";

					}
					else if (is_house_brilliance) {
						hypesquad_str = "```Sí. (House Brilliance)```";

					}
					else {
						hypesquad_str = "```No.```";

					}

					switch (username_have_nitro_basic) {
					case 0 || false:
						have_nitro = "```No.```";
						if (username_have_nitro_classic) {
							have_nitro = "```Tiene nitro classic.```";

						}
						else if (username_have_nitro_full) {
							have_nitro = "```Tiene nitro full.```";
						}

						break;
					case 1 || true:
						have_nitro = "```Sí.```";
						if (username_have_nitro_classic) {
							have_nitro = "```Tiene nitro classic.```";

						}
						else if (username_have_nitro_full) {
							have_nitro = "```Tiene nitro full.```";
						}
						break;
					}

					switch (is_bot_verified) {
					case 0 || false:
						is_bot_verified_str = "```No.```";
						break;

					case 1 || true:
						is_bot_verified_str = "```Sí.```";
						break;

					}

						event.reply(message(interaction.get_channel().id, embed_infousuario));
				}
				else {
					dpp::user user = interaction.get_resolved_user(subcommand.get_value<snowflake>(0));

					const auto username = "```" + user.username + "```";
					const std::string username_avatar_formatted = "[Ver aquí](" + user.get_avatar_url() + ").";
					const auto username_discriminator = "```" + std::to_string(user.discriminator) + "```";
					const auto username_have_nitro_basic = user.has_nitro_basic();
					const auto username_have_nitro_classic = user.has_nitro_classic();
					const auto username_have_nitro_full = user.has_nitro_full();
					const auto is_bot_verified = user.is_verified_bot();
					const auto is_house_brilliance = user.is_house_brilliance();
					const auto is_house_bravery = user.is_house_bravery();
					const auto is_house_balance = user.is_house_balance();
					const auto is_early_supporter = user.is_early_supporter();

					const std::string user_id_formatted = "```" + std::to_string(user.id) + "```";

					std::string have_nitro, is_bot_verified_str, hypesquad_str;

					if (is_house_balance) {
						hypesquad_str = "```Sí. (House Balance)```";

					}
					else if (is_house_bravery) {
						hypesquad_str = "```Sí. (House Bravery)```";

					}
					else if (is_house_brilliance) {
						hypesquad_str = "```Sí. (House Brilliance)```";

					}
					else {
						hypesquad_str = "```No.```";

					}

					switch (username_have_nitro_basic) {
					case 0 || false:
						have_nitro = "```No.```";
						if (username_have_nitro_classic) {
							have_nitro = "```Tiene nitro classic.```";

						}
						else if (username_have_nitro_full) {
							have_nitro = "```Tiene nitro full.```";
						}

						break;
					case 1 || true:
						have_nitro = "```Sí.```";
						if (username_have_nitro_classic) {
							have_nitro = "```Tiene nitro classic.```";

						}
						else if (username_have_nitro_full) {
							have_nitro = "```Tiene nitro full.```";
						}
						break;
					}

					switch (is_bot_verified) {
					case 0 || false:
						is_bot_verified_str = "```No.```";
						break;

					case 1 || true:
						is_bot_verified_str = "```Sí.```";
						break;

					}

					std::time_t timestamp_user = user.get_creation_time();
					std::tm* fecha_hora_user = std::gmtime(&timestamp_user);
					char buffer_user[80];
					std::strftime(buffer_user, sizeof(buffer_user), "%Y-%m-%d a las %H:%M:%S horas.", fecha_hora_user);
					std::string formatted_date_user = "```" + std::string(buffer_user) + "```";

					if (user.is_bot()) {
						const dpp::embed embed_infousuario = embed()
							.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
							.set_color(ec_default)
							.add_field("<:member:1129180523407884368> Nombre de usuario", username, false)
							.add_field("<:members:1129182568584069210> Discriminador", username_discriminator, true)
							.add_field("<:slashcmd:1129193506787840091> Es un bot", "```Sí.```", true)
							.add_field("<:slashcmd:1129193506787840091> Bot verificado", is_bot_verified_str, true)
							.add_field("<:idlog:1129209889739251813> ID", user_id_formatted, false)
							.add_field("<:joined:1129241382930894859> Se unió a discord el", formatted_date_user, false)
							.add_field("<:preview:1129409265715642399> Avatar", username_avatar_formatted, false);

						event.reply(message(interaction.get_channel().id, embed_infousuario));

					}
					else if (!user.is_bot()) {
						const dpp::embed embed_infousuario = embed()
							.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
							.set_color(ec_default)
							.add_field("<:member:1129180523407884368> Nombre de usuario", username, false)
							.add_field("<:members:1129182568584069210> Discriminador", username_discriminator, true)
							.add_field("<:nitroc:1129193504527110166> Tiene nitro", have_nitro, true)
							.add_field("<:hypesquadevents:1129203280216600638> HypeSquad", hypesquad_str, true)
							.add_field("<:idlog:1129209889739251813> ID", user_id_formatted, false)
							.add_field("<:joined:1129241382930894859> Se unió a discord el", formatted_date_user, false)
							.add_field("<:preview:1129409265715642399> Avatar", username_avatar_formatted, false);

						event.reply(message(interaction.get_channel().id, embed_infousuario));

					}
				}

				slashcmd_reg(interaction);
				//cooldown_slashcmds;

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

				if(guild_is_partnered == 0) {
					partnered_guild_str = "```No.```";
                }
                else {
                    partnered_guild_str = "```Si.```";
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
					std::string ban_issue = std::get<std::string>(event.get_parameter("motivo"));
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
			
			on_button_click(event, bytebot);
		});


	bytebot.start(st_wait);
	return 0;
}