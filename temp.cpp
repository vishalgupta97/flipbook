#define WITHOUT_NUMPY
#include "matplotlib-cpp/matplotlibcpp.h"
namespace plt = matplotlibcpp;

int main()
{
	int n = 5000;
	std::vector<double> x(n), y(n), z(n), w(n,2);
	for(int i = 0; i < n; i++)
	{
		x[i] = i*i;
		y[i] = sin(2*M_PI*i/360.0);
		z[i] = log(i);		
	}

	plt::figure_size(1200, 780);
	plt::plot(x,y);
	plt::plot(x,w,"r--");
	plt::named_plot("log(x)",x,z);
	plt::xlim(0,1000*1000);
	plt::title("Sample Figure");
	plt::legend();
	plt::save("./basic.png");
}
