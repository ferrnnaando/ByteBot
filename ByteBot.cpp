#include "header.h"
#pragma warning(disable : 4996)

using namespace dpp; //testing
using namespace std;

const uint64_t ec_default = colors::pink;
const uint64_t ec_error = colors::red_blood; //embed color
const string discord_link_inv = "https://discord.gg/bYDhwFFVk5";
const string blacklisted_users[3] = { "122222", "921516505735262251", "3" };

int main() {
	//Create bot cluster
	cluster bytebot(BOT_TOKEN, i_default_intents | i_message_content);

	//Output log information
	bytebot.on_log(utility::cout_logger());




	//Handler for slash commands
	bytebot.on_slashcommand([&bytebot](const slashcommand_t& event) { //DO find arrays with find and end.
		dpp::interaction interaction = event.command;
		dpp::command_interaction cmd_data = interaction.get_command_interaction();
		auto subcommand = cmd_data;

		if (event.command.usr.id == blacklisted_users[0] || event.command.usr.id == blacklisted_users[1]) {
			const embed embed_blacklisted = embed()
				.set_color(ec_error)
				.set_author(" ByteBot", discord_link_inv, "https://i.imgur.com/U95zuYh.png")
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
			else if (interaction.get_command_name() == "commands") {
				const embed embed_commands = embed()
					.set_color(ec_default)
					.set_author(" ByteBot", discord_link_inv, "https://i.imgur.com/U95zuYh.png")
					.set_description("`/commands` | **¡Hola! Maybe you know me, maybe not. Anyway, Im here to help you making discord a chiller place. My commands are sub-divided into categories**");

				event.reply(message(event.command.get_channel().id, embed_commands));
				//event.reply(message(event.command.get_channel().id, embed_commands).set_reference(event.command.msg.id));
				 

			}
			else if (interaction.get_command_name() == "userinfo") {
				auto subcommand = cmd_data;
				
				dpp::user user = interaction.get_resolved_user(subcommand.get_value<dpp::snowflake>(0));

				std::string has_rejoined_str, activeDeveloperBadge_str, haveDiscordNitro_str, isBot_str, isCertifiedModerator_str, isDiscordEmployee_str, isEarlySupporter_str, hypesquad_str, bughunter_str, mfa_str, partnered_str, verifiedacc_str, verifiedbot_str, earlybotdev_str;
				const auto activeDeveloperBadge = user.is_active_developer();

				const auto haveDiscordNitroB = user.has_nitro_basic();
				const auto haveDiscordNitroC = user.has_nitro_classic();
				const auto haveDiscordNitroF = user.has_nitro_full();

				const auto isEarlySupporter = user.is_early_supporter();

				const auto isHouseBrilliance = user.is_house_brilliance();
				const auto isHouseBravery = user.is_house_bravery();
				const auto isHouseBalance = user.is_house_balance();

				const auto isCertifiedModerator = user.is_certified_moderator();
				const auto isDiscordEmployee = user.is_discord_employee();
				const auto isBugHunterLv1 = user.is_bughunter_1();
				const auto isBugHunterLv2 = user.is_bughunter_2();
				const auto createTime = user.get_creation_time();

				const auto isearlybotdev2 = user.is_verified_bot_dev();
				const auto isVerifiedAcc = user.is_verified();
				const auto isVerifiedBot = user.is_verified_bot();
				const auto isPartnered = user.is_partnered_owner();
				const auto mfaEnabled = user.is_mfa_enabled();
				const auto isBot = user.is_bot();
		//		const auto nickname = interaction.usr.nickname;

				switch (activeDeveloperBadge) {
				case 0 || false:
					activeDeveloperBadge_str = "<a:no2:1127991706156015626>";
					break;

				case 1 || true:
					activeDeveloperBadge_str = "<:yes:1127991707863093359>";
					break;

				default:
					break;
				}

				switch (haveDiscordNitroB) {
				case 0 || false:
					haveDiscordNitro_str = "<a:no2:1127991706156015626>";
					if (haveDiscordNitroC) {
						haveDiscordNitro_str += ", <:yes:1127991707863093359> *(Discord Classic)*";
					}

					if (haveDiscordNitroF) {
						haveDiscordNitro_str += ", <:yes:1127991707863093359> *(Discord Full)*";
					}
					break;

				case 1 || true:
					haveDiscordNitro_str = "<:yes:1127991707863093359> *(Discord Basic)*";
					if (haveDiscordNitroC) {
						haveDiscordNitro_str += ", <:yes:1127991707863093359> *(Discord Classic)*";
					}

					if (haveDiscordNitroF) {
						haveDiscordNitro_str += ", <:yes:1127991707863093359> *(Discord Classic)*";
					}
					break;

				default:
					break;
				}

				switch (isBot) {
				case 0 || false:
					isBot_str = "<a:no2:1127991706156015626>";
					break;

				case 1 || true:
					isBot_str = "<:yes:1127991707863093359>";
					break;

				default:
					break;
				}

				switch (isCertifiedModerator) {
				case 0 || false:
					isCertifiedModerator_str = "<a:no2:1127991706156015626>";
					break;

				case 1 || true:
					isCertifiedModerator_str = "<:yes:1127991707863093359>";
					break;

				default:
					break;
				}

				switch (isDiscordEmployee) {
						case 0 || false:
							isDiscordEmployee_str = "<a:no2:1127991706156015626>";
							break;

						case 1 || true:
							isDiscordEmployee_str = "<:yes:1127991707863093359>";
							break;

						default:
							break;

						}

						switch (isEarlySupporter) {
						case 0 || false:
							isEarlySupporter_str = "<a:no2:1127991706156015626>";
							break;

						case 1 || true:
							isEarlySupporter_str = "<:yes:1127991707863093359>";
							break;

						default:
							break;

						}


						if (isHouseBalance) {
							hypesquad_str = "<:hypebalance:1128026294253269134> *(House Balance)*";

						}
						else if (isHouseBravery) {
							hypesquad_str = "<:hypebravery:1128026297860366476> *(House Bravery)*";

						}
						else if (isHouseBrilliance) {
							hypesquad_str = "<:hypebrilliance:1128026299781349416> *(House Brilliance)*";

						}
						else {
							hypesquad_str = "<a:no2:1127991706156015626>";

						}



						if (isBugHunterLv1) {
							bughunter_str = "<:bughunter:1128027090915180707> *(Lv1)*";

						}
						else if (isBugHunterLv2) {
							bughunter_str = "<:bughunter2:1128027094203519057> *(Lv2)*";

						}
						else {
							bughunter_str = "<a:no2:1127991706156015626>";

						}

						switch (mfaEnabled) {
						case 0 || false:
							mfa_str = "<a:no2:1127991706156015626>";
							break;

						case 1 || true:
							mfa_str = "<:yes:1127991707863093359>";
							break;

						default:
							break;

						}

						switch (isPartnered) {
						case 0 || false:
							partnered_str = "<a:no2:1127991706156015626>";
							break;

						case 1 || true:
							partnered_str = "<:yes:1127991707863093359>";
							break;

						default:
							break;

						}

						switch (isVerifiedAcc) {
						case 0 || false:
							verifiedacc_str = "<a:no2:1127991706156015626>";
							break;

						case 1 || true:
							verifiedacc_str = "<:yes:1127991707863093359>";
							break;

						default:
							break;

						}

						switch (isearlybotdev2) {
						case 0 || false:
							earlybotdev_str = "<a:no2:1127991706156015626>";
							break;

						case 1 || true:
							earlybotdev_str = "<:yes:1127991707863093359>";
							break;

						default:
							break;

						}

						switch (isVerifiedBot) {
						case 0 || false:
							verifiedbot_str = "<a:no2:1127991706156015626>";
							break;

						case 1 || true:
							verifiedbot_str = "<:yes:1127991707863093359>";
							break;

						default:
							break;

						}

						/*switch (have_nickname) {
							case 0 || false:
								has_rejoined_str = "<a:no2:1127991706156015626>";
								break;

							case 1 || true:
								has_rejoined_str = "<:yes:1127991707863093359>";
								break;

							default:
								break;

						}*/

						const embed embed_userinfo = embed()
							.set_color(ec_default)
							.set_thumbnail(user.get_avatar_url())
							.set_author("Información del usuario " + user.username, discord_link_inv, user.get_avatar_url())
							.add_field("<:active_developer:1127568563176222760> | ¿Es un desarrollador activo?", activeDeveloperBadge_str, true)
							.add_field("<a:nitro:1127997712009273434> | ¿Tiene discord nitro?", haveDiscordNitro_str, true)
							.add_field("<a:hypesquad34:1128024167472697374> | HpyeSquad", hypesquad_str, true)
							.add_field("<:earlysupporter:1128019763797434409> | ¿Es early supporter?", isEarlySupporter_str, true)
							.add_field("<:certifiedmod:1128014727277183026> | ¿Es moderador certificado de Discord?", isCertifiedModerator_str, true)
							.add_field("<:discordemployee:1128018688822485012> | ¿Es empleado de Discord?", isDiscordEmployee_str, true)
							.add_field("<:bot:1127621337700122745> | ¿Es un bot?", isBot_str, true)
							.add_field("<:verifiedbot:1128901397002321931> | ¿Es un bot verificado?", verifiedbot_str, true)
							.add_field("<:earlybotdev:1128903773662752849> | ¿Es un desarrollador de Discord certificado?", earlybotdev_str, true)
							.add_field("<:bughunter:1128027090915180707> | ¿Es un bug hunter de Discord?", bughunter_str, true)
							.add_field("<:2fa:1128034931365400617> | ¿Tiene la seguridad 2fa?", mfa_str, true)
							.add_field("<:partnered:1128896026363834438> | ¿Es partner?", partnered_str, true)
							.add_field("<:verified:1128898205418000444> | ¿Es una cuenta verificada?", verifiedacc_str, true)
							.add_field("<:clock_timestamp:1128052428688867370> | Cuenta creada el", "*Pronto...*", true)
							//.add_field("<:joinedat:1129010450638590024> | Se unió al servidor el", "a", true)
							.add_field("<:joinedat:1129010450638590024> | ¿Ha hecho rejoin?", "aa", true)
							.set_footer(embed_footer().set_text(discord_link_inv + " || " + utility::current_date_time()));

						std::cout << "[" + utility::current_date_time() + "] - " << interaction.usr.username << " || Slashcommand /" << interaction.get_command_name() << " ejecutado." << std::endl;
						event.reply(message(interaction.get_channel().id, embed_userinfo).set_flags(m_ephemeral));	

			}
			else if (interaction.get_command_name() == "serverinfo") {

				const auto guild_id = interaction.guild_id;
				const double guild_created_at = interaction.guild_id.get_creation_time();
				//const auto server_owner = guild::owner_id;
			//	const auto is_partnered3 = interaction.get_guild(interaction.guild.gk);

				const std::string info_str = "**" + std::to_string(get_channel_count()) + "** *canales*, " + " **" + std::to_string(get_role_count()) + "** *roles*,  **" + std::to_string(get_emoji_count()) + "** *emojis*, **" + std::to_string(get_user_count()) + "** *usuarios*.";

				std::chrono::time_point<std::chrono::system_clock> start_time = std::chrono::system_clock::from_time_t(1420070400);
				std::chrono::duration<double> duration(guild_created_at);
				start_time += std::chrono::duration_cast<std::chrono::system_clock::duration>(duration);
				std::time_t timestamp = std::chrono::system_clock::to_time_t(start_time);
				std::stringstream ss;
				ss << std::put_time(std::gmtime(&timestamp), "%Y-%m-%d %H:%M:%S");
				std::string timestamp_str = ss.str();

				const embed embed_serverinfo = embed()
					.set_color(ec_default)
					.add_field("<:nofaceid:1129006938773016666> | ID del servidor", std::to_string(guild_id), true)
					.add_field("<:clock_timestamp:1128052428688867370> | Creado el", timestamp_str, true)
					.add_field("<:channel:1129045509059903558> | Informacion general", info_str, true)
					//.add_field(" | Dueño ", , true)
					//.set_image()
					.set_footer(embed_footer().set_text(discord_link_inv + " || " + utility::current_date_time()));

				std::cout << "[" + utility::current_date_time() + "] - " << interaction.usr.username << " || Slashcommand /" << interaction.get_command_name() << " ejecutado." << std::endl;
				event.reply(message(interaction.get_channel().id, embed_serverinfo).set_flags(m_ephemeral));

		  }
		  else if (interaction.get_command_name() == "avatar") {	
				dpp::user avatar = interaction.get_resolved_user(subcommand.get_value<dpp::snowflake>(0));

				const embed embed_avatar = embed()
					.set_color(ec_default)
					.set_image(avatar.get_avatar_url());

				std::cout << "[" + utility::current_date_time() + "] - " << interaction.usr.username << " || Slashcommand /" << interaction.get_command_name() << " ejecutado." << std::endl;
				event.reply(message(interaction.get_channel().id, embed_avatar).set_flags(m_ephemeral));

			}
		  else if (interaction.get_command_name() == "report") {
			  std::string report_str = std::get <std::string>(event.get_parameter("mensaje"));

			  std::cout << "[" + utility::current_date_time() + "] - " << interaction.usr.username << " || Slashcommand /" << interaction.get_command_name() << " ejecutado." << std::endl;
			  event.reply(report_str);
			  //event.reply(message("aa").set_flags(m_ephemeral));
			}
		}
		});

		//Register slash commands
		bytebot.on_ready([&bytebot](const ready_t& event) {
			bytebot.set_presence(presence(ps_idle, at_listening, "/commands en " + std::to_string(get_guild_count()))); //define bot status

			if (run_once<struct register_bot_commands>()) { //Avoid re-running on-ready declaration everytime that the bots makes a full reconnection
				
				//########################################################################################################################

				dpp::slashcommand userinfo("userinfo", "Muestra toda la información a mi disposición sobre un usuario.", bytebot.me.id);
				userinfo.add_option(command_option(co_user, "usuario", "Usuario del que quieras saber mas.", true));

				slashcommand serverinfo("serverinfo", "Muestra toda la información a mi disposición sobre el servidor en el que se ejecuta el comando", bytebot.me.id);

				slashcommand avatar("avatar", "Muestra la foto de perfil de alguien.", bytebot.me.id);
				avatar.add_option(command_option(co_user, "usuario", "Usuario del que mostrar su foto de perfil.", true));

				//########################################################################################################################

				slashcommand report("report", "Envia un mensaje de error o queja de forma directa al desarrollador de ByteBot", bytebot.me.id);
				report.add_option(command_option(co_string, "mensaje", "Envia un mensaje a los desarrolladores. Un uso inpropio conlleva la prohibicìón.", true));

				//main slashcmd
				bytebot.global_command_create(slashcommand("commands", "¡Muestra de lo que soy capaz!", bytebot.me.id));

				//utilitties (just will be displayed for oneself)
				bytebot.global_command_create(userinfo);
				bytebot.global_command_create(serverinfo);
				bytebot.global_command_create(avatar);
				
				//others (not will be displayed for another thats not herslf)
				bytebot.global_command_create(report);
				


			}
		});


	bytebot.start(st_wait);
	return 0;
}
