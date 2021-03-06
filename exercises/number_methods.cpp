#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

//typedef pair<double, double> point;
typedef struct {
    double x;
    double y;
} point;
typedef pair<vector<double>, vector<double>> tab_data;

double sample1(double x) {
    return sin(x);
}

tab_data sampler(double from, double to, double step, double (*func)(double)) {
    vector<double> ys;
    vector<double> xs;
    for (double x = from; (x - to) < 0.001; x += step) {
        ys.push_back(func(x));
        xs.push_back(x);
    }
    return make_pair(xs, ys);
}

double interpolate_line_lr(double x, point left, point right) {
    double c = left.y * (x - right.x) - right.y * (x - left.x);
    return c/(left.x - right.x);
}

double interpolate_line(double x, tab_data *d) {
    auto it = find_if(d->first.begin(), d->first.end(), [x](double s){return s > x;});
    size_t index = distance(d->first.begin(), it);
    point left = point{d->first.at(index), d->second.at(index)};
    point right = point{d->first.at(index+1), d->second.at(index+1)};
    double y = interpolate_line_lr(x, left, right);
    d->first.insert(d->first.begin() + index, x);
    d->second.insert(d->second.begin() + index, y);
}

double interpolate_with(double x, tab_data *d, double (*func)(double, tab_data)) {
    auto it = find_if(d->first.begin(), d->first.end(), [x](double s){return s > x;});
    size_t index = distance(d->first.begin(), it);
    point left = point{d->first.at(index), d->second.at(index)};
    point right = point{d->first.at(index+1), d->second.at(index+1)};
    double y = func(x, *d);
    d->first.insert(d->first.begin() + index, x);
    d->second.insert(d->second.begin() + index, y);
}
double Lj(vector<double> xs, double x, size_t j) {
    double prod = 1;
    for (size_t i = 0; i < xs.size(); ++i) {
        if (i == j) continue;
        prod *= (x - xs[i]);
    }
    return prod;
}

double interpolate_Lagrange(double x, tab_data d) {
    double y = 0;
    for (size_t j = 0; j < d.first.size(); ++j) {
        double c = Lj(d.first, x, j) / Lj(d.first, d.first[j], j);
        y += d.second[j] * c;
    }
    return y;
}

void tabulate_func() {
    auto p = sampler(-2, 2, 0.15, &sample1);
    double ly = interpolate_with(0.123, &p, &interpolate_Lagrange);
    //double y = interpolate_line(0.123, &p);
    auto xs = p.first;
    auto ys = p.second;
    for (int i = 0; i < xs.size(); ++i) {
        cout << setprecision(3) << setw(6) << left;
        cout << xs[i] << " | ";
        cout << setprecision(3) << setw(6) << left;
        cout << ys[i] << endl;
    }
}

int main() {
    tabulate_func();
    return 0;
}
