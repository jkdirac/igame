#ifndef _GEN_MODEL_THREAD_H_
#define _GEN_MODEL_THREAD_H_

#include <QThread>

class GenModelThread : public QThread
{
	Q_OBJECT
	public:
		GenModelThread();
		void stop();
		void run();

	protected:
	private:
	   	volatile bool m_stop;

};

#endif
