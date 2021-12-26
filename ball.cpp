#include "ball.hpp"
#include <utility>

Ball::~Ball() {
    SDL_DestroyTexture(m_image);
}

void Ball::init(SDL_Renderer* renderer, int x, int y) {
    IMG_Init(IMG_INIT_PNG);

    SDL_Surface* image = IMG_Load("ball.png");

    m_image = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    IMG_Quit();

    m_position.x = x;
    m_position.y = y;

    m_x = m_position.x;

    SDL_QueryTexture(m_image, nullptr, nullptr, &m_position.w, &m_position.h);

    std::random_device dev;
    std::mt19937 rand_gen(dev());
    std::uniform_int_distribution<> dist_x(0, 1);
    std::uniform_int_distribution<> dist_y(1, 3);

    m_velocity_y = dist_y(rand_gen);
    if (dist_x(rand_gen) == 0) {
        m_velocity_x = -3; 
        m_velocity_y = -m_velocity_y;
    }
    else {
        m_velocity_x = 3;
        m_velocity_y = -m_velocity_y;
    }
}

void Ball::random_velocity(bool leftHit, bool rightHit) {
    std::random_device dev;
    std::mt19937 rand_gen(dev());
    std::uniform_int_distribution<> dist_x(1, 4);
    std::uniform_int_distribution<> dist_y(1, 3);
    m_velocity_y = dist_y(rand_gen);
    if (leftHit == true && rightHit == false) {
        m_velocity_x = -m_velocity_x;
        m_velocity_y = -m_velocity_y;
    }
    else if (leftHit == false && rightHit == true) {
        m_velocity_x = -m_velocity_x;
        m_velocity_y = -m_velocity_y;
    }
}

void Ball::update(double delta_time, SDL_Renderer *renderer, int rh, std::pair<int, int> r1pos, std::pair<int,int> r2pos) {
    int wx, wy;
    SDL_RenderGetLogicalSize(renderer, &wx, &wy);
    if (m_position.x > wx-30 || m_position.x < 0) { // For x-axis
        m_velocity_x = -m_velocity_x;
    }

    if (m_position.y > wy-30 || m_position.y < 0) {
        m_velocity_y = -m_velocity_y;
    }

    const int padding = 15;

    bool ph1 = m_position.x <= r1pos.first + padding && ((m_position.y >= r1pos.second - rh) && (m_position.y <= r1pos.second + rh)); 
    bool ph2 = m_position.x >= r2pos.first - padding && ((m_position.y >= r2pos.second - rh) && (m_position.y <= r2pos.second + rh));

    bool hit = ph1 | ph2;

    random_velocity(ph1, ph2);

    /*if (ph1 == true && ((m_position.y >= r1pos.second - rh) && (m_position.y <= r1pos.second + rh) )) { // First paddle
        m_velocity_x = -m_velocity_x;
        m_velocity_y = -m_velocity_y;
    }

    else if (ph2 == true && ((m_position.y >= r2pos.second - rh) && (m_position.y <= r2pos.second + rh) )) { // Second paddle
        m_velocity_x = -m_velocity_x;
        m_velocity_y = -m_velocity_y;
    }*/

    m_x = m_x + (m_velocity_x * delta_time);
    m_y = m_y + (m_velocity_y * delta_time);
    m_position.x = m_x;
    m_position.y = m_y;
}

/*void Ball::update(double delta_time, SDL_Renderer *renderer) {
    int wx, wy;
    SDL_RenderGetLogicalSize(renderer, &wx, &wy);
    if (m_position.x > wx || m_position.x < 0) { // For x-axis
        m_velocity_x = -m_velocity_x;
    }

    if (m_position.y > wy || m_position.y < 0) {
        m_velocity_y = -m_velocity_y;
    }

    m_x = m_x + (m_velocity_x * delta_time);
    m_y = m_y + (m_velocity_y * delta_time);
    m_position.x = m_x;
    m_position.y = m_y;
}*/

void Ball::draw(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, m_image, nullptr, &m_position);
}

