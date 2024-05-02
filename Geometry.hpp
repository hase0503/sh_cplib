double const EPS = 1e-10;
double feq(double x, double y) { return fabs(x - y) < EPS; }

struct Point;
struct Vector;

struct Point {
	double x, y;

	Point(double x = 0, double y = 0) : x(x), y(y) {}

	operator Vector();
	Point(Vector v);

	Point operator + (Point p) { return Point(x + p.x, y + p.y); }
	Point operator - (Point p) { return Point(x - p.x, y - p.y); }
	Point operator * (double a) { return Point(x * a, y * a); }
	Point operator / (double a) { return Point(x / a, y / a); }
};

struct Vector {
	double x, y;

	Vector(double x = 0, double y = 0) : x(x), y(y) {}

	operator Point();
	Vector(Point p);
	Vector(Point p, Point q);

	Vector operator + (Vector a) { return Vector(x + a.x, y + a.y); }
	Vector operator - (Vector a) { return Vector(x - a.x, y - a.y); }
	Vector operator * (double a) { return Vector(x * a, y * a); }
	Vector operator / (double a) { return Vector(x / a, y / a); }

	double len() { return hypot(x, y); }
	double norm() { return x * x + y * y; }

	double dot(Vector a) { return x * a.x + y * a.y; }
	double cross(Vector a) { return x * a.y - y * a.x; }

	bool is_orthogonal_to(Vector a) { return feq(dot(a), 0); }
	bool is_parallel_to(Vector a) { return feq(cross(a), 0); }

	Point project(Point p) {
		return Point(*this) * (dot(Vector(p)) / norm());
	}

	Point reflect(Point p) {
		return p + (project(p) - p) * 2;
	}
};

Point::operator Vector() { return Vector(x, y); }
Point::Point(Vector v) : x(v.x), y(v.y) {}

Vector::operator Point() { return Point(x, y); }
Vector::Vector(Point p) : x(p.x), y(p.y) {}
Vector::Vector(Point p, Point q) : x(q.x - p.x), y(q.y - p.y) {}

struct Segment {
	Point p1, p2;

	Point project(Point p) {
		Vector a = Vector(p2 - p1);
		Point q = p - p1;
		return p1 + a.project(q);
	}

	Point reflect(Point p) {
		return p + (project(p) - p) * 2;
	}
};

