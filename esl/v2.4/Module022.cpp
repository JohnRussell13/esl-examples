#include "Module022.hpp"
#include <cstdlib>
#include <ctime>

using namespace sc_core;
using namespace std;

Module022::Module022(sc_core::sc_module_name name)
{
	SC_THREAD(loto);
 	SC_THREAD(p1);
	SC_THREAD(p2);
	SC_THREAD(p3);
	SC_THREAD(judge);
	srand(time(NULL));
}

void Module022::loto()
{
    int val;
    std::deque<int>::iterator i;
	while(true){
		wait(100, SC_MS);
        numbers.clear();
        while(numbers.size() < 7){
            val = rand() %33 + 7;
            i = numbers.begin();
            while(i != numbers.end()){
                if(*i == val)
                    break;
                i++;
            }
            if(i == numbers.end())
                numbers.push_back(val);
        }
		wait(900, SC_MS);
	}
}

void Module022::p1()
{
    int val;
    std::deque<int>::iterator i;
	while(true)
	{
        p1_n.clear();
        p1_b = (rand()%2 == 0);
        if(p1_b){
            while(p1_n.size() < 7){
                val = rand() %33 + 7;
                i = p1_n.begin();
                while(i != p1_n.end()){
                    if(*i == val)
                        break;
                    i++;
                }
                if(i == p1_n.end())
                    p1_n.push_back(val);
            }
        }
		wait(1, SC_SEC);
	}
}

void Module022::p2()
{
    int val;
    std::deque<int>::iterator i;
	while(true)
	{
        p2_n.clear();
        p2_b = (rand()%2 == 0);
        if(p2_b){
            while(p2_n.size() < 7){
                val = rand() %33 + 7;
                i = p2_n.begin();
                while(i != p2_n.end()){
                    if(*i == val)
                        break;
                    i++;
                }
                if(i == p2_n.end())
                    p2_n.push_back(val);
            }
        }
		wait(1, SC_SEC);
	}
}

void Module022::p3()
{
    int val;
    std::deque<int>::iterator i;
	while(true)
	{
        p3_n.clear();
        p3_b = (rand()%2 == 0);
        if(p3_b){
            while(p3_n.size() < 7){
                val = rand() %33 + 7;
                i = p3_n.begin();
                while(i != p3_n.end()){
                    if(*i == val)
                        break;
                    i++;
                }
                if(i == p3_n.end())
                    p3_n.push_back(val);
            }
        }
		wait(1, SC_SEC);
	}
}

void Module022::judge()
{
    int a, b, c;
    int i, j;
	while(true)
	{
		wait(200, SC_MS);
        a = 0;
        b = 0;
        c = 0;
        std::cout << "At " << sc_core::sc_time_stamp() << " :" << std::endl;
        std::cout << "Loto is: ";
        i = 0;
        while(i < 7){
            std::cout << numbers[i++] << " ";
        }
        std::cout << std::endl;
        i = 0;
        while(i < 7){
            j = 0;
            while(j < 7 && p1_b){
                if(p1_n[j++] == numbers[i]){
                    a++;
                    break;
                }
            }
            j = 0;
            while(j < 7 && p2_b){
                if(p2_n[j++] == numbers[i]){
                    b++;
                    break;
                }
            }
            j = 0;
            while(j < 7 && p3_b){
                if(p3_n[j++] == numbers[i]){
                    c++;
                    break;
                }
            }
            i++;
        }
        int maxn;
        if(a > b){
            if(a > c) maxn = a;
            else maxn = c;
        }
        else{
            if(b > c) maxn = b;
            else maxn = c;
        }

        if(maxn == a && p1_b){
            std::cout << "Player 1 has: ";
            i = 0;
            while(i < 7){
                j = 0;
                while(j < 7){
                    if(p1_n[i] == numbers[j]){
                        std::cout << "(" << p1_n[i] << ")" << " ";
                        j = 10;
                        break;
                    }
                    j++;
                }
                if(j != 10)
                    std::cout << p1_n[i] << " ";
                i++;
            }
            std::cout << std::endl;
        }

        if(maxn == b && p2_b){
            std::cout << "Player 2 has: ";
            i = 0;
            while(i < 7){
                j = 0;
                while(j < 7){
                    if(p2_n[i] == numbers[j]){
                        std::cout << "(" << p2_n[i] << ")" << " ";
                        j = 10;
                        break;
                    }
                    j++;
                }
                if(j != 10)
                    std::cout << p2_n[i] << " ";
                i++;
            }
            std::cout << std::endl;
        }

        if(maxn == c && p3_b){
            std::cout << "Player 3 has: ";
            i = 0;
            while(i < 7){
                j = 0;
                while(j < 7){
                    if(p3_n[i] == numbers[j]){
                        std::cout << "(" << p3_n[i] << ")" << " ";
                        j = 10;
                        break;
                    }
                    j++;
                }
                if(j != 10)
                    std::cout << p3_n[i] << " ";
                i++;
            }
            std::cout << std::endl;
        }
		wait(800, SC_MS);
	}
}
