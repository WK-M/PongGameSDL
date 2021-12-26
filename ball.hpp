#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <random>

class Ball {

    public:
        Ball() = default;
        ~Ball();
        void init(SDL_Renderer *renderer, int x, int y);
        void update(double delta_time, SDL_Renderer *renderer, int rh, std::pair<int, int> r1pos, std::pair<int, int> r2pos);
        void draw(SDL_Renderer* renderer);
        void random_velocity(bool leftHit, bool rightHit);

    private:
        //int m_velocity;
        int m_velocity_x, m_velocity_y;
        double m_x, m_y;
        SDL_Texture *m_image;
        SDL_Rect m_position;

};
