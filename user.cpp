#include "user.h"

#include <stdio.h>

using namespace TgBot;

ChessUser::ChessUser() {
	bot = new Bot(TOKEN);

	bot->getEvents().onCommand("start", [this](Message::Ptr msg) {
		bot->getApi().sendMessage(msg->chat->id, "Hi!");
	});
}
