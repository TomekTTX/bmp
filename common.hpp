#pragma once
#include <optional>
#include <functional>
#include "positions.hpp"

constexpr inline static double tau = 6.28318530718;
constexpr inline static double pi = 3.14159265359;

constexpr inline int8_t sgn(int32_t x) { return (x > 0) - (x < 0); }
inline int32_t rnd(double d) { return static_cast<int32_t>(std::round(d)); }


template <typename T>
class GeneratorIterator {
public:
	using iterator_category = std::input_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = value_type *;
	using reference = value_type &;
	using optional = std::optional<value_type>;
private:
	optional state;
	std::function<optional()> operation;
public:
	GeneratorIterator() = default;
	GeneratorIterator(std::function<optional()> op) : operation(std::move(op)) {
		if (operation)
			state = operation();
	}

	T operator*() const { return *state; }
	GeneratorIterator &operator++() {
		state = operation();
		return *this;
	}
	GeneratorIterator operator++(int) {
		auto ret = *this;
		state = operation();
		return ret;
	}
	friend bool operator==(const GeneratorIterator &lhs, const GeneratorIterator &rhs) {
		return (!lhs.state && !rhs.state);
	}
	friend bool operator!=(const GeneratorIterator &lhs, const GeneratorIterator &rhs) {
		return !(lhs == rhs);
	}
};

template <typename T>
class CompositeIterator {
public:
	using iterator_category = typename T::iterator_category;
	using difference_type = typename T::difference_type;
	using value_type = typename T::value_type;
	using pointer = value_type *;
	using reference = value_type &;
	struct IterPair { T begin, end; };
private:
	std::vector<IterPair> iters{};
	value_type state = value_type();
	uint32_t index = 0;
	bool done = true;
public:
	CompositeIterator() = default;
	CompositeIterator(std::vector<IterPair> &&itervec) : iters(itervec) {
		operator++();
	}
	CompositeIterator(std::initializer_list<IterPair> iterlist) {
		for (const auto &pair : iterlist)
			iters.push_back(pair);
		operator++();
	}

	value_type operator*() const { return state; }
	CompositeIterator &operator++() {
		if (index == iters.size()) {
			done = true;
		}
		else {
			state = *iters[index].begin++;
			if (iters[index].begin == iters[index].end)
				++index;
		}
		return *this;
	}
	CompositeIterator operator++(int) {
		auto ret = *this;
		operator++();
		return ret;
	}
	friend bool operator==(const CompositeIterator &lhs, const CompositeIterator &rhs) {
		return (lhs.done && rhs.done);
	}
	friend bool operator!=(const CompositeIterator &lhs, const CompositeIterator &rhs) {
		return !(lhs == rhs);
	}
};