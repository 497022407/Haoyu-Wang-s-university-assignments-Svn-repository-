// Operating system assignment1
// 2020 Semester2
// Student name: Haoyu Wang
// Student ID； a1785394

#include <iostream>
#include <iomanip> 
#include <fstream>
#include <vector>
using namespace std;

// create class for customer
class Customer
{
public:
	string id;
	int arrival_time, priority, age, total_tickets; //input variables
	int count, runs, time_to_q2, rest, end, is_read, ready, running_time; //controlling and result variables

public:
	Customer(string id, int arrival_time, int priority, int age, int total_tickets)
	{
		this->id = id;
		this->arrival_time = arrival_time;
		this->priority = priority;
		this->age = age;
		this->total_tickets = total_tickets;

		running_time = total_tickets * 5;
		rest = (10 - this->priority) * 10;
		count = running_time;
		runs = 0;
		is_read = 0;
	}

	void print_result()
	{
		cout << id << setw(10) << arrival_time << setw(10) << end << setw(10) << ready << setw(10) << running_time << setw(10) << (end - running_time - ready) << endl;
	}
	void change_rest()
	{
		rest = (10 - this->priority) * 10;
	}
	void print_info()
	{
		cout << id << "\t" << arrival_time << "\t" << priority << "\t" << age << "\t" << total_tickets << endl;
	}
	void print_detail()
	{
		cout << id << "\t" << arrival_time << "\t" << count / 5 << "\t" << priority << "\t" << runs << "\t" << age << endl;
	}
};

vector<Customer> q0; //all customers
vector<Customer> q1;	//queue 1
vector<Customer> q2;	//queue 2
vector<Customer> executed_customer; //execured customer

int current_time;

void print_q(vector<Customer> q)
{
	for (int i = 0; i < (int)q.size(); ++i)
	{
		q[i].print_result();
	}
}
void print_q_input(vector<Customer> q)
{
	for (int i = 0; i < (int)q.size(); ++i)
	{
		q[i].print_info();
	}
	cout << endl;
}
void print_detail(vector<Customer> q)
{
	for (int i = 0; i < (int)q.size(); ++i)
	{
		q[i].print_detail();
	}
}
void print_detail()
{
	cout << "current_time: " << current_time << endl << "Queue1: " << endl;
	print_detail(q1);
	cout<< "Queue2: " << endl;
	print_detail(q2);
	cout << endl;
}

void sort_q2()
{
	if (q2.size() > 1)
	{
		for (int i = 0; i < q2.size() - 1; i++)
		{
			for (int j = i + 1; j > 0; j--)
			{
				if (q2[j].count < q2[j - 1].count)
				{
					swap(q2[j], q2[j - 1]);
				}
				else
					break;
			}
		}
	}
}

void sort_q_priority(vector<Customer> &q)
{
	if (q.size()>1)
	{
		for (int i = 0; i < q.size() - 1; i++)
		{
			for (int j = i + 1; j > 0; j--)
			{
				if (q[j].priority < q[j - 1].priority)
				{
					swap(q[j], q[j - 1]);
				}
				else
					break;
			}
		}
	}
}

void insert_q1()
{
	q1.push_back(q1[0]);	
	q1.erase(q1.begin());
}

int main()
{
	string id_temp;
	int priority_temp, arrival_time, age_temp, tickets_temp;

	ifstream infile;
	infile.open("input.txt");

	//read files if there is something to read
	while (infile >> id_temp >> arrival_time >> priority_temp >> age_temp >> tickets_temp)
	{
		//store customer to vector
		q0.push_back(Customer(id_temp, arrival_time, priority_temp, age_temp, tickets_temp));
	}
	int count = q0.size();
	
	sort_q_priority(q0);
	//print_q_input(q0);

	int pos = 0;
	for (int i = 0; i < q0.size(); i++)
	{
		pos = i;
		if (q0[pos].priority >=4)
		{
			break;
		}
	}
	if (q0.size() - 1 - pos > 0)
	{
		for (int i = pos; i < q0.size() - 1; i++)
		{
			for (int j = i +1 ; j > pos; j--)
			{
				if (q0[j].count < q0[j - 1].count)
				{
					swap(q0[j], q0[j - 1]);
				}
				else
					break;
			}
		}
	}

	//print_q_input(q0);

	//start
	while (count > 0)
	{
		//processes arrive
		for (int i = 0; i < (int)q0.size(); i++)
		{
			if (q0[i].arrival_time == current_time)
			{
				//std::cout << q0[i].id << " arrived at " << current_time << endl;
				if (q0[i].priority <= 3)
				{
					q1.push_back(q0[i]);
					q0.erase(q0.begin() + i);
					i--;
				}
				else
				{
					q2.push_back(q0[i]);
					q0.erase(q0.begin() + i);
					i--;
				}
			}
		}

		if (!q1.empty() && (q1[0].count <= 0 || q1[0].rest <= 0))
		{
			if (q1[0].count <= 0)
			{
				//cout << q1[0].id << " end at " << current_time << endl;
				q1[0].end = current_time;
				executed_customer.push_back(q1[0]);
				q1.erase(q1.begin());
				count--;
				sort_q_priority(q1);
			}
			else if (q1[0].rest <= 0)
			{
				if (q1[0].runs <= 0)
				{
					//cout << q1[0].id << " move to q1 at " << current_time << endl;
					q1[0].runs++;
					q1[0].change_rest();
					insert_q1();
					sort_q_priority(q1);
					q1[0].change_rest();
					//q1.push_back(q1[0]);
					//q1.erase(q1.begin());
				}
				else if (q1[0].runs > 0)
				{
					q1[0].runs = 0;
					q1[0].priority++;
					q1[0].change_rest();
					if (q1[0].priority >= 4)
					{
						//cout << q1[0].id << " demoted to q2 at " << current_time << endl;
						q1[0].time_to_q2 = current_time;
						q2.push_back(q1[0]);
						q1.erase(q1.begin());
						sort_q_priority(q1);
					}
					else
					{
						//cout << q1[0].id << " move to q1 at " << current_time << " with decreased priority " << endl;
						insert_q1();
						sort_q_priority(q1);
						q1[0].change_rest();
						//q1.push_back(q1[0]);
						//q1.erase(q1.begin());
					}
				}
			}
			//print_detail();
		}
		if (q1.empty() && (!q2.empty() && q2[0].count <= 0))
		{
			//cout << q2[0].id << " end at " << current_time << endl;
			q2[0].end = current_time;
			executed_customer.push_back(q2[0]);
			q2.erase(q2.begin());
			count--;
			//print_detail();
		}

		if (!q2.empty())
		{
			for (int i = 0; i < q2.size(); i++)
			{
				if (q2[i].priority <= 3)
				{
					//cout << q2[i].id << " promoted to q1 at " << current_time << endl;
					q1.push_back(q2[i]);
					q2.erase(q2.begin() + i);
					i--;
				}
			}
		}

		sort_q2();

		//record ready current_time
		if (!q1.empty() && q1[0].is_read == 0)
		{
			q1[0].ready = current_time;
		}
		else if (!q2.empty() && q2[0].is_read == 0)
		{
			q2[0].ready = current_time;
		}

		//precess request
		if (!q1.empty() && (q1[0].count > 0 && q1[0].rest > 0))
		{
			q1[0].is_read = 1;
			q1[0].count -= 5;
			q1[0].rest -= 5;
		}
		else if (!q2.empty() && q2[0].count > 0)
		{
			q2[0].is_read = 1;
			q2[0].count -= 5;
			q2[0].age = 0;
		}

		current_time += 5;

		if (!q2.empty())
		{
			for (int i = 0; i < q2.size(); i++)
			{
				q2[i].age += 5;
				if (q2[i].age >= 100)
				{
					q2[i].age = 0;
					q2[i].priority--;
					q2[i].change_rest();
				}
			}
		}

	}

	//print result
	cout << "name   arrival   end   ready   running   waiting" << endl;
	print_q(executed_customer);
	return 0;
}


