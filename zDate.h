#pragma once
class zDate {
private:
	int4 timestamp;

public:
	zDate() { timestamp = -1; }
	void setCurrentDate() {
		timestamp = time(0);
	}
	boolean isValid() const {
		return timestamp != -1;
	}

	char* asString(char* buf, size_t buf_size, const char* format = "%c")
		const {
		strftime(buf, buf_size, format, localtime((time_t*)&timestamp));
		return buf;
	}
	char* asString(const char* format = "%c") const {
		static char buf[64];
		return asString(buf, sizeof buf, format);
	}

	int compare(zDate const& date) const {
		return timestamp - date.timestamp;
	}
	int operator >= (zDate const& date) const {
		return compare(date) >= 0;
	}
	int operator <= (zDate const& date) const {
		return compare(date) <= 0;
	}
	int operator > (zDate const& date) const {
		return compare(date) > 0;
	}
	int operator < (zDate const& date) const {
		return compare(date) < 0;
	}
	int operator == (zDate const& date) const {
		return compare(date) == 0;
	}
	int operator != (zDate const& date) const {
		return compare(date) == 0;
	}

	friend field_descriptor& describe_field(zDate& z);

	field_descriptor& describe_components() { return FIELD(timestamp); }
};

inline field_descriptor& describe_field(zDate& z) {
	return z.describe_components();
}
