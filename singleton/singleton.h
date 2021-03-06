#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <string>
#include <iostream>
#include <memory>
#include <mutex>

template <typename T>
class Singleton {
  public:
    template <typename... Args>
    static inline std::shared_ptr<T> instance(Args &&... args) {
        // using double-check-lock.
        if (!instance_.get()) {
            std::unique_lock<std::mutex> lock(instanceMutex_);
            if (!instance_.get()) {
                instance_.reset(new T(std::forward<Args>(args)...));
            }
        }
        return instance_;
    }

  private:
    Singleton() = default;
    virtual ~Singleton() = default;
    Singleton(const Singleton &) = default;
    Singleton &operator=(const Singleton &) = delete;

    // instance
    static std::shared_ptr<T> instance_;
    static std::mutex instanceMutex_;
};

template <typename T>
std::shared_ptr<T> Singleton<T>::instance_;

template <typename T>
std::mutex Singleton<T>::instanceMutex_;

#define SINGLETON_DECL(type)        \
    \
friend class std::shared_ptr<type>; \
    \
friend class Singleton<type>;

#endif // SINGLETON_H_