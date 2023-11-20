#include "scene.h"
#include <QDebug>

bool Scene::endState = false;

Scene::Scene(QWidget *parent, float _Xvel, float _Yvel, float _initHeight) : QWidget(parent),
    Xvel(_Xvel),
    Yvel(_Yvel),
    initHeight(_initHeight),
    world(b2Vec2(0.0f, 10.0f)),
    timer(this),
    image(":/images/vibrant_cannon_ball.png") // Make a resource file - mac executables are in a hidden folder
{
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 35.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(50.0f, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 24.785f);
    bodyDef.angularDamping = 0.0f;
    bodyDef.linearDamping = 0.0f;
    body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.2f, 0.2f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 1;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    // scale image:
    image = image.scaled(40, 40, Qt::KeepAspectRatio);
    connect(&timer, &QTimer::timeout, this, &Scene::updateWorld);
}

/**
 * @brief paintEvent for the cannon ball
 */
void Scene::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    b2Vec2 position = body->GetPosition();
    painter.drawImage((int)(position.x*20), (int)(position.y*20), image);
    painter.end();
}

/**
 * @brief updateWorld
 */
void Scene::updateWorld() {
    world.Step(1.0/30.0, 6, 2);
    //when projectile hits target:
    if (body->GetPosition().y >= 24.5 && this->count > 20) {
        timer.stop();
        setEndState(true);
        this->count = 0;
    }
    update();
    count++;
}

/**
 * @brief applyImpulse
 * @param x
 * @param y
 */
void Scene::applyImpulse(float x, float y) {
    b2Vec2 impulse(x, -y);
    timer.start(50);
    body->SetLinearVelocity(impulse);
    this->count = 0;
}

/**
 * @brief getEndState
 * @return
 */
bool Scene::getEndState() {
    return endState;
}

/**
 * @brief setEndState
 * @param state
 */
void Scene::setEndState(bool state) {
    endState = state;
}
