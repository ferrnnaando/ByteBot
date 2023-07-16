#include "header.h"
#include "variables.cpp"
#include "functions.cpp"

void slashcmd_reg(const dpp::interaction& interaction) {
	std::cout << "[" + dpp::utility::current_date_time() + "] - " << interaction.usr.username << " || Slashcommand /" << interaction.get_command_name() << " ejecutado." << std::endl;
} 

int main() {
	//Create bot cluster
	dpp::cluster bytebot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);
	dpp::webhook bytebot_wh("https://discord.com/api/webhooks/1129797836255547443/NJimRvFP1yjR5HKbAkczyA07QBcQP-6zEKmen-PimQtyCPQo2rmjrFujrLfjNJ7Gz9sf");

	//Output log information
	bytebot.get_gateway_bot_sync();
	bytebot.on_log(utility::cout_logger());

	//Handleer for messages events
	bytebot.on_message_create([&bytebot](const dpp::message_create_t& msg) {
		if (msg.msg.is_dm()) {
			if (msg.msg.author.id != bytebot.me.id && msg.msg.is_dm()) { //avoid loop for self-replying
				bytebot.start_timer([=, &bytebot](dpp::timer h) {
					msg.reply(message("<:guide:1129765954834939944> ¿Necesitas ayuda? Escríbeme mediante un servidor y estaré encantado de ayudarte.").add_component(
						component().add_component(
							component().set_label("Servidor de soporte")
							.set_type(cot_button)
							.set_style(cos_danger)
							//.set_emoji(u8"😄")
							.set_id("md_btn")
						)));
						 
					bytebot.stop_timer(h);
					}, 1);
			}
		}
		else if (msg.msg.content == "/") {

			bytebot.start_timer([=, &bytebot](dpp::timer h) {
				msg.reply("<:warningdisc:1129900021718982757> ¿Quieres ver todo lo que puedo hacer? Escribe **/**, elige alguno de mis comandos y deja que la magia fluya.");
				bytebot.stop_timer(h);
				}, 5);
		}
	});

	//Handler for slash commands
	bytebot.on_slashcommand([&bytebot, &bytebot_wh](const slashcommand_t& event) { //DO find arrays with find and end.
		dpp::interaction interaction = event.command;
		dpp::command_interaction cmd_data = interaction.get_command_interaction();
		auto subcommand = cmd_data;

		std::time_t timestamp_guild = interaction.get_guild().get_creation_time();
		std::tm* fecha_hora_guild = std::gmtime(&timestamp_guild);
		char buffer_guild[80];
		std::strftime(buffer_guild, sizeof(buffer_guild), "%Y-%m-%d a las %H:%M:%S horas.", fecha_hora_guild);
		std::string formatted_date_guild = "```" + std::string(buffer_guild) + "```";

		auto cooldown_slashcmds = bytebot.start_timer([=, &interaction, &bytebot](dpp::timer h) {
			event.delete_original_response();
			bytebot.stop_timer(h);
			}, 15);

		if (interaction.usr.id == blacklisted_users[0] || interaction.usr.id == blacklisted_users[1]) {
			const embed embed_blacklisted = embed()
				.set_color(ec_error)
				.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
				.set_description("Puedes apelar la sancion en el servidor de Discord oficial [haciendo click aqui](https://discord.gg/bYDhwFFVk5).\n \nNo es seguro que puedas volver a usar el bot, pero tienes la oportunidad de apelar; Motivos por los que tu cuenta puede resultar en una prohibicion del uso de ByteBot:\n \n> Automatizacion de los comandos de ByteBot en servidores via self-bots u otros.\n \n> Uso del bot con fines maliciosos, estafas, phising, mensajes de estafas, etc.\n \n> Presencia del bot en servidores con fines maliciosos.\n \n> Otros motivos. \n ")
				.set_title("Tienes una prohibicion permanente del uso de ByteBot.");

			std::cout << "[" + utility::current_date_time() + "] - " << interaction.usr.username << " || Intento ejecutar un comando, pero su ID se encuentra prohibida del uso de ByteBot." << std::endl;
			event.reply(message(event.command.get_channel().id, embed_blacklisted).set_flags(m_ephemeral));

		}
		else {
			if (interaction.get_command_name() == "bytebot") {
				const dpp::embed embed_bytebot = embed()
					.set_color(ec_default)
					//.set_image(banner_url)
					.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
					.set_title("El poder de ByteBot en tus teclas.")
					.set_description("¡Saludos, querido usuario!\n\nPermíteme presentarme, soy ByteBot, tu asistente virtual personal diseñado para brindarte una experiencia segura y optimizada en este servidor. Estoy aquí para ayudarte con la configuración y la administración, asegurando que tus necesidades de seguridad se cumplan y que puedas disfrutar de un entorno confiable.\n\nComo experto en seguridad, puedo ayudarte a proteger tus datos y a mantener el servidor seguro. Puedo implementar funciones como verificación de dos factores (2FA) para asegurar que solo usuarios autorizados tengan acceso, y puedo monitorear y filtrar mensajes en busca de contenido no deseado.\n\nPero mi papel no se limita solo a la seguridad. También puedo ayudarte con la configuración y personalización del servidor. Desde establecer roles y permisos hasta gestionar canales y categorías, estoy aquí para asegurarme de que todo esté configurado según tus preferencias y necesidades.\n\nAdemás, como asistente de administración, puedo realizar tareas rutinarias y automatizar procesos para que puedas dedicar más tiempo a interactuar con los miembros del servidor. Puedo programar recordatorios, gestionar eventos y facilitar la moderación para mantener un entorno armonioso y organizado.\n\nMi objetivo es brindarte tranquilidad y eficiencia en la administración de este servidor. Estoy aquí para resolver tus consultas, proporcionar orientación y ser tu compañero confiable en la gestión diaria.\n\n¡Aprovecha el poder de ByteBot y descubre todo lo que puedo hacer por ti! Si necesitas ayuda o tienes alguna consulta, simplemente escribe `!ayuda` y estaré encantado de asistirte.\n\nGracias por permitirme ser parte de tu experiencia en este servidor. Espero hacer de tu tiempo aquí algo seguro y sin complicaciones. ¡Disfruta y confía en ByteBot para una experiencia de servidor excepcional!") // Descripción del bot				
					.add_field("Soporte", "```Estoy aquí para ofrecerte un soporte técnico confiable y eficiente. Si tienes alguna pregunta, problema o consulta, no dudes en escribir `!ayuda` o mencionarme. Estaré encantado de brindarte asistencia y resolver cualquier inconveniente que puedas tener.```", true) // Campo de Soporte
					.add_field("Automatización", "```Simplifica tu vida y ahorra tiempo con mi capacidad para automatizar tareas. Puedo encargarme de recordatorios, eventos programados y moderación automática, permitiéndote concentrarte en otras actividades importantes en el servidor. \n ```", true) // Campo de Automatización
					.add_field("", "", false)
					.add_field("Personalización", "```Haz que el servidor sea único y se adapte a tus necesidades mediante mi capacidad de configuración y personalización. Puedo ayudarte a establecer roles, permisos, canales y categorías de manera precisa y eficiente. \n ```", true) // Campo de Personalización
					.add_field("Seguridad Avanzada", "```Protege tu servidor y tus datos con mi conjunto de funciones de seguridad avanzadas. Desde la verificación de dos factores (2FA) hasta la detección y filtrado de contenido no deseado, estoy aquí para garantizar un entorno seguro para todos los miembros.```", true); //a
				
				slashcmd_reg(interaction);
				cooldown_slashcmds;
				event.reply(message(interaction.get_channel().id, embed_bytebot).set_flags(m_ephemeral));

				slashcmd_reg(interaction);
				cooldown_slashcmds;
			}
			else if (interaction.get_command_name() == "commands") {
				const embed embed_commands = embed()
					.set_color(ec_default)
					.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
					.set_description("`/commands` | **¡Hola! Maybe you know me, maybe not. Anyway, Im here to help you making discord a chiller place. My commands are sub-divided into categories**");

				slashcmd_reg(interaction);
				cooldown_slashcmds;
				event.reply(message(event.command.get_channel().id, embed_commands));

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

					std::time_t timestamp_user = interaction.usr.get_creation_time();
					std::tm* fecha_hora_user = std::gmtime(&timestamp_user);
					char buffer_user[80];
					std::strftime(buffer_user, sizeof(buffer_user), "%Y-%m-%d a las %H:%M:%S horas.", fecha_hora_user);
					std::string formatted_date_user = "```" + std::string(buffer_user) + "```";

					if (interaction.usr.is_bot()) {
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
					else if (!interaction.usr.is_bot()) {
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

					slashcmd_reg(interaction);
					cooldown_slashcmds;
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
				cooldown_slashcmds;

			}
			else if (interaction.get_command_name() == "infoservidor") {
				std::string partnered_guild_str;

				const dpp::guild& g = interaction.get_guild();

				const std::string guild_owner_formatted = "<@" + std::to_string(g.owner_id) + ">";
				const std::string guild_id = "```" + std::to_string(g.id) + "```";
				const std::string guild_name = "```" + interaction.get_guild().name + "```";
				const auto guild_description_formatted = "```" + g.description + "```";

				const auto guild_created_at = g.get_creation_time();
				const bool guild_is_partnered = g.is_partnered();
				const auto guild_2fa_level = "```" + std::to_string(g.mfa_level) + "```";

				const std::vector<dpp::snowflake>& channels = g.channels;
				const std::vector<dpp::snowflake>& roles = g.roles;
				const std::vector<dpp::snowflake>& emojis = g.emojis;
				// Obtiene el recuento de canales en el gremio utilizando el método `size()`
				std::size_t channelCount = channels.size();
				std::size_t roleCount = roles.size();
				std::size_t emojiCount = emojis.size();
				const auto total_guild_channels = "```" + std::to_string(channelCount) + "```";
				const auto total_guild_roles = "```" + std::to_string(roleCount) + "```";
				const auto total_guild_emojis = "```" + std::to_string(emojiCount) + "```";

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

				if (!g.description.empty()) {
					const dpp::embed embed_infoservidor = embed()
						.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
						.set_image(interaction.get_guild().get_banner_url())
						.set_color(ec_default)
						.add_field("<:owner:1129273470040158319> Propietario", guild_owner_formatted, true)
						.add_field("<:publicguild:1129249322228264960> Nombre del servidor", guild_name, true)
						.add_field("<:partnered2:1129275181559451658> Partner", partnered_guild_str, true)
						.add_field("<:insights:1129270499378208768> Canales", total_guild_channels, true)
						.add_field("<:insights:1129270499378208768> Roles", total_guild_roles, true)
						.add_field("<:insights:1129270499378208768> Emojis", total_guild_emojis, true)
						.add_field("<:idlog:1129209889739251813> ID", guild_id, true)
						.add_field("<:devbadge:1129269023784308738> Se creó el", formatted_date_guild, true)
						.add_field("", "", false)
						.add_field("<:communityrules:1129286064549400647> Descripción", guild_description_formatted, true)
						.add_field("<:moderatorbadge:1129286080294813839> Nivel de seguridad", guild_2fa_level, false);

					event.reply(message(interaction.get_channel().id, embed_infoservidor));

				} else {
				const dpp::embed embed_infoservidor = embed()
					.set_image(interaction.get_guild().get_banner_url())
					.set_color(ec_default)
					.add_field("<:owner:1129273470040158319> Propietario", guild_owner_formatted, true)
					.add_field("<:publicguild:1129249322228264960> Nombre del servidor", guild_name, true)
					.add_field("<:partnered2:1129275181559451658> Partner", partnered_guild_str, true)

					//.add_field("<:publicguild:1129249322228264960> Canales", "`" + std::to_string(get_channel_count())  + "`, <#" + std::to_string(text) + ">", true);
					.add_field("<:insights:1129270499378208768> Canales", total_guild_channels, true)
					.add_field("<:insights:1129270499378208768> Roles", total_guild_roles, true)
					.add_field("<:insights:1129270499378208768> Emojis", total_guild_emojis, true)
					.add_field("<:idlog:1129209889739251813> ID", guild_id, false)
					.add_field("<:devbadge:1129269023784308738> Se creó el", formatted_date_guild, false)
					.add_field("<:moderatorbadge:1129286080294813839> Nivel de seguridad", guild_2fa_level, false);
				
				event.reply(message(interaction.get_channel().id, embed_infoservidor));

				}
				slashcmd_reg(interaction);
				cooldown_slashcmds;

		  }
			else if (interaction.get_command_name() == "avatar") {

				if (subcommand.options.empty()) {
					const embed embed_avatar = embed()
						.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
						.set_color(ec_default)
						.set_image(interaction.usr.get_avatar_url(1024));

					event.reply(message(interaction.get_channel().id, embed_avatar));
				}
				else {
					dpp::user avatar = interaction.get_resolved_user(subcommand.get_value<dpp::snowflake>(0));
					const embed embed_avatar = embed()
						.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
						.set_color(ec_default)
						.set_image(avatar.get_avatar_url(1024));

					event.reply(message(interaction.get_channel().id, embed_avatar));

				}
				slashcmd_reg(interaction);
				cooldown_slashcmds;
			}
		  else if (interaction.get_command_name() == "ban") {
			  dpp::user usuario = interaction.get_resolved_user(subcommand.get_value<dpp::snowflake>(0));
			}
			else if (interaction.get_command_name() == "report") {
				std::string report_string_value = std::get<std::string>(event.get_parameter("mensaje"));
				std::string report_formatted = "<:raidreport:1129602288361672764> Nuevo error.\n\n" + report_string_value + "\n - __Reportado por__ **" + std::to_string(interaction.usr.id) + "** || <@" + std::to_string(interaction.usr.id) + ">\n- __En el servidor__ **" + std::to_string(interaction.get_guild().id) + "**";
				
				bytebot.direct_message_create(1068126654368583770, report_formatted);
				bytebot.execute_webhook_sync(bytebot_wh, report_formatted);
				event.reply("<:clydecheck:1129147137146503278> Mensaje enviado.");
				slashcmd_reg(interaction);

				 bytebot.start_timer([=, &bytebot, &interaction](dpp::timer h) {
					event.delete_original_response();
					bytebot.stop_timer(h);
				}, 2);
			}
		}
		});

		//Register slash commands
		bytebot.on_ready([&bytebot](const ready_t& event) {
			bytebot.set_presence(presence(ps_idle, at_listening, "/bytebot en " + std::to_string(bytebot.current_user_get_guilds_sync().size()) + " servidores")); //define bot status

			if (run_once<struct register_bot_commands>()) { //Avoid re-running on-ready declaration everytime that the bots makes a full reconnection
				
				//########################################################################################################################

				dpp::slashcommand infousuario("infousuario", "Muestra toda la información a mi disposición sobre un usuario.", bytebot.me.id);
				infousuario.add_option(command_option(co_user, "usuario", "Usuario del que quieras saber mas.", false));

				slashcommand infoservidor("infoservidor", "Muestra toda la información a mi disposición sobre el servidor en el que se ejecuta el comando", bytebot.me.id);

				slashcommand avatar("avatar", "Muestra la foto de perfil de alguien.", bytebot.me.id);
				avatar.add_option(command_option(co_user, "usuario", "Usuario del que mostrar su foto de perfil.", false));

				//########################################################################################################################
				//########################################################################################################################

				slashcommand ban("ban", "Banea a un usuario del servidor", bytebot.me.id);
				ban.add_option(command_option(co_user, "usuario", "Menciona al usuario a sancionar", true));

				//########################################################################################################################
				//########################################################################################################################

				slashcommand report("report", description_slashcmd_report, bytebot.me.id);
				report.add_option(command_option(co_string, "mensaje", option_usuario_slashcmd_report, true));

				//########################################################################################################################

				//main slashcmd
				bytebot.global_command_create(slashcommand("commands", "Muestra de lo que soy capaz", bytebot.me.id));
				bytebot.global_command_create(slashcommand("bytebot", "Comando principal de ByteBot el cual te dirá que hacer conmigo", bytebot.me.id));

				//utilitties (just will be displayed for oneself)
				bytebot.global_command_create(infousuario);
				bytebot.global_command_create(infoservidor);
				bytebot.global_command_create(avatar);
				

				bytebot.global_command_create(ban);
				
				//others
				bytebot.global_command_create(report);
				


			}
		});


	bytebot.start(st_wait);
	return 0;
}
