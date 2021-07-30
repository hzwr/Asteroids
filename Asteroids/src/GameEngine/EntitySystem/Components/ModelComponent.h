#pragma once
#include "../Component.h"

class ModelComponent :
    public Component
{
public:
    ModelComponent(class Actor *owner);
    ~ModelComponent();

    virtual void SetModel(class Model *model) { m_model = model; }
    virtual void Draw(class Shader *shader);


private:
    class Model *m_model;


};

