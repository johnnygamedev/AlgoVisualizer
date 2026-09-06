#include "raylib.h"
#include <vector>
#include <random>
#include <set>

using namespace std;
class AlgoVisualizer {
public: 
	AlgoVisualizer() {
		InitWindow(WIDTH, HEIGHT, "VISUALIZER");

		//i like having it lower to make it easier to see
		SetTargetFPS(60);

		mt19937_64 gen{};
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
			m_compared.clear();
			sort_step();
			EndDrawing();

			ClearBackground(BLACK);
		}
		
	}
	void draw_array() {
		size_t x_step{ WIDTH / static_cast<size_t>(MAX_AMOUNT) };
		for (size_t i{}; i < MAX_AMOUNT; i++) {
			float height_rect{ m_to_sort[i] * HEIGHT * 0.9f };
			auto colour{ m_done ? PURPLE : m_compared.contains(i) ? BLUE : WHITE };
			DrawRectangle( x_step * i, HEIGHT - height_rect, x_step, height_rect, colour);

		}
	
	}

	void sort_step() {
		static int right{ 0 };

		if (right >= MAX_AMOUNT) {
			m_done = true;
			return;
		}

		size_t min_idx{ static_cast<size_t>(right) };
		for (size_t i{ static_cast<size_t>(right) }; i < MAX_AMOUNT;i++) {
			if (m_to_sort[min_idx] > m_to_sort[i])
				min_idx = i;
		}

		auto temp{ m_to_sort[right] };
		m_to_sort[right] = m_to_sort[min_idx];
		m_to_sort[min_idx] = temp;
		m_compared.emplace(min_idx);
		m_compared.emplace(right);
		right++;
	}

private: 
	
	const int WIDTH{ 1000};
	const int HEIGHT{ 800 };
	const int MAX_AMOUNT{ 500 };
	vector<float> m_to_sort{};

	bool m_done{};
	set<size_t> m_compared{};
};

	int main() {
		AlgoVisualizer instance{};
		instance.main();

		return 0;
	}

