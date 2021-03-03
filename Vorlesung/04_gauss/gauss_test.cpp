#include<stdio.h>
#include<math.h>

void gauss(double *m, double *x, double *r, int n);

int main()
{
	const int n = 4;
	double M[n][n], x[n], R[n];

	M[0][0] = 1.2;
	M[0][1] = 2.0;
	M[0][2] = 7.1;
	M[0][3] = 2.0;

	M[1][0] = 0.2;
	M[1][1] = 2.4;
	M[1][2] = 3.1;
	M[1][3] = 5.0;

	M[2][0] = 3.4;
	M[2][1] = 1.4;
	M[2][2] = 0.0;
	M[2][3] = 1.0;

	M[3][0] = 0.4;
	M[3][1] = 1.8;
	M[3][2] = 1.0;
	M[3][3] = 7.0;

	R[0] = 3.5;
	R[1] = 9.0;
	R[2] = 8.3;
	R[3] = 1.0;

	gauss(*M, x, R, n);

	double err[n];
	double err_tot = 0.0;

	for (int i = 0; i < n; ++i)
	{
		double lhs = 0.0;
		for (int j = 0; j < n; ++j)
		{
			lhs += M[i][j] * x[j];
		}
		err[i] = fabs(R[i] - lhs);
		err_tot += fabs(R[i] - lhs);
	}

	printf("%-6s %15s %16s", "i", "x[i]", "err[i]\n");
	for (int i = 0; i < n; ++i)
	{
		printf("%-6d %15.12f %15.12f\n", i, x[i], err[i]);
	}

	printf("\n\nDruecken Sie Enter zum Schliessen des Fensters.\n");
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
	getchar();

	return 0;
}