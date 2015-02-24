#ifndef __SIGSLOT_H__
#define __SIGSLOT_H__

#include <functional>
#include <vector>

namespace sigslot
{
    template <typename... Args>
    class signal
    {
    public:
        typedef std::function<void(Args...)> slot;

        signal() = default;
        signal(const signal &) = delete;
        signal & operator=(const signal &) = delete;
        signal(signal &&) = default;
        signal & operator=(signal &&) = default;

        ~signal() = default;

        void connect(const slot & sl)
        {
            _slots.push_back(sl);
        }

        void connect(slot && sl)
        {
            _slots.push_back(std::forward<slot>(sl));
        }

        void emit(Args... args) const
        {
            for(auto & s : _slots)
            {
                s(args...);
            }
        }

    private:
        std::vector<slot> _slots;
    };

    template <typename... Args>
    void emit(const signal<Args...> & sig, Args... args)
    {
        sig.emit(args...);
    }
}

#endif // __SIGSLOT_H__

