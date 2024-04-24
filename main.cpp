#include <iostream>
#include <cmath>

double factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

double ann(int idx, double traffic) {

    return (pow(traffic, idx)) / factorial(idx);
}

double precision2(double value) {

    return round(value * 100.0) / 100.0;
}

double calculate_erlang_p(double traffic, int lines) {
    double _sum = 0.0;
    for (int i = 0; i <= lines; ++i) {
        _sum += ann(i, traffic);
    }


    double Pb = ann(lines, traffic) / _sum;


    return precision2(Pb);
}

double read_traffic() {
    double traffic;
    do {
        std::cout << "Podaj ruch w Erlangach (zakres od 0.1 do 180): ";
        std::cin >> traffic;
        if (traffic < 0.1 || traffic > 180) {
            std::cout << "Wartość ruchu powinna być w zakresie od 0.1 do 180." << std::endl;
        }
    } while (traffic < 0.1 || traffic > 180);
    return traffic;
}

double read_blocking_rate() {
    double blocking_rate;
    do {
        std::cout << "Podaj wskaźnik blokady (zakres od 0.001 do 0.999): ";
        std::cin >> blocking_rate;
        if (blocking_rate < 0.001 || blocking_rate > 0.999) {
            std::cout << "Wartość wskaźnika blokady powinna być w zakresie od 0.001 do 0.999." << std::endl;
        }
    } while (blocking_rate < 0.001 || blocking_rate > 0.999);
    return blocking_rate;
}

int read_lines() {
    int lines;
    do {
        std::cout << "Podaj liczbę linii (zakres od 1 do 180): ";
        std::cin >> lines;
        if (lines < 1 || lines > 180) {
            std::cout << "Liczba linii powinna być w zakresie od 1 do 180." << std::endl;
        }
    } while (lines < 1 || lines > 180);
    return lines;
}

int main() {
    std::cout << "Program do obliczeń wskaźnika blokady, liczby linii i ruchu Erlanga." << std::endl;
    std::cout << "Wskaźnik blokady to prawdopodobieństwo blokady połączenia w systemie telekomunikacyjnym." << std::endl;
    std::cout << "Liczba linii to liczba dostępnych linii w systemie." << std::endl;
    std::cout << "Ruch Erlanga to miara obciążenia systemu telekomunikacyjnego." << std::endl;

    int choice;
    std::cout << "Wybierz co chcesz obliczyc:" << std::endl;
    std::cout << "1. Wskaźnik blokady" << std::endl;
    std::cout << "2. Liczbę linii" << std::endl;
    std::cout << "3. Ruch Erlanga" << std::endl;
    std::cin >> choice;

    switch (choice) {
        case 1: {
            double traffic = read_traffic();
            int lines = read_lines();
            double blocking_rate = calculate_erlang_p(traffic, lines);
            blocking_rate= precision2(blocking_rate);
            std::cout << "Wskaźnik blokady: " << blocking_rate << std::endl;
            break;
        }
        case 2: {
            double traffic = read_traffic();
            double blocking_rate = read_blocking_rate();
            int lines = 0;
            while (calculate_erlang_p(traffic, lines) > blocking_rate) {
                lines++;
            }
            std::cout << "Liczba linii: " << lines << std::endl;
            break;
        }
        case 3: {
            int lines = read_lines();
            double blocking_rate = read_blocking_rate();

            double low = 0.1;
            double high = 180.0;
            double epsilon = 0.0001;

            while (high - low > epsilon) {
                double mid = (low + high) / 2;
                double current_rate = calculate_erlang_p(mid, lines);
                if (current_rate > blocking_rate) {
                    high = mid;
                } else {
                    low = mid;
                }
            }
            double traffic = (low + high) / 2;
            traffic = precision2(traffic);

            std::cout << "Ruch Erlanga: " << traffic <<std::endl;
            break;
        }
        default:
            std::cout << "Nieprawidlowy wybor." << std::endl;
            break;
    }

    return 0;
}



