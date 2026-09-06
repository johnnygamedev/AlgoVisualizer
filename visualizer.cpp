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
			draw_array();
			sort_step();
			EndDrawing();

			ClearBackground(BLACK);
		}
		
	}
	void draw_array() {
		size_t x_step{ WIDTH / static_cast<size_t>(MAX_AMOUNT) };
		for (size_t i{}; i < MAX_AMOUNT; i++) {
			float height_rect{ m_to_sort[i] * HEIGHT * 0.9f };
			DrawRectangle( x_step * i, HEIGHT - height_rect, x_step, height_rect, WHITE);

		}
	
	}

	void sort_step() {
		static int right{ 0 };

		size_t min_idx{ static_cast<size_t>(right) };
		for (size_t i{ static_cast<size_t>(right) }; i < MAX_AMOUNT;i++) {
			if (m_to_sort[min_idx] > m_to_sort[i])
				min_idx = i;
		}

		auto temp{ m_to_sort[right] };
		m_to_sort[right] = m_to_sort[min_idx];
		m_to_sort[min_idx] = temp;

		right++;
	}

private: 
	
	const int WIDTH{ 1000};
	const int HEIGHT{ 800 };
	const int MAX_AMOUNT{ 100 };
	vector<float> m_to_sort{};
};

	int main() {
		AlgoVisualizer instance{};
		instance.main();

		return 0;
	}

