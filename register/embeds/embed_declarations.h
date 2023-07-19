#pragma once
#include "../../headers/mainheader.h"

dpp::embed blacklist_embed(dpp::interaction& interaction);
dpp::embed bytebot_embed(dpp::interaction& interaction);
dpp::embed commands_embed(dpp::interaction& interaction);
dpp::embed infoservidor(dpp::interaction& interaction, std::string& guild_owner_formatted, std::string& guild_name, std::string& partnered_guild_str, bool& guild_is_partnered, std::string& total_guild_channels, std::string& total_guild_roles, std::string& total_guild_emojis, const std::vector<dpp::snowflake>& channels, const std::vector<dpp::snowflake>& roles, const std::vector<dpp::snowflake>& emojis, const dpp::guild& g, std::string& guild_id, std::string& formatted_date_guild, std::string& guild_description_formatted, std::string& guild_2fa_level);
dpp::embed avatar_embed(dpp::interaction& interaction);
dpp::embed usuario_avatar_embed(dpp::interaction& interaction, dpp::user& avatar);
dpp::embed ban_embed(dpp::interaction& interaction, std::string& member_staff);
