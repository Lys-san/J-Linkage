#include "line.h"

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

Point Line::randomPoint() {
    if(_a == INFTY) {
        return Point::randomlyGeneratedOnXvalue(_p1.x());
    }
    double x = Point::randomCoordinate();
    double min = -_b/_a;

    // to guaranty that the selectionned point is in [0, 1]²
    if(x < min) {
        x += min;
    }
    return Point(x, _a*x + _b);
}


std::ostream &operator<<(std::ostream &out, Line &line) {
    out << line.a() << "x + " << line.b();
    return out;
}

void Line::display() {
    Point tmp1 = _p1.scale(WINDOW_WIDTH, WINDOW_HEIGHT);
    Point tmp2 = _p2.scale(WINDOW_WIDTH, WINDOW_HEIGHT);
    Imagine::drawLine(tmp1.x(), tmp1.y(), tmp2.x(), tmp2.y(), LINE_COLOR);
}

int Line::mmss() {
    return 2;
}

std::set<Point> Line::computeConsensusSet(const std::set<Point> &dataSet) {
    std::set<Point> cs;
    for(Point point : dataSet) {
        if(distance(*this, point) <= EPSILON) {
            point.accept();
            cs.emplace(point);
        }
    }
    return cs;
}

double distance(Line line, Point point) {
    auto x = point.x();
    auto y = point.y();

    auto a = line.a();
    auto b = line.b();

    double num = std::abs(a*x -y + b);
    double den = std::sqrt(a*a + 1);
    return num/den;
}
