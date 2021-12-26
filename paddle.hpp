#pragma once

#include <SDL2/SDL.h>
#include <utility>

class Paddle {

    public:
        enum class Type {LEFT, RIGHT};
        enum class Direction {NONE, UP, DOWN};
        Paddle(Type type, int x, int y);
        ~Paddle() = default;

        std::pair<int, int> getWH();
        void handle_input(SDL_Event const& event);
        void update(double delta_time);
        void draw(SDL_Renderer* renderer);

    private:
        double m_y; // Keeps track of original point of where player is
        Type m_type; // Note left or right
        Direction m_direction; // Go up or down
        SDL_Rect m_position; // Current position of block

};
