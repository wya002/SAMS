#include <cmath>
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <functional>

using namespace std;
using namespace chrono;

struct Point
{
	double x;
	double y;
};

struct RelativePoint
{
	double radian;
	double distance;
};

class Coordinate
{
public:
	double GetDistanceFromPoints(Point start, Point end)
	{
		return sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
	}

	double GetAngleFromPoints(Point start, Point end)
	{
		return atan2(end.y - start.y, end.x - start.x);
	}

	Point GetPointFromAngleAndDistance(RelativePoint relativePoint)
	{
		Point point = {};
		point.x = relativePoint.distance * cos(relativePoint.radian);
		point.y = relativePoint.distance * sin(relativePoint.radian);

		return point;
	}
};

class AircraftUnit
{
public:
	AircraftUnit(Point startPosition, Point endPosition, double speedPerSecond)
		: startPosition(startPosition), endPosition(endPosition), speedPerSecond(speedPerSecond), currentPosition(startPosition) {}

	Point UpdatePosition(int timeByMilliSeconds)
	{
		Point movingPosition = GetMovingPosition(timeByMilliSeconds);
		currentPosition.x += movingPosition.x;
		currentPosition.y += movingPosition.y;

		if (IsArrival())
		{
			currentPosition = endPosition;
		}

		return currentPosition;
	}

private:
	Point GetMovingPosition(int timeByMilliSeconds)
	{
		Coordinate coordinate;
		RelativePoint currentRelativePoint = {};
		currentRelativePoint.radian = coordinate.GetAngleFromPoints(startPosition, endPosition);
		currentRelativePoint.distance = speedPerSecond * timeByMilliSeconds;

		return coordinate.GetPointFromAngleAndDistance(currentRelativePoint);
	}

	bool IsArrival()
	{
		Coordinate coordinate;
		double distanceFromStartPositionToEndPosition = coordinate.GetDistanceFromPoints(startPosition, endPosition);
		double distanceFromStartPositionToCurrentPosition = coordinate.GetDistanceFromPoints(startPosition, currentPosition);

		return distanceFromStartPositionToEndPosition < distanceFromStartPositionToCurrentPosition;
	}

	Point startPosition;
	Point endPosition;
	double speedPerSecond;
	Point currentPosition;
};

class AircraftSimulator
{
public:
	void StartSimulator(Point startPosition, Point endPosition, double speedPerSecond, int timeByMilliSeconds, bool isHighResolution, function<void(Point point)> callback)
	{
		cout << "Simulation : Start!" << endl << endl;
		AircraftUnit aircraftUnit(startPosition, endPosition, speedPerSecond);
		isStarted.store(true);
		if (isHighResolution)
		{
			simulationThread = thread(&AircraftSimulator::RunHighResolution, this, aircraftUnit, timeByMilliSeconds, callback);
		}
		else
		{
			simulationThread = thread(&AircraftSimulator::RunLowResolution, this, aircraftUnit, timeByMilliSeconds, callback);
		}
	}

	void RunHighResolution(AircraftUnit aircraftUnit, int timeByMilliSeconds, function<void(Point point)> callback)
	{
		auto startTime = high_resolution_clock::now();
		auto localStartTime = high_resolution_clock::now();
		while (isStarted.load())
		{
			Point point = aircraftUnit.UpdatePosition(timeByMilliSeconds);
			auto localEndTime = high_resolution_clock::now();
			this_thread::sleep_for(milliseconds(timeByMilliSeconds - 50) - duration_cast<microseconds>(localEndTime - localStartTime));
			while (milliseconds(timeByMilliSeconds) > duration_cast<microseconds>(localEndTime - localStartTime))
			{
				localEndTime = high_resolution_clock::now();
			}

			localStartTime = high_resolution_clock::now();
			auto endTime = high_resolution_clock::now();
			callback(point);

			cout << "sending time: " << duration_cast<milliseconds>(endTime - startTime).count() << " ms" << endl << endl;
		}
	}

	void RunLowResolution(AircraftUnit aircraftUnit, int timeByMilliSeconds, function<void(Point point)> callback)
	{
		auto startTime = high_resolution_clock::now();
		while (isStarted.load())
		{
			Point point = aircraftUnit.UpdatePosition(timeByMilliSeconds);
			this_thread::sleep_for(milliseconds(timeByMilliSeconds));
			auto endTime = high_resolution_clock::now();
			callback(point);
			cout << "sending time: " << duration_cast<milliseconds>(endTime - startTime).count() << " ms" << endl << endl;
		}
	}

	void StopSimulator()
	{
		isStarted.store(false);

		if (simulationThread.joinable())
		{
			simulationThread.join();
		}

		cout << "Simulation : Stop!" << endl << endl;
	}

	void ShootDownSimulator()
	{
		isStarted.store(false);
		if (simulationThread.joinable())
		{
			simulationThread.join();
		}

		cout << "Simulation : Shoot Down!" << endl << endl;
	}

private:
	thread simulationThread;
	atomic<bool> isStarted;
};

enum class State
{
	None, START, STOP, SHOOTDOWN
};

class Network
{
public:
	void Send(Point point)
	{
		cout << "Network -Send(): " << "x: " << point.x << ", y: " << point.y << endl;
	}

	State Receive()
	{
		static int count = 0;
		this_thread::sleep_for(3s);
		count++;
		if (count % 5 == 1)
		{
			return State::START;
		}
		else if (count % 5 == 2)
		{
			return State::STOP;
		}
		else if (count % 5 == 3)
		{
			return State::START;
		}
		else if (count % 5 == 4)
		{
			return State::SHOOTDOWN;
		}
		else if (count % 5 == 0)
		{
			return State::STOP;
		}
		else
		{
			return State::None;
		}
	}
};

class SimulatorController
{
public:
	void Start()
	{
		Point startPosition = { 10.0, 20.0 };
		Point endPosition = { 40.0, 60.0 };
		double speedPerSecond = 5;
		int updatePeriodByMilliSeconds = 1000;
		bool isHighResolution = true;
		aircraftSimulator.StartSimulator(startPosition, endPosition, speedPerSecond, updatePeriodByMilliSeconds,
			isHighResolution, bind(&Network::Send, &network, placeholders::_1));
	}
	void Stop()
	{
		aircraftSimulator.StopSimulator();
	}

	void ShootDown()
	{
		aircraftSimulator.ShootDownSimulator();
	}

	void ProcessMessage()
	{
		while (true)
		{
			State state = network.Receive();
			switch (state)
			{
			case State::START:
			{
				Start();
				break;
			}
			case State::STOP:
			{
				Stop();
				break;
			}
			case State::SHOOTDOWN:
			{
				ShootDown();
				break;
			}
			default:
			{}
			}
		}
	}

private:
	AircraftSimulator aircraftSimulator;
	Network network;
};

int main()
{
	SimulatorController simulatorController;
	simulatorController.ProcessMessage();

	return 0;
}