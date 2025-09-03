#ifndef __SCENE_H__
#define __SCENE_H__

class Scene
{
private:
    /* data */
public:
    Scene(/* args */);
    virtual ~Scene() = default;

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void clean() = 0;
};

#endif