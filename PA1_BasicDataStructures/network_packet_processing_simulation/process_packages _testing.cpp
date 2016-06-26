#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
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

    Response Process(const Request &request) {
        // write your code here
        Response res(false, 0);
        if(finish_time_.empty()){
            res.start_time = request.arrival_time;
            finish_time_.push(request.arrival_time + request.process_time);
        }
        else{
            // not empty, but need to check when recieve new request whether if the old requests finished.
            while(!finish_time_.empty()){
                if(request.arrival_time >= finish_time_.front())
                    finish_time_.pop();
                else{
                    // buffer is full
                    if(finish_time_.size() == size_){
                        res.start_time = 0;
                        res.dropped = true;
                    }
                    // buffer is not full, current request can be hold in buffer
                    // but its start_time and finish_time depends on the last one in buffer
                    else if(finish_time_.size() < size_){
                        res.start_time = finish_time_.back();
                        finish_time_.push(res.start_time + request.process_time);
                    }
                    break;
                }

            }
            // buffer is empty
            if(finish_time_.empty()){
                res.start_time = request.arrival_time;
                finish_time_.push(request.arrival_time + request.process_time);
            }
        }
        return res;
    }
private:
    int size_;
    queue <int> finish_time_;
};

vector <Request> ReadRequests(ifstream &fin) {
    vector <Request> requests;
    int count;
    fin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        fin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    fin.close();
    return requests;
}

vector <Response> ProcessRequests(const vector <Request> &requests, Buffer *buffer) {
    vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const vector <Response> &responses, ifstream &fa) {
    for (int i = 0; i < responses.size(); ++i){
        int answer;
        fa >> answer;
        if((responses[i].dropped ? -1 : responses[i].start_time) != answer){
            cout << "line " << i << " different to answer" << endl;
        }
    }
    fa.close();
}

int main() {
    int size;
    ifstream fin("tests/22");
    ifstream fanswer("tests/22.a");
    if(!fin || !fanswer){
        cout << "Can't open file" << endl;
        return 0;
    }

    fin >> size;
    // 先一次讀完資料到requests vector array, 不是邊讀邊處理
    vector <Request> requests = ReadRequests(fin);
    Buffer buffer(size);
    // 丟入Process處理得到每個packet的回應時間
    vector <Response> responses = ProcessRequests(requests, &buffer);
    // 再一次印出來
    PrintResponses(responses, fanswer);

    return 0;
}
