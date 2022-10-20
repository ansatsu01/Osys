#ifndef CHANNEL_BUFFERED_CHANNEL_H
#define CHANNEL_BUFFERED_CHANNEL_H
#include <queue>
#include <thread>
#include <condition_variable>

template <class T>
class BufferedChannel{
    std::queue<T> queue;
    int buffer_size;
    bool is_opened;
    std::mutex lock;
    std::condition_variable c_v;
public:
    BufferedChannel();
    BufferedChannel(int size);
    std::pair<T, bool> receive();
    void send(T value);
    void close();
    int getSize();
};

template <class T>
BufferedChannel<T>::BufferedChannel() {
    buffer_size = 20;
    is_opened = true;
}

template <class T>
BufferedChannel<T>::BufferedChannel(int size) {
    buffer_size = size;
    is_opened = true;
}

template <class T>
void BufferedChannel<T>::send(T value) {
    std::unique_lock<std::mutex> u_lock(lock);
    if(!is_opened){
        throw std::runtime_error("channel has been already closed");
    }
    c_v.wait(u_lock, [this]{return queue.size() < buffer_size;});
    queue.push(value);
    c_v.notify_one();
}

template <class T>
std::pair<T, bool> BufferedChannel<T>::receive() {
    std::unique_lock<std::mutex> u_lock(lock);

    if(!is_opened && queue.empty()){
        return std::pair<T, bool>(T(), false);
    }
    c_v.wait(u_lock,[this]{return !(queue.empty());});
    T value = queue.front();
    queue.pop();
    c_v.notify_one();

    return std::pair<T, bool>(value, is_opened);
}

template <class T>
void BufferedChannel<T>::close() {
    std::unique_lock<std::mutex> u_lock(lock);
    is_opened = false;
    c_v.notify_one();
}

template <class T>
int BufferedChannel<T>::getSize() {return this->buffer_size;}
#endif //CHANNEL_BUFFERED_CHANNEL_H
