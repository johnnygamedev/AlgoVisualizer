#include "raylib.h"
#include <vector>
#include <random>

using namespace std;
class AlgoVisualizer {
public: 
	AlgoVisualizer() {
		InitWindow(WIDTH, HEIGHT, "VISUALIZER");
		SetTargetFPS(60);

		mt19937 gen{};
		uniform_real_distribution<float> range{ 0.0f, 1.0f };
	
		for (size_t i{}; i < MAX_AMOUNT; i++) {
			m_to_sort.push_back(range(gen));
		}
	}
	void main() {
		while(!WindowShouldClose())
		{
			PollInputEvents();


			BeginDrawing();
			EndDrawing();

			ClearBackground(BLACK);
		}
		
	}

private: 
	
	const int WIDTH{ 1600};
	const int HEIGHT{ 800 };
	const int MAX_AMOUNT{ 100 };
	vector<float> m_to_sort{};
};

	int main() {
		AlgoVisualizer instance{};
		instance.main();

		return 0;
	}

