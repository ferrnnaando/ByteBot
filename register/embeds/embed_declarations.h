#pragma once
#include "../../headers/mainheader.h"

		dpp::embed bytebot_embed(dpp::interaction& interaction);
		dpp::embed commands_embed(dpp::interaction& interaction);
		dpp::embed blacklist_embed(dpp::interaction& interaction);
		dpp::embed ban_embed(dpp::interaction& interaction, std::string& member_staff);
		dpp::embed avatar_embed(dpp::interaction& interaction, dpp::user& avatar);
		dpp::embed infoservidor(dpp::interaction& interaction, std::string& guild_owner_formatted, std::string& guild_name, std::string& partnered_guild_str, bool& guild_is_partnered, std::string& total_guild_channels, std::string& total_guild_roles, std::string& total_guild_emojis,  const std::vector<dpp::snowflake>& channels, const std::vector<dpp::snowflake>& roles, const std::vector<dpp::snowflake>& emojis, const dpp::guild& g, std::string& guild_id, std::string& formatted_date_guild, std::string& guild_description_formatted, std::string& guild_2fa_level);
		dpp::embed infousuario(dpp::user& user, dpp::interaction& interaction, std::string& is_active_developer_str, std::string& have_nitro, std::string& is_bot_verified_str, std::string& hypesquad_str ,std::string& username, std::string& username_avatar_formatted, std::string& username_discriminator, std::string& user_id_formatted, std::string& formatted_date_user);
