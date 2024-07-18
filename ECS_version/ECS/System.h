#pragma once

class System {
public:
    virtual ~System() = default;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
};
