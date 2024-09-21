#include "galba.h"
#include <vector>
using namespace std;

// Name: IBTISAM ADIL


constexpr int CIRCLE_RADIUS = 16;

struct Position {
	float x;
	float y;
};

struct Circle {
	Position position;

	Circle create_circle() {
		Circle new_circle;
		new_circle.position.x = static_cast<float>(get_mouse_x());
		new_circle.position.y = static_cast<float>(get_mouse_y());
		return new_circle;
	}
};

Color random_color() {
	Color color;
	color.r = static_cast<unsigned char>(random_int_in_range(0, 255));
	color.g = static_cast<unsigned char>(random_int_in_range(0, 255));
	color.b = static_cast<unsigned char>(random_int_in_range(0, 255));
	color.a = static_cast<unsigned char>(random_int_in_range(0, 255));
	return color;
}

bool is_mouse_over_circle(Position position_of_mouse, Circle circle) {
	float distane_x = position_of_mouse.x - circle.position.x;
	float distance_y = position_of_mouse.y - circle.position.y;

	return (distane_x * distane_x + distance_y * distance_y) <= (CIRCLE_RADIUS * CIRCLE_RADIUS);
}

vector <Circle> circles;

void update() {
	Position position_of_mouse;
	position_of_mouse.x = static_cast<float>(get_mouse_x());
	position_of_mouse.y = static_cast<float>(get_mouse_y());

	for (auto it = circles.begin(); it != circles.end(); ++it) {
		if (is_mouse_over_circle(position_of_mouse, *it) && is_button_pressed(Button::Right)) {
			circles.erase(it);
			return;
		}
	}

	if (is_button_pressed(Button::Right)) {
		Circle new_circle = Circle().create_circle();
		circles.push_back(new_circle);
	}

}

void render() {
	for (const Circle& circle : circles) {
		draw_circle(round_to_int(circle.position.x), round_to_int(circle.position.y), CIRCLE_RADIUS);
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