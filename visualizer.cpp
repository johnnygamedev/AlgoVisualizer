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
		generate();

	}
	void main() {
		while (!WindowShouldClose())
		{
			PollInputEvents();


			BeginDrawing();
			ClearBackground(BLACK);
			draw_buttons();
			draw_array();
			m_compared.clear();
			if (!m_selecting) sort_step();
			EndDrawing();
		}

	}

	void sort_step() {
		if (m_done) return;
		switch (m_algo) {
		case SortAlgo::Selection: selection_step(); break;
		case SortAlgo::Bubble: bubble_step(); break;
		case SortAlgo::Insertion: insertion_step(); break;
		}
	}

	bool is_hovered(Rectangle btn) {

		Vector2 mouse = GetMousePosition();

		return CheckCollisionPointRec(mouse, btn);
	}

	bool is_clicked(Rectangle btn) {
		return is_hovered(btn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
	}

	void draw_button(Rectangle btn, const char* label, bool active) {
		Color bg = active ? BLUE : is_hovered(btn) ? DARKGRAY : GRAY;
		DrawRectangleRec(btn, bg);
		DrawRectangleLinesEx(btn, 2, WHITE);

		int text_w = MeasureText(label, 18);
		DrawText(label, static_cast<int>(btn.x + btn.width / 2 - text_w / 2), static_cast<int>(btn.y + btn.height / 2 - 9), 18, WHITE);
	}

	void draw_buttons() {
		draw_button(btn_selection, "Selection", m_algo == SortAlgo::Selection);

		draw_button(btn_bubble, "Bubble", m_algo == SortAlgo::Bubble);
		draw_button(btn_insertion, "Insertion", m_algo == SortAlgo::Insertion);
		draw_button(btn_reset, "Reset", false);

		if (is_clicked(btn_selection)) { TraceLog(LOG_INFO, "Selection clicked!"), m_algo = SortAlgo::Selection; m_selecting = false; generate(); }
		if (is_clicked(btn_bubble)) { m_algo = SortAlgo::Bubble; m_selecting = false; generate(); }
		if (is_clicked(btn_insertion)) { m_algo = SortAlgo::Insertion; m_selecting = false; generate(); }
		if (is_clicked(btn_reset)) { m_selecting = false; generate(); }

		if (m_done) DrawText("SORTED!", WIDTH - 120, BTN_Y + 10, 24, PURPLE);
	}



	void draw_array() {
		size_t x_step{ WIDTH / static_cast<size_t>(MAX_AMOUNT) };
		for (size_t i{}; i < MAX_AMOUNT; i++) {
			float height_rect{ m_to_sort[i] * HEIGHT * 0.9f };
			auto colour{ m_done ? PURPLE : m_compared.contains(i) ? BLUE : WHITE };
			DrawRectangle(static_cast<int>(x_step * i),
				static_cast<int>(HEIGHT - height_rect),
				static_cast<int>(x_step),
				static_cast<int>(height_rect),
				colour);

		}

	}

	void selection_step() {
		

		if (m_right >= MAX_AMOUNT) {
			m_done = true;
			return;
		}

		size_t min_idx{ static_cast<size_t>(m_right) };
		for (size_t i{ static_cast<size_t>(m_right) }; i < MAX_AMOUNT;i++) {
			if (m_to_sort[min_idx] > m_to_sort[i])
				min_idx = i;
		}

		auto temp{ m_to_sort[m_right] };
		m_to_sort[m_right] = m_to_sort[min_idx];
		m_to_sort[min_idx] = temp;
		m_compared.emplace(min_idx);
		m_compared.emplace(m_right);
		m_right++;
	}


	void bubble_step() {
		
		if (m_pass >= MAX_AMOUNT - 1) { m_done = true; return; };

		m_compared.clear();

		for (int step = 0; step < MAX_AMOUNT; step++) {
			if (m_to_sort[m_bubble_i] > m_to_sort[m_bubble_i + 1]) {
				swap(m_to_sort[m_bubble_i], m_to_sort[m_bubble_i + 1]);
			}

			m_bubble_i++;

			if (m_bubble_i >= MAX_AMOUNT - 1 - m_pass) {
				m_bubble_i = 0;m_pass++;
				if (m_pass >= MAX_AMOUNT - 1) {
					m_done = true;
					break;
				}
			}
		}
		m_compared.emplace(m_bubble_i);
		m_compared.emplace(m_bubble_i + 1);
	}

	void insertion_step() {
		if (m_right >= MAX_AMOUNT) {
			m_done = true;
			return;
		}

		if (m_right == 0) {
			m_right = 1;
		}



		m_compared.clear();

		if (!m_shifting) {
			m_insert_key = m_to_sort[m_right];
			m_insert_i = m_right - 1;
			m_shifting = true;
		}

		if (m_insert_i >= 0 && m_to_sort[m_insert_i] > m_insert_key) {
			m_to_sort[m_insert_i + 1] = m_to_sort[m_insert_i];
			m_compared.emplace(m_insert_i);
			m_compared.emplace(m_insert_i + 1);
			m_insert_i--;
		}
		else {
			m_to_sort[m_insert_i + 1] = m_insert_key;
			m_compared.emplace(m_insert_i + 1);
			m_shifting = false;
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

	Rectangle btn_selection{ 10.0f,15.0f, 180.0f,45.0f};
	Rectangle btn_bubble{ 200.0f,15.0f, 180.0f,45.0f };
	Rectangle btn_insertion{ 390.0f,15.0f, 180.0f,45.0f };
	Rectangle btn_reset{ 580.0f,15.0f, 180.0f,45.0f };

	void generate() {
		m_to_sort.clear();
		m_done = false;	
		m_pass = 0;
		m_right = 0;
		m_bubble_i = 0;
		m_insert_i = -1;
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

