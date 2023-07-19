#include "headers/mainheader.h"

#include "register/slashcommands/slashcommand_on_ready/slashcommands.h"
#include "register/slashcommands/slashcommand_logger/logger.h"
#include "register/embeds/embed_declarations.h"

int main() {
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

			/*if (g) {
				if (interaction.usr.id == owner_guild_id) {

					event.reply(message(interaction.channel_id, "<:warningdisc:1129900021718982757> ¡Vaya! No puedes usar mis comandos porque estoy listo para marcharme de este servidor, te he enviado un mensaje privado explicando el motivo. ¡Suerte!").set_flags(dpp::m_ephemeral));
					const dpp::embed embed_blacklistguild = dpp::embed()
						.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
						.set_description("Me he marchado del servidor `" + guild_name + "`. A continuación se te proporcionan algunos detalles.")
						.set_color(ec_default)
						.add_field("<:discordstuff:1129970524903190659> Responsable", formated_bytebot_moderator, true)
						.add_field("<:warningdisc:1129900021718982757> Motivo", "```Tu servidor está marcado en la lista negra de servidores por los desarrolladores de ByteBot. ```", true)
						.set_footer(embed_footer().set_icon(interaction.usr.get_avatar_url()).set_text("Advertencia: Puedes apelar esta decisión en el servidor oficial de ByteBot."));


					bytebot.direct_message_create(owner_guild_id, message(interaction.get_channel().is_dm(), embed_blacklistguild).add_component(
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

					std::cout << "[" + dpp::utility::current_date_time() + "] - " << interaction.usr.username << " || Ha intentado ejecutar un comando en el servidor <@&" << interaction.guild_id << "> pero está este último está marcado en la lista negra, abandonando servidor." << std::endl;

					bytebot.current_user_leave_guild(blacklisted_servers[0]);
				}
				else if (interaction.usr.id != interaction.get_guild().owner_id) {
					event.reply(message(interaction.channel_id, "<:warningdisc:1129900021718982757> ¡Vaya! No puedes usar mis comandos porque estoy listo para marcharme de este servidor. Le he enviado un mensaje privado al dueño del servidor explicando el motivo de esta acción. Habla con él para conocer los detalles ya que, por motivos de privacidad yo no puedo hacerlo directamente. ¡Suerte!").set_flags(dpp::m_ephemeral));

					const dpp::embed embed_blacklistguild = dpp::embed()
						.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
						.set_description("Me he marchado del servidor `" + guild_name + "`. A continuación se te proporcionan algunos detalles.")
						.set_color(ec_default)
						.add_field("<:discordstuff:1129970524903190659> Responsable", formated_bytebot_moderator, true)
						.add_field("<:warningdisc:1129900021718982757> Motivo", "```Tu servidor está marcado en la lista negra de servidores por los desarrolladores de ByteBot. ```", true)
						.set_footer(embed_footer().set_icon(interaction.usr.get_avatar_url()).set_text("Advertencia: Puedes apelar esta decisión en el servidor oficial de ByteBot."));


					bytebot.direct_message_create(owner_guild_id, message(interaction.get_channel().is_dm(), embed_blacklistguild).add_component(
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
				}
			}*/

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
					//cooldown_slashcmds;
					event.reply(message(interaction.get_channel().id, embed_bytebot).set_flags(ephemeral));

				}
				else if (interaction.get_command_name() == "comandos") {
					const embed embed_commands = embed()
						.set_color(ec_default)
						.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
						.set_description("`/commands` | **¡Hola! Maybe you know me, maybe not. Anyway, Im here to help you making discord a chiller place. My commands are sub-divided into categories**");

					slashcmd_reg(interaction);
					//cooldown_slashcmds;
					event.reply(message(event.command.get_channel().id, embed_commands));

				}
				else if (interaction.get_command_name() == "infousuario") {
					if (subcommand.options.empty()) {
						

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
						//cooldown_slashcmds;
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

					}
					else {
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
					//cooldown_slashcmds;

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
					//cooldown_slashcmds;
				}
				else if (interaction.get_command_name() == "banear") {
					dpp::permission ban_perm = interaction.resolved.member_permissions.find(interaction.usr.id)->second;

					if (ban_perm.has(dpp::p_ban_members) || ban_perm.has(dpp::p_administrator)) {
						dpp::user usuario = interaction.get_resolved_user(subcommand.get_value<dpp::snowflake>(0));
						std::string ban_issue = std::get<std::string>(event.get_parameter("motivo")) + "```";
						static const std::string member_staff = "<@" + std::to_string(interaction.usr.id) + ">";

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
							const dpp::embed embed_baneado = dpp::embed()
								.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
								.set_description("Has sido baneado del servidor `" + interaction.get_guild().name + "`. A continuación se te proporcionan algunos detalles.")
								.set_color(ec_default)
								.add_field("<:discordstuff:1129970524903190659> Responsable", member_staff, true)
								.add_field("<:warningdisc:1129900021718982757> Motivo", "``` No especificado. ```", true)
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
