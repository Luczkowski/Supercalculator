#include <iostream>
#include <cmath>
using namespace std;

# define M_PI 3.14159265358979323846

int tab[1000];

// function for reading and inserting 'n' charaters into a table
void read(int n){
    for(int i = 0; i < n; i++){
        cin >> tab[i];
    }
}
// function for finding pointer to first lowest number in table/structure
int *minimal(int *start, int *end, int step){
    int *pointer_for_min = start;
    while(start < end - step){
        if(*pointer_for_min > *(start + step)) pointer_for_min = start + step;
        start += step;
    }
    return pointer_for_min;
}
// function for finding pointer to first highest number in table/structure
int *maximal(int *start, int *end, int step){
    int *pointer_for_max = start;
    while(start < end - step){
        if(*pointer_for_max < *(start + step)) pointer_for_max = start + step;
        start += step;
    }
    return pointer_for_max;
}
// function for sum values in table
int summary_of_table(int n){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += tab[i];
    }
    return sum;
}
// function for squaring and sum values in table
int summary_of_square(int n){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += tab[i] * tab[i];
    }
    return sum;
}
// function for swapping values
void swap(int *first, int *second){
    *first ^= *second;
    *second ^= *first;
    *first ^= *second;
}

void f0(int n){
    read(n);
    int *pointer_for_min = minimal(tab, tab+n, 1);
    for(int i = 0; i < n; i++){
        if(tab[i] == *pointer_for_min){
            cout << i+1 << " ";
        }
    }
    cout << "\n";
}

void f1(int n){
    read(n);
    for(int i = 0; i < n; i++){
        int *pointer_for_min = minimal(tab+i, tab+n, 1);
        if(tab[i] != *pointer_for_min) swap(tab[i], *pointer_for_min);
    }
    for(int i = n-1; i >= 0; i--){
        cout << tab[i] << " ";
    }
    cout << "\n";
}

void f2(int n){
    read(n);
    cout << floor(sqrt(summary_of_square(n))) << "\n";
}

void f3(int n){
    read(n);
    int sum_of_table = summary_of_table(n);
    for(int i = 0; i < n; i++){
        tab[i] = (tab[i] * n) - sum_of_table;
    }
    int sum_of_square = summary_of_square(n);
    cout << floor(sqrt(sum_of_square / pow(n, 3))) << "\n";
}

void f4(int n){
    read(n);
    for(int i = 0; i < (n/2); i++){
        swap(tab[i], tab[n-1-i]);
    }
    for(int i = 0; i < n; i++){
        cout << tab[i] << " ";
    }
    cout << "\n";
}

void f5(int n){
    read(n);
    int lp = 0;
    for(int i = 0; i < n; i++){
        for(int j = 2; j <= sqrt(tab[i]); j++){
            if (tab[i] % j == 0){
                lp = 0;
                break;
            }
            else lp = 1;
        }
        cout << lp << " ";
    }
    cout << "\n";
}

void f6(int n){
    
    struct coordinates{
        int x;
        int y;
        int angle;
    } points[1000];
    
    // reading data into structure
    for(int i = 0; i < n; i++){
        (i%2) ? cin >> points[i/2].y : cin >> points[i/2].x;
    }
    
    // finding center point
    int *x_max = maximal(&points[0].x, &points[n/2].x, 3);
    int *x_min = minimal(&points[0].x, &points[n/2].x, 3);
    int *y_max = maximal(&points[0].y, &points[n/2].y, 3);
    int *y_min = minimal(&points[0].y, &points[n/2].y, 3);
    
    double x_center = (*x_max + *x_min) / 2.0;
    double y_center = (*y_max + *y_min) / 2.0;
    
    // calculating angle
    for(int i = 0; i < n/2; i++){
        points[i].angle = 10000 * atan2(points[i].y - y_center, points[i].x - x_center);
    }
    
    // sorting by angle
    for(int i = 0; i < n/2; i++){
        int *min = minimal(&points[i].angle, &points[n/2].angle, 3);
        if(points[i].angle != *min){
            swap(points[i].x, *(min-2));
            swap(points[i].y, *(min-1));
            swap(points[i].angle, *min);
        }
    }
    
    // orginal code
    long long sum = 0;
    for(int i = 1; i < (n/2)-1; i++){
        sum += abs((points[i].x - points[0].x)*(points[i+1].y - points[0].y) - (points[i].y - points[0].y)*(points[i+1].x - points[0].x));
    }
    
    cout << (sum/2) << "\n";
}

void f7(int n){
    float tab_2[4];
    for(int i = 0; i < n; i++){
        cin >> tab_2[i];
    }
    float delta = (tab_2[2] * tab_2[2]) - (4 * tab_2[1] * tab_2[3]);
    double x_1 = (-tab_2[2] - sqrt(delta)) / (2.0 * tab_2[1]);
    double x_2 = (-tab_2[2] + sqrt(delta)) / (2.0 * tab_2[1]);
    
    if (x_1 == x_2) cout << floor(x_1) << "\n";
    else if (x_1 > x_2) cout << floor(x_2) << " " << floor(x_1) << "\n";
    else cout << floor(x_1) << " " << floor(x_2) << "\n";
}

void f8(int n){
    read(n);
    for(int i = 0; i < n; i++){
         long long x = tab[i];
        
        // n * (n+1) * (n+1) = n^3 + 2 * n^2 + n
        // sum(n^3 + 2 * n^2 + n) =
        // sum(n^3) + 2 * sum(n^2) + sum(n) =
        // (n*n+n)/2 + 2 * n*(n+1)*(n+2)/6 + (n*n+n)*(n*n+n)/4 =
        // 1/12 * (3*n^4 + 14*n^3 + 21*n^2 + 10*n)
        
        long long sum = (3 * x*x*x*x) + (14 * x*x*x) + (21 * x*x) + (10 * x);
        cout << sum/12 << " ";
    }
    cout << "\n";
}
void f9(int n){
    unsigned long long t[1000];
    for(int i = 0; i < n; i++){
        cin >> t[i];
    }
    for(int i = 0; i < n; i++){
        int count = 0;
        for(int j = 0; j < sizeof(tab[i]) * 8; j ++){
            count += t[i] & 1;
            t[i] >>= 1;
        }
        /*while(t[i]){
            count += t[i] & 1;
            t[i] >>= 1;
        }*/
        cout << count << " ";
    }
    cout << "\n";
}

int main(){
    int fn, n;
    while(cin >> fn >> n){
        switch (fn){
            case 0: f0(n); break;
            case 1: f1(n); break;
            case 2: f2(n); break;
            case 3: f3(n); break;
            case 4: f4(n); break;
            case 5: f5(n); break;
            case 6: f6(n); break;
            case 7: f7(n); break;
            case 8: f8(n); break;
            case 9: f9(n); break;
        }
    }
}