#pragma once

#include <optional>
#include <functional>

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
	optional state, prev;
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
	// this isn't ideal but GeneratorIterator is somewhat expensive to copy
	const value_type *operator++(int) {
		prev = state;
		//auto copy = *this;
		state = operation();
		return &*prev;
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
	value_type state = value_type(), prev = value_type();
	uint32_t index = 0;
	bool done = true;
public:
	CompositeIterator() = default;
	CompositeIterator(std::vector<IterPair> &&itervec) : iters(itervec) {
		done = false;
		operator++();
	}
	CompositeIterator(std::initializer_list<IterPair> iterlist) {
		for (const auto &pair : iterlist)
			iters.push_back(pair);
		done = false;
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
	// normally this would return the iterator by value, but complex CompositeIterators
	// might become expensive to copy since GeneratorIterator holds an std::function
	const value_type *operator++(int) {
		prev = state;
		operator++();
		return &prev;
	}
	friend bool operator==(const CompositeIterator &lhs, const CompositeIterator &rhs) {
		return (lhs.done && rhs.done);
	}
	friend bool operator!=(const CompositeIterator &lhs, const CompositeIterator &rhs) {
		return !(lhs == rhs);
	}
};
