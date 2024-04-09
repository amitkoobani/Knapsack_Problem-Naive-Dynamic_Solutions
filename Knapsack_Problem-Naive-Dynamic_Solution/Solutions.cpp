#include <iostream>
#include <vector>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <chrono>


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
vector<int> initializeVector(int size, int minValue, int maxValue) {
	vector<int> result(size);
	for (int i = 0; i < size; ++i) {
		result[i] = rand() % (maxValue - minValue + 1) + minValue;
	}
	return result;
}


int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	// Initialize vector with 20 values in the range of 1 to 100
	int size = 20;
	int minValue = 1;
	int maxValue = 20;
	int weightlimit = 300;
	vector<int> prices = initializeVector(size, minValue, maxValue);
	vector<int>  weights = initializeVector(size, minValue, maxValue);


	//// Display the initialized vector
	//cout << "Initialized vector: ";
	//for (int i = 0; i < size; ++i) {
	//	cout << myVector[i] << " ";
	//}
	//cout << endl;

	/*vector<int> weights = { 2, 3, 4, 5 };
	vector<int> prices = { 3, 4, 5, 6 };
	*/

	//Naive solution
	auto start = std::chrono::high_resolution_clock::now();

	int solution = KnapsackProblemNaive(weights, prices, 0, weightlimit, 0, 0);

	auto end = std::chrono::high_resolution_clock::now();
	cout << "The naive solution of Knapsack Problem is: " << solution << endl;

	std::chrono::duration<double> duration = end - start;

	cout << "The  running time is: " << duration.count() << " seconds" << std::endl;

	//Dynamic solution
	start = std::chrono::high_resolution_clock::now();
	
	solution = KnapsackProblemDynamic(weights, prices, weightlimit);
	end = std::chrono::high_resolution_clock::now();
	
	cout << "The dynamic solution of Knapsack Problem is: " << solution << endl;
	duration = end - start;

	cout << "The  running time is: " << duration.count() << " seconds" << std::endl;

	return 0;


}




