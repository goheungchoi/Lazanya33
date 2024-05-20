#pragma once

#include <random>

class RandomGenerator {
	std::random_device rd;  // a seed source for the random number engine
  std::mt19937 gen; // mersenne_twister_engine seeded with rd()

	static std::unique_ptr<RandomGenerator> _instance;

public:
	RandomGenerator() : gen(rd()) {}
	RandomGenerator(const RandomGenerator&) = delete;
  RandomGenerator(RandomGenerator&&) noexcept = delete;
  RandomGenerator& operator=(const RandomGenerator&) = delete;
  RandomGenerator& operator=(RandomGenerator&&) noexcept = delete;
	~RandomGenerator() {}

	template<typename T>
	static T Get(T to) { 
		if (!_instance) 
			throw std::runtime_error("Access of uninitialized RandomGenerator detected!");

		return _instance->operator()<T>(to); 
	}

	template<typename T>
	static T Get(T from, T to) { 
		if (!_instance) 
			throw std::runtime_error("Access of uninitialized RandomGenerator detected!");

		return _instance->operator()<T>(from, to); 
	}

private:

	template<typename Integer>
	std::enable_if_t<std::is_integral<Integer>::value, Integer>  
	operator()(Integer to) {
		std::uniform_int_distribution<Integer> uniform_dist(0, to);
		return uniform_dist(gen);
	}

	template<typename Float>
	std::enable_if_t<std::is_floating_point<Float>::value, Float>  
	operator()(Float to) {
		std::uniform_real_distribution<Float> uniform_dist(0.0, to);
		return uniform_dist(gen);
	}

	template<typename Integer>
	std::enable_if_t<std::is_integral<Integer>::value, Integer> 
	operator()(Integer from, Integer to) {
		std::uniform_int_distribution<Integer> uniform_dist(from, to);
		return uniform_dist(gen);
	}

	template<typename Float>
	std::enable_if_t<std::is_floating_point<Float>::value, Float> 
	operator()(Float from, Float to) {
		std::uniform_real_distribution<Float> uniform_dist(from, to);
		return uniform_dist(gen);
	}

public:
	static RandomGenerator& Create() { 
		if (_instance) 
			throw std::runtime_error("Recreation of RandomGenerator detected!");

		_instance.reset(new RandomGenerator());
		return *_instance;
	}
	static void Destory() { 
		if (!_instance) 
			throw std::runtime_error("Destruction of uninitialized RandomGenerator detected!");

		_instance.release(); 
	}
};

inline std::unique_ptr<RandomGenerator> RandomGenerator::_instance(nullptr);
