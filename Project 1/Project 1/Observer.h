#ifndef OBSERVER_H
#define OBSERVER_H
#include <string>

//Observer class for the Observer pattern.
namespace starkey
{
	class Observer
	{
	public:
		Observer();
		virtual void Update(int x, int y, int height, int width);
		virtual ~Observer();
		friend bool operator ==(const Observer &observer1, const Observer &observer2)
		{
			if (&observer1 == &observer2)
			{
				return true;
			}
			return false;
		}
	private:
		
	};
}



#endif 
