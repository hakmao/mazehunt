#ifndef GAMEOBJ_H
#define GAMEOBJ_H

class GameObject
{
  public:
    virtual Point next_point();
    virtual Point current_point();

  private:
    Point current_p;
};

class Player: public GameObject
{
  ;
}

class Zombie: public GameObject
{
  ;
}

class Food: public GameObject
{
  ;
}

#endif
