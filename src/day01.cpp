#include "day01.h"

Day01::Day01()
{
    dayNumber = 1;
}

void Day01::load(File file)
{
    while(file.available())
	{
		list1.push_back(file.parseInt());
		list2.push_back(file.parseInt());
	}
	file.close();

    //This method of reading the file puts a 0 on the end of each list. Remove it
    list1.pop_back();
    list2.pop_back();
}

uint64_t Day01::solve1()
{
    long sum = 0;

    std::sort(list1.begin(), list1.end());
	std::sort(list2.begin(), list2.end());

	for(int i = 0; i < list1.size(); i++)
	{
		sum += std::abs(list1[i] - list2[i]);
	}

    return sum;
}

uint64_t Day01::solve2()
{
    long prev_val = -1;
	long similarity = 0;
	int j = 0;
	int count = 0;
	long sum = 0;

    //Note: This algorithm assumes both lists are sorted, which happens in part 1
	for(int i = 0; i < list1.size(); i++)
	{
		if(list1[i] == prev_val)
			sum += similarity;
		else
		{
			count = 0;
			while(list2[j] < list1[i])
				j++;
			while(list2[j] == list1[i])
			{
				count++;
				j++;
			}
			similarity = list1[i] * count;
			sum += similarity;
			prev_val = list1[i];
		}
	}

    return sum;
}
