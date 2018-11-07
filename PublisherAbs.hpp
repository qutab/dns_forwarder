#pragma once

#include <vector>
#include <functional>

namespace utils {

/** Publisher interface for notifying observers */
class PublisherAbs
{
public:
    virtual ~PublisherAbs() = default;

    using CallBack = std::function<void(std::vector<uint8_t>)>;

    void subscribe(CallBack funcP)
    {
        callbacksM.push_back(funcP);
    }

protected:
    virtual void notify() = 0;
    std::vector<CallBack> callbacksM;
};

} /* namespace utils */
