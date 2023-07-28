#!/bin/bash

if [ -z "$1" ]; then
    echo "enter a name for the program to be compiled."
else
    if [ -e $1 ]; then
    echo "A $1 file already exists, deleting it..."
    rm $1
    else
        g++ -std=c++17 main.cpp register/slashcommands/slashcommand_on_ready/slashcommands.cpp register/buttons/on_button_click/on_button_click.cpp register/embeds/embed_declarations.cpp register/on_messages/on_messages.cpp -o $1 -ldpp -I dotenv_library/include/laserpants/dotenv

        chmod +x main
        echo "compiled with exec permissions on $1"
        ./$1
    fi
    g++ -std=c++17 main.cpp register/slashcommands/slashcommand_on_ready/slashcommands.cpp register/buttons/on_button_click/on_button_click.cpp register/embeds/embed_declarations.cpp register/on_messages/on_messages.cpp -o $1 -ldpp -I dotenv_library/include/laserpants/dotenv

    chmod +x main
    echo "compiled with exec permissions on $1"
    ./$1
fi