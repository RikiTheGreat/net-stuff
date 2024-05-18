#include "riklibc.hpp"

int main() {
	RIK::RikServer srv(AF_INET, SOCK_STREAM, {}, 4444, INADDR_ANY, 4);
	srv.lunch();
}