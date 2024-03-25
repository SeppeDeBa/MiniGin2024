#pragma once
template<typename... Args>
class IObserver
{
public:
	IObserver() = default;
	virtual ~IObserver() = default;
	virtual void OnNotify(Args... arguments) = 0;
	IObserver(const IObserver& other) = delete;
	IObserver(IObserver&& other) = delete;
	IObserver& operator=(const IObserver& other) = delete;
	IObserver& operator=(IObserver&& other) = delete;
};


