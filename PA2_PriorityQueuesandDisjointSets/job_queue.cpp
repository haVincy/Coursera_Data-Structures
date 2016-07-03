#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Thread{
    int threadIndex;
    long long finish_time = 0;
};
class JobQueue{

private:
    int num_workers_;
    vector<Thread> threads;

    vector<long long> jobs_;

    vector<int> assigned_workers_;
    vector<long long> start_times_;

    void WriteResponse() const{
        for (int i = 0; i < jobs_.size(); ++i){
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }

    void ReadData(){
        long long m;
        cin >> num_workers_ >> m;
        threads.resize(num_workers_);
        jobs_.resize(m);
        for(long long i = 0; i < m; ++i)
            cin >> jobs_[i];
    }

    void AssignJobs(){
        // TODO: replace this code with a faster algorithm.
        /*
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        vector<long long> next_free_time(num_workers_, 0);
        for (int i = 0; i < jobs_.size(); ++i){
            int duration = jobs_[i];
            int next_worker = 0;
            for (int j = 0; j < num_workers_; ++j){
                if (next_free_time[j] < next_free_time[next_worker])
                    next_worker = j;
            }
            assigned_workers_[i] = next_worker;
            start_times_[i] = next_free_time[next_worker];
            next_free_time[next_worker] += duration;
        }*/
        for(int i = 0; i < num_workers_; i++){
            threads[i].threadIndex = i;
            threads[i].finish_time = 0;
        }
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        for (int i = 0; i < jobs_.size(); ++i){
            assigned_workers_[i] = threads[0].threadIndex;
            start_times_[i] = threads[0].finish_time;
            // update finish time of root
            long long new_finish_time = threads[0].finish_time + jobs_[i];
            threads[0].finish_time = new_finish_time;
            // check after updating finish_time of root whether if the heap change or not
            SiftDown(0);
        }
    }

    // use finish_time to determine order
    void SiftDown(int i){
        int minIndex = i;
        int l = LeftChild(i);
        // if both finish_time are the same compare index of threads
        if(l < threads.size()){
            if((threads[l].finish_time < threads[minIndex].finish_time)
               || (threads[l].finish_time == threads[minIndex].finish_time
               && threads[l].threadIndex < threads[minIndex].threadIndex)) {
                minIndex = l;
            }
        }
        int r = RightChild(i);
        if(r < threads.size()){
            if((threads[r].finish_time < threads[minIndex].finish_time)
               || (threads[r].finish_time == threads[minIndex].finish_time
               && threads[r].threadIndex < threads[minIndex].threadIndex)){
                minIndex = r;
            }
        }
        if(i != minIndex){
            swap(threads[i], threads[minIndex]);
            SiftDown(minIndex);
        }
    }
    int LeftChild(int i){
        if(i == 0)
            return i + 1;
        return 2*i + 1;
    }
    int RightChild(int i){
        if(i == 0)
            return i + 2;
        return 2*i + 2;
    }

public:
    void Solve(){
        ReadData();
        AssignJobs();
        WriteResponse();
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    JobQueue job_queue;

    job_queue.Solve();

    return 0;
}
