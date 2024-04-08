#include <iostream>
#include <vector>

using namespace std;

int KnapsackProblemNaive(const vector<int>& Weights, const vector<int>& Prices, int Index, int WeightLimit,
	const int& WeightCap, int Value)
{
	if (WeightCap > WeightLimit)
		return 0;
	if (Index == Weights.size())
		return Value;

	int RightTurn = KnapsackProblemNaive(Weights, Prices, Index + 1, WeightLimit, WeightCap + Weights[Index], Value + Prices[Index]);
	int LeftTurn = KnapsackProblemNaive(Weights, Prices, Index + 1, WeightLimit, WeightCap, Value);

	return max(RightTurn, LeftTurn);

}


int KnapsackProblemDynamic(const vector<int>& Weights, const vector<int>& prices, int Weightlimit)
{
	//Based on Wiki code

	int num_items = prices.size();

	vector<int> row(Weightlimit + 1, 0);
	vector<vector<int>> M(num_items + 1, row);


	for (int i = 1; i <= num_items; ++i) {
		for (int j = 1; j <= Weightlimit; ++j) {

			if (Weights[i - 1] > j) 
				M[i][j] = M[i - 1][j];
			
			else 
				M[i][j] = max(M[i - 1][j], prices[i - 1] + M[i - 1][j - Weights[i - 1]]);
		
		}
	}
	return M[num_items][Weightlimit];

}


int main()
{
	vector<int> weights = { 2, 3, 4, 5 };
	vector<int> prices = { 3, 4, 5, 6 };
	int weightlimit = 11;
	
	int solution = KnapsackProblemNaive(weights, prices, 0, weightlimit, 0, 0);
	cout << "The  naive solution to Knapsack Problem is: " << solution << endl;

	solution = KnapsackProblemDynamic(weights, prices, weightlimit);
	cout << "The dynamic solution to Knapsack Problem is: " << solution << endl;

	return 0;
}