#include "user.h"

#include <stdio.h>

using namespace TgBot;

ChessUser::ChessUser() {
	bot = new Bot(TOKEN);
}
