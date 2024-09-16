template <long long mod>
struct ModInt {
	long long val;

	constexpr ModInt(const long long x = 0) noexcept : val(x % mod) {}
	constexpr ModInt operator+(const ModInt rhs) const noexcept {
		return ModInt(val) += rhs;
	}
	constexpr ModInt operator-(const ModInt rhs) const noexcept {
		return ModInt(val) -= rhs;
	}
	constexpr ModInt operator*(const ModInt rhs) const noexcept {
		return ModInt(val) *= rhs;
	}
	constexpr ModInt operator/(const ModInt rhs) const noexcept {
		return ModInt(val) /= rhs;
	}

	template <typename T>
	constexpr ModInt pow(T rhs) const noexcept {
		assert(rhs >= 0);
		ModInt ret = ModInt(1ll), x = ModInt(val);
		while (rhs) {
			if (rhs & 1ll) {
				ret *= x;
			}
			rhs >>= 1ll;
			x *= x;
		}
		return ret;
	}
	constexpr ModInt& operator+=(const ModInt rhs) noexcept {
		val += rhs.val;
		if (val >= mod) {
			val -= mod;
		}
		return *this;
	}
	constexpr ModInt& operator-=(const ModInt rhs) noexcept {
		if (val < rhs.val) {
			val += mod;
		}
		val -= rhs.val;
		return *this;
	}
	constexpr ModInt& operator*=(const ModInt rhs) noexcept {
		val = val * rhs.val % mod;
		return *this;
	}
	constexpr ModInt& operator/=(const ModInt rhs) noexcept {
		val *= rhs.inv();
		return *this;
	}
	constexpr ModInt inv() noexcept {
		return this->pow(mod - 2ll);
	}
};
