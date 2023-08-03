#include <string>
#include "dpp/dpp.h"

enum flags {
	ephemeral = dpp::m_ephemeral,
	label(std::string text) = dpp::component().set_label(text)
};

const uint64_t ec_default = dpp::colors::pink;
const uint64_t ec_error = dpp::colors::red_blood;
const uint64_t ec_slashcmd_devusage = dpp::colors::green;

const std::string application_id = "1126691771506757713";
const std::string reports_webhook = "https://discord.com/api/webhooks/1129797836255547443/NJimRvFP1yjR5HKbAkczyA07QBcQP-6zEKmen-PimQtyCPQo2rmjrFujrLfjNJ7Gz9sf";
const std::string bot_invite = "https://discord.com/oauth2/authorize?client_id=1126691771506757713&scope=bot&permissions=1099511627767";
const std::string discord_link_inv = "https://discord.gg/bYDhwFFVk5";
const std::string banner_url = "https://i.imgur.com/QN4KH0H.png";
const std::string logo_url = "https://i.imgur.com/pLxW45q.png";

const std::string blacklisted_users[3] = { "", "921516505735262251", "3" };
const std::string blacklisted_servers[1] = { "1130583864818016278"};
const std::string bytebot_developers[1] = { "1068126654368583770"};
const std::string devcommands_prefix = "###";
//const dpp::guild* g = dpp::find_guild(blacklisted_servers[0]);

const std::string description_slashcmd_report = "Envia un mensaje a los desarrolladores, un uso inpropio conlleva la prohibicìón";
const std::string option_slashcmd_report = "Especifica el mensaje que deseas enviar.";

const std::string description_slashcmd_avatar = "Muestra tu foto de perfil.";
const std::string option_slashcmd_avatar = "Usuario del que mostrar su foto de perfil.";

const std::string description_slashcmd_infousuario = "Muestra toda la información a mi disposición sobre un usuario.";
const std::string option_slashcmd_infousuario = "Usuario del que quieras saber mas.";

const std::string description_slashcmd_infoservidor = "Muestra toda la información a mi disposición sobre el servidor en el que se ejecuta el comando";
const std::string option_slashcmd_infoservidor = "Muestra la informacion sobre un servidor en especifico";

const std::string description_slashcmd_banear = "Banea a un usuario del servidor";
const std::string option_slashcmd_banear = "Especifica al usuario que deseas banear.";
const std::string option2_slashcmd_infoservidor = "Especifica un motivo por el que banear al usuario.";

const std::string description_slashcmd_admin = "Comando destinado a los administradores y moderadores de comunidades.";

const std::string description_slashcmd_dev = "Consola para desarolladores de ByteBot";
const std::string option_slashcmd_dev = "Muestra el output";
