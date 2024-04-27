//INSPIRED BY MIKE SHAH, The Observer Design Pattern on his youtube and cppcon 2022, adapted to prog 4, modified with personal notes from last year
#pragma once
#include <vector>
#include "IObserver.h"
template<typename... Args>
class Subject final
{
private:
	std::vector<IObserver<Args...>*> m_pObserverVector;
public:

	Subject() = default;
	~Subject()
	{
		//no deletion of the vector because the subject is not the owner
	};

	void AddObserver(IObserver<Args...>* observerToAdd)
	{
		m_pObserverVector.push_back(observerToAdd);
	}

	void RemoveObserver(IObserver<Args...>* observerToRemove)
	{
		/*m_pObserverVector.erase(std::remove(m_pObserverVector.begin(), m_pObserverVector.end(), observerToRemove),
			m_pObserverVector.end());*/
		if(!m_pObserverVector.empty()) m_pObserverVector.erase(std::remove(m_pObserverVector.begin(), m_pObserverVector.end(), observerToRemove), m_pObserverVector.end());

	}

	//void NotifyAll() --> REDUNDANT SINCE IT IS NOW TEMPLATED //leaving for personal interest, was from Mikes video
	//{
	//	for (ObserversMap::iterator it = m_observers.begin(); it != m_observers.end(); ++it)
	//	{
	//		for (auto& observer : m_observers[it->first])
	//		{
	//			observer->OnNotify();
	//		}
	//	}
	//}

	void Notify(Args... message)
	{
		for (auto& observer : m_pObserverVector)
		{
			observer->OnNotify(message...);
		}
	}


};
