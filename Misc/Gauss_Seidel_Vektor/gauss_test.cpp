#include<stdio.h>
#include<math.h>
#include <vector>


std::vector<double> gauss_seidel(std::vector<std::vector<double>> M, std::vector<double> R, int num_iter = 100);

int main()
{
  std::vector<double> R = {3.5, 9.0, 8.3, 1.0};
  int n = R.size();
  
  std::vector<std::vector<double>> M(n,std::vector<double>(n,0.0));

	M[0][0] = 10.0;
	M[0][1] = 4.0;
	M[0][2] = 1.0;
	M[0][3] = 2.0;

	M[1][0] = 3.0;
	M[1][1] = 18.0;
	M[1][2] = 2.0;
	M[1][3] = 1.0;

	M[2][0] = 1.0;
	M[2][1] = 2.0;
	M[2][2] = 16.0;
	M[2][3] = 2.0;

	M[3][0] = 2.0;
	M[3][1] = 2.0;
	M[3][2] = 1.0;
	M[3][3] = 12.0;

  std::vector<double> X = gauss_seidel(M, R);

  std::vector<double> ERR(n,0.0);
	double err_tot = 0.0;

	for (int i = 0; i < n; ++i)
	{
		double lhs = 0.0;
		for (int j = 0; j < n; ++j)
		{
			lhs += M[i][j] * X[j];
		}
		ERR[i] = fabs(R[i] - lhs);
		err_tot += fabs(R[i] - lhs);
	}

	printf("%-6s %15s %16s", "i", "X[i]", "ERR[i]\n");
	for (int i = 0; i < n; ++i)
	{
		printf("%-6d %15.12f %15.12f\n", i, X[i], ERR[i]);
	}

	return 0;
}
