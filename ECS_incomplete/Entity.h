#include <cstdint>

class Entity
{
public:
    using Id = uint32_t;
    explicit Entity(Id id) : id(id) {}
    Id getId() const { return id; }

private:
    Id id;
};
