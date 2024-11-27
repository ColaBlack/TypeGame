#include "../libs/httplib.h"

int main() {
    httplib::Client cli("localhost", 8080);
    auto res = cli.Get("/hello");
    if (res) {
        std::cout << res->body << std::endl;
    } else {
        std::cout << "Error: " << res.error() << std::endl;
    }
    return 0;
}