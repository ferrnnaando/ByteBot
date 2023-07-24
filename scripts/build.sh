#!/bin/bash

g++ main.cpp register/slashcommands/slashcommand_on_ready/slashcommands.cpp register/slashcommands/slashcommand_logger/slashcommand_logger.cpp register/buttons/on_button_click/on_button_click.cpp register/embeds/embed_declarations.cpp register/on_messages/on_messages.cpp -o main -ldpp -I dotenv_library/include/laserpants/dotenv

chmod +x main
echo "compiled"
