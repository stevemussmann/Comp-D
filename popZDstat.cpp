#include "popZDstat.h"
#include "Dstat.h"
#include "DstatParent.h"

#include "popZParent.h"

#include <iostream>

#include <boost/math/distributions/normal.hpp>

popZDstat::popZDstat(){

}

void popZDstat::add(DstatParent *d){
    Dstat* nd = dynamic_cast<Dstat*>(d);
    D.push_back(nd->getD());
}

void popZDstat::calcStats(std::string filename){
    dstatZ(filename);
}

void popZDstat::dstatZ(std::string filename){
	double* Darr = this->toArr(D, D.size());
	
	double avgD = this->average(Darr, D.size());
	
	double sdD = this->stdev(Darr, avgD, D.size());
	
	double ZD = this->calcZ(avgD, sdD);
	
	boost::math::normal_distribution<> zdist(0.0, 1.0);
	double ZDpval = 2.0*(1-boost::math::cdf(zdist, abs(ZD)));
	
	std::ofstream popout;
	popout.open(filename, std::ios::out);
	if(popout.is_open())
	{
		popout << "Statistic" << "\t" << "Z-score" << "\t" << "P-val" << std::endl;
		popout << "D" << "\t" << ZD << "\t" << ZDpval << std::endl;
	}
	popout.close();
}
