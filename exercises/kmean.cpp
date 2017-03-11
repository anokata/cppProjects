#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int sqr(int x) {
    return x*x;
}

void kmean2() {
    int a[10] = {1, 2, 3, 8, 9, 12, 14, 15, 16, 17};
    int center = 0;
    int min_center = 0;
    int min_sum = 20000000;
    int sum = 0;
    for (center = 0; center < 10; center++) {
        sum = 0;
        for (int i = 0; i < 10; i++) {
            sum += sqr(a[i] - a[center]);
        }
        if (sum < min_sum) {
           min_center = center;
           min_sum = sum;
        }
    }
    cout << min_center << ' ' << min_sum;
}

void kmean22() {
    int a[10] = {1, 2, 3, 8, 9, 12, 14, 15, 16, 17};
    int edge = 1;

    int min_edge = 0;
    int min_sum = 20000000;
    int sum = 0;
    int center1;
    int center2;
    for (edge = 1; edge < 10; edge++) {
        center1 = edge / 2;
        center2 = (10 - edge) / 2 + edge;

        sum = 0;
        for (int i = 0; i < 10; i++) {
            int center = (i < edge) ? center1 : center2;
            sum += sqr(a[i] - a[center]);
        }
        if (sum < min_sum) {
           min_edge = edge;
           min_sum = sum;
        }
    }
    cout << min_edge << ' ' << min_sum << endl;
    cout << center1 << ' ' << center2;
}

void kmean3(vector<int> a) {
    int size = a.size();
    int edge_count = 2;
    int edges[edge_count] = {1, 2};
    int centers[edge_count + 1];
    int min_edges[edge_count] = {0};

    int min_sum = 20000000;
    int sum = 0;

    int edge_index = 0;
    for (int edge_index = 0; edge_index < edge_count; edge_index++)
    for (edges[edge_index] = 1; edges[edge_index] < size; edges[edge_index]++) {
        //if (edges[edge_index] == edges[edge_index+1]) break;
        int start = 0;
        int end = edges[0];
        centers[0] = (end - start) / 2;
        for (int i = 1; i < edge_count; i++) {
            start = end;
            end = edges[i];
            centers[i] = (end - start) / 2 + edges[i];
            //cout << centers[i] << ' ';
        }
        start = end;
        end = size;
        centers[edge_count] = (end - start) / 2 + edges[edge_count-1];
        //cout << centers[0] << ' '<< centers[edge_count] << ' ' << endl;
        //centers[edge_index] = edges[edge_index] / 2;
        //centers[edge_index + 1] = (size - edges[edge_index]) / 2 + edges[edge_index];
        //cout << centers[0] << ' '<< centers[edge_count] << ' ';
        sum = 0;
        for (int i = 0; i < size; i++) {

            int e = 0;
            for (e = 0; e < edge_count; e++)
                if (i >= edges[e]) {
                    break;
                }
            int cen; 
            if (e > 0) {
                cen = centers[e-1];
            }
            if (i >= edges[edge_index]) {
                cen = centers[edge_count];
            }
            //int center = (i < edges[0]) ? centers[0] : centers[1];
            //cout << e << ' ' << cen << ' ' << center << endl;
            sum += sqr(a[i] - a[cen]);
        }
        if (sum < min_sum) {
           for (int i = 0; i < edge_count; i++) 
               min_edges[i] = edges[i];
           min_sum = sum;
        }
    }

    sort(centers, centers+edge_count);
    sort(min_edges, min_edges+edge_count);
    int start = 0;
    for (int e = 0; e < edge_count; e++) {
        cout << "edge#" << e << "at: " << min_edges[e] << " sum= " << min_sum << " cen= " << centers[e] << endl;
    }
    for (int e = 0; e < edge_count; e++) {
        for (int i = start; i <= min_edges[e]; i++)
            cout <<  ' ' << a[i];
        start = min_edges[e] + 1;
        cout << endl;
    }
    for (int i = start; i < size; i++)
        cout <<  ' ' << a[i];
    cout << endl;

    /*
    start = 0;
    for (int e = 0; e < edge_count; e++) {
        for (int i = start; i < centers[e]; i++)
            cout <<  ' ' << a[i];
        start = centers[e];
        cout << endl;
    }*/
}

int main() {
    kmean3({1,2,3,5,6,9});
    kmean3({1,2,3,5,6,9,20,21,21,22});
    kmean3({3,3,3,4,4,4,5,5,5});
    return 0;
}
