#include <iostream>
#include <vector>
#include <math.h>

struct vertex {
       float x, y, z; // location
	 float r, g, b; // color	
   };
typedef std::vector<vertex> ptCloud;


inline double euclidianDiatance(vertex v1 , vertex v2)
{
	return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) + pow(v1.z - v2.z, 2)) ; 

}
class Cloud
{
private :

	ptCloud* points_cloud;
public:

	Cloud() ;
	~Cloud();
	void add(vertex v) ;
	Cloud* transform() ;
	double distanceFrom (Cloud* cloud) ;
	ptCloud* getCloudPoints();

};
Cloud::Cloud()
{
	points_cloud = new ptCloud();

}

 Cloud::~Cloud()
{
	delete points_cloud;

}

void Cloud::add(vertex v) 
{
	points_cloud->push_back(v); 
}

double Cloud::distanceFrom (Cloud* cloud) 
{
	// I suppose here that the distance between two pointCloinds is the distance between the two nearest points
	// the distance could be also the distance betwwen the tow centroids 


	//in this distance I ignored the color component because a significant distance in this case requires the definition of a 
	//threshold that allows to select the nearest point (dist <threshold) in terms of color then find the closer physically among these points
	
	ptCloud *myCloud = this->getCloudPoints();

	ptCloud *distantCloud = cloud->getCloudPoints();

	double minDistance = DBL_MAX;
	double distance = DBL_MAX;
	
	

	for (int i = 0 ; i< myCloud->size(); i++)

	{ // for each element of the cloud we search for the minimum distance
	
		for (int j= 0; j < distantCloud->size(); j++)
		{
		distance = euclidianDiatance((*myCloud)[i] , (*distantCloud)[j]);
	     if( distance < minDistance)
			minDistance = distance;

		}
		 if(minDistance < distance)
			 distance = minDistance;
	}
	return distance;

}

Cloud* Cloud::transform() 
{
Cloud*  transformed_cloud  = new  Cloud ();
ptCloud* originalCloud = this->getCloudPoints();

vertex v;

for (std::vector< vertex >::iterator it = (*originalCloud).begin() ; it != (*originalCloud).end(); ++it)
{
 v.x= (*it).x;
 v.y = (*it).y;
 v.z = 10* (*it).x + 20 *(*it).y + (*it).z;

 v.r = (*it).r;
 v.g = (*it).g;
 v.b = (*it).b;


transformed_cloud->add(v);
}

return transformed_cloud;
}
ptCloud* Cloud::getCloudPoints()
{
	return points_cloud;
}



int main(int argc, char* argv[])


{
	vertex v1, v2, v3 ;

	v1.x = -5;
	v1.y = 1 ;
	v1.z = 0;

	v2.x = 3;
	v2.y = -7 ;
	v2.z = 10.5;

	v3.x = 20;
	v3.y = -6.3 ;
	v3.z = 12;


	Cloud *C1 = new Cloud();
	C1->add(v1);
	C1->add(v2);
	C1->add(v3);

	v1.x = 0;
	v1.y = 0 ;
	v1.z = 0;

	v2.x = 16.8;
	v2.y = 2 ;
	v2.z = 0;

	v3.x = 5;
	v3.y = -1 ;
	v3.z = 1.2;

	Cloud *C2 = new Cloud();
	C2->add(v1);
	C2->add(v2);
	C2->add(v3);

	Cloud *C3 = C2->transform();

	double dist = C3->distanceFrom(C1);

	std::cout<< dist;

	delete C1;
	delete C2;
	delete C3;

	return 0;

}