#pragma once

typedef struct {
	double x, y;
}Position;

enum class State {
	IDLE,
	START,
	PAUSE,
	DONE
};