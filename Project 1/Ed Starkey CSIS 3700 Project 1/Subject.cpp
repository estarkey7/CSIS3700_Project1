#include "Subject.h"
#include "Observer.h"
using namespace starkey;
using namespace std;

namespace starkey
{

	Subject::Subject()
	{
		observerVect = new vector<Observer*>();
	}

	void Subject::RegisterObserver(Observer *observer)
	{
		observerVect->push_back(observer);		
	}


	void Subject::UnregisterObserver(Observer *observer)
	{		
		for (int x = 0; x < observerVect->size(); x++)
		{
			if (observerVect->at(x) == observer)
			{
				observerVect->erase(observerVect->begin() + x);
				break;
			}
		}
				
	}

	void Subject::UnregisterAll()
	{
		observerVect->clear();
	}

	void Subject::NotifyObservers(int topLeft, int topRight, int bottomLeft, int bottomRight)
	{
		for (int x = 0; x < observerVect->size(); x++)
		{
			observerVect->at(x)->Update(topLeft, topRight,bottomLeft, bottomRight);
		}
	}


	Subject::~Subject()
	{
		observerVect->clear();
		delete observerVect;
	}

}
