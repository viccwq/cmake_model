#ifndef __VXLMUTEX_H__
#define __VXLMUTEX_H__

#include <mutex>

class CVxlLockGuard
{
public:
    explicit CVxlLockGuard(std::mutex &lock) : m_lock(lock)
    {
        m_lock.lock();
    }

    ~CVxlLockGuard()
    {
        m_lock.unlock();
    }

private:
    std::mutex &m_lock;

    CVxlLockGuard(const CVxlLockGuard &);
    CVxlLockGuard &operator=(const CVxlLockGuard &);
};

#endif
