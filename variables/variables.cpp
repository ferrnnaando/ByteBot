#include "../headers/mainheader.h"

const uint64_t ec_default = dpp::colors::pink;
const uint64_t ec_error = dpp::colors::red_blood; //embed color
const std::string reports_webhook = "https://discord.com/api/webhooks/1129797836255547443/NJimRvFP1yjR5HKbAkczyA07QBcQP-6zEKmen-PimQtyCPQo2rmjrFujrLfjNJ7Gz9sf";
const std::string bot_invite = "https://discord.com/oauth2/authorize?client_id=1126691771506757713&scope=bot&permissions=1099511627767";
const std::string discord_link_inv = "https://discord.gg/bYDhwFFVk5";
const std::string banner_url = "https://i.imgur.com/QN4KH0H.png";
const std::string logo_url = "https://i.imgur.com/pLxW45q.png";
const std::string blacklisted_users[3] = { "", "921516505735262251", "3" };
const std::string blacklisted_servers[1] = { "1130583864818016278"};
const dpp::guild* g = dpp::find_guild(blacklisted_servers[0]);

enum flags {
	ephemeral = dpp::m_ephemeral
};

//###########################################################################################################################################################################

const std::string option_usuario_slashcmd_report = "Envia un mensaje a los desarrolladores, un uso inpropio conlleva la prohibicìón";
const std::string description_slashcmd_report = "Envia un mensaje de error o queja de forma directa al desarrollador de ByteBot";

const std::string description_slashcmd_ban = "Banea a un usuario del servidor";
const std::string option_usuario_slashcmd_ban = "Banea a un usuario del servidor";

const std::string description_slashcmd_avatar = "Usuario del que mostrar su foto de perfil.";
const std::string option_usuario_slashcmd_avatar = "Muestra la foto de perfil de alguien.";

const std::string description_slashcmd_infousuario = "Muestra toda la información a mi disposición sobre un usuario.";
const std::string option_slashcmd_infousuario = "Usuario del que quieras saber mas.";

const std::string description_slashcmd_infoservidor = "Muestra toda la información a mi disposición sobre el servidor en el que se ejecuta el comando";
