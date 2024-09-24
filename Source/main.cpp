#include "galba.h"
#include <vector>
using namespace std;

// Name: IBTISAM ADIL

struct Circle;

constexpr int CIRCLE_RADIUS = 16;
int CIRCLE_SPAWNED{};
vector <Circle> circles;

struct Position {
	float x;
	float y;
};

struct Circle {
	Position position;
	Color circle_color;

	Circle(float x = 0, float y = 0, Color color = white)
		: position{ x, y }, circle_color(color) {}

	Color random_color() {
		Color color;
		color.r = static_cast<unsigned char>(random_int_in_range(0, 255));
		color.g = static_cast<unsigned char>(random_int_in_range(0, 255));
		color.b = static_cast<unsigned char>(random_int_in_range(0, 255));
		color.a = static_cast<unsigned char>(random_int_in_range(0, 255));
		return color;
	}

};

bool is_mouse_over_circle(Position position_of_mouse, Circle circle) {
	float distane_x = position_of_mouse.x - circle.position.x;
	float distance_y = position_of_mouse.y - circle.position.y;

	return (distane_x * distane_x + distance_y * distance_y) <= (CIRCLE_RADIUS * CIRCLE_RADIUS);
}

void update() {
	Position position_of_mouse;
	position_of_mouse.x = static_cast<float>(get_mouse_x());
	position_of_mouse.y = static_cast<float>(get_mouse_y());

	for (auto it = circles.begin(); it != circles.end(); ++it) {
		if (is_mouse_over_circle(position_of_mouse, *it) && is_button_pressed(Button::Right)) {
			circles.erase(it);
			CIRCLE_SPAWNED--;
			return;
		}
		if (is_mouse_over_circle(position_of_mouse, *it) && is_button_pressed(Button::Left)) {
			it->circle_color = it->random_color();
		}
	}

	if (is_button_pressed(Button::Right) && CIRCLE_SPAWNED < 12) {
		Circle new_circle(static_cast<float>(get_mouse_x()), static_cast<float>(get_mouse_y()));
		circles.push_back(new_circle);
		CIRCLE_SPAWNED++;
	}
}

void render() {
	for (const Circle& circle : circles) {
		draw_circle(round_to_int(circle.position.x), round_to_int(circle.position.y), CIRCLE_RADIUS, circle.circle_color);
	}
}

int main()
{
	initialize(720, 480, "Window");

	while (is_window_open())
	{
		update();

		clear_window();
		render();
		display();
	}

	return 0;
}
