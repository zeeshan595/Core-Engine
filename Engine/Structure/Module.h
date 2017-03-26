#ifndef _MODULE
#define _MODULE

class Entity;
class Camera;
class Module
{
public:
    Entity* entity;

    virtual void Start(){}
    virtual void Stop(){}
    virtual void Update(){}
    virtual void Render(Camera* rendering_camera){}
    
    void SetExecutionOrder(uint32_t order)
    {
        this->execution_order = order;
    }

protected:
    uint32_t        execution_order        = 0;
};

#endif