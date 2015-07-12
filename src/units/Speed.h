#pragma once

namespace sim {

class Speed {

public:
    virtual ~Speed() = 0;
    double getMetersPerSecond() const;

protected:
    Speed();
    double m_metersPerSecond;

};

} // namespace sim
