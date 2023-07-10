#include "header.h"

using namespace dpp; //testing
using namespace std;

const std::string BOT_TOKEN = "MTEyNjY5MTc3MTUwNjc1NzcxMw.Gja_M3.Lp8jiHG9feS7qswW9IPtEdUttoVivBUzjQcWzQ";
const uint64_t ec_default = colors::pink;
const uint64_t ec_error = colors::red_blood; //embed color
const string blacklisted_users[3] = { "1", "2", "3" };

string test[2] = {"1068126654368583770", "921516505735262251"};

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

			event.reply(message(event.command.get_channel().id, embed_blacklisted).set_reference(event.command.msg.id));
				bytebot.message_add_reaction(event.command.message_id, event.command.get_channel().id, "🙂", utility::log_error()); //check err
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
				const embed embed_userinfo = embed()
					.set_color(ec_default)
					.set_author(" ByteBot", "https://discord.gg/bYDhwFFVk5", "https://i.imgur.com/U95zuYh.png")
					.add_field("| Active Developer", "Yes", true);
			}
		}
		});

	//Register slash commands
	bytebot.on_ready([&bytebot](const ready_t& event) {
		bytebot.set_presence(presence(ps_idle, at_listening, "/commands")); //define bot status

		if (run_once<struct register_bot_commands>()) { //Avoid re-running on-ready declaration everytime that the bots makes a full reconnection
			bytebot.global_command_create(slashcommand("ping", "Pong!", bytebot.me.id));
			bytebot.global_command_create(slashcommand("commands", "Show all my functions!", bytebot.me.id));

		}
		});

	bytebot.start(st_wait);
	return 0;
}