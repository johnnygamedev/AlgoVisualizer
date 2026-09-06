#include "raylib.h"
#include <vector>
#include <random>
#include <set>

using namespace std;

enum class SortAlgo {
	Selection,
	Bubble,
	Insertion
};
class AlgoVisualizer {
public:
	AlgoVisualizer() {
		InitWindow(WIDTH, HEIGHT, "VISUALIZER");

		//i like having it lower to make it easier to see
		SetTargetFPS(30);

		mt19937_64 gen{};
		uniform_real_distribution<float> range{ 0.0f, 1.0f };

		for (size_t i{}; i < MAX_AMOUNT; i++) {
			m_to_sort.push_back(range(gen));
		}
	}
	void main() {
		while (!WindowShouldClose())
		{
			PollInputEvents();


			BeginDrawing();
			draw_array();
			m_compared.clear();
			/*bubble_step();*/
			selection_step();
			/*insertion_step();*/
			EndDrawing();

			ClearBackground(BLACK);
		}

	}
	void draw_array() {
		size_t x_step{ WIDTH / static_cast<size_t>(MAX_AMOUNT) };
		for (size_t i{}; i < MAX_AMOUNT; i++) {
			float height_rect{ m_to_sort[i] * HEIGHT * 0.9f };
			auto colour{ m_done ? PURPLE : m_compared.contains(i) ? BLUE : WHITE };
			DrawRectangle(x_step * i, HEIGHT - height_rect, x_step, height_rect, colour);

		}

	}

	void selection_step() {
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


	void bubble_step() {
		static int i = 0;
		if (m_pass >= MAX_AMOUNT - 1) { m_done = true; return; };

		m_compared.clear();

		for (int step = 0; step < MAX_AMOUNT; step++) {
			if (m_to_sort[i] > m_to_sort[i + 1]) {
				swap(m_to_sort[i], m_to_sort[i + 1]);
			}

			i++;

			if (i >= MAX_AMOUNT - 1 - m_pass) {
				i = 0;m_pass++;
				if (m_pass >= MAX_AMOUNT - 1) {
					m_done = true;
					break;
				}
			}
		}
		m_compared.emplace(i);
		m_compared.emplace(i + 1);
	}

	void insertion_step() {
		if (m_right >= MAX_AMOUNT) {
			m_done = true;
			return;
		}

		if (m_right == 0) {
			m_right = 1;
		}


		static int i = -1;
		static float key = 0.0f;
		static bool shifting = false;

		m_compared.clear();

		if (!shifting) {
			key = m_to_sort[m_right];
			i = m_right - 1;
			shifting = true;
		}

		if (i >= 0 && m_to_sort[i] > key) {
			m_to_sort[i + 1] = m_to_sort[i];
			m_compared.emplace(i);
			m_compared.emplace(i + 1);
			i--;
		}
		else {
			m_to_sort[i + 1] = key;
			m_compared.emplace(i + 1);
			shifting = false;
			m_right++;
		}
	}






private:

	const int WIDTH{ 1000 };
	const int HEIGHT{ 800 };
	const int MAX_AMOUNT{ 100 };
	vector<float> m_to_sort{};

	bool m_done{};
	int m_pass = 0;
	int m_right = 0;
	int m_current_idx{ 0 };
	set<size_t> m_compared{};

	bool m_selecting{ true };
	SortAlgo m_algo{ SortAlgo::Selection };
	int m_bubble_i{ 0 };
	int m_insert_i{ -1 };
	float m_insert_key{ 0.0f };
	bool m_shifting{ false };

	const int BTN_W{ 180 };
	const int BTN_H{ 45 };
	const int BTN_Y{ 15 };

	Rectangle btn_selection{ 10.0f,(float)BTN_Y, (float)BTN_W,(float)BTN_H };
	Rectangle btn_bubble{ 200.0f,(float)BTN_Y, (float)BTN_W,(float)BTN_H };
	Rectangle btn_insertion{ 390.0f,(float)BTN_Y, (float)BTN_W,(float)BTN_H };
	Rectangle btn_reset{ 580.0f,(float)BTN_Y, (float)BTN_W,(float)BTN_H };

	void generate() {
		m_to_sort.clear();
		m_done = false;	
		m_pass = 0;
		m_right = 0;
		m_bubble_i = 0;
		m_insert_i = 0;
		m_insert_key = 0.0f;
		m_shifting = false;
		m_compared.clear();

		mt19937_64 gen{};
		uniform_real_distribution<float> range{ 0.0f,1.0f };
		for (size_t i{}; i < MAX_AMOUNT; i++) {
			m_to_sort.push_back(range(gen));
		}
	}



	
};

	int main() {
		AlgoVisualizer instance{};
		instance.main();

		return 0;
	}

