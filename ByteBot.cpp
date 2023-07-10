#include "header.h"

using namespace dpp; //testing
using namespace std;

const uint64_t ec_default = colors::pink;
const uint64_t ec_error = colors::red_blood; //embed color
const string blacklisted_users[3] = { "1", "2", "3" };

//const auto badge = user::is_active_developer;

string test[2] = { "10681266543685", "921516505735262251" };

int main() {
	//Create bot cluster
	cluster bytebot(BOT_TOKEN, i_default_intents | i_message_content);

	//Output log information
	bytebot.on_log(utility::cout_logger());

	//Handler for slash commands
	bytebot.on_slashcommand([&bytebot](const slashcommand_t& event) { //DO find arrays with find and end.
		if (event.command.usr.id == test[0] || event.command.usr.id == test[1]) {
			const embed embed_blacklisted = embed()
				.set_color(ec_error)
				.set_author(" ByteBot", "https://discord.gg/bYDhwFFVk5", "https://i.imgur.com/U95zuYh.png")
				.set_description("Puedes apelar la sancion en el servidor de Discord oficial [haciendo click aqui](https://discord.gg/bYDhwFFVk5).\n \nNo es seguro que puedas volver a usar el bot, pero tienes la oportunidad de apelar; Motivos por los que tu cuenta puede resultar en una prohibicion del uso de ByteBot:\n \n> Automatizacion de los comandos de Node en servidores via self-bots u otros.\n \n> Uso del bot con fines maliciosos, estafas, phising, mensajes de estafas, etc.\n \n> Presencia del bot en servidores con fines maliciosos.\n \n> Otros motivos. \n ")
				.set_title("Tienes una prohibicion permanente del uso de ByteBot.");

			event.reply(message(event.command.get_channel().id, embed_blacklisted));
			bytebot.message_add_reaction(event.command.msg.id, event.command.get_channel().id, "🙂", utility::log_error()); //check err
			cout << event.command.message_id;

		}
		else {

			if (event.command.get_command_name() == "ping") {
				event.reply("Pong");

			}
			else if (event.command.get_command_name() == "commands") {
				const embed embed_commands = embed()
					.set_color(ec_default)
					.set_author(" ByteBot", "https://discord.gg/bYDhwFFVk5", "https://i.imgur.com/U95zuYh.png")
					.set_description("`/commands` | **¡Hola! Maybe you know me, maybe not. Anyway, Im here to help you making discord a chiller place. My commands are sub-divided into categories**");

				event.reply(message(event.command.get_channel().id, embed_commands).set_reference(event.command.msg.id));
			}
			else if (event.command.get_command_name() == "userinfo") {
				const auto isCertifiedModerator = event.command.usr.is_certified_moderator();
				const auto activeDeveloperBadge = event.command.usr.is_active_developer();
				const auto haveDiscordNitroB = event.command.usr.has_nitro_basic();
				const auto haveDiscordNitroC = event.command.usr.has_nitro_classic();
				const auto haveDiscordNitroF = event.command.usr.has_nitro_full();
				const auto isBot = event.command.usr.is_bot();
				const auto isDiscordEmployee = event.command.usr.is_discord_employee();

				std::string activeDeveloperBadge_str, haveDiscordNitro_str, isBot_str, isCertifiedModerator_str, isDiscordEmployee_str;

				switch (activeDeveloperBadge) {
				case 0:
					activeDeveloperBadge_str = "<a:no2:1127991706156015626>";
					break;

				case 1:
					activeDeveloperBadge_str = "<:yes:1127991707863093359>";
					break;

				default:
					break;
				}

				switch (haveDiscordNitroB) {
				case 0:
					haveDiscordNitro_str = "<a:no2:1127991706156015626>";
					if (haveDiscordNitroC) {
						haveDiscordNitro_str += ", <:yes:1127991707863093359> (Discord Classic)";
					}

					if (haveDiscordNitroF) {
						haveDiscordNitro_str += ", <:yes:1127991707863093359> (Discord Full)";
					}
					break;

				case 1:
					haveDiscordNitro_str = "<:yes:1127991707863093359> (Discord Basic).";
					if (haveDiscordNitroC) {
						haveDiscordNitro_str += ", <:yes:1127991707863093359> (Discord Classic)";
					}

					if (haveDiscordNitroF) {
						haveDiscordNitro_str += ", <:yes:1127991707863093359> (Discord Classic)";
					}
					break;

				default:
					break;
				}

				switch (isBot) {
				case 0:
					isBot_str = "<a:no2:1127991706156015626>";
					break;

				case 1:
					isBot_str = "<:yes:1127991707863093359>";
					break;

				default:
					break;
				}

				switch (isCertifiedModerator) {
				case 0:
					isCertifiedModerator_str = "<a:no2:1127991706156015626>";
					break;

				case 1:
					isCertifiedModerator_str = "<:yes:1127991707863093359>";
					break;

				default:
					break;
				}

				switch (isDiscordEmployee) {
				case 0:
					isDiscordEmployee_str = "<a:no2:1127991706156015626>";
					break;

				case 1:
					isDiscordEmployee_str = "<:yes:1127991707863093359>";
						break;

				default:
					break;

				}

				const embed embed_userinfo = embed()
					.set_color(ec_default)
					.set_author(" ByteBot", "https://discord.gg/bYDhwFFVk5", "https://i.imgur.com/U95zuYh.png")
					.add_field("<:active_developer:1127568563176222760> | ¿Es un desarrollador activo?", activeDeveloperBadge_str, true)
					.add_field("<a:nitro:1127997712009273434> | ¿Tiene discord nitro?", haveDiscordNitro_str, true)
					.add_field("<:bot:1127621337700122745> | ¿Es un bot?", isBot_str, true)
					.add_field("")
					.add_field("<:certifiedmod:1128014727277183026> | ¿Es un moderador certificado de Discord?", isCertifiedModerator_str, false)
					.add_field("<:discordemployee:1128018688822485012 | ¿Es empleado de Discord?", isDiscordEmployee_str, true)
					.add_field("", "*¡Advertencia! Estar en posesion de esta insignia no esta relacionado directamente con saber programar o saber desarrollar discord de bots puesto que hay APIs, servicios y scripts que te permiten obtener esta insignia facilmente sin saber programar.*", false);
				//.set_footer(default_footer);
				event.reply(message(event.command.get_channel().id, embed_userinfo));
			}
		}
		});

	//Register slash commands
	bytebot.on_ready([&bytebot](const ready_t& event) {
		bytebot.set_presence(presence(ps_idle, at_listening, "/commands")); //define bot status

		if (run_once<struct register_bot_commands>()) { //Avoid re-running on-ready declaration everytime that the bots makes a full reconnection
			bytebot.global_command_create(slashcommand("ping", "Pong!", bytebot.me.id));
			bytebot.global_command_create(slashcommand("commands", "¡Muestra de lo que soy capaz!", bytebot.me.id));
			bytebot.global_command_create(slashcommand("userinfo", "Soy capaz de mostrarte toda la informacion posible sobre la persona que quieras o ti mismo.", bytebot.me.id));

		}
		});

	bytebot.start(st_wait);
	return 0;
}
