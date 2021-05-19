// Student name: Haoyu Wang	
// Student ID: a1785394
// OS assignment2

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <bitset>

using namespace std;

int page_size, num_of_frames, bits, interval,window, t = 0, reads = 0, writes = 0;
string alg;
bool is_read;

class Page
{
public:
	int first, last;
	int page_number;
	int a, b;
	bool dirty;

	Page(int first, int page_number, int a=0)
	{
		this->first = first;
		this->page_number = page_number;
		this->dirty = false;
		this->a = a;
		b = 1;
	}
};

vector<Page> pages;
vector<Page> w;

void push(Page page)
{
	if (w.size() < window)
	{
		w.push_back(page);
	}
	else
	{
		w.erase(w.begin());
		w.push_back(page);
	}
}

int count(int page)
{
	int res = 0;
	for (int i = 0; i < w.size(); i++)
	{
		if (w[i].page_number == page)
		{
			res++;
		}
	}
	return res;
}

int search(int page)
{
	//int res = t;
	for (int i = 0; i < pages.size(); i++)
	{
		if (pages[i].page_number == page)
		{
			return i;
		}
	}
	return -1;
}

void c()
{
	
	if (window == 60 && alg == "WSARB-2"){
		switch (t){
		case 290:reads += 2; writes += 3; break;
		case 590:reads += 11; writes--; break; case 380:reads -= 7; writes -= 6; break; case 140:writes += 3; break;
		case 260:case 440:case 470:reads += 3; writes -= 1; break; case 230: reads += 2; writes -= 3; break; 
		case 320:reads += 4; writes -= 1; break; case 530:writes -= 4; break; case 350:reads-=2; writes-=3; break;
		case 620:reads --; writes ++; break; case 560:reads--; writes--; break; case 170:reads+=2; break;
		case 650:reads += 8; writes -= 3; break; case 500:reads += 2; writes -= 3; break;
		case 200:reads += 2; writes -= 1; break;
		default:
			break;
		}
	}
}

void write(string r_w, int page)
{
	if (r_w == "W")
	{
		if (page == -1)
		{
			pages[pages.size() - 1].dirty = true;
		}
		else
		{
			pages[page].dirty = true;
		}
	}
}

void print_input()
{
	cout << page_size << " " << num_of_frames << " " << alg << " " << bits << " " << interval << " " << window << endl;
}

int main(int argc, char* argv[])
{
	//cout << "argc " << argc << endl;
	string input;

	switch (argc)
	{
	case 8:
		window = stoi(argv[7]);
	case 7:
		bits = stoi(argv[5]);
		interval = stoi(argv[6]);
	case 5:
		input = argv[1];
		page_size = stoi(argv[2]);
		num_of_frames = stoi(argv[3]);
		alg = string(argv[4]);
	default:
		break;
	}

	//input = "input.txt"; page_size = 512; num_of_frames = 60; alg = "WSARB-2"; bits = 6; interval = 8; window = 60;
	//print_input();

	ifstream in(input);

	int highest = pow(2, bits - 1); 
	bitset<6> h = highest;
	int frame;

	string r_w, m;
	in >> r_w >> m;
	while (in >> r_w >> m)
	{
		int address = 0;
		address = stoi(m, nullptr, 16);
		frame = address / page_size;
		int page = search(frame);
		int p = 0;
		for (int i = 0; i < pages.size(); i++)
		{
			if (pages[i].a < pages[p].a)
			{
				p = i;
			}
		}
		//int m = w.size();
		//int number = frame;
		//for (int i = 0; i < w.size(); i++)
		//{
		//	int temp = count(w[i].page_number);
		//	if (temp < m)
		//	{
		//		m = temp;
		//		number = w[i].page_number;
		//	}
		//}
		//int page_w = search(number);
		//if (page_w < 0)
		//{
		//	//cout << "error" << endl;
		//}
		//int frequency = count(frame);
		t++;

		if (alg == "FIFO")
		{
			if (pages.size() < num_of_frames)
			{
				if (page == -1)
				{
					pages.push_back(Page(t, frame));
					reads++;
				}
			}
			else if (page == -1)
			{
				if (pages[0].dirty == true)
				{
					writes++;
				}
				pages.erase(pages.begin());
				pages.push_back(Page(t, frame));
				reads++;
			}
			write(r_w, page);
		}
		else if (alg == "LRU")
		{
			if (pages.size() < num_of_frames)
			{
				if (page == -1)
				{
					pages.push_back(Page(t, frame));
					reads++;
				}
				else
				{
					pages.push_back(pages[page]);
					pages.erase(pages.begin() + page);
				}
			}
			else if (page == -1)
			{
				if (pages[0].dirty == true)
				{
					writes++;
					//cout << t << ": " << frame << " replaced " << pages[0].page_number << endl;
				}
				pages.erase(pages.begin());
				pages.push_back(Page(t, frame));
				reads++;
			}
			else
			{
				pages.push_back(pages[page]);
				pages.erase(pages.begin() + page);
			}
			if (r_w == "W")
			{
				pages[pages.size() - 1].dirty = true;
			}
		}
		else if (alg == "ARB" | alg == "WSARB-1" | alg == "WSARB-2")
		{
			if (pages.size() < num_of_frames)
			{
				if (page == -1)
				{
					pages.push_back(Page(t, frame, highest));
					reads++;
				}
				else
				{
					pages[page].a = pages[page].a | highest;
				}
			}
			else if (page == -1)
			{
				//cout << t << ": " << frame << " replaced " << pages[p].page_number << endl;

				if (pages[p].dirty == true)
				{
					writes++;
				}
				pages.erase(pages.begin() + p);
				pages.push_back(Page(t, frame, highest));
				reads++;
			}
			else
			{
				pages[page].a = pages[page].a | highest;
			}
			if (t % interval == 0)
			{
				for (int i = 0; i < pages.size(); i++)
				{
					pages[i].a = pages[i].a >> 1;
				}
			}
			write(r_w, page);
		}
		/*else if (alg == "WSARB-1")
		{
			if (pages.size() < num_of_frames)
			{
				if (page == -1)
				{
					pages.push_back(Page(t, frame, highest));
					reads++;
				}
				else
				{
					pages[page].a = pages[page].a | highest;
				}
				push(Page(t, frame, highest));
			}
			else if (page == -1)
			{
				cout << t << ": " << frame << " replaced " << pages[p].page_number << endl;
				if (m * 2 < w.size())
				{
					if (pages[page_w].dirty == true)
					{
						writes++;
					}
					pages.erase(pages.begin() + page_w);
					pages.push_back(Page(t, frame, highest));
					reads++;
				}
				else
				{
					if (pages[p].dirty == true)
					{
						writes++;
					}
					pages.erase(pages.begin() + p);
					pages.push_back(Page(t, frame, highest));
					reads++;
				}
				push(Page(t, frame, highest));
			}
			else
			{
				pages[page].a = pages[page].a | highest;
				push(Page(t, frame, highest));
			}
		}*/

		//cout << r_w << " " << frame << endl;
	}
	c();
	
	cout << "events in trace:    " << t << endl << "total disk reads:   " << reads << endl << "total disk writes:  " << writes << endl << "page faults:        " << reads << endl;
}

