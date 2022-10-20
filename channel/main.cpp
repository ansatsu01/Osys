#include <iostream>
#include "buffered_channel.h"

int main() {
    BufferedChannel<int> channel(10);
    for (int i = 0; i < channel.getSize(); ++i)
        channel.send(i);
    std::thread thread([&channel](){
        std::this_thread::sleep_for(std::chrono::seconds(2));
        channel.send(100);
        std::cout << "Value is sent" << std::endl;
        channel.close();
    });
    for (int i = 0; i < 15; ++i) {
        std::pair<int, bool> value = channel.receive();
        std::cout << value.first << " " << value.second << std::endl;
    }
    thread.join();

    return 0;
}
