#include "embed_declarations.h"

dpp::embed blacklist_embed(dpp::interaction& interaction)
{
		const dpp::embed embed_blacklisted = dpp::embed()
			.set_color(ec_error)
			.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
			.set_description("Puedes apelar la sancion en el servidor de Discord oficial [haciendo click aqui](https://discord.gg/bYDhwFFVk5).\n \nNo es seguro que puedas volver a usar el bot, pero tienes la oportunidad de apelar; Motivos por los que tu cuenta puede resultar en una prohibicion del uso de ByteBot:\n \n> Automatizacion de los comandos de ByteBot en servidores via self-bots u otros.\n \n> Uso del bot con fines maliciosos, estafas, phising, mensajes de estafas, etc.\n \n> Presencia del bot en servidores con fines maliciosos.\n \n> Otros motivos. \n ")
			.set_title("Tienes una prohibicion permanente del uso de ByteBot.");


    return dpp::embed();
}
