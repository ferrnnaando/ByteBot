#include "embed_declarations.h"

class embed_definition : public lol {
	public:
		dpp::embed blacklist_embed(dpp::interaction& interaction)
		{
			const dpp::embed embed_blacklisted = dpp::embed()
				.set_color(ec_error)
				.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
				.set_description("Puedes apelar la sancion en el servidor de Discord oficial [haciendo click aqui](https://discord.gg/bYDhwFFVk5).\n \nNo es seguro que puedas volver a usar el bot, pero tienes la oportunidad de apelar; Motivos por los que tu cuenta puede resultar en una prohibicion del uso de ByteBot:\n \n> Automatizacion de los comandos de ByteBot en servidores via self-bots u otros.\n \n> Uso del bot con fines maliciosos, estafas, phising, mensajes de estafas, etc.\n \n> Presencia del bot en servidores con fines maliciosos.\n \n> Otros motivos. \n ")
				.set_title("Tienes una prohibicion permanente del uso de ByteBot.")
				;

			return embed_blacklisted;
		}

		dpp::embed bytebot_embed(dpp::interaction& interaction)
		{
			const dpp::embed embed_bytebot = embed()
				.set_color(ec_default)
				.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
				.set_title("El poder de ByteBot en tus teclas.")
				.set_description("Saludos, querido usuario!\n\nPermiteme presentarme, soy ByteBot, tu asistente virtual personal disenado para brindarte una experiencia segura y optimizada en este servidor. Estoy aqui para ayudarte con la configuracion y la administracion, asegurando que tus necesidades de seguridad se cumplan y que puedas disfrutar de un entorno confiable.\n\nComo experto en seguridad, puedo ayudarte a proteger tus datos y a mantener el servidor seguro. Puedo implementar funciones como verificacion de dos factores (2FA) para asegurar que solo usuarios autorizados tengan acceso, y puedo monitorear y filtrar mensajes en busca de contenido no deseado.\n\nPero mi papel no se limita solo a la seguridad. Tambien puedo ayudarte con la configuracion y personalizacion del servidor. Desde establecer roles y permisos hasta gestionar canales y categorias, estoy aqui para asegurarme de que todo este configurado segun tus preferencias y necesidades.\n\nAdemas, como asistente de administracion, puedo realizar tareas rutinarias y automatizar procesos para que puedas dedicar mas tiempo a interactuar con los miembros del servidor. Puedo programar recordatorios, gestionar eventos y facilitar la moderacion para mantener un entorno armonioso y organizado.\n\nMi objetivo es brindarte tranquilidad y eficiencia en la administracion de este servidor. Estoy aqui para resolver tus consultas, proporcionar orientacion y ser tu companero confiable en la gestion diaria.\n\nAprovecha el poder de ByteBot y descubre todo lo que puedo hacer por ti! Si necesitas ayuda o tienes alguna consulta, simplemente escribe `!ayuda` y estare encantado de asistirte.\n\nGracias por permitirme ser parte de tu experiencia en este servidor. Espero hacer de tu tiempo aqui algo seguro y sin complicaciones. Disfruta y confia en ByteBot para una experiencia de servidor excepcional!") // Descripción del bot				
				.add_field("Soporte", "```Estoy aqui para ofrecerte un soporte tecnico confiable y eficiente. Si tienes alguna pregunta, problema o consulta, no dudes en escribir `!ayuda` o mencionarme. Estare encantado de brindarte asistencia y resolver cualquier inconveniente que puedas tener.```", true) // Campo de Soporte
				.add_field("Automatizacion", "```Simplifica tu vida y ahorra tiempo con mi capacidad para automatizar tareas. Puedo encargarme de recordatorios, eventos programados y moderacion automatica, permitiendote concentrarte en otras actividades importantes en el servidor. \n ```", true) // Campo de Automatización
				.add_field("", "", false)
				.add_field("Personalizacion", "```Haz que el servidor sea unico y se adapte a tus necesidades mediante mi capacidad de configuracion y personalizacion. Puedo ayudarte a establecer roles, permisos, canales y categorias de manera precisa y eficiente. \n ```", true) // Campo de Personalización
				.add_field("Seguridad Avanzada", "```Protege tu servidor y tus datos con mi conjunto de funciones de seguridad avanzadas. Desde la verificacion de dos factores (2FA) hasta la deteccion y filtrado de contenido no deseado, estoy aqui para garantizar un entorno seguro para todos los miembros.```", true) //a
				;

			return embed_bytebot;
		}

		dpp::embed commands_embed(dpp::interaction& interaction)
		{
			const embed embed_commands = embed()
				.set_color(ec_default)
				.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
				.set_description("`/commands` | **¡Hola! Maybe you know me, maybe not. Anyway, Im here to help you making discord a chiller place. My commands are sub-divided into categories**")
				;

			return embed_commands;
		}

		dpp::embed infoservidor(dpp::interaction& interaction, std::string& guild_owner_formatted, std::string& guild_name, std::string& partnered_guild_str, bool& guild_is_partnered, std::string& total_guild_channels, std::string& total_guild_roles, std::string& total_guild_emojis, const std::vector<dpp::snowflake>& channels, const std::vector<dpp::snowflake>& roles, const std::vector<dpp::snowflake>& emojis, const dpp::guild& g, std::string& guild_id, std::string& formatted_date_guild, std::string& guild_description_formatted, std::string& guild_2fa_level)
		{
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
					.add_field("<:moderatorbadge:1129286080294813839> Nivel de seguridad", guild_2fa_level, false)
					;

				return embed_infoservidor;
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
					.add_field("<:moderatorbadge:1129286080294813839> Nivel de seguridad", guild_2fa_level, false)
					;

				return embed_infoservidor;
			}
		}

		dpp::embed avatar_embed(dpp::interaction& interaction)
		{
			//maybe can check for both embeds here and avoid using 2 ifs on the commmand.
			const embed embed_avatar = embed()
				.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
				.set_color(ec_default)
				.set_image(interaction.usr.get_avatar_url(1024))
				;

			return embed_avatar;
		}

		dpp::embed usuario_avatar_embed(dpp::interaction& interaction, dpp::user& avatar)
		{
			const embed usuario_embed_avatar = embed()
				.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
				.set_color(ec_default)
				.set_image(avatar.get_avatar_url(1024))
				;

			return usuario_embed_avatar;
		}

		dpp::embed ban_embed(dpp::interaction& interaction, std::string& member_staff)
		{
			const dpp::embed embed_baneado = dpp::embed()
				.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
				.set_description("Has sido baneado del servidor `" + interaction.get_guild().name + "`. A continuación se te proporcionan algunos detalles.")
				.set_color(ec_default)
				.add_field("<:discordstuff:1129970524903190659> Responsable", member_staff, true)
				.add_field("<:warningdisc:1129900021718982757> Motivo", "``` No especificado. ```", true)
				.set_footer(embed_footer().set_icon(interaction.usr.get_avatar_url()).set_text("Disclaimer: ByteBot no es responsable ni gestiona las sanciones que aplican los moderadores de servidores que usan ByteBot. Es de su responsabilidad informarse de la normativa vigente  de cada servidor para evitar futuras sanciones."))
				;

			return embed_baneado;
		}

};