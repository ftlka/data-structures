#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Job {
	long long timeStart;
	long long timeEnd;
	long long workerName;
	long long jobName;
};

class HeapBuilder {
private:
    void SiftDown(long long idx, vector<Job>& data) {
        long long min_idx = idx;
        long long min_val = data[idx].timeEnd;
        long long min_worker = data[idx].workerName;
        if (2 * idx + 1 < data.size() &&
        	(data[2 * idx + 1].timeEnd < min_val ||
        	(data[2 * idx + 1].timeEnd == min_val &&
        	data[2 * idx + 1].workerName < min_worker))) {
            min_idx = 2 * idx + 1;
            min_val = data[min_idx].timeEnd;
            min_worker = data[min_idx].workerName;
        }
        if (2 * (idx + 1) < data.size() &&
        	(data[2 * (idx + 1)].timeEnd < min_val ||
        	(data[2 * (idx + 1)].timeEnd == min_val &&
        	data[2 * (idx + 1)].workerName < min_worker))) {
            min_idx = 2 * (idx + 1);
        }

        if (idx != min_idx) {
            swap(data[idx], data[min_idx]);
            SiftDown(min_idx, data);
        }
    }

    void SiftUp(long long idx, vector<Job>& data) {
    	while (idx > 0 &&
    		(data[(idx-1)/2].timeEnd > data[idx].timeEnd ||
    		(data[(idx-1)/2].timeEnd == data[idx].timeEnd &&
    		data[(idx-1)/2].workerName > data[idx].workerName))) {
    		swap(data[(idx-1)/2], data[idx]);
    		idx--;
    		idx /= 2;
    	}
    }

    void GenerateSwaps(vector<Job>& data) {
        long long nodes_end_idx = data.size() / 2;
        for (long long i = data.size() / 2; i >= 0; i--) {
            SiftDown(i, data);
        }
    }

public:
    void Solve(vector<Job>& data) {
        GenerateSwaps(data);
    }

    void Insert(Job job, vector<Job>& data) {
    	data.push_back(job);
    	SiftUp(data.size() - 1, data);
    }

    Job ExtractMin(vector<Job>& data) {
    	Job result = data[0];
    	data[0] = data[data.size() - 1];
    	data.pop_back();
    	SiftDown(0, data);
    	return result;
    }

    void PrintData(const vector<Job>& data) {
    	for (auto e : data) {
    		cout << "timeEnd: " << e.timeEnd << ", timeStart: " << e.timeStart << ", workerName: " << e.workerName << ", jobName: " << e.jobName << endl;
    	}
    	cout << endl;
    }
};

class JobQueue {
private:
	long long num_workers_;
	vector<long long> jobs_;

	vector<long long> assigned_workers_;
  	vector<long long> start_times_;

  	void WriteResponse() const {
    	for (long long i = 0; i < jobs_.size(); i++) {
      		cout << assigned_workers_[i] << " " << start_times_[i] << endl;
    	}
  	}

  	void ReadData() {
    	long long m;
    	cin >> num_workers_ >> m;
    	jobs_.resize(m);
    	for(long long i = 0; i < m; i++) {
      		cin >> jobs_[i];    		
    	}
  	}

  	void AssignJobs() {
    	assigned_workers_.resize(jobs_.size());
    	start_times_.resize(jobs_.size());
    	long long m = jobs_.size();
    	vector<Job> jobs_heap(min(num_workers_, m));
    	long long worker_number = 0;
    	for (long long i = 0; i < jobs_heap.size(); i++) {
    		jobs_heap[i] = {0, jobs_[i], worker_number, i};
    		if (jobs_[i] != 0) {
    			worker_number++;
    		}
    	}
    	HeapBuilder builder;
    	builder.Solve(jobs_heap);
    	long long jobsDone = 0;
    	while (jobsDone < jobs_.size()) {
    		Job currentJob = builder.ExtractMin(jobs_heap);
    		start_times_[currentJob.jobName] = currentJob.timeStart;
    		assigned_workers_[currentJob.jobName] = currentJob.workerName;
    		if (jobsDone + num_workers_ < jobs_.size()) {
    			builder.Insert({currentJob.timeEnd, currentJob.timeEnd + jobs_[jobsDone + num_workers_], currentJob.workerName,
    				jobsDone + num_workers_}, jobs_heap);
    		}
    		jobsDone++;
    	}
	}

public:
	void Solve() {
    	ReadData();
    	AssignJobs();
    	WriteResponse();
    }
};

int main() {
	ios_base::sync_with_stdio(false);
  	JobQueue job_queue;
  	job_queue.Solve();
  	return 0;
}
