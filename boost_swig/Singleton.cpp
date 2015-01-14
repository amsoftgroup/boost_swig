#include "Singleton.h"

using namespace singularity;

boost::atomic<Singleton *> Singleton::instance_(0);
boost::mutex Singleton::instantiation_mutex;

Singleton::Singleton(){}

 Singleton* Singleton::instance()
{
	Singleton * tmp = instance_.load(boost::memory_order_consume);
	if (!tmp) {
		boost::mutex::scoped_lock guard(instantiation_mutex);
		tmp = instance_.load(boost::memory_order_consume);
		if (!tmp) {
			tmp = new Singleton();
			instance_.store(tmp, boost::memory_order_release);
		}
	}
	return tmp;
}



