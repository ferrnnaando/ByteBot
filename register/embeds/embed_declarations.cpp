#include "embed_declarations.h"

#ifdef __linux__

	#include <cstdio>
	#include <memory>
	#include <stdexcept>
	#include <sys/sysinfo.h>
	#include <sys/statvfs.h>
	#include <iomanip>

	struct system_info {
		std::string model_name; //cpu
		std::string cores; //cpu
		std::string gpu_info; //gpu
		double ram_total; //ram
		double ram_used; //ram
		double ram_percent; //ram
		long ram_total_literal; //ram
		long memav_value; //ram
		std::string os_name; //os info
		std::string os_model = "Linux"; //os info
		std::string disk_usage; //disk info
		std::string network_usage; //network info

		bool found_cpu, found_gpu, found_ram, found_os;
	};

	struct statvfs buffer;

	double calculateCpuUsage(unsigned long long& prevIdle, unsigned long long& prevTotal) {
		std::ifstream statFile("/proc/stat");
		std::string line4;
		unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;

		if (std::getline(statFile, line4)) {
			std::istringstream iss(line4);
			std::string cpuLabel;
			iss >> cpuLabel >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
		}

		unsigned long long total = user + nice + system + idle + iowait + irq + softirq + steal;
		unsigned long long totalDiff = total - prevTotal;
		unsigned long long idleDiff = idle - prevIdle;
		double cpu_usage = (totalDiff > 0) ? (1.0 - static_cast<double>(idleDiff) / totalDiff) * 100.0 : 0.0;
		prevTotal = total;
		prevIdle = idle;

    return cpu_usage;
}
	
	#elif _WIN32
		struct system_info std::string os_model = "Windows";
#endif

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

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
			
			const dpp::embed embed_bytebot = dpp::embed()
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
			const dpp::embed embed_commands = dpp::embed()
				.set_color(ec_default)
				.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
				.set_description("`/commands` | **¡Hola! Maybe you know me, maybe not. Anyway, Im here to help you making discord a chiller place. My commands are sub-divided into categories**")
				;

			return embed_commands;
		}

		dpp::embed infousuario(dpp::user& user, dpp::interaction& interaction, std::string& is_active_developer_str, std::string& have_nitro, std::string& is_bot_verified_str, std::string& hypesquad_str ,std::string& username, std::string& username_avatar_formatted, std::string& username_discriminator, std::string& user_id_formatted, std::string& formatted_date_user)
		{
			dpp::embed embed_infousuario = dpp::embed()
				.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
				.set_color(ec_default)
				.add_field("<:member:1129180523407884368> Nombre de usuario", username, false)
				;

				if (user.is_bot()) {
					embed_infousuario.add_field("<:slashcmd:1129193506787840091> Es un bot", "```Sí.```", true);
					embed_infousuario.add_field("<:slashcmd:1129193506787840091> Bot verificado", is_bot_verified_str, true);
					embed_infousuario.add_field("<:idlog:1129209889739251813> ID", user_id_formatted, true);
					embed_infousuario.add_field("<:joined:1129241382930894859> Se unió a discord el", formatted_date_user, true);
					embed_infousuario.add_field("<:preview:1129409265715642399> Avatar", username_avatar_formatted, false);
					
					return embed_infousuario;
				} 
				else {
					embed_infousuario.add_field("<:active_developer:1127568563176222760> Desarrollador activo", is_active_developer_str, true);
					embed_infousuario.add_field("<:nitroc:1129193504527110166> Tiene nitro", have_nitro, true);
					embed_infousuario.add_field("<:hypesquadevents:1129203280216600638> HypeSquad", hypesquad_str, true);
					embed_infousuario.add_field("<:idlog:1129209889739251813> ID", user_id_formatted, true);
					embed_infousuario.add_field("<:joined:1129241382930894859> Se unió a discord el", formatted_date_user, true);
					embed_infousuario.add_field("<:preview:1129409265715642399> Avatar", username_avatar_formatted, false);

					return embed_infousuario;
				}
			}

		dpp::embed infoservidor(dpp::interaction& interaction, std::string& guild_owner_formatted, std::string& guild_name, std::string& partnered_guild_str, bool& guild_is_partnered, std::string& total_guild_channels, std::string& total_guild_roles, std::string& total_guild_emojis, 
		const std::vector<dpp::snowflake>& channels, const std::vector<dpp::snowflake>& roles, const std::vector<dpp::snowflake>& emojis, const dpp::guild& g, std::string& guild_id, std::string& formatted_date_guild, std::string& guild_description_formatted, std::string& guild_2fa_level)
		{
			if (!g.description.empty()) {
				const dpp::embed embed_infoservidor = dpp::embed()
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
				const dpp::embed embed_infoservidor = dpp::embed()
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

		dpp::embed avatar_embed(dpp::interaction& interaction, dpp::user& avatar)
		{
			const dpp::embed embed_avatar = dpp::embed()
				.set_author(interaction.get_guild().name, discord_link_inv, interaction.get_guild().get_icon_url())
				.set_color(ec_default)
				.set_image(avatar.get_avatar_url(1024))
				;

			return embed_avatar;
		}

		dpp::embed dev_usage_embed(dpp::cluster& bytebot, dpp::interaction& interaction)
		{

			system_info cpu;
			system_info gpu;
			system_info ram;
			system_info os;
			system_info disk;
			system_info network;
			std::string line, line2, line3;

			
			std::string info_cpu;
			std::string info_gpu;
			std::string info_os;
			std::string info_ram;
			std::string ram_usage;
			std::string formated_consum;
			std::string formated_bot_status;
			std::string status_title;
			std::string formated_disk_usage;
			std::string formated_network_usage;

			std::ifstream cpuinfo("/proc/cpuinfo");
			
			cpu.found_cpu = false;

			while (std::getline(cpuinfo, line)) {
				size_t delimiter_pos = line.find(':');

				if (line.find("model name") != std::string::npos) {
					if (delimiter_pos != std::string::npos) {
						cpu.model_name = line.substr(delimiter_pos + 2); // Skip ": "	
						cpu.found_cpu = true;
					}
				} else if(line.find("cpu cores") != std::string::npos) { //what is npos 
						if(delimiter_pos != std::string::npos) {
							cpu.cores = line.substr(delimiter_pos + 2);
						}
					}
			}

			std::ifstream ram_info("/proc/meminfo");
			ram.found_ram = false;

			while(std::getline(ram_info, line2)) {
   			 size_t delimiter_pos = line2.find(':');

			if (line2.find("MemTotal") != std::string::npos) {
				if (delimiter_pos != std::string::npos) {
					ram.found_ram = true;
					std::istringstream iss(line2);
					std::string memtotal_identifier;
					long memtotal_value;

					iss >> memtotal_identifier >> memtotal_value;
					ram.ram_total_literal = memtotal_value;

					if (memtotal_value > 1000000) {
						 double value_gb = static_cast<double>(memtotal_value) / (1024.0 * 1024.0);
						ram.ram_total = value_gb;
					} else {
						double value_mb = static_cast<double>(memtotal_value) / 1024.0;
						ram.ram_total = value_mb;
					}
				}
			} else if (line2.find("MemFree") != std::string::npos) {
				if (delimiter_pos != std::string::npos) {
					std::istringstream iss(line2);
					std::string memfree_identifier;
					double memfree_value;

					iss >> memfree_identifier >> memfree_value;
					double memused_identifier = ram.ram_total_literal - memfree_value;

					if (memused_identifier > 1000000) {
						double total = static_cast<double>(memused_identifier) / (1024.0 * 1024.0);
						ram.ram_used = total;
					} else {
						double total = static_cast<double>(memused_identifier) / 1024.0;
						ram.ram_used = total;
					}
				}
			} else if (line2.find("MemAvailable") != std::string::npos) {
				if (delimiter_pos != std::string::npos) {
					std::istringstream iss(line2);
					std::string memav_identifier;
					long memav_value;

					iss >> memav_identifier >> memav_value;

					double memused_identifier = ram.ram_total_literal - memav_value;
					ram.ram_percent = (memused_identifier / ram.ram_total_literal) * 100.0;
					//ram.ram_percent = ram_percent;
					//if(ram.ram_percent)
				}
			}
		}

		std::ifstream osname("/etc/os-release");
		os.found_os = false;

		//if(osname.is_open()) {
			while(std::getline(osname, line3)) {
				size_t pos;
				while ((pos = line.find("\"")) != std::string::npos) {
					line.erase(pos, 1);
       			}

				if(line3.find("PRETTY_NAME") != std::string::npos) {
					bool found_os_name = true;
					std::string delimiter = "=";
					size_t delimiter_pos = line3.find(delimiter);
					if (delimiter_pos != std::string::npos) {
						std::string os_name = line3.substr(delimiter_pos + delimiter.length());
						size_t start_pos = os_name.find_first_not_of(" \"");
						size_t end_pos = os_name.find_last_not_of(" \"");
						if (start_pos != std::string::npos && end_pos != std::string::npos) {
							os_name = os_name.substr(start_pos, end_pos - start_pos + 1);
						}

                os.os_name = os_name;
            }
        }
    }
		os.found_os = true;

		gpu.gpu_info = exec("lspci | grep -E 'VGA|3D'");

		if(cpu.found_cpu) { //is this a good way to check true or is better a cpu.found_cpu
			info_cpu = "```Modelo: " + cpu.model_name + " || Núcleos: " + cpu.cores + " ```";
		} else {
			info_cpu = "```Se está ejecutando en un sistema operativo no preparado para esta función.```";
		}

		if(!gpu.gpu_info.empty()) {
			info_gpu = "```" + gpu.gpu_info + "```";
		} else {
			info_gpu = "```Se está ejecutando en un sistema operativo no preparado para esta función.```";
		}

		if(ram.found_ram)  {
			std::ostringstream ram_percentStream, ram_usedStream, ram_totalStream;
			ram_percentStream << std::fixed << std::setprecision(2) << ram.ram_percent;
			ram_usedStream << std::fixed << std::setprecision(2) << ram.ram_used;
			ram_totalStream << std::fixed << std::setprecision(2) << ram.ram_total;

			ram_usage = ram_percentStream.str() + "% [" + ram_usedStream.str() + " / " + ram_totalStream.str() + " GB]"; //should add dynamic memory value
		} else {
			ram_usage = "Se está ejecutando en un sistema operativo no preparado para esta función.";
		}
		if(os.found_os) {
			info_os = "```" + os.os_model + " || " + os.os_name + "```";
		} else {
			info_os = "```Se está ejecutando en un sistema operativo no preparado para esta función.```";
		}

		unsigned long long prevIdle = 0;
		unsigned long long prevTotal = 0;
		double cpuUsage = calculateCpuUsage(prevIdle, prevTotal);
		std::ostringstream cpuStream;
		cpuStream << std::fixed << std::setprecision(2) << cpuUsage;

		formated_consum = "```CPU: " + cpuStream.str() + "% \nRAM: " + ram_usage + " ```";

		if(cpuUsage < 50) {
			status_title = "<:greendot:1129182356046094367> Estado";
			formated_bot_status = "```Eficiente.```";
		} 
		else if(cpuUsage > 50) {
			status_title = "<:yellowdot:1136657266964189236> Estado";
			formated_bot_status = "```Carga moderada.```";
		} 
		else if(cpuUsage > 70) {
			status_title = "<:greendot:1136657264615366686> Estado";
			formated_bot_status = "```Carga alta.```";
		} 
		else if(cpuUsage > 90) {
			status_title = "<:reddot:1136657261708705815> Estado";
			formated_bot_status = " ```Sobrecarga / carga excesiva.```";
		} else {
			status_title = "<a:statuscharge:1136657270332199073> Estado";
			formated_bot_status = " ```No reconocido.```";
		}
	
		disk.disk_usage = exec("df -h /");
		formated_disk_usage = "```" + disk.disk_usage + "```";

		network.network_usage = exec("ip -4 addr show $(ip -4 route get 8.8.8.8 | awk '{print $5}')");
		formated_network_usage = "```" + network.network_usage + "```";

		dpp::embed dev_usage_embed = dpp::embed()
			.set_color(ec_slashcmd_devusage)
			.set_author(interaction.get_guild().name, bot_invite, interaction.get_guild().get_icon_url())
			.add_field("<:good_wifi:1136678307799240774> Red", formated_network_usage, false)
			.add_field("<:isofile:1136667867870396447> Particiones", formated_disk_usage, false)
			.add_field("<:nvidia:1136047715483132084> Informacion de la GPU", info_gpu, false)
			.add_field("<:intel:1136064422801068135> Informacion del procesador", info_cpu, true)
			.add_field("<:infopng:1136304396536402061> Informacion del sistema", info_os, true)
			.add_field("", "", false)
			.add_field(status_title, formated_bot_status, true)
			.add_field("<:ram:1136066444468179024> Consumo", formated_consum, true)
			
			;

		return dev_usage_embed;
		}