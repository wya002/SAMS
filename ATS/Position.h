#pragma once

typedef struct {
	double x, y;
}Position;

enum class State {
	START,
	PAUSE,
	DONE
};