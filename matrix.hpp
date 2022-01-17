#pragma once
#include <vector>
#include <iomanip>
#include <ostream>

template <typename T>
class Matrix {
private:
	using size_t = std::size_t;

	size_t rows_ = 0, cols_ = 0;
	std::vector<T> content_;
public:
	using iterator = typename std::vector<T>::iterator;
	using const_iterator = typename std::vector<T>::const_iterator;

	Matrix() = default;
	Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
		content_ = std::vector<T>(rows * cols);
	}
	Matrix(size_t rows, size_t cols, const T &initial) : rows_(rows), cols_(cols) {
		content_ = std::vector<T>(rows * cols, initial);
	}

	inline size_t rows() const { return rows_; }
	inline size_t cols() const { return cols_; }
	inline size_t size() const { return rows_ * cols_; }
	inline const std::vector<T>& content() const { return content_; }

	inline iterator begin() { return std::begin(content_); }
	inline iterator end() { return std::end(content_); }
	inline const_iterator begin() const { return cbegin(); }
	inline const_iterator end() const { return cend(); }
	inline const_iterator cbegin() const { return std::cbegin(content_); }
	inline const_iterator cend() const { return std::cend(content_); }

	inline const T &operator()(size_t row, size_t col) const {
		return content_[row * cols_ + col];
	}

	inline T &operator()(size_t row, size_t col) {
		return content_[row * cols_ + col];
	}

	inline const_iterator operator[](size_t row) const {
		return std::cbegin(content_) + (row * cols_);
	}

	inline iterator operator[](size_t row) {
		return std::begin(content_) + (row * cols_);
	}

	friend std::ostream &operator<<(std::ostream &ost, const Matrix<T> &m) {
		const auto width = ost.width();
		for (size_t i = 0; i < m.rows_; ++i) {
			for (size_t j = 0; j < m.cols_; ++j)
				ost << std::setw(width) << m(i, j) << ' ';
			ost << '\n';
		}
		return ost;
	}
};

/*

using reverse_iterator = typename std::vector<T>::reverse_iterator;
using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;

inline reverse_iterator rbegin() { return std::rbegin(content_); }
inline reverse_iterator rend() { return std::rend(content_); }
inline const_reverse_iterator crbegin() const { return std::crbegin(content_); }
inline const_reverse_iterator crend() const { return std::crend(content_); }
*/