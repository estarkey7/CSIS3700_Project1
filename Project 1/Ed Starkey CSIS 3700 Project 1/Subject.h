#ifndef SUBJECT_H
#define SUBJECT_H
//Subject class for the Observer pattern.

#include "Observer.h"
#include <Vector>;

namespace starkey
{
	class Subject
	{
	public:
		Subject();
		virtual ~Subject();
		void RegisterObserver(Observer *observer);
		void UnregisterObserver(Observer *observer);
		void UnregisterAll();
		void NotifyObservers(int topLeft, int topRight, int bottomLeft, int bottomRight);

	protected:
		std::vector<Observer*> *observerVect;				
	};
}


#endif
