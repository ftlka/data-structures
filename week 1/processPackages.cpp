/*
    You are given a series of incoming network packets,
    and your task is to simulate their processing.
    Packets arrive in some order. For each packet number i,
    you know the time when it arrived Ai and the time it
    takes the processor to process it Pi(both in milliseconds).
    There is only one processor, and it processes the incoming
    packets in the order of their arrival. If the processor started
    to process some packet, it doesn’t interrupt or stop until
    it finishes the processing of this packet, and the processing
    of packet i takes exactly Pi milliseconds.
    
    The computer processing the packets has a network buffer
    of fixed size S. When packets arrive, they are stored in
    the buffer before being processed. However, if the buffer
    is full when a packet arrives (there are S packets which have
    arrived before this packet, and the computer hasn’t finished
    processing any of them), it is dropped and won’t be processed
    at all. If several packets arrive at the same time, they are
    first all stored in the buffer (some of them may be dropped
    because of that — those which are described later in the
    input). The computer processes the packets in the order of
    their arrival, and it starts processing the next available
    packet from the buffer as soon as it finishes processing
    the previous one. If at some point the computer is not busy,
    and there are no packets in the buffer, the computer just
    waits for the next packet to arrive. Note that a packet leaves
    the buffer and frees the space in the buffer as soon as
    the computer finishes processing it.
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
        size_(size),
        finish_time_()
    {}

    Response Process(const Request& request) {
        while(finish_time_.size() &&
            request.arrival_time >= finish_time_.front()) {
            finish_time_.pop();
        }

        if (finish_time_.size() == size_) {
            return {true, request.arrival_time};
        }

        if (!finish_time_.size()) {
            finish_time_.push(request.process_time + request.arrival_time);
            return {false, request.arrival_time};
        }

        int current = finish_time_.back();
        finish_time_.push(current + request.process_time);
        return {false, current};
    }
private:
    int size_;
    queue <int> finish_time_;
};

vector <Request> ReadRequests() {
    vector <Request> requests;
    int count;
    cin >> count;
    for (int i = 0; i < count; i++) {
        int arrival_time, process_time;
        cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

vector <Response> ProcessRequests(const vector <Request>& requests, Buffer* buffer) {
    vector <Response> responses;
    for (int i = 0; i < requests.size(); i++)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const vector <Response> &responses) {
    for (int i = 0; i < responses.size(); i++) {
        cout << (responses[i].dropped ? -1 : responses[i].start_time) << endl;
    }
}

int main() {
    int size;
    cin >> size;
    vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
