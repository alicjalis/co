#ifndef CO_UTILITY_HPP
#define CO_UTILITY_HPP

#pragma ide diagnostic ignored "cert-err58-cpp"
#pragma ide diagnostic ignored "cert-msc51-cpp"

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

namespace ig {

    struct random {

        random() = delete;

        inline static std::default_random_engine engine{static_cast<unsigned int>(time(nullptr))};
    };

    int random_int(int min, int max) {
        return std::uniform_int_distribution<int>{min, max}(random::engine);
    }

    float random_float(float min, float max) {
        return std::uniform_real_distribution<float>{min, max}(random::engine);
    }

    bool random_bool(float chance_for_true) {
        return random_float(0, 1) <= chance_for_true;
    }

    std::vector<std::pair<int, int>> load_edges(const std::string& file_name) {
        std::vector<std::pair<int, int>> edges;
        std::ifstream input(file_name);
        int size;
        input >> size;
        // the size variable is ignored, at least for now
        int left, right;
        if (input.good())
            while (not input.eof()) {
                input >> left >> right;
                edges.emplace_back(left, right);
            }
        input.close();
        return edges;
    }

    // Zegarek :D
    template<typename Dur> requires std::chrono::__is_duration<Dur>::value
    class timer {

        std::chrono::time_point<std::chrono::high_resolution_clock, Dur> start_point, end_point;
        bool running = false;

    public:

        timer() {
            start_point = std::chrono::high_resolution_clock::now();
            end_point = std::chrono::high_resolution_clock::now();
            running = false;
        }

        std::chrono::time_point<std::chrono::high_resolution_clock, Dur> now() const {
            return std::chrono::high_resolution_clock::now();
        }

        void start() {
            if (!running) {
                running = true;
                start_point = now();
            } else throw std::runtime_error("Illegal timer state: timer is already running");
        }

        void stop() {
            if (running) {
                end_point = now();
                running = false;
            } else throw std::runtime_error("Illegal timer state: timer is not running");
        }

        int get_measured_time() {
            Dur time = std::chrono::duration_cast<Dur>(end_point - start_point);
            return time.count();
        }

        std::string unit() {
            constexpr intmax_t denominator = Dur::period::den;
            if (denominator == 1) return "s";
            else if (denominator == 1000) return "ms";
            else if (denominator == 1000000) return "us";
            else if (denominator == 1000000000) return "ns";
            return "?";
        }
    };

    typedef std::chrono::duration<double, std::nano> precision_ns;
    typedef std::chrono::duration<double, std::micro> precision_us;
    typedef std::chrono::duration<double, std::milli> precision_ms;
    typedef std::chrono::duration<double, std::ratio<1, 1>> precision_s;
}

#endif //CO_UTILITY_HPP
