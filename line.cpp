#include "line.h"

Line::Line() {}


Line::Line(Point p1, Point p2):
    _p1 {p1},
    _p2 {p2} {
    // calculate _a and _b values at initialization
    if(p1.x() == p2.x()) {
        _a = INFTY;
    }
    else {
        _a = (p2.y() - p1.y())/(p2.x() - p1.x());
    }

    _b = p1.y() - _a*p1.x();
}


Line::Line(const Line& other):
    _p1 {other._p1},
    _p2 {other._p2},
    _a {other._a},
    _b {other._b} {

}


Line Line::randomlyGenerated() {
    Point p = Point::randomlyGeneratedOnYvalue(0.);
    Point q = Point::randomlyGeneratedOnYvalue(1.);
    return Line(p, q);
}

Line::~Line() {}

double Line::a() const {
    return _a;
}

double Line::b() const {
    return _b;
}

Point Line::p1() const {
    return _p1;
}

Point Line::p2() const {
    return _p2;
}

double Line::squaredLength() {
    return squaredDistance(_p1, _p2);
}

std::set<Point> Line::generateRandomInliers(unsigned int n) {
    std::set<Point> inliers;

    for(int i = 0; i < n; i++) {
        Point pp = randomPoint();
        pp.addNoise();
        inliers.emplace(pp);
    }
    return inliers;
}


std::ostream &operator<<(std::ostream &out, Line &line) {
    out << line.a() << "x + " << line.b();
    return out;
}

bool Line::operator<(const Line &other) const {
    return _a < other._a && _b != other._b; // actually this is a random definition, just to be able to make sets
}

bool Line::operator==(const Line &other) const {
    return _a == other._a && _b == other._b;
}

void Line::display() {
    Point tmp1 = _p1.scale(WINDOW_WIDTH, WINDOW_HEIGHT);
    Point tmp2 = _p2.scale(WINDOW_WIDTH, WINDOW_HEIGHT);
    Imagine::drawLine(tmp1.x(), tmp1.y(), tmp2.x(), tmp2.y(), LINE_COLOR);
}

void Line::display(Imagine::Color color) {
    Point tmp1 = _p1.scale(WINDOW_WIDTH, WINDOW_HEIGHT);
    Point tmp2 = _p2.scale(WINDOW_WIDTH, WINDOW_HEIGHT);
    Imagine::drawLine(tmp1.x(), tmp1.y(), tmp2.x(), tmp2.y(), color);
}

int Line::mmss() {
    return 2;
}

std::set<Point> Line::computeConsensusSet(const std::set<Point> &dataSet) {
    std::set<Point> cs;
    for(Point point : dataSet) {
        if(distance(*this, point) <= EPSILON) {
            //point.accept();
            cs.emplace(point);
        }
    }
    return cs;
}

std::vector<bool> Line::computeBooleanConsensusSet(const std::set<Point> &dataSet) {
    std::vector<bool> cs;
    for(Point point : dataSet) {

        if(distance(*this, point) <= EPSILON) {

            cs.emplace_back(true);
        }
        else {
            cs.emplace_back(false);
        }
    }
    return cs;
}


////////////////////////////////////////////////////////////////////////////////////////

Point Line::randomPoint() {
    if(_a == INFTY) {
        return Point::randomlyGeneratedOnXvalue(_p1.x());
    }

    double x = Point::randomCoordinate();
//    double min = -_b/_a;

    // to guaranty that the selectionned point is in [0, 1]²
    // code better later
    while(_a*x + _b < 0 || _a*x + _b > 1) {
        x = Point::randomCoordinate();
    }
    return Point(x, _a*x + _b);
}

////////////////////////////////////////////////////////////////////////////////////////


double distance(Line line, Point point) {
    auto x = point.x();
    auto y = point.y();

    auto a = line.a();
    auto b = line.b();

    double num = std::abs(a*x -y + b);
    double den = std::sqrt(a*a + 1);
    return num/den;
}

std::vector<bool> computePreferenceSetFor(const Point &point, const std::set<Line> &modelSet) {
    std::vector<bool> ps;
    // TODO
    return ps;
}
