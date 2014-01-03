#pragma once	

#include <boost/atomic.hpp>
#include <boost/thread/mutex.hpp>

namespace singularity{

	class Singleton {

	private:
		
		static boost::atomic<Singleton *> instance_;
		static boost::mutex instantiation_mutex;

	public:
		Singleton();
		static Singleton *instance();
		

	};
}
