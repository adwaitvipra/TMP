#include <ctime>
#include <cstdlib>
#include <iostream>

#define DEF_CNT 24
#define DEF_WIN 4
#define DEF_VAL 2
#define LIMIT 5
#define POS 0
#define NEG 1
#define DEF_FLAG POS

using namespace std;

/*
 * array is pointer to an array of floats
 * count is total number of samples in array
 * window is size of window same for positive and negative cycle
 * valid is total number of valid samples in window considered from end
 * flag is sign of window at start of array
 */

float diffmean (float *array, int count, int window, int valid, int flag)
{
	int invalid, val_cnt, itr = 0;
	float sum, diff, avg, pos = 0.0, neg = 0.0;

	invalid = window - valid;
	while (itr < count)
	{
		if (itr % window)
		{
			sum = 0.0;
			for (int i = 0; i < valid; i++)
				sum += array[itr + i];

			if (!flag)
				pos += sum;
			else
				neg += sum;

			itr += valid;
		}
		else
		{
			/* 
			 * no need to flip flag at start of array
			 * flip flag when new window is encountered
			 */
			if (itr)
				flag = !flag;
			itr += invalid;
		}
	}

	val_cnt = (count / window) * valid;
	diff = (pos - neg);
	avg = (diff / (val_cnt / 2));

	return avg;
}

int main (const int argc, const char *argv [])
{
	int count, window, valid, flag;
	float result, *array = NULL;

	if (argc > 1)
	{
		count = atoi(argv[1]);
		window = atoi(argv[2]);
		valid = atoi(argv[3]);
		flag = atoi(argv[4]) % 2;
	}
	else
	{
		count = DEF_CNT;
		window = DEF_WIN;
		valid = DEF_VAL;
		flag = DEF_FLAG;
	}

	array = (float*) malloc(sizeof(float) *count);

	srand (time(NULL));
	for (int i = 0; i < count; i++)
		array[i] = ((float) rand () / (1 + (float) rand())) + LIMIT;

	for (int j = 0; j < count; j++)
		cout << array[j] << " ";
	result = diffmean (array, count, window, valid, flag);
	cout << "\nresult = " << result << endl;

	free(array);
	return 0;
}
