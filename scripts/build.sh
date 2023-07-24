#!/bin/bash

if [ -z "$1" ]; then
    echo "enter a name for the program to be compiled."
else
    g++ main.cpp register/slashcommands/slashcommand_on_ready/slashcommands.cpp register/slashcommands/slashcommand_logger/slashcommand_logger.cpp register/buttons/on_button_click/on_button_click.cpp register/embeds/embed_declarations.cpp register/on_messages/on_messages.cpp -o $1 -ldpp -I dotenv_library/include/laserpants/dotenv

    chmod +x main
    echo "compiled with exec permissions on $1"

fi
