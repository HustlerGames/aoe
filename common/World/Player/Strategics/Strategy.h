#pragma once

#define STRATEGY_STATE_NEED_RESOURCES 1
#define STRATEGY_STATE_IN_PROGRESS 2
#define STRATEGY_STATE_COMPLETED 3


class Strategy {
	int state;
};