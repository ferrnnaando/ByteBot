#!/bin/bash

g++ main.cpp register/slashcommands/slashcommand_on_ready/slashcommands.cpp register/slashcommands/slashcommand_logger/slashcommand_logger.cpp register/buttons/on_button_click/on_button_click.cpp register/embeds/embed_declarations.cpp register/on_messages/on_messages.cpp -o main -ldpp -I dotenv_library/include/laserpants/dotenv

if [ -x "main" ]; then
echo "Programa compilado. Ya tenía los permisos de ejecución."

else
chmod +x main
echo "Programa compilado. Los permisos de ejecución han sido añadidos durante este proceso ya que no los tenía"

fi
